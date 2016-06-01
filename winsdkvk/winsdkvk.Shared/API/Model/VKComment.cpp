#include "pch.h"
#include "VKComment.h"
#include "VKAttachment.h"

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

					Platform::String ^VKComment::text::get()
					{
						return _text;
					}

					void VKComment::text::set(Platform::String ^value)
					{
						_text = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
