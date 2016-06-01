#include "pch.h"
#include "VKPopupControlBase.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Platform::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Pages
			{
				Vector<VKPopupControlBase^> ^VKPopupControlBase::_currentlyShownInstances = ref new Vector<VKPopupControlBase^>();

				IVector<VKPopupControlBase^> ^VKPopupControlBase::CurrentlyShownInstances::get()
				{
					return _currentlyShownInstances;
				}

				bool VKPopupControlBase::IsShown::get()
				{
					return _parentPopup->IsOpen;
				}

				void VKPopupControlBase::IsShown::set(bool value)
				{
					_parentPopup->IsOpen = value;

					if (!value)
					{
						OnClosing();
						unsigned int i;
						if(_currentlyShownInstances->IndexOf(this, &i))
							_currentlyShownInstances->RemoveAt(i);
					}
				}

				void VKPopupControlBase::ShowInPopup(Platform::IBox<float64>^ width, Platform::IBox<float64>^ height)
				{
					auto popup = ref new Popup();
					if (width != nullptr)
					{
						popup->Width = width->Value;
						this->Width = width->Value;
					}
					if (height != nullptr)
					{
						popup->Height = height->Value;
						this->Height = height->Value;
					}

					this->_parentPopup = popup;

					popup->Child = this;

					popup->IsOpen = true;

					_currentlyShownInstances->Append(this);

					this->PrepareForLoad();

				}

				void VKPopupControlBase::OnClosing()
				{

				}

				void VKPopupControlBase::PrepareForLoad()
				{
				}
			}
		}
	}
}
