#pragma once

#include "Resources.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace winsdkvk { namespace WindowsPhone { namespace SDK_XAML { namespace Strings { ref class Resources; } } } }

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Strings
			{
				public ref class VKLocalizedStrings sealed
				{
				private:
					static Resources ^_localizedResources;

				public:
					property Resources ^LocalizedResources
					{
						Resources ^get();
					}
				};
			}
		}
	}
}
