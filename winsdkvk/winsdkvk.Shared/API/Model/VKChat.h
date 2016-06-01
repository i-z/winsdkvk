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
					public ref class VKChat sealed
					{
					public:
						property Platform::String ^type;
						property int64 id;

					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}
						property int64 admin_id;
						property Windows::Foundation::Collections::IVector<int64> ^users;
						property Platform::String ^photo_100;
						property Platform::String ^photo_200;
					};
				}
			}
		}
	}
}
