#include "pch.h"

#include "VKCaptchaRequestUserControl.xaml.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation;
using namespace winsdkvk::WindowsPhone::SDK::API;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{

				VKCaptchaRequestUserControl::VKCaptchaRequestUserControl()
				{
					//this->InitializeComponent();
				}

				void VKCaptchaRequestUserControl::SendButton_Click(Platform::Object ^sender, RoutedEventArgs ^e)
				{
					ValidateCaptcha();
				}

				void VKCaptchaRequestUserControl::ValidateCaptcha()
				{
					/*
					VKCaptchaUserResponse ^tempVar = ref new VKCaptchaUserResponse();
					tempVar->EnteredString = textBoxCaptcha->Text;
					tempVar->IsCancelled = false;
					tempVar->Request = _captchaUserRequest;
					_callback->Invoke(tempVar);
					Visibility = Visibility::Collapsed;
					*/
				}

				void VKCaptchaRequestUserControl::ShowCaptchaRequest(VKCaptchaUserRequest ^captchaUserRequest, EventHandler<VKCaptchaUserResponse^> ^callback)
				{
					/*
					textBoxCaptcha->Text = "";
					imageCaptcha->Source = ref new BitmapImage(ref new Uri(captchaUserRequest->Url));
					_captchaUserRequest = captchaUserRequest;
					_callback = callback;
					ShowInPopup(Window::Current->Bounds->Width, Window::Current->Bounds->Height);
					*/
				}

				void VKCaptchaRequestUserControl::CancelButton_Click(Platform::Object ^sender, RoutedEventArgs ^e)
				{
					/*
					VKCaptchaUserResponse ^tempVar = ref new VKCaptchaUserResponse();
					tempVar->IsCancelled = true;
					tempVar->Request = _captchaUserRequest;
					_callback->Invoke(tempVar);

					Visibility = Visibility::Collapsed;
					*/
				}

				void VKCaptchaRequestUserControl::textBoxCaptcha_KeyDown(Platform::Object ^sender, KeyRoutedEventArgs ^e)
				{
					if (e->Key == VirtualKey::Enter)
					{
						ValidateCaptcha();
					}
				}
			}
		}
	}
}
