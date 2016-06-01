#pragma once
#include "VKRequestParameters.h"
#include "ISerializable.h"

#define USER_AUTHORIZATION_FAILED 5
#define CAPTCHA_REQUIRED 14
#define VALIDATION_REQUIRED 17

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class VKError sealed : ISerializable
				{
				public:
					property int32 error_code;
					property Platform::String ^error_msg;
					property Windows::Foundation::Collections::IVector<VKRequestParam^> ^request_params;
					property Platform::String ^captcha_sid;
					property Platform::String ^captcha_img;
					property Platform::String ^redirect_uri;

					virtual void Deserialize(Platform::String ^data);
					virtual Platform::String ^Serialize();
				};
			}
		}
	}
}
