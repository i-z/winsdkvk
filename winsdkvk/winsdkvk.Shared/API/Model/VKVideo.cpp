#include "pch.h"
#include "VKVideo.h"

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

					Platform::String ^VKVideo::title::get()
					{
						return _title;
					}

					void VKVideo::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKVideo::description::get()
					{
						return _description;
					}

					void VKVideo::description::set(Platform::String ^value)
					{
						_description = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
