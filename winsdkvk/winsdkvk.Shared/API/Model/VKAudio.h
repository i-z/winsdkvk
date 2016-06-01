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
					public ref class VKAudio sealed
					{
					public:
						property int64 id;
						property int64 owner_id;

					private:
						Platform::String ^_artist;

					public:
						property Platform::String ^artist
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_title;

					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property int32 duration;
						property Platform::String ^url;
						property int64 lyrics_id;
						property int64 album_id;
						property int64 genre_id;
					};
				}
			}
		}
	}
}
