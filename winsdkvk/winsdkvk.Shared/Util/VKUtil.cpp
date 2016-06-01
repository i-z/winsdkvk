#include "pch.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include "VKUtil.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				Windows::Foundation::DateTime VKUtil::Jan1St1970 = Windows::Foundation::DateTime();

				IMap<Platform::String^, Platform::String^> ^VKUtil::ExplodeQueryString(Platform::String ^queryString)
				{
					auto wqstr = queryString->Data();
					std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
					auto qstr = converter.to_bytes(wqstr);

					std::vector<std::string> keyValuePairs;
					std::stringstream sstream(qstr);
					std::string item;
					while (std::getline (sstream, item, '&'))
					{
						keyValuePairs.push_back(item);
					}

					auto parameters = ref new Map<Platform::String^, Platform::String^>();

					for (auto keyValueString : keyValuePairs)
					{
						auto idx = keyValueString.find('=', 0);
						if (idx != std::string::npos)
						{
							auto key = keyValueString.substr(0, idx);
							auto val = keyValueString.substr(idx + 1, keyValueString.length() - idx - 1);
							auto wkey = converter.from_bytes(key);
							auto wval = converter.from_bytes(val);
							parameters->Insert(ref new Platform::String(wkey.data()), ref new Platform::String(wval.data()));
						}
					}

					return parameters;
				}

				Platform::String ^VKUtil::GetParamsOfQueryString(Platform::String ^queryString)
				{
					/*
					int32 indOfQ = queryString->IndexOf('?');

					if (indOfQ >= 0 && indOfQ < queryString->Length - 1)
					{
						auto paramsString = queryString->Substring(indOfQ + 1);

						return paramsString;
					}
					*/
					return "";
				}

				Platform::String ^VKUtil::JoinParams(IMap<Platform::String^, Platform::Object^> ^queryArgs, bool isUri)
				{
					std::wstringstream ss;
					bool start = true;
					for (auto entry : queryArgs)
					{
						if (!start)
							ss << '&';
						auto value = entry->Value;
						ss << entry->Key->Data() << '=' << (isUri ? UriEncode(value->ToString())->Data() : value->ToString()->Data());

						start = false;
					}

					return ref new Platform::String(ss.str().data());
				}

				IMap<Platform::String^, Platform::String^> ^VKUtil::DictionaryFrom(const Platform::Array<Platform::String^> ^args)
				{
					if (args->Length % 2 != 0)
					{
						throw ref new HResult("Args must be paired. Last one is ignored");
					}

					auto result = ref new Map<Platform::String^, Platform::String^>();
					for (int32 i = 0; i + 1 < args->Length; i += 2)
					{
						if (args[i + 1] != nullptr && args[i + 1] != "")
						{
							result->Insert(args[i], args[i + 1]);
						}
					}

					return result;
				}

				Platform::String ^VKUtil::FileToString(Platform::String ^filename)
				{
					/*
					#if defined(SILVERLIGHT)

					Platform::String ^text;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var iso = IsolatedStorageFile.GetUserStoreForApplication())
					{
						auto iso = IsolatedStorageFile::GetUserStoreForApplication();
						if (!iso->FileExists(filename))
						{
							return nullptr;
						}

						auto reader = ref new StreamReader(ref new IsolatedStorageFileStream(filename, FileMode::Open, iso));
						text = reader->ReadToEnd();
						reader->Close();
					}

					return text;
							#else

					Platform::String ^text = "";

					Task::Run(async[&] ()
					{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							auto file = await Windows::Storage::ApplicationData::Current->LocalFolder.GetFileAsync(filename);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							text = await Windows::Storage::FileIO::ReadTextAsync(file);
					}).Wait();

					return text;

							#endif
							*/
					return "";
				}

				void VKUtil::StringToFile(Platform::String ^filename, Platform::String ^stringToWrite)
				{
					/*
							#if defined(SILVERLIGHT)
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var iso = IsolatedStorageFile.GetUserStoreForApplication())
					{
						auto iso = IsolatedStorageFile::GetUserStoreForApplication();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (IsolatedStorageFileStream file = iso.OpenFile(filename, FileMode.Create, FileAccess.Write))
						{
							IsolatedStorageFileStream ^file = iso->OpenFile(filename, FileMode::Create, FileAccess::Write);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter writer = new StreamWriter(file))
							{
								StreamWriter ^writer = ref new StreamWriter(file);
								writer->WriteLineAsync(stringToWrite);
								delete writer;
							}
						}
					}
							#else

					Task::Run(async[&] ()
					{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							auto file = await ApplicationData::Current->LocalFolder.CreateFileAsync(filename, CreationCollisionOption::ReplaceExisting);

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							await Windows::Storage::FileIO::WriteTextAsync(file, stringToWrite);

					}).Wait();
							#endif
					return nullptr;
					*/
				}

				int64 VKUtil::CurrentTimeMillis()
				{
					return time(nullptr);
				}

				void VKUtil::ClearCookies()
				{
					Windows::Web::Http::Filters::HttpBaseProtocolFilter ^myFilter = ref new Windows::Web::Http::Filters::HttpBaseProtocolFilter();
					auto cookieManager = myFilter->CookieManager;
					auto myCookieJar = cookieManager->GetCookies(ref new Uri("https://vk.com"));
					for (auto cookie : myCookieJar)
					{
						cookieManager->DeleteCookie(cookie);
					}

					myCookieJar = cookieManager->GetCookies(ref new Uri("https://login.vk.com"));
					for (auto cookie : myCookieJar)
					{
						cookieManager->DeleteCookie(cookie);
					}
				}


				const char HEX2DEC[256] =
				{
					/*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
					/* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

					/* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

					/* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

					/* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
					/* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
				};

				std::string VKUtil::UriDecode(const std::string & sSrc)
				{
					// Note from RFC1630:  "Sequences which start with a percent sign
					// but are not followed by two hexadecimal characters (0-9, A-F) are reserved
					// for future extension"

					const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
					const int SRC_LEN = sSrc.length();
					const unsigned char * const SRC_END = pSrc + SRC_LEN;
					const unsigned char * const SRC_LAST_DEC = SRC_END - 2;   // last decodable '%' 

					char * const pStart = new char[SRC_LEN];
					char * pEnd = pStart;

					while (pSrc < SRC_LAST_DEC)
					{
						if (*pSrc == '%')
						{
							char dec1, dec2;
							if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
								&& -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
							{
								*pEnd++ = (dec1 << 4) + dec2;
								pSrc += 3;
								continue;
							}
						}

						*pEnd++ = *pSrc++;
					}

					// the last 2- chars
					while (pSrc < SRC_END)
						*pEnd++ = *pSrc++;

					std::string sResult(pStart, pEnd);
					delete[] pStart;
					return sResult;
				}

				// Only alphanum is safe.
				const char SAFE[256] =
				{
					/*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
					/* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,

					/* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
					/* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
					/* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
					/* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,

					/* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

					/* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
					/* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
				};

				std::string VKUtil::UriEncode(const std::string & sSrc)
				{
					const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
					const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
					const int SRC_LEN = sSrc.length();
					unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
					unsigned char * pEnd = pStart;
					const unsigned char * const SRC_END = pSrc + SRC_LEN;

					for (; pSrc < SRC_END; ++pSrc)
					{
						if (SAFE[*pSrc])
							*pEnd++ = *pSrc;
						else
						{
							// escape this char
							*pEnd++ = '%';
							*pEnd++ = DEC2HEX[*pSrc >> 4];
							*pEnd++ = DEC2HEX[*pSrc & 0x0F];
						}
					}

					std::string sResult((char *)pStart, (char *)pEnd);
					delete[] pStart;
					return sResult;
				}

				Platform::String ^VKUtil::UriDecode(Platform::String^ src)
				{
					std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
					std::string sSrc = converter.to_bytes(src->Data());
					auto res = UriDecode(sSrc);
					return ref new Platform::String(converter.from_bytes(res.data()).data());
				}

				Platform::String ^VKUtil::UriEncode(Platform::String^ src)
				{
					std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
					std::string sSrc = converter.to_bytes(src->Data());
					auto res = UriEncode(sSrc);
					return ref new Platform::String(converter.from_bytes(res.data()).data());
				}
			}
		}
	}
}
