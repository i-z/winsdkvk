#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				public ref class VKUtil sealed
				{
					/// <summary>
					/// Breaks key=value&key=value string to map
					/// </summary>
					/// <param name="queryString">string to explode</param>
					/// <returns>Key-value map of passed string</returns>
				public:
					static Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^ExplodeQueryString(Platform::String ^queryString);

					static Platform::String ^GetParamsOfQueryString(Platform::String ^queryString);

					/// <summary>
					/// Join parameters to map into string, usually query string
					/// </summary>
					/// <param name="queryArgs">Map to join</param>
					/// <param name="isUri">Indicates that value parameters must be url-encoded</param>
					/// <returns>Result query string, like k=v&k1=v=1</returns>
					/// <summary>
					/// Join parameters to map into string, usually query string
					/// </summary>
					/// <param name="queryArgs">Map to join</param>
					/// <param name="isUri">Indicates that value parameters must be url-encoded</param>
					/// <returns>Result query string, like k=v&k1=v=1</returns>
					static Platform::String ^JoinParams(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^> ^queryArgs, bool isUri);


					static Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^DictionaryFrom(const Platform::Array<Platform::String^> ^args);

					/// <summary>
					/// Reads content of file and returns result as string
					/// </summary>
					/// <param name="filename">File name in IsolatedStorage</param>
					/// <returns>Contents of file</returns>
					static Platform::String ^FileToString(Platform::String ^filename);

					/// <summary>
					/// Saves passed string to file in IsolatedStorage.
					/// </summary>
					/// <param name="filename">Filename in IsolatedStorage</param>
					/// <param name="stringToWrite">String to save</param>
					static void StringToFile(Platform::String ^filename, Platform::String ^stringToWrite);

				private:
					static Windows::Foundation::DateTime Jan1St1970;

					static std::string UriDecode(const std::string & sSrc);
					static std::string UriEncode(const std::string & sSrc);
				public:
					/// <summary>
					/// Helper method to retreive current time from Jan 1st 1970 in milliseconds.
					/// </summary>
					/// <returns>Current time from Jan 1st 1970 in milliseconds</returns>
					static int64 CurrentTimeMillis();


					static void ClearCookies();
					static Platform::String ^VKUtil::UriDecode(Platform::String^ src);
					static Platform::String ^VKUtil::UriEncode(Platform::String^ src);
				};
			}
		}
	}
}
