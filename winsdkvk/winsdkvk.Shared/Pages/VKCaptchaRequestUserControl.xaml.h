#pragma once

#include "Strings/VKLocalizedStrings.h"
#include "VKPopupControlBase.h"
#include "Pages/VKCaptchaRequestUserControl.g.h"
#include "../API/VKCaptchaUserRequest.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{
				public ref class VKCaptchaRequestUserControl sealed
				{
				private:
					API::VKCaptchaUserRequest ^_captchaUserRequest;
					Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^> ^_callback;

				public:
					VKCaptchaRequestUserControl();

				private:
					void SendButton_Click(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);

					void ValidateCaptcha();

				public:
					void ShowCaptchaRequest(API::VKCaptchaUserRequest ^captchaUserRequest, Windows::Foundation::EventHandler<API::VKCaptchaUserResponse^> ^callback);

				private:
					void CancelButton_Click(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);
					void textBoxCaptcha_KeyDown(Platform::Object ^sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs ^e);
				};
			}
		}
	}
}
