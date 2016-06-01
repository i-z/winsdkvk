#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Strings
			{
				public ref class Resources sealed
				{
					/// <summary>
					///   Looks up a localized string similar to cancel.
					/// </summary>
				public:
					static property Platform::String ^Captcha_Cancel
					{
						Platform::String ^get();
					}

					/// <summary>
					///   Looks up a localized string similar to Enter the code from the picture.
					/// </summary>
					static property Platform::String ^Captcha_RequiredText
					{
						Platform::String ^get();
					}

					/// <summary>
					///   Looks up a localized string similar to send.
					/// </summary>
					static property Platform::String ^Captcha_Send
					{
						Platform::String ^get();
					}

					/// <summary>
					///   Looks up a localized string similar to Error.
					/// </summary>
					static property Platform::String ^Error
					{
						Platform::String ^get();
					}

					static Platform::String ^GetLocalizedString(Platform::String ^key);
				};
			}
		}
	}
}
