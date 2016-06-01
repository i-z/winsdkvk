#include "pch.h"
#include "VKPoll.h"

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

					Platform::String ^VKPoll::question::get()
					{
						return _question;
					}

					void VKPoll::question::set(Platform::String ^value)
					{
						_question = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKPollAnswer::text::get()
					{
						return _text;
					}

					void VKPollAnswer::text::set(Platform::String ^value)
					{
						_text = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
