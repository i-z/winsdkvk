#include "pch.h"
#include "VKAlbum.h"

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

					Platform::String ^VKAlbum::title::get()
					{
						return _title;
					}

					void VKAlbum::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKAlbum::description::get()
					{
						return _description;
					}

					void VKAlbum::description::set(Platform::String ^value)
					{
						_description = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
