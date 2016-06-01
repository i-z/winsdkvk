#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{
				public ref class VKPopupControlBase : Windows::UI::Xaml::Controls::UserControl
				{
				private:
					Windows::UI::Xaml::Controls::Primitives::Popup ^_parentPopup;

					static Platform::Collections::Vector<VKPopupControlBase^> ^_currentlyShownInstances;

				public:
					static property Windows::Foundation::Collections::IVector<VKPopupControlBase^> ^CurrentlyShownInstances
					{
						Windows::Foundation::Collections::IVector<VKPopupControlBase^> ^get();
					}

					property bool IsShown
					{
						bool get();
						void set(bool value);
					}

					void ShowInPopup(Platform::IBox<float64>^ width, Platform::IBox<float64>^ height);

				protected:
					virtual void OnClosing();

					virtual void PrepareForLoad();
				};
			}
		}
	}
}
