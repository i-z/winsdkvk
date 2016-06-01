#include "pch.h"
#include "VKSDK.h"
#include "VKHttpRequestHelper.h"

#include <sstream>

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Storage::Streams;
using namespace winsdkvk::WindowsPhone::SDK::API;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				IVKLogger ^VKHttpRequestHelper::Logger::get()
				{
					return VKSDK::Logger;
				}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async void DispatchHTTPRequest(string baseUri, Dictionary<string, string> parameters, Action<VKHttpResult> resultCallback)
				void VKHttpRequestHelper::DispatchHTTPRequest(Platform::String ^baseUri, IMap<Platform::String^, Platform::String^> ^parameters, HttpResultCallback ^resultCallback)
				{
					auto msg = L">>> VKHttpRequestHelper starting http request. baseUri = " + baseUri + "; parameters = " + GetAsLogString(parameters);
					Logger->Info(msg, nullptr);

					auto queryString = ConvertDictionaryToQueryString(parameters, true);
					
					try
					{

						auto filter = ref new HttpBaseProtocolFilter();

						filter->AutomaticDecompression = true;

						auto httpClient = ref new Windows::Web::Http::HttpClient(filter);

						HttpFormUrlEncodedContent ^content = ref new HttpFormUrlEncodedContent(parameters);

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
						concurrency::create_task(httpClient->PostAsync(ref new Uri(baseUri), content)).then([resultCallback](HttpResponseMessage ^result)
						{
							//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
							auto resultStr = result->Content->ReadAsStringAsync()->GetResults();

							SafeInvokeCallback(resultCallback, result->IsSuccessStatusCode, resultStr);
						});

					}
					catch (Platform::Exception ^exc)
					{
						Logger->Error("VKHttpRequestHelper.DispatchHTTPRequest failed.", exc);
						SafeInvokeCallback(resultCallback, false, nullptr);
					}
				}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async void Upload(string uri, Stream data, string paramName, string uploadContentType,Action<VKHttpResult> resultCallback, Action<double> progressCallback = null, string fileName = null)
				void VKHttpRequestHelper::Upload(Platform::String ^uri, IInputStream ^data, Platform::String ^paramName, Platform::String ^uploadContentType, HttpResultCallback ^resultCallback, ProgressCallback ^progressCallback, Platform::String ^fileName)
				{
					try
					{
						auto httpClient = ref new Windows::Web::Http::HttpClient();
						HttpMultipartFormDataContent ^content = ref new HttpMultipartFormDataContent();
						content->Add(ref new HttpStreamContent(data), paramName, (fileName != nullptr) ? fileName : "myDataFile");
						content->Headers->Append("Content-Type", uploadContentType);
						auto postAsyncOp = httpClient->PostAsync(ref new Uri(uri), content);

						/*
						postAsyncOp->Progress = ref new AsyncOperationProgressHandler<HttpResponseMessage^, HttpProgress>( [progressCallback] (HttpResponseMessage^ r, HttpProgress progress)
						{
								if (progressCallback != nullptr && progress.TotalBytesToSend && progress.TotalBytesToSend->Value > 0)
								{
									progressCallback((safe_cast<float64>(progress.BytesSent) * 100) / progress.TotalBytesToSend->Value);
								}
						});
						*/

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
						auto result = postAsyncOp->GetResults();

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
						auto resultStr = result->Content->ReadAsStringAsync()->GetResults();

						SafeInvokeCallback(resultCallback, result->IsSuccessStatusCode, resultStr);
					}
					catch (Platform::Exception ^exc)
					{
						Logger->Error("VKHttpRequestHelper.Upload failed.", exc);
						SafeInvokeCallback(resultCallback, false, nullptr);
					}
				}

				void VKHttpRequestHelper::SafeInvokeCallback(HttpResultCallback ^action, bool p, Platform::String ^stringContent)
				{
					try
					{
						VKHttpResult ^tempVar = ref new VKHttpResult();
						tempVar->IsSucceeded = p;
						tempVar->Data = stringContent;
						action(tempVar);
					}
					catch (Platform::Exception ^exc)
					{
						Logger->Error("VKHttpRequestHelper.SafeInvokeCallback failed.", exc);
					}
				}

				Platform::String ^VKHttpRequestHelper::ConvertDictionaryToQueryString(IMap<Platform::String^, Platform::String^> ^parameters, bool escapeString)
				{
					if (parameters == nullptr || parameters->Size == 0)
					{
						return "";
					}

					std::wstringstream sb;
					
					bool begin = true;
					for (auto kvp : parameters)
					{
						if (kvp->Key == nullptr || kvp->Value == nullptr)
						{
							continue;
						}

						if (!begin)
						{
							sb << '&';
							begin = false;
						}

						Platform::String ^valueStr = escapeString ? Uri::EscapeComponent(kvp->Value) : kvp->Value;

						sb << kvp->Key->Data() << '=' << valueStr->Data();
					}

					return ref new Platform::String(sb.str().data());
				}

				Platform::String ^VKHttpRequestHelper::GetAsLogString(IMap<Platform::String^, Platform::String^> ^parameters)
				{
					std::wstringstream result;
					for (auto kvp : parameters)
					{
						result << kvp->Key->Data() << " = " << kvp->Value->Data() << '\n';
					}
					return ref new Platform::String(result.str().data());
				}
			}
		}
	}
}
