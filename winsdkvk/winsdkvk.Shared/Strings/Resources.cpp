#include "pch.h"
#include "Resources.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel::Resources;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Strings
			{
				Platform::String ^Resources::Captcha_Cancel::get()
				{
					return GetLocalizedString("Captcha_Cancel");
				}

				Platform::String ^Resources::Captcha_RequiredText::get()
				{
					return GetLocalizedString("Captcha_RequiredText");
				}

				Platform::String ^Resources::Captcha_Send::get()
				{
					return GetLocalizedString("Captcha_Send");
				}

				Platform::String ^Resources::Error::get()
				{
					return GetLocalizedString("Error");
				}

				Platform::String ^Resources::GetLocalizedString(Platform::String ^key)
				{
					auto rl = ResourceLoader::GetForCurrentView("VK.WindowsPhone.SDK-XAML/Resources");
				   return rl->GetString(key);
				}
			}
		}
	}
}
