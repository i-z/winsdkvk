#include "pch.h"
#include "VKLoginUserControl.xaml.h"
#include "VKSDK.h"
#include "Util/StringUtil.h"
#include <sstream>

using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation;
using namespace winsdkvk::WindowsPhone::SDK;
using namespace winsdkvk::WindowsPhone::SDK::API;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace winsdkvk::WindowsPhone::SDK;
using namespace winsdkvk::WindowsPhone::SDK::Util;


#define REDIRECT_URL L"https://oauth.vk.com/blank.html"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{
				VKLoginUserControl ^VKLoginUserControl::_currentlyShownInstance = nullptr;

				Platform::String ^VKLoginUserControl::ValidationUri::get()
				{
					return _validationUri;
				}

				void VKLoginUserControl::ValidationUri::set(Platform::String ^value)
				{
					_validationUri = value;
					_isValidating = _validationUri != nullptr;
				}

				EventHandler<VKValidationResponse^> ^VKLoginUserControl::ValidationCallback::get()
				{
					return _validationCallback;
				}

				void VKLoginUserControl::ValidationCallback::set(EventHandler<VKValidationResponse^> ^value)
				{
					_validationCallback = value;
				}

				VKLoginUserControl ^VKLoginUserControl::CurrentlyShownInstance::get()
				{
					return _currentlyShownInstance;
				}

				IVector<Platform::String^> ^VKLoginUserControl::Scopes::get()
				{
					return _scopes;
				}

				void VKLoginUserControl::Scopes::set(IVector<Platform::String^> ^value)
				{
					_scopes = safe_cast<Vector<Platform::String^>^>(value);
				}

				bool VKLoginUserControl::Revoke::get()
				{
					return _revoke;
				}

				void VKLoginUserControl::Revoke::set(bool value)
				{
					_revoke = value;
				}

				VKLoginUserControl::VKLoginUserControl()
				{
					InitializeComponent();
				}

				void VKLoginUserControl::PrepareForLoad()
				{
					InitializeWebBrowser();
				}

				void VKLoginUserControl::InitializeWebBrowser()
				{
					Platform::String ^urlToLoad;
					if (_validationUri != nullptr)
						urlToLoad = _validationUri;
					else
					{
						std::wstringstream ss;

						ss	<< L"https://oauth.vk.com/authorize?client_id=" << VKSDK::Instance->CurrentAppID->Data()
							<< L"&scope=" << StrUtil::GetCommaSeparated(_scopes)->Data()
							<< L"&redirect_uri=" << REDIRECT_URL
							<< L"&display=mobile&v=" << API_VERSION
							<< L"&response_type=token&revoke={4}" << (_revoke ? L"1" : L"0");
						urlToLoad = ref new Platform::String(ss.str().data());
					}

					webView->NavigationStarting += ref new TypedEventHandler<WebView^, WebViewNavigationStartingEventArgs^>(this, &VKLoginUserControl::BrowserOnNavigating);
					_navCompleted = webView->NavigationCompleted += ref new TypedEventHandler<WebView^, WebViewNavigationCompletedEventArgs^>(this, &VKLoginUserControl::BrowserOnLoadCompleted);

					webView->Navigate(ref new Uri(urlToLoad));
				}

				void VKLoginUserControl::BrowserOnLoadCompleted(WebView ^sender, WebViewNavigationCompletedEventArgs ^args)
				{
					if (!args->IsSuccess)
					{
						progressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
						errorTextBlock->Visibility = Windows::UI::Xaml::Visibility::Visible;
					}
					else
					{
						webView->NavigationCompleted -= _navCompleted;
						webView->Visibility = Windows::UI::Xaml::Visibility::Visible;
						progressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
					}
				}

				void VKLoginUserControl::BrowserOnNavigating(WebView ^sender, WebViewNavigationStartingEventArgs ^args)
				{
					auto purl = args->Uri->AbsoluteUri;
					std::wstring url = purl->Data();

					if (url.find(REDIRECT_URL) == 0 && !_processedResult)
					{
						auto an = url.find('#');
						auto nresult = url.substr(an + 1, url.length() - an - 1);
						auto result = ref new Platform::String(nresult.data());

						_processedResult = true;
						VKSDK::ProcessLoginResult(result, _isValidating, _validationCallback);
						this->IsShown = false;
					}
				}

				void VKLoginUserControl::OnClosing()
				{
					VKPopupControlBase::OnClosing();
					if (!_processedResult)
					{
						VKSDK::ProcessLoginResult(nullptr, _isValidating, _validationCallback);
					}
				}
			}
		}
	}
}
