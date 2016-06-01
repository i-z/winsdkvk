using namespace System;

#include "GZipExtensions.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Diagnostics;
using namespace System::Diagnostics::CodeAnalysis;
using namespace System::IO;
using namespace System::Net;
using namespace System::Windows;
using namespace System::Windows::Resources;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				namespace Networking
				{

					void GzipExtensions::AddAcceptEncodingHeader(HttpWebRequest ^request)
					{
						if (nullptr == request)
						{
							throw ref new ArgumentNullException("request");
						}
						request->Headers[HttpRequestHeader::AcceptEncoding] = GZIP;
					}

					IAsyncResult ^GzipExtensions::BeginGetCompressedResponse(HttpWebRequest ^request, AsyncCallback ^callback, Platform::Object ^state)
					{
						AddAcceptEncodingHeader(request);
						return request->BeginGetResponse(callback, state);
					}

					Stream ^GzipExtensions::GetCompressedResponseStream(HttpWebResponse ^response)
					{
						// Validate arguments
						if (nullptr == response)
						{
							throw ref new ArgumentNullException("response");
						}

						// Check the response for GZIP
						auto responseStream = response->GetResponseStream();
						if (Platform::String::Equals(response->Headers[HttpRequestHeader::ContentEncoding], GZIP, StringComparison::OrdinalIgnoreCase))
						{
							// Read header
							if ((0x1f != responseStream->ReadByte()) || (0x8b != responseStream->ReadByte()) || (8 != responseStream->ReadByte())) // CM (8 == deflate) -  ID2 -  ID1
							{
								throw ref new NotSupportedException("Compressed data not in the expected format.");
							}

							// Read flags
							auto flg = responseStream->ReadByte(); // FLG
							auto fhcrc = 0 != (0x2 & flg); // CRC16 present before compressed data
							auto fextra = 0 != (0x4 & flg); // extra fields present
							auto fname = 0 != (0x8 & flg); // original file name present
							auto fcomment = 0 != (0x10 & flg); // file comment present

							// Skip unsupported fields
							responseStream->ReadByte();
							responseStream->ReadByte();
							responseStream->ReadByte();
							responseStream->ReadByte(); // MTIME
							responseStream->ReadByte(); // XFL
							responseStream->ReadByte(); // OS
							if (fextra)
							{
								// Skip XLEN bytes of data
								auto xlen = responseStream->ReadByte() | (responseStream->ReadByte() << 8);
								while (0 < xlen)
								{
									responseStream->ReadByte();
									xlen--;
								}
							}
							if (fname)
							{
								// Skip 0-terminated file name
								while (0 != responseStream->ReadByte())
								{
								}
							}
							if (fcomment)
							{
								// Skip 0-terminated file comment
								while (0 != responseStream->ReadByte())
								{
								}
							}
							if (fhcrc)
							{
								responseStream->ReadByte();
								responseStream->ReadByte(); // CRC16
							}

							// Read compressed data
							const int32 zipHeaderSize = 30 + 1; // 30 bytes + 1 character for file name
							const int32 zipFooterSize = 68 + 1; // 68 bytes + 1 character for file name

							// Download unknown amount of compressed data efficiently (note: Content-Length header is not always reliable)
							auto buffers = ref new List<Platform::Array<uint8>^>();
							auto buffer = ref new Platform::Array<uint8>(4096);
							auto bytesInBuffer = 0;
							auto totalBytes = 0;
							auto bytesRead = 0;
							do
							{
								if (buffer->Length == bytesInBuffer)
								{
									// Full, allocate another
									buffers->Add(buffer);
									buffer = ref new Platform::Array<uint8>(buffer->Length);
									bytesInBuffer = 0;
								}
								Debug::Assert(bytesInBuffer < buffer->Length);
								bytesRead = responseStream->Read(buffer, bytesInBuffer, buffer->Length - bytesInBuffer);
								bytesInBuffer += bytesRead;
								totalBytes += bytesRead;
							} while (0 < bytesRead);
							buffers->Add(buffer);

							// "Trim" crc32 and isize fields off the end
							auto compressedSize = totalBytes - 4 - 4;
							if (compressedSize < 0)
							{
								throw ref new NotSupportedException("Compressed data not in the expected format.");
							}

							// Create contiguous buffer
							auto compressedBytes = ref new Platform::Array<uint8>(zipHeaderSize + compressedSize + zipFooterSize);
							auto offset = zipHeaderSize;
							auto remainingBytes = totalBytes;
							for (auto b : buffers)
							{
								auto length = Math::Min(b->Length, remainingBytes);
								Array::Copy(b, 0, compressedBytes, offset, length);
								offset += length;
								remainingBytes -= length;
							}
							Debug::Assert(0 == remainingBytes);

							// Read footer from end of compressed bytes (note: footer is within zipFooterSize; will be overwritten below)
							Debug::Assert(totalBytes <= compressedSize + zipFooterSize);
							offset = zipHeaderSize + compressedSize;
							auto crc32 = compressedBytes[offset + 0] | (compressedBytes[offset + 1] << 8) | (compressedBytes[offset + 2] << 16) | (compressedBytes[offset + 3] << 24);
							auto isize = compressedBytes[offset + 4] | (compressedBytes[offset + 5] << 8) | (compressedBytes[offset + 6] << 16) | (compressedBytes[offset + 7] << 24);

							// Create ZIP file stream
							Platform::String ^ const fileName = "f"; // MUST be 1 character (offsets below assume this)
							Debug::Assert(1 == fileName->Length);
							auto zipFileMemoryStream = ref new MemoryStream(compressedBytes);
							auto writer = ref new BinaryWriter(zipFileMemoryStream);

							// Local file header
							writer->Write(safe_cast<uint32>(0x04034b50)); // local file header signature
							writer->Write(safe_cast<uint16>(20)); // version needed to extract (2.0 == compressed using deflate)
							writer->Write(safe_cast<uint16>(0)); // general purpose bit flag
							writer->Write(safe_cast<uint16>(8)); // compression method (8: deflate)
							writer->Write(safe_cast<uint16>(0)); // last mod file time
							writer->Write(safe_cast<uint16>(0)); // last mod file date
							writer->Write(crc32); // crc-32
							writer->Write(compressedSize); // compressed size
							writer->Write(isize); // uncompressed size
							writer->Write(safe_cast<uint16>(1)); // file name length
							writer->Write(safe_cast<uint16>(0)); // extra field length
							writer->Write(safe_cast<uint8>(fileName[0])); // file name

							// File data (already present)
							zipFileMemoryStream->Seek(compressedSize, SeekOrigin::Current);

							// Central directory structure
							writer->Write(safe_cast<uint32>(0x02014b50)); // central file header signature
							writer->Write(safe_cast<uint16>(20)); // version made by
							writer->Write(safe_cast<uint16>(20)); // version needed to extract (2.0 == compressed using deflate)
							writer->Write(safe_cast<uint16>(0)); // general purpose bit flag
							writer->Write(safe_cast<uint16>(8)); // compression method
							writer->Write(safe_cast<uint16>(0)); // last mod file time
							writer->Write(safe_cast<uint16>(0)); // last mod file date
							writer->Write(crc32); // crc-32
							writer->Write(compressedSize); // compressed size
							writer->Write(isize); // uncompressed size
							writer->Write(safe_cast<uint16>(1)); // file name length
							writer->Write(safe_cast<uint16>(0)); // extra field length
							writer->Write(safe_cast<uint16>(0)); // file comment length
							writer->Write(safe_cast<uint16>(0)); // disk number start
							writer->Write(safe_cast<uint16>(0)); // internal file attributes
							writer->Write(safe_cast<uint32>(0)); // external file attributes
							writer->Write(safe_cast<uint32>(0)); // relative offset of local header
							writer->Write(safe_cast<uint8>(fileName[0])); // file name
							// End of central directory record
							writer->Write(safe_cast<uint32>(0x06054b50)); // end of central dir signature
							writer->Write(safe_cast<uint16>(0)); // number of this disk
							writer->Write(safe_cast<uint16>(0)); // number of the disk with the start of the central directory
							writer->Write(safe_cast<uint16>(1)); // total number of entries in the central directory on this disk
							writer->Write(safe_cast<uint16>(1)); // total number of entries in the central directory
							writer->Write(safe_cast<uint32>(46 + 1)); // size of the central directory (46 bytes + 1 character for file name)
							writer->Write(safe_cast<uint32>(zipHeaderSize + compressedSize)); // offset of start of central directory with respect to the starting disk number
							writer->Write(safe_cast<uint16>(0)); // .ZIP file comment length

							// Reset ZIP file stream to beginning
							zipFileMemoryStream->Seek(0, SeekOrigin::Begin);

							auto sw = Stopwatch::StartNew();

							// Return the decompressed stream
							auto decompressedStream = Application::GetResourceStream(ref new StreamResourceInfo(zipFileMemoryStream, nullptr), ref new Uri(fileName, UriKind::Relative)).Stream;
							sw->Stop();

							Debug::WriteLine("Decompression took " + sw->ElapsedMilliseconds + "ms.");

							LogCompression(zipFileMemoryStream->Length, decompressedStream->Length);

							return decompressedStream;
						}
						else
						{
							// Not GZIP-compressed; return stream as-is
							return responseStream;
						}
					}

					void GzipExtensions::LogCompression(int64 compressedStreamLength, int64 decompressedStreamLength)
					{
						float64 ratio = -1;

						if (decompressedStreamLength > 0)
						{
							ratio = safe_cast<float64>(compressedStreamLength) / decompressedStreamLength;
						}

						Debug::WriteLine(Platform::String::Format("CompressedLength={0}, DecompressedLength={1}, Ratio={2}", compressedStreamLength, decompressedStreamLength, ratio));
					}
				}
			}
		}
	}
}
