#pragma once

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKPollAnswer; } } } } }

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
					public ref class VKPoll sealed
					{
					public:
						property int64 id;

						property int64 owner_id;

						property int64 created;

						property int32 is_closed;

					private:
						Platform::String ^_question;
					public:
						property Platform::String ^question
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property int32 votes;

						property int64 answer_id;

						property Windows::Foundation::Collections::IVector<VKPollAnswer^> ^answers;
					};

					public ref class VKPollAnswer sealed
					{
					public:
						property int64 id;

					private:
						Platform::String ^_text;
					public:
						property Platform::String ^text
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}
						property int32 votes;
						property float64 rate;
					};
				}
			}
		}
	}
}
