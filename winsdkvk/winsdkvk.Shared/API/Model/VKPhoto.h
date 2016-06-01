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
					public ref class VKPhoto sealed
					{
					public:
						property int64 id;
						property int64 album_id;

						property int64 owner_id;
						property int64 user_id;

						property Platform::String ^photo_75;
						property Platform::String ^photo_130;
						property Platform::String ^photo_604;
						property Platform::String ^photo_807;
						property Platform::String ^photo_1280;
						property Platform::String ^photo_2560;

						property int32 width;
						property int32 height;
					private:
						Platform::String ^_text;
					public:
						property Platform::String ^text
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property int32 date;
					};
				}
			}
		}
	}
}
