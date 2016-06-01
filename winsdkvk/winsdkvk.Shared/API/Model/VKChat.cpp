#include "pch.h"
#include "VKChat.h"

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

					Platform::String ^VKChat::title::get()
					{
						return _title;
					}

					void VKChat::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
