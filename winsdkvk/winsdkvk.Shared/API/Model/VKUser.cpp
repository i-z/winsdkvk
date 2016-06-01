#include "pch.h"
#include "VKUser.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Data::Json;

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
					Platform::String ^VKUser::first_name::get()
					{
						return _fName;
					}

					void VKUser::first_name::set(Platform::String ^value)
					{
						_fName = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::last_name::get()
					{
						return _lName;
					}

					void VKUser::last_name::set(Platform::String ^value)
					{
						_lName = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::activities::get()
					{
						return _activity;
					}

					void VKUser::activities::set(Platform::String ^value)
					{
						_activity = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::interests::get()
					{
						return _interests;
					}

					void VKUser::interests::set(Platform::String ^value)
					{
						_interests = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::movies::get()
					{
						return _movies;
					}

					void VKUser::movies::set(Platform::String ^value)
					{
						_movies = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::tv::get()
					{
						return _tv;
					}

					void VKUser::tv::set(Platform::String ^value)
					{
						_tv = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::books::get()
					{
						return _books;
					}

					void VKUser::books::set(Platform::String ^value)
					{
						_books = ((value != nullptr) ? value : "");//.ForUI();

					}

					Platform::String ^VKUser::games::get()
					{
						return _games;
					}

					void VKUser::games::set(Platform::String ^value)
					{
						_games = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::about::get()
					{
						return _about;
					}

					void VKUser::about::set(Platform::String ^value)
					{
						_about = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUser::quotes::get()
					{
						return _quotes;
					}

					void VKUser::quotes::set(Platform::String ^value)
					{
						_quotes = ((value != nullptr) ? value : "");//.ForUI();
					}

					Platform::String ^VKUserPersonal::inspired_by::get()
					{
						return _inspired_by;
					}

					void VKUserPersonal::inspired_by::set(Platform::String ^value)
					{
						_inspired_by = ((value != nullptr) ? value : "");//.ForUI();
					}


					void VKUser::Deserialize(Platform::String ^data)
					{
						JsonObject^ json = ref new JsonObject();
						if (JsonObject::TryParse(data, &json))
						{
							auto resp = json->Lookup("response");
							JsonObject ^response;
							if (resp->ValueType == JsonValueType::Array)
							{
								response = resp->GetArray()->First()->Current->GetObject();
								_json = response->Stringify();
								first_name = response->GetNamedString("first_name");
								last_name = response->GetNamedString("last_name");
							}
							else
							{
								_json = data;
							}
						}
					}

					Platform::String ^VKUser::Serialize()
					{
						return _json;
					}
				}
			}
		}
	}
}
