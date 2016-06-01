#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKAppLaunchAuthorizationHelper sealed abstract
			{
			private:
				static initonly Platform::String ^_launchUriStrFrm = R"(vkappconnect://authorize?State={0}&ClientId={1}&Scope={2}&Revoke={3}&RedirectUri={4})";

			public:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task AuthorizeVKApp(string state, string clientId, List<string> scopeList, bool revoke)
				static Task ^AuthorizeVKApp(Platform::String ^state, Platform::String ^clientId, List<Platform::String^> ^scopeList, bool revoke);

			private:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private static async Task<string> GetRedirectUri()
				static Task<Platform::String^> ^GetRedirectUri();

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: async private static Task<string> GetVKLoginCallbackSchemeName()
				static Task<Platform::String^> ^GetVKLoginCallbackSchemeName();

			internal:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: internal async static Task<string> GetFilteredManifestAppAttributeValue(string node, string attribute, string prefix)
				static Task<Platform::String^> ^GetFilteredManifestAppAttributeValue(Platform::String ^node, Platform::String ^attribute, Platform::String ^prefix);
			};
		}
	}
}
}
