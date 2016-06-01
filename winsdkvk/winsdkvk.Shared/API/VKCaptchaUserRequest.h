#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class VKCaptchaUserRequest sealed
				{
				public:
					property Platform::String ^CaptchaSid;
					property Platform::String ^Url;
				};

				public ref class VKCaptchaUserResponse sealed
				{
				public:
					property VKCaptchaUserRequest ^Request;

					property bool IsCancelled;

					property Platform::String ^EnteredString;
				};
			}
		}
	}
}
