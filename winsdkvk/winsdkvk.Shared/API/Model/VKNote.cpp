#include "pch.h"
#include "VKNote.h"

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

					int64 VKNote::owner_id::get()
					{
						return user_id;
					}

					void VKNote::owner_id::set(int64 value)
					{
						user_id = value;
					}

					Platform::String ^VKNote::title::get()
					{
						return _title;
					}

					void VKNote::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKNote::text::get()
					{
						return _text;
					}

					void VKNote::text::set(Platform::String ^value)
					{
						_text = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
