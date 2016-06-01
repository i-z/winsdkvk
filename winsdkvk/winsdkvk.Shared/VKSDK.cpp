#include "pch.h"
#include "VKSDK.h"

#include "VKScope.h"
//#include "VKAppLaunchAuthorizationHelper.h"
#include "API/DefaultLogger.h"
#include "Pages/VKLoginUserControl.xaml.h"
#include "API/VKRequest.h"
#include "API/VKResultCode.h"
#include "Util/VKUtil.h"
#include "LoginType.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace winsdkvk::WindowsPhone::SDK::API;
using namespace winsdkvk::WindowsPhone::SDK::Pages;
using namespace winsdkvk::WindowsPhone::SDK::Util;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			VKSDK ^VKSDK::_instance = nullptr;
			IVKLogger ^VKSDK::Logger = nullptr;

			VKSDK ^VKSDK::Instance::get()
			{
				if (_instance == nullptr)
				{
					_instance = ref new VKSDK();
				}
				return _instance;
			}

			Platform::String ^VKSDK::DeviceId::get()
			{
				return Windows::System::UserProfile::AdvertisingManager::AdvertisingId;
			}

			void VKSDK::Initialize(Platform::String ^appId)
			{
				Logger = ref new API::DefaultLogger();

				if (appId == nullptr || appId == "")
				{
					throw ref new Platform::Exception(1, "VKSDK could not initialize. " + "Application ID cannot be null or empty. " + "If you don't have one, create a standalone app here: https://vk.com/editapp?act=create");
				}

				Instance->CurrentAppID = appId;
			}

			void VKSDK::Initialize(Platform::String ^appId, VKAccessToken ^token)
			{
				Initialize(appId);
				Instance->AccessToken = token;
				Instance->PerformTokenCheck(token, true);
			}

			void VKSDK::Authorize(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList, bool revoke, bool forceOAuth, LoginType loginType)
			{
				try
				{
					CheckConditions();
				}
				catch (Platform::Exception ^e)
				{
					OutputDebugString(e->ToString()->Data());
					return;
				}

				if (scopeList == nullptr)
				{
					scopeList = ref new Platform::Collections::Vector<Platform::String^>();
				}

				// Force OFFLINE scope using
				unsigned int idx;
				if (!scopeList->IndexOf(VKScope::OFFLINE, &idx))
				{
					scopeList->Append(VKScope::OFFLINE);
				}


				switch (loginType)
				{
					case LoginType::VKApp:

						AuthorizeVKApp(scopeList, revoke);

						break;
					default:
						auto loginUserControl = ref new VKLoginUserControl();

						loginUserControl->Scopes = scopeList;
						loginUserControl->Revoke = revoke;

						loginUserControl->ShowInPopup((double)Windows::UI::Xaml::Window::Current->Bounds.Width, (double)Windows::UI::Xaml::Window::Current->Bounds.Height);
						break;
				}
			}

			void VKSDK::Authorize(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList)
			{
				Authorize(scopeList, false, false, LoginType::WebView);
			}

			void VKSDK::AuthorizeVKApp(Windows::Foundation::Collections::IVector<Platform::String^> ^scopeList, bool revoke)
			{
				/*
				VKAppLaunchAuthorizationHelper::AuthorizeVKApp("", VKSDK::Instance->CurrentAppID, scopeList, revoke);
				*/
			}

			void VKSDK::CheckConditions()
			{

			}

			VKSDK::CheckTokenResult VKSDK::CheckAndSetToken(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^tokenParams, bool isTokenBeingRenewed)
			{
				auto token = VKAccessToken::TokenFromParameters(tokenParams);
				if (token == nullptr || token->AccessToken == nullptr)
				{
					if (tokenParams->HasKey(VKAccessToken::SUCCESS))
					{
						return CheckTokenResult::Success;
					}

					auto error = ref new VKError();
					error->error_code = safe_cast<int32>(API::VKResultCode::UserAuthorizationFailed);

					return CheckTokenResult::Error;
				}
				else
				{
					SetAccessToken(token, isTokenBeingRenewed);
					return CheckTokenResult::Success;
				}


			}

			void VKSDK::SetAccessToken(VKAccessToken ^token, bool renew)
			{
				if (Instance->AccessToken == nullptr || (Instance->AccessToken->AccessToken != token->AccessToken || Instance->AccessToken->ExpiresIn != token->ExpiresIn))
				{
					Instance->AccessToken = token;

					if (!renew)
					{
						VKAccessTokenReceivedEventArgs ^tempVar = ref new VKAccessTokenReceivedEventArgs();
					
						tempVar->NewToken = token;
						AccessTokenReceived(nullptr, tempVar);
					}
					else
					{
						AccessTokenRenewedEventArgs ^tempVar2 = ref new AccessTokenRenewedEventArgs();
					
						tempVar2->Token = token;
						AccessTokenRenewed(nullptr, tempVar2);
					}

					Instance->AccessToken->SaveTokenToIsolatedStorage(VKSDK_ACCESS_TOKEN_ISOLATEDSTORAGE_KEY);
				}
			}

			VKAccessToken ^VKSDK::GetAccessToken()
			{
				if (Instance->AccessToken != nullptr)
				{
					if (Instance->AccessToken->IsExpired)
					{
						VKAccessTokenExpiredEventArgs ^tempVar = ref new VKAccessTokenExpiredEventArgs();
					
						tempVar->ExpiredToken = Instance->AccessToken;
						AccessTokenExpired(nullptr, tempVar);
					}
					return Instance->AccessToken;
				}

				return nullptr;
			}

			void VKSDK::SetAccessTokenError(VKError ^error)
			{
				VKAccessDeniedEventArgs ^tempVar = ref new VKAccessDeniedEventArgs();
				tempVar->AuthorizationError = error;
				AccessDenied(nullptr, tempVar);
			}

			bool VKSDK::PerformTokenCheck(VKAccessToken ^token, bool isUserDefinedToken)
			{
				if (token == nullptr)
				{
					return false;
				}

				if (token->IsExpired)
				{
					VKAccessTokenExpiredEventArgs ^tempVar = ref new VKAccessTokenExpiredEventArgs();
					tempVar->ExpiredToken = token;
					AccessTokenExpired(nullptr, tempVar);
					return false;
				}
				if (token->AccessToken != nullptr)
				{
					if (isUserDefinedToken)
					{
						VKAccessTokenAcceptedEventArgs ^tempVar2 = ref new VKAccessTokenAcceptedEventArgs();
					
						tempVar2->Token = token;
						AccessTokenAccepted(nullptr, tempVar2);
					}
					return true;
				}

				auto error = ref new VKError();
				error->error_code = safe_cast<int32>(API::VKResultCode::InvalidToken);
				VKAccessDeniedEventArgs ^tempVar3 = ref new VKAccessDeniedEventArgs();
				tempVar3->AuthorizationError = error;
				AccessDenied(nullptr, tempVar3);
				return false;
			}

			bool VKSDK::WakeUpSession()
			{
				bool result = true;

				auto token = VKAccessToken::TokenFromIsolatedStorage(VKSDK_ACCESS_TOKEN_ISOLATEDSTORAGE_KEY);

				if (!Instance->PerformTokenCheck(token))
				{
					result = false;
				}
				else
				{
					Instance->AccessToken = token;
				}

				TrackStats();

				return result;
			}

			void VKSDK::TrackStats()
			{
				/*
				int64 appId = 0;
				bool appIdParsed = true;
				appId = _wtoi64(Instance->CurrentAppID->Data());

				if (Instance->AccessToken != nullptr)
				{
					auto params = ref new Array<Platform::String^>{ ref new Platform::String(L"platform"), ref new Platform::String(PLATFORM_ID), ref new Platform::String(L"app_id"), appId.ToString(), L"device_id", DeviceId };
					VKRequest ^checkUserInstallRequest = ref new VKRequest("apps.checkUserInstall", params);

					checkUserInstallRequest->Dispatch[&] (res)
					{
							int32 responseVal = 0;

							if (res::Data != nullptr && int32::TryParse(res::Data->ToString(), responseVal))
							{
								if (responseVal == 1)
								{
									MobileCatalogInstallationDetected(nullptr, EventArgs::Empty);
								}
							}

							VKRequest ^trackVisitorRequest = ref new VKRequest("stats.trackVisitor");

							trackVisitorRequest->Dispatch<Platform::Object^>([&] (res2)
							{
							}, [&] (jsonStr)
							{
								ref new Platform::Object();
							});

					});
				}
				else
				{
					if (!Platform::String::IsNullOrEmpty(DeviceId) && appIdParsed)
					{
						VKRequest ^checkUserInstallRequest = ref new VKRequest("apps.checkUserInstall", "platform", PLATFORM_ID, "app_id", appId.ToString(), "device_id", DeviceId);

						checkUserInstallRequest->Dispatch<Platform::Object^>([&] (res)
						{
							int32 responseVal = 0;

							if (res::Data != nullptr && int32::TryParse(res::Data->ToString(), responseVal))
							{
								if (responseVal == 1)
								{
									MobileCatalogInstallationDetected(nullptr, EventArgs::Empty);
								}
							}
						});
					}
				}
				*/
			}

			void VKSDK::CheckMobileCatalogInstallation(Windows::Foundation::EventHandler<bool> ^resultCallback)
			{
				/*
				VKRequest ^checkUserInstallRequest = nullptr;
				int64 appId = 0;
				bool appIdParsed = int64::TryParse(Instance->CurrentAppID, appId);
				if (Instance->AccessToken != nullptr)
				{
					checkUserInstallRequest = ref new VKRequest("apps.checkUserInstall", "platform", PLATFORM_ID, "app_id", appId.ToString(), "device_id", DeviceId);
				}
				else
				{
					if (!Platform::String::IsNullOrEmpty(DeviceId) && appIdParsed)
					{
						checkUserInstallRequest = ref new VKRequest("apps.checkUserInstall", "platform", PLATFORM_ID, "app_id", appId.ToString(), "device_id", DeviceId);
					}
					else
					{
						resultCallback(false);
						return;
					}
				}

				checkUserInstallRequest->Dispatch<Platform::Object^>([&] (res)
				{
					int32 responseVal = 0;

					if (res::Data != nullptr)
					{
						int32::TryParse(res::Data->ToString(), responseVal);
					}

					resultCallback(responseVal == 1);
				});
				*/

			}

			void VKSDK::Logout()
			{
				Instance->AccessToken = nullptr;

				VKAccessToken::RemoveTokenInIsolatedStorage(VKSDK_ACCESS_TOKEN_ISOLATEDSTORAGE_KEY);

				VKUtil::ClearCookies();
			}

			bool VKSDK::IsLoggedIn::get()
			{
				return Instance->AccessToken != nullptr && !Instance->AccessToken->IsExpired;
			}

			void VKSDK::ProcessLoginResult(Platform::String ^result, bool wasValidating, Windows::Foundation::EventHandler<API::VKValidationResponse^> ^validationCallback)
			{
				bool success = false;

				if (result == nullptr)
				{
					VKError ^tempVar = ref new VKError();
					tempVar->error_code = safe_cast<int32>(VKResultCode::UserAuthorizationFailed);
					SetAccessTokenError(tempVar);
				}
				else
				{
					auto tokenParams = VKUtil::ExplodeQueryString(result);
					if (CheckAndSetToken(tokenParams, wasValidating) == CheckTokenResult::Success)
					{
						success = true;

						if (!wasValidating)
						{
							TrackStats();
						}
					}
					else
					{
						VKError ^tempVar2 = ref new VKError();
						tempVar2->error_code = safe_cast<int32>(VKResultCode::UserAuthorizationFailed);
						SetAccessTokenError(tempVar2);
					}
				}

				if (validationCallback != nullptr)
				{
					VKValidationResponse ^tempVar3 = ref new VKValidationResponse();
					tempVar3->IsSucceeded = success;
					validationCallback(nullptr, tempVar3);
				}
			}

			void VKSDK::InvokeCaptchaRequest(VKCaptchaUserRequest ^request, Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^> ^callback)
			{
				if (CaptchaRequest == nullptr)
				{
					// no handlers are registered

					VKCaptchaUserResponse ^tempVar = ref new VKCaptchaUserResponse();
					tempVar->Request = request;
					tempVar->EnteredString = "";
					tempVar->IsCancelled = true;
					callback(nullptr, tempVar);
				}
				else
				{
					/*
					VKExecute::ExecuteOnUIThread([&] ()
					{
						CaptchaRequest(request, callback);
					});
					*/
				}
			}

			void VKSDK::InvokeValidationRequest(VKValidationRequest ^request, Windows::Foundation::EventHandler<API::VKValidationResponse^> ^callback)
			{
				/*
				VKExecute::ExecuteOnUIThread([&] ()
				{
					#if defined(SILVERLIGHT)
						VKParametersRepository::SetParameterForId("ValidationCallback", callback);
						RootFrame->Navigate(ref new Uri(Platform::String::Format("/VK.WindowsPhone.SDK;component/Pages/VKLoginPage.xaml?ValidationUri={0}", HttpUtility::UrlEncode(request->ValidationUri)), UriKind::Relative));
					#else
						auto loginUserControl = ref new VKLoginUserControl();

						loginUserControl->ValidationUri = request->ValidationUri;
						loginUserControl->ValidationCallback = callback;

						loginUserControl->ShowInPopup(Windows::UI::Xaml::Window::Current->Bounds->Width, Windows::UI::Xaml::Window::Current->Bounds->Height);
					#endif
				});
				*/
			}
		}
	}
}
