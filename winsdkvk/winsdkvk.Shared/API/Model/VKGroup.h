#pragma once
#include "VKUser.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKPlace; } } } } }

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
				   /// <summary>
				   /// https://vk.com/dev/fields_groups
				   /// </summary>
					public ref class VKGroup sealed
					{
					public:
						property int64 id;

						property Platform::String ^name;

						property Platform::String ^screen_name;

						property int32 is_closed;

						property Platform::String ^deactivated;

						property int32 is_admin;

						property int32 admin_level;

						property int32 is_member;

						property Platform::String ^type;

						property Platform::String ^photo_50;

						property Platform::String ^photo_100;

						property Platform::String ^photo_200;

						property int64 city;

						property int64 country;

						property VKPlace ^place;

					private:
						Platform::String ^_desc;
					public:
						property Platform::String ^description
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property Platform::String ^wiki_page;

						property int32 members_count;

						property VKCounters ^counters;

						property int64 start_date;

						property int64 finish_date;

						property int32 can_post;

						property int32 can_see_all_posts;

						property int32 can_upload_doc;

						property int32 can_create_topic;

						property Platform::String ^activity;

						property Platform::String ^status;

						property Platform::String ^contacts;

						property Platform::String ^links;

						property int64 fixed_post;

						property int32 verified;

						property Platform::String ^site;

					};

					public ref class VKPlace sealed
					{
					public:
						property int64 id;

						property Platform::String ^title;

						property int32 latitude;

						property int32 longitude;

						property Platform::String ^type;

						property int64 country;

						property int64 city;

						property Platform::String ^address;
					};
				}
			}
		}
	}
}
