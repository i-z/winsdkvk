#pragma once
#include "VKAttachment.h"
#include "VKGeo.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKPushSettings; } } } } }

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
					public ref class VKMessage sealed
					{

					public:
						property int64 id;

						property int64 user_id;

						property int64 date;

						property int32 read_state;

						property int32 out;

					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_body;

					public:
						property Platform::String ^body
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property Windows::Foundation::Collections::IVector<VKAttachment^> ^attachments;
						property VKGeo ^geo;
						property Windows::Foundation::Collections::IVector<VKMessage^> ^fwd_messages;

						property int32 emoji;
						property int32 important;

						property int32 deleted;

						property int64 chat_id;

						property Windows::Foundation::Collections::IVector<int64> ^chat_active;

						property int32 users_count;
						property int64 admin_id;

						property VKPushSettings ^push_settings;

					private:
						Platform::String ^_action;
					public:
						property Platform::String ^action
						{
							Platform::String ^get();

							void set(Platform::String ^value);
						}

						property int64 action_mid;

					private:
						Platform::String ^_action_email;
					public:
						property Platform::String ^action_email
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

					private:
						Platform::String ^_action_text;
					public:
						property Platform::String ^action_text
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property Platform::String ^photo_50;

						property Platform::String ^photo_100;

						property Platform::String ^photo_200;
					};

					public ref class VKPushSettings sealed
					{
					public:
						property int32 disabled_until;

						property int32 sound;
					};
				}
			}
		}
	}
}
