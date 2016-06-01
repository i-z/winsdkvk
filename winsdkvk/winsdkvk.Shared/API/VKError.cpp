#include "pch.h"
#include "VKError.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				void VKError::Deserialize(Platform::String ^data)
				{
				}

				Platform::String ^ VKError::Serialize()
				{
					return L"";
				}
			}
		}
	}
}
