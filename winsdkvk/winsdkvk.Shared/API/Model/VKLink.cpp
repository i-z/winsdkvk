#include "pch.h"
#include "VKLink.h"

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

					Platform::String ^VKLink::title::get()
					{
						return _title;
					}

					void VKLink::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKLink::description::get()
					{
						return _desc;
					}

					void VKLink::description::set(Platform::String ^value)
					{
						_desc = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
