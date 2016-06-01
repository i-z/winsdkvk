#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKAccessToken sealed
			{
			public:
				static property Platform::String ^ACCESS_TOKEN		{ Platform::String ^get(){ return ref new Platform::String(L"access_token");	 }};
				static property Platform::String ^EXPIRES_IN		{ Platform::String ^get(){ return ref new Platform::String(L"expires_in");		 }};
				static property Platform::String ^USER_ID			{ Platform::String ^get(){ return ref new Platform::String(L"user_id");		 }};
				static property Platform::String ^SECRET			{ Platform::String ^get(){ return ref new Platform::String(L"secret");			 }};
				static property Platform::String ^HTTPS_REQUIRED	{ Platform::String ^get(){ return ref new Platform::String(L"https_required");	 }};
				static property Platform::String ^CREATED			{ Platform::String ^get(){ return ref new Platform::String(L"created");		 }};
				static property Platform::String ^SUCCESS			{ Platform::String ^get(){ return ref new Platform::String(L"success");		 }};

				/// <summary>
				/// String token for use in request parameters
				/// </summary>
				property Platform::String ^AccessToken;

				/// <summary>
				/// Time when token expires
				/// </summary>
				property int32 ExpiresIn;

				/// <summary>
				/// Current user id for this token
				/// </summary>
				property Platform::String ^UserId;

				/// <summary>
				/// User secret to sign requests (if nohttps used)
				/// </summary>
				property Platform::String ^Secret;

				/// <summary>
				/// If user sets "Always use HTTPS" setting in his profile, it will be true
				/// </summary>
				property bool IsHttpsRequired;

				/// <summary>
				/// Indicates time of token creation
				/// </summary>
				property long long Created;

				/// <summary>
				/// Save token into Isolated Storage with key
				/// </summary>
				/// <param name="tokenKey">Your key for saving settings</param>
				void SaveTokenToIsolatedStorage(Platform::String ^tokenKey);

				/// <summary>
				/// Removes token from Isolated Storage with specified key
				/// </summary>
				/// <param name="tokenKey">Your key for saving settings</param>
				static void RemoveTokenInIsolatedStorage(Platform::String ^tokenKey);


				/// <summary>
				/// Serialize token into string
				/// </summary>
				/// <returns></returns>
			protected:
				Platform::String ^SerializeTokenData();

			public:
				VKAccessToken();

				/// <summary>
				/// Retreive token from key-value query string
				/// </summary>
				/// <param name="urlString">String that contains URL-query part with token. E.g. access_token=eee&expires_in=0..</param>
				/// <returns>parsed token</returns>
				static VKAccessToken ^FromUrlString(Platform::String ^urlString);

				/// <summary>
				/// Retreive token from key-value map
				/// </summary>
				/// <param name="args">Dictionary containing token info</param>
				/// <returns>Parsed token</returns>
				static VKAccessToken ^TokenFromParameters(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^args);

				/// <summary>
				/// Retreives token from Isolated Storage
				/// </summary>
				/// <param name="tokenKey">Your key for saving settings</param>
				/// <returns>Previously saved token or null</returns>
				static VKAccessToken ^TokenFromIsolatedStorage(Platform::String ^tokenKey);

				/// <summary>
				/// Retreive token from file. Token must be saved into file via VKAccessToken.SaveToTokenFile()
				/// </summary>
				/// <param name="filename"></param>
				/// <returns></returns>
				static VKAccessToken ^TokenFromFile(Platform::String ^filename);

				/// <summary>
				/// Checks token expiration time
				/// </summary>
				/// <returns>true if token has expired</returns>
				property bool IsExpired
				{
					bool get();
				}
			};
		}
	}
}
