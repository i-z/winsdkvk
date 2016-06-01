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
					public ref class VKDocument sealed
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
						property int64 size;
						property Platform::String ^ext;
						property Platform::String ^url;

						property Platform::String ^photo_100;
						property Platform::String ^photo_130;
					};
				}
			}
		}
	}
}
