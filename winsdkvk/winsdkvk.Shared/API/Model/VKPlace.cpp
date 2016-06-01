#include "pch.h"
#include "VKPlace.h"

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

					Platform::String ^Place::title::get()
					{
						return _title;
					}

					void Place::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^Place::address::get()
					{
						return _address;
					}

					void Place::address::set(Platform::String ^value)
					{
						_address = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
