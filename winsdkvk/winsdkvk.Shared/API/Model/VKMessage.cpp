#include "pch.h"
#include "VKMessage.h"

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

					Platform::String ^VKMessage::title::get()
					{
						return _title;
					}

					void VKMessage::title::set(Platform::String ^value)
					{
						_title = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKMessage::body::get()
					{
						return _body;
					}

					void VKMessage::body::set(Platform::String ^value)
					{
						_body = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKMessage::action::get()
					{
						return _action;
					}

					void VKMessage::action::set(Platform::String ^value)
					{
						_action = ((value != nullptr) ? value : "");
					}

					Platform::String ^VKMessage::action_email::get()
					{
						return _action_email;
					}

					void VKMessage::action_email::set(Platform::String ^value)
					{
						_action_email = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKMessage::action_text::get()
					{
						return _action_text;
					}

					void VKMessage::action_text::set(Platform::String ^value)
					{
						_action_text = ((value != nullptr) ? value : "");//.ForUI();
					}
				}
			}
		}
	}
}
