#pragma once

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
					/// <summary>
					/// Class that provides helper methods to add support for GZIP to Windows Phone.
					/// </summary>
					/// <remarks>
					/// GZIP file format specification: http://tools.ietf.org/rfc/rfc1952.txt
					/// ZIP file specification: http://www.pkware.com/documents/casestudies/APPNOTE.TXT
					/// </remarks>
					private ref class GzipExtensions sealed abstract
					{
						/// <summary>
						/// HTTP request header Accept-Encoding string.
						/// </summary>
					private:
						static Platform::String ^GZIP = "gzip";

						/// <summary>
						/// Adds an HTTP Accept-Encoding header for GZIP.
						/// </summary>
						/// <param name="request">Request to modify.</param>
					public:
						static void AddAcceptEncodingHeader(HttpWebRequest ^request);

						/// <summary>
						/// Begins an asynchronous request to an Internet resource, using GZIP when supported by the server.
						/// </summary>
						/// <param name="request">Request to act on.</param>
						/// <param name="callback">The AsyncCallback delegate.</param>
						/// <param name="state">The state object for this request.</param>
						/// <returns>An IAsyncResult that references the asynchronous request for a response.</returns>
						/// <remarks>
						/// Functionally equivalent to BeginGetResponse (with GZIP).
						/// </remarks>
						static IAsyncResult ^BeginGetCompressedResponse(HttpWebRequest ^request, AsyncCallback ^callback, Platform::Object ^state);

						/// <summary>
						/// Returns the data stream from the Internet resource.
						/// </summary>
						/// <param name="response">Response to act on.</param>
						/// <returns>An instance of the Stream class for reading data from the Internet resource.</returns>
						/// Functionally equivalent to GetResponseStream (with GZIP).
						[SuppressMessage("Microsoft.Reliability", "CA2000:Dispose objects before losing scope", Justification = "Returning a Stream for the caller to use.")]
						static Stream ^GetCompressedResponseStream(HttpWebResponse ^response);

					private:
						static void LogCompression(int64 compressedStreamLength, int64 decompressedStreamLength);
					};
				}
			}
		}
	}
}
