#include "pch.h"
#include "VKAudio.h"

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

					Platform::String ^VKAudio::artist::get()
					{
						return _artist;
					}

					void VKAudio::artist::set(Platform::String ^value)
					{
						_artist = ((value != nullptr) ? value : "");
						// do not allow new line
						//_artist = _artist->MakeIntoOneLine();

					}

					Platform::String ^VKAudio::title::get()
					{
						return _title;
					}

					void VKAudio::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");
						// do not allow new line
						//_title = _title->MakeIntoOneLine();
					}
				}
			}
		}
	}
}
