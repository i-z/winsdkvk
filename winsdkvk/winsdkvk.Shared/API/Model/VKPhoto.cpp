#include "pch.h"
#include "VKPhoto.h"

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

					Platform::String ^VKPhoto::text::get()
					{
						return _text;
					}

					void VKPhoto::text::set(Platform::String ^value)
					{
						_text = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
