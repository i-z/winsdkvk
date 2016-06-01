#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				private ref class VKValidationRequest
				{
				public:
					property Platform::String ^ValidationUri;
				};

				private ref class VKValidationResponse
				{
				public:
					property bool IsSucceeded;
				};
			}
		}
	}
}
