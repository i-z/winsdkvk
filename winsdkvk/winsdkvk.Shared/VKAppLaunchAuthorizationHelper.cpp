using namespace System;

#include "VKAppLaunchAuthorizationHelper.h"
#include "VKSDK.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Linq;
using namespace System::Net;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Xml::Linq;
using namespace winsdkvk::WindowsPhone::SDK::Util;
using namespace Windows::System;
using namespace System::IO;
using namespace System::Windows;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task AuthorizeVKApp(string state, string clientId, List<string> scopeList, bool revoke)
			Task ^VKAppLaunchAuthorizationHelper::AuthorizeVKApp(Platform::String ^state, Platform::String ^clientId, List<Platform::String^> ^scopeList, bool revoke)
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				Platform::String ^redirectUri = await GetRedirectUri();

				auto uriString = Platform::String::Format(_launchUriStrFrm, WebUtility::UrlEncode(state == nullptr ? Platform::String::Empty : state), clientId, StrUtil::GetCommaSeparated(scopeList), revoke, redirectUri);

				auto fallbackUri = Platform::String::Format(VKSDK::VK_AUTH_STR_FRM, VKSDK::Instance->CurrentAppID, scopeList->GetCommaSeparated(), WebUtility::UrlEncode("vk" + clientId + "://authorize"), VKSDK::API_VERSION, revoke ? 1 : 0);

				try
				{

					Uri(uriString), ref new LauncherOptions tempVar = ref new Uri(uriString), ref new LauncherOptions();
					tempVar->FallbackUri = ref new Uri(fallbackUri);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
					await Launcher::LaunchUriAsync(tempVar);

				}
				catch (HResult ^e1)
				{

					#if defined(SILVERLIGHT)
					auto msg = "VK App authorization is not supported for this type of the project. Please, use WebView authorization.";
					MessageBox::Show(msg);
					#endif
				}


			}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private static async Task<string> GetRedirectUri()
			Task<Platform::String^> ^VKAppLaunchAuthorizationHelper::GetRedirectUri()
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				return await GetVKLoginCallbackSchemeName() + "://authorize";
			}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: async private static Task<string> GetVKLoginCallbackSchemeName()
			Task<Platform::String^> ^VKAppLaunchAuthorizationHelper::GetVKLoginCallbackSchemeName()
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				Platform::String ^result = await GetFilteredManifestAppAttributeValue("Protocol", "Name", "vk");
				return result;
			}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: internal async static Task<string> GetFilteredManifestAppAttributeValue(string node, string attribute, string prefix)
			Task<Platform::String^> ^VKAppLaunchAuthorizationHelper::GetFilteredManifestAppAttributeValue(Platform::String ^node, Platform::String ^attribute, Platform::String ^prefix)
			{

					#if !defined(SILVERLIGHT)
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				auto file = await Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(ref new Uri("ms-appx:///VKConfig.xml"));
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (Stream strm = await file.OpenStreamForReadAsync())
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				{
					Stream ^strm = await file->OpenStreamForReadAsync();
					#else
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (System.IO.Stream strm = Microsoft.Xna.Framework.TitleContainer.OpenStream("WMAppManifest.xml"))
					{
					System::IO::Stream ^strm = Microsoft::Xna::Framework::TitleContainer::OpenStream("WMAppManifest.xml");
					#endif
					auto xml = XElement::Load(strm);
					}
					auto filteredAttributeValue = (from app in xml->Descendants(node) let xAttribute = app::Attribute(attribute) where xAttribute != nullptr select xAttribute->Value).FirstOrDefault([&] (Platform::Object ^a)
					{
						a->StartsWith(prefix);
					});

					if (Platform::String::IsNullOrWhiteSpace(filteredAttributeValue))
					{
						return Platform::String::Empty;
					}

					return filteredAttributeValue;
			}
		}
	}
}
