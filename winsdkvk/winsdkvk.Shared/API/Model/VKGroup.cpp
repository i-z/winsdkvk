#include "pch.h"
#include "VKGroup.h"

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
				namespace Model
				{

					Platform::String ^VKGroup::description::get()
					{
						return _desc;
					}

					void VKGroup::description::set(Platform::String ^value)
					{
						_desc = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
