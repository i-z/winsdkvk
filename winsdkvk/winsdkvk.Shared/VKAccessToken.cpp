#include "pch.h"
#include "VKAccessToken.h"
#include "Util/VKUtil.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			void VKAccessToken::SaveTokenToIsolatedStorage(Platform::String ^tokenKey)
			{
				Windows::Storage::ApplicationData::Current->LocalSettings->Values->Remove(tokenKey);
				Windows::Storage::ApplicationData::Current->LocalSettings->Values->Insert(tokenKey, SerializeTokenData());
			}

			void VKAccessToken::RemoveTokenInIsolatedStorage(Platform::String ^tokenKey)
			{
				Windows::Storage::ApplicationData::Current->LocalSettings->Values->Remove(tokenKey);
			}

			Platform::String ^VKAccessToken::SerializeTokenData()
			{
				auto args = ref new Platform::Collections::Map<Platform::String^, Platform::Object^>();
				args->Insert(ACCESS_TOKEN, AccessToken);
				args->Insert(EXPIRES_IN, ExpiresIn);
				args->Insert(USER_ID, UserId);
				args->Insert(CREATED, Created);

				if (Secret != nullptr)
				{
					args->Insert(SECRET, Secret);
				}

				if (IsHttpsRequired)
				{
					args->Insert(HTTPS_REQUIRED, "1");
				}

				return Util::VKUtil::JoinParams(args, false);
			}

			VKAccessToken::VKAccessToken()
			{
			}

			VKAccessToken ^VKAccessToken::FromUrlString(Platform::String ^urlString)
			{
				if (urlString == nullptr)
				{
					return nullptr;
				}

				auto args = Util::VKUtil::ExplodeQueryString(urlString);

				return TokenFromParameters(args);
			}

			VKAccessToken ^VKAccessToken::TokenFromParameters(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^args)
			{
				if (args == nullptr || args->Size == 0)
				{
					return nullptr;
				}

				try
				{
					auto token = ref new VKAccessToken();
					if (args->HasKey(ACCESS_TOKEN))
					{
						token->AccessToken = args->Lookup(ACCESS_TOKEN);
					}
					else
						return nullptr;

					Platform::String ^expiresValue;
					expiresValue = args->Lookup(EXPIRES_IN);
					token->ExpiresIn = _wtoi(expiresValue->Data());

					token->UserId = args->Lookup(USER_ID);

					if (args->HasKey(SECRET))
					{
						token->Secret = args->Lookup(SECRET);
					}
					if (args->HasKey(HTTPS_REQUIRED))
					{
						token->IsHttpsRequired = args->Lookup(HTTPS_REQUIRED) == "1";
					}
					else if (token->Secret == nullptr)
					{
						token->IsHttpsRequired = true;
					}

					if (args->HasKey(CREATED))
					{
						token->Created =  _wtoi64(args->Lookup(CREATED)->Data());
					}
					else
					{
						token->Created = Util::VKUtil::CurrentTimeMillis();
					}

					return token;
				}
				catch (...)
				{
				}

				return nullptr;
			}

			VKAccessToken ^VKAccessToken::TokenFromIsolatedStorage(Platform::String ^tokenKey)
			{
				if (!Windows::Storage::ApplicationData::Current->LocalSettings->Values->HasKey(tokenKey))
				{
					return nullptr;
				}

				Platform::String ^tokenString = Windows::Storage::ApplicationData::Current->LocalSettings->Values->Lookup(tokenKey)->ToString();

				return FromUrlString(tokenString);
			}

			VKAccessToken ^VKAccessToken::TokenFromFile(Platform::String ^filename)
			{
				try
				{
					Platform::String ^data = Util::VKUtil::FileToString(filename);
					return FromUrlString(data);
				}
				catch (...)
				{
					return nullptr;
				}
			}

			bool VKAccessToken::IsExpired::get()
			{
				return ExpiresIn > 0 && ExpiresIn * 1000 + Created < Util::VKUtil::CurrentTimeMillis();
			}
		}
	}
}
