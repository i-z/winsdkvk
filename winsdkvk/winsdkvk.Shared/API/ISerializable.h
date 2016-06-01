#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public interface class ISerializable
				{
					void Deserialize(Platform::String ^data);
					Platform::String ^Serialize();
				};
			}
		}
	}
}
