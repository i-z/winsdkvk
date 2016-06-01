#pragma once
#include "VKPopupControlBase.h"
#include "Pages/VKLoginUserControl.g.h"
#include "../API/VKValidationRequest.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{
				public ref class VKLoginUserControl sealed
				{
				private:

					Platform::Collections::Vector<Platform::String^> ^_scopes;
					bool _revoke = false;
					Windows::UI::Xaml::Controls::Primitives::Popup ^_parentPopup;
					Windows::Foundation::EventHandler<API::VKValidationResponse^> ^_validationCallback;
					bool _isValidating = false;
					bool _processedResult = false;
					Platform::String ^_validationUri;

					static VKLoginUserControl ^_currentlyShownInstance;
					Windows::Foundation::EventRegistrationToken _navCompleted;

				public:
					property Platform::String ^ValidationUri
					{
						Platform::String ^get();
						void set(Platform::String ^value);
					}

				internal:
					property Windows::Foundation::EventHandler<API::VKValidationResponse^> ^ValidationCallback
					{
						Windows::Foundation::EventHandler<API::VKValidationResponse^> ^get();
						void set(Windows::Foundation::EventHandler<API::VKValidationResponse^> ^value);
					}

				public:
					static property VKLoginUserControl ^CurrentlyShownInstance
					{
						VKLoginUserControl ^get();
					}


					property Windows::Foundation::Collections::IVector<Platform::String^> ^Scopes
					{
						Windows::Foundation::Collections::IVector<Platform::String^> ^get();
						void set(Windows::Foundation::Collections::IVector<Platform::String^> ^value);
					}

					property bool Revoke
					{
						bool get();
						void set(bool value);
					}

					VKLoginUserControl();

				protected:
					virtual void PrepareForLoad() override;

				private:
					void InitializeWebBrowser();
					void BrowserOnLoadCompleted(Windows::UI::Xaml::Controls::WebView ^sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs ^args);
					void BrowserOnNavigating(Windows::UI::Xaml::Controls::WebView ^sender, Windows::UI::Xaml::Controls::WebViewNavigationStartingEventArgs ^args);

				protected:
					virtual void OnClosing() override;
				};
			}
		}
	}
}
