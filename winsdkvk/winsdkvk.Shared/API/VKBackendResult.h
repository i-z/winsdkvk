#pragma once
#include "VKResultCode.h"
#include "VKError.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class VKBackendResult sealed
				{
				public:
					property VKResultCode ResultCode;

					property Platform::String ^ResultString;

					property Platform::Object^ Data;

					property VKError ^Error;
				};
			}
		}
	}
}
