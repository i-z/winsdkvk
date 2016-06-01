#pragma once
#include "LoginType.h"
#include "VKEventArgs.h"
#include "API/IVKLogger.h"
#include "API/VKCaptchaUserRequest.h"
#include "API/VKValidationRequest.h"

#define SDK_VERSION "1.2.5"
#define API_VERSION L"5.21"
#define PLATFORM_ID L"winphone"

/// <summary>
/// Default SDK access token key for storing value in IsolatedStorage.
/// You shouldn't modify this key or value directly in IsolatedStorage.
/// </summary>
#define VKSDK_ACCESS_TOKEN_ISOLATEDSTORAGE_KEY "VKSDK_ACCESS_TOKEN_DONTTOUCH"
#define VK_NAVIGATE_STR_FRM "/VK.WindowsPhone.SDK;component/Pages/VKLoginPage.xaml?Scopes={0}&Revoke={1}"
#define VK_AUTH_STR_FRM "https://oauth.vk.com/authorize?client_id={0}&scope={1}&redirect_uri={2}&display=mobile&v={3}&response_type=token&revoke={4}"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKSDK sealed
			{
			private:
				static VKSDK ^_instance;

				/// <summary>
				/// SDK instance
				/// </summary>
			internal:
				static property VKSDK ^Instance
				{
					VKSDK ^get();

				}

				/// <summary>
				/// Access token for API-requests
				/// </summary>
			private:
				VKAccessToken ^AccessToken;

			internal:
				/// <summary>
				/// Your VK app ID. 
				/// If you don't have one, create a standalone app here: https://vk.com/editapp?act=create 
				/// </summary>
				Platform::String ^CurrentAppID;

				static property Platform::String ^DeviceId
				{
					Platform::String ^get();
				}

				static API::IVKLogger ^Logger;

				/// <summary>
				/// Initialize SDK
				/// </summary>
				/// <param name="appId">Your VK app ID. 
				/// If you don't have one, create a standalone app here: https://vk.com/editapp?act=create </param>
			public:
				static void Initialize(Platform::String ^appId);

				/// <summary>
				/// Initialize SDK with custom token key (e.g. saved from other source or for some test reasons)
				/// </summary>
				/// <param name="appId">Your VK app ID. 
				/// If you don't have one, create a standalone app here: https://vk.com/editapp?act=create </param>
				/// <param name="token">Custom-created access token</param>
				static void Initialize(Platform::String ^appId, VKAccessToken ^token);

				//delegate Platform::String^ CaptchaRequestDelegate(API::VKCaptchaUserRequest^, Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^>^);

				static property Windows::Foundation::TypedEventHandler<API::VKCaptchaUserRequest^, Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^>^> ^CaptchaRequest;

				//    public static Action<ValidationUserRequest, Action<ValidationUserResponse>> ValidationRequest { private get; set; }


				/// <summary>
				/// Invokes when existing token has expired
				/// </summary>
				static event Windows::Foundation::EventHandler<VKAccessTokenExpiredEventArgs^> ^AccessTokenExpired;

				/// <summary>
				/// Invokes when user authorization has been canceled
				/// </summary>
				static event Windows::Foundation::EventHandler<VKAccessDeniedEventArgs^> ^AccessDenied;

				/// <summary>
				/// Invokes when new access token has been received
				/// </summary>
				static event Windows::Foundation::EventHandler<VKAccessTokenReceivedEventArgs^> ^AccessTokenReceived;

				/// <summary>
				/// Invokes when predefined token has been received and accepted
				/// </summary>
				static event Windows::Foundation::EventHandler<VKAccessTokenAcceptedEventArgs^> ^AccessTokenAccepted;

				/// <summary>
				/// Invokes when access token has been renewed (e.g. user passed validation)
				/// </summary>
				static event Windows::Foundation::EventHandler<AccessTokenRenewedEventArgs^> ^AccessTokenRenewed;

				/// <summary>
				/// Invoked if current app installation is the installation from the VK mobile games catalog
				/// </summary>
				static event Windows::Foundation::EventHandler<Platform::Object^> ^MobileCatalogInstallationDetected;

				/// <summary>
				/// Starts authorization process. Opens and requests for access if VK App is installed. 
				/// Otherwise SDK will navigate current app to SDK navigation page and start OAuth in WebBrowser.
				/// </summary>
				/// <param name="scopeList">List of permissions for your app</param>
				/// <param name="revoke">If true user will be allowed to logout and change user</param>
				/// <param name="forceOAuth">SDK will use only OAuth authorization via WebBrowser</param>
				static void Authorize(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList, bool revoke, bool forceOAuth, LoginType loginType);

				/// <summary>
				/// Starts authorization process. Opens and requests for access if VK App is installed. 
				/// Otherwise SDK will navigate current app to SDK navigation page and start OAuth in WebBrowser.
				/// </summary>
				/// <param name="scopeList">List of permissions for your app</param>
				/// <param name="revoke">If true user will be allowed to logout and change user</param>
				/// <param name="forceOAuth">SDK will use only OAuth authorization via WebBrowser</param>
				static void Authorize(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList);

			private:
				static void AuthorizeVKApp(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList, bool revoke);

			private:
				enum class CheckTokenResult
				{
					None,
					Success,
					Error
				};

			private:
				static void CheckConditions();

				/// <summary>
				/// Check new access token and assign as instance token 
				/// </summary>
				/// <param name="tokenParams">Params of token</param>
				/// <param name="isTokenBeingRenewed">Flag indicating token renewal</param>
				/// <returns>Success if token has been assigned or error</returns>
			private:
				static CheckTokenResult CheckAndSetToken(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^tokenParams, bool isTokenBeingRenewed);

				/// <summary>
				/// Save API access token in IsolatedStorage with default key.
				/// </summary>
				/// <param name="token">Access token to be used for API requests</param>
				/// <param name="renew">Is token being renewed. Raises different event handlers (AccessTokenReceived or AccessTokenRenewed)</param>
			public:
				static void SetAccessToken(VKAccessToken ^token, bool renew);

				/// <summary>
				/// Get access token to be used for API requests.
				/// </summary>
				/// <returns>Received access token, null if user has not been authorized yet</returns>
				static VKAccessToken ^GetAccessToken();

				/// <summary>
				/// Notify SDK that user denied login
				/// </summary>
				/// <param name="error">Description of error while authorizing user</param>
				static void SetAccessTokenError(API::VKError ^error);

			private:
				bool PerformTokenCheck(VKAccessToken ^token, bool isUserDefinedToken = false);

			public:
				static bool WakeUpSession();

			private:
				static void TrackStats();


			public:
				static void CheckMobileCatalogInstallation(Windows::Foundation::EventHandler<bool> ^resultCallback);

				/// <summary>
				/// Removes active token from memory and IsolatedStorage at default key.
				/// </summary>
				static void Logout();

				static property bool IsLoggedIn
				{
					bool get();
				}


			internal:
				static void ProcessLoginResult(Platform::String ^result, bool wasValidating, Windows::Foundation::EventHandler<API::VKValidationResponse^> ^validationCallback);

				static void InvokeCaptchaRequest(API::VKCaptchaUserRequest ^request, Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^> ^callback);

				static void InvokeValidationRequest(API::VKValidationRequest ^request, Windows::Foundation::EventHandler<API::VKValidationResponse^> ^callback);
			};
		}
	}
}
