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
					/// <summary>
					/// https://vk.com/dev/video_object
					/// </summary>
					public ref class VKVideo sealed
					{
					public:
						property int64 id;

						property int64 owner_id;

					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}
						property int32 duration;

					private:
						Platform::String ^_description;

					public:
						property Platform::String ^description
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}
						property int32 date;
						property int32 views;

						property Platform::String ^photo_130;

						property Platform::String ^photo_320;

						property Platform::String ^photo_640;

						property Platform::String ^player;
					};
				}
			}
		}
	}
}
