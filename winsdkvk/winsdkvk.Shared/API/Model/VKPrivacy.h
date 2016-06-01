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
					/// https://vk.com/dev/privacy_setting
					/// </summary>
					public ref class VKPrivacy sealed
					{
					public:
						property Platform::String ^type;
						property Windows::Foundation::Collections::IVector<int64> ^users;
						property Windows::Foundation::Collections::IVector<int64> ^lists;
						property Windows::Foundation::Collections::IVector<int64> ^except_lists;
						property Windows::Foundation::Collections::IVector<int64> ^except_users;
					};

				}
			}
		}
	}
}
