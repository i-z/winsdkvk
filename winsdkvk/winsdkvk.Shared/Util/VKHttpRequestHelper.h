#pragma once
#include "API/IVKLogger.h"

#define BUFFER_SIZE 5000

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				public ref class VKHttpResult sealed
				{
				public:
					property bool IsSucceeded;

					property Platform::String ^Data;
				};

				public delegate void HttpResultCallback(VKHttpResult^);
				public delegate void ProgressCallback(float64);

				public ref class VKHttpRequestHelper sealed
				{
				private:
					static property API::IVKLogger ^Logger
					{
						API::IVKLogger ^get();
					}

				public:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async void DispatchHTTPRequest(string baseUri, Dictionary<string, string> parameters, Action<VKHttpResult> resultCallback)
					static void DispatchHTTPRequest(Platform::String ^baseUri, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters, HttpResultCallback ^resultCallback);

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async void Upload(string uri, Stream data, string paramName, string uploadContentType,Action<VKHttpResult> resultCallback, Action<double> progressCallback = null, string fileName = null)
					static void Upload(Platform::String ^uri, Windows::Storage::Streams::IInputStream ^data, Platform::String ^paramName, Platform::String ^uploadContentType, HttpResultCallback ^resultCallback, ProgressCallback ^progressCallback, Platform::String ^fileName);

					static void SafeInvokeCallback(HttpResultCallback ^action, bool p, Platform::String ^stringContent);

					static Platform::String ^ConvertDictionaryToQueryString(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters, bool escapeString);

					static Platform::String ^GetAsLogString(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters);
				};
			}
		}
	}
}
