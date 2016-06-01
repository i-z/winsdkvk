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
					public ref class VKLink sealed
					{
					public:
						property Platform::String ^url;
					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_desc;
					public:
						property Platform::String ^description
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}
						property Platform::String ^image_src;
					};
				}
			}
		}
	}
}
