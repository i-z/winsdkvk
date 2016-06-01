#pragma once
#include "API/VKError.h"
//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace winsdkvk { namespace WindowsPhone { namespace SDK { ref class VKAccessToken; } } }
#include "VKAccessToken.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKCaptchaReceivedEventArgs sealed
			{
				/// <summary>
				/// Error returned from API. You can load captcha image from CaptchaImg property.
				/// After user answered current captcha, call AnswerCaptcha method with user entered answer. 
				/// </summary>
			public:
				property API::VKError ^Error;
			};

			public ref class VKAccessTokenExpiredEventArgs sealed
			{
				/// <summary>
				/// Old token that has expired
				/// </summary>
			public:
				property VKAccessToken ^ExpiredToken;
			};

			public ref class VKAccessDeniedEventArgs sealed
			{
				/// <summary>
				/// Error describing authorization error
				/// </summary>
			public:
				property API::VKError ^AuthorizationError;
			};

			public ref class VKAccessTokenReceivedEventArgs sealed
			{
				/// <summary>
				/// New token for API requests
				/// </summary>
			public:
				property VKAccessToken ^NewToken;
			};

			public ref class VKAccessTokenAcceptedEventArgs sealed
			{
				/// <summary>
				/// Used token for API requests
				/// </summary>
			public:
				property VKAccessToken ^Token;
			};

			public ref class AccessTokenRenewedEventArgs sealed
			{
				/// <summary>
				/// Used token for API requests
				/// </summary>
			public:
				property VKAccessToken ^Token;
			};

			public ref class VKRequestErrorEventArgs sealed
			{
				/// <summary>
				/// Error for VKRequest
				/// </summary>
			public:
				property API::VKError ^Error;
			};

			public ref class VKRequestProgressEventArgs sealed
			{
				//todo
			};
		}
	}
}
