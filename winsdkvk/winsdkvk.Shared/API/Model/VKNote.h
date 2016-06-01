#pragma once

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
					public ref class VKNote sealed
					{
					public:
						property int64 id;

						property int64 user_id;
						property int64 owner_id
						{
							int64 get();
							void set(int64 value);
						}

					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}


					private:
						Platform::String ^_text;
					public:
						property Platform::String ^text
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}


						property int32 comments;

						property int32 read_comments;

						property Platform::String ^view_url;
					};
				}
			}
		}
	}
}
