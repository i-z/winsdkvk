#include "pch.h"
#include "VKLocalizedStrings.h"
#include "Resources.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Strings
			{

				Resources ^VKLocalizedStrings::_localizedResources  = ref new Resources();

				Resources ^VKLocalizedStrings::LocalizedResources::get()
				{
					return _localizedResources;
				}
			}
		}
	}
}
