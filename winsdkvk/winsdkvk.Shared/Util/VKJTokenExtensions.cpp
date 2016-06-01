using namespace System;

#include "VKJTokenExtensions.h"

using namespace Windows::Foundation;
using namespace Newtonsoft::Json::Linq;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				bool VKJTokenExtensions::ValueVKBool(JToken ^json, Platform::String ^name)
				{
					return json != nullptr && json->Value<int32>(name) == 1;
				}
			}
		}
	}
}
