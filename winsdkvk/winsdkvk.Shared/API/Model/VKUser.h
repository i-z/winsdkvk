#pragma once
#include "VKCountry.h"
#include "VKCity.h"
#include "VKAudio.h"
#include "API/ISerializable.h"

#define OCCUPATION_TYPE_WORK "work"
#define OCCUPATION_TYPE_SCHOOL "school"
#define OCCUPATION_TYPE_UNIVERSITY "university"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKUniversity; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKSchool; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKCounters; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKUserOccupation; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKUserRelative; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKUserPersonal; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKUserExports; } } } } }

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
					/// https://vk.com/dev/fields
					/// </summary>
					public ref class VKUser sealed : ISerializable
					{
						Platform::String ^_json;
					public:
						property int64 id;

					private:
						Platform::String ^_fName;
					public:
						property Platform::String ^first_name
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_lName;
					public:
						property Platform::String ^last_name
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property Platform::String ^deactivated;

						property int32 hidden;

						property int32 verified;

						property int32 blacklisted;

						property int32 sex;

						property Platform::String ^bdate;

						property VKCity ^city;

						property VKCountry ^country;

						property Platform::String ^home_town;

						property Platform::String ^photo_50;

						property Platform::String ^photo_100;

						property Platform::String ^photo_200_orig;

						property Platform::String ^photo_200;

						property Platform::String ^photo_400_orig;

						property Platform::String ^photo_max;

						property Platform::String ^photo_max_orig;

						property int32 online;

						property Windows::Foundation::Collections::IVector<int64> ^lists;

						property Platform::String ^domain;

						property int32 has_mobile;

						property Platform::String ^mobile_phone;

						property Platform::String ^home_phone;

						property Platform::String ^site;



						property int64 university;

						property Platform::String ^university_name;

						property int64 faculty;

						property Platform::String ^faculty_name;

						property int32 graduation;


						property Windows::Foundation::Collections::IVector<VKUniversity^> ^universities;

						property Windows::Foundation::Collections::IVector<VKSchool^> ^schools;

						property Platform::String ^status;

						property VKAudio ^status_audio;

						property int32 followers_count;

						property int32 common_count;

						property VKCounters ^counters;

						property VKUserOccupation ^occupation;

						property Platform::String ^nickname;

						property Windows::Foundation::Collections::IVector<VKUserRelative^> ^relatives;

						property int32 relation;

						property VKUserPersonal ^personal;

						property Platform::String ^facebook;

						property Platform::String ^twitter;

						property Platform::String ^livejournal;

						property Platform::String ^instagram;


						property VKUserExports ^exports;

						property int32 wall_comments;

					private:
						Platform::String ^_activity;
					public:
						property Platform::String ^activities
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}


					private:
						Platform::String ^_interests;
					public:
						property Platform::String ^interests
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_movies;
					public:
						property Platform::String ^movies
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_tv;
					public:
						property Platform::String ^tv
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_books;
					public:
						property Platform::String ^books
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_games;
					public:
						property Platform::String ^games
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_about;
					public:
						property Platform::String ^about
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_quotes;
					public:
						property Platform::String ^quotes
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}


						property int32 can_post;

						property int32 can_see_all_posts;

						property int32 can_see_audio;

						property int32 can_write_private_message;

						property int32 timezone;

						property Platform::String ^screen_name;

						property Platform::String ^maiden_name;

						virtual void Deserialize(Platform::String ^data);
						virtual Platform::String ^Serialize();
					};


					public ref class VKUserExports sealed
					{
					public:
						property int32 twitter;

						property int32 facebook;

						property int32 livejournal;

						property int32 instagram;
					};

					public ref class VKUserPersonal sealed
					{
					public:
						property int32 political;

						property Windows::Foundation::Collections::IVector<Platform::String^> ^langs;

						property Platform::String ^religion;


					private:
						Platform::String ^_inspired_by;
					public:
						property Platform::String ^inspired_by
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property int32 people_main;

						property int32 life_main;

						property int32 smoking;

						property int32 alcohol;
					};

					public ref class VKUserRelative sealed
					{
					public:
						property int64 id;

						property Platform::String ^name;

						property Platform::String ^type;
					};

					public ref class VKUserOccupation sealed
					{
					public:

						property Platform::String ^type;

						property int64 id;

						property Platform::String ^name;
					};

					public ref class VKCounters sealed
					{

					public:
						property int32 albums;

						property int32 videos;

						property int32 audios;

						property int32 notes;
						property int32 groups;

						property int32 photos;
						property int32 friends;
						property int32 online_friends;
						property int32 mutual_friends;
						property int32 user_videos;
						property int32 user_photos;
						property int32 followers;
						property int32 subscriptions;

						property int32 topics;
						property int32 docs;

						property int32 pages;

					};


					public ref class VKUserStatus sealed
					{
					public:
						property int64 time;

						property int32 platform;
					};

					public ref class VKUniversity sealed
					{
					public:
						property int64 id;

						property int64 country;

						property int64 city;

						property Platform::String ^name;

						property int64 faculty;

						property Platform::String ^faculty_name;

						property int64 chair;

						property Platform::String ^chair_name;

						property int32 graduation;

					};

					public ref class VKSchool sealed
					{
					public:
						property int64 id;

						property int64 country;

						property int64 city;

						property Platform::String ^name;

						property int32 year_from;

						property int32 year_to;

						property int32 year_graduated;

						property Platform::String ^class_Renamed;

						property Platform::String ^speciality;

						property int64 type;

						property Platform::String ^type_str;

					};
				}
			}
		}
	}
}
