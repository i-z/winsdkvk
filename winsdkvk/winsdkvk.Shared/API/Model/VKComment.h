#pragma once

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKAttachment; } } } } }

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
					public ref class VKComment sealed
					{
					public:
						property int64 id;

						property int64 from_id;

						property int64 date;

					private:
						property Platform::String ^_text;
					public:
						property Platform::String ^text
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property int64 reply_to_user;
						property int64 reply_to_comment;
						property Windows::Foundation::Collections::IVector<VKAttachment^> ^attachments;
					};
				}
			}
		}
	}
}
