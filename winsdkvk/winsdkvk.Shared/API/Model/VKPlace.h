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
					public ref class Place sealed
					{
					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_address;
					public:
						property Platform::String ^address
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property float64 latitude;
						property float64 longitude;
						property Platform::String ^country;
						property Platform::String ^city;
						property Platform::String ^icon;
						property Platform::String ^type;
						property int64 group_id;
						property Platform::String ^group_photo;
						property int32 checkins;
						property int64 updated;

					};
				}
			}
		}
	}
}
