#pragma once
#include "VKGeo.h"
#include "VKAttachment.h"
//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKComments; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKLikes; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKReposts; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKPostSource; } } } } }

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
					/// https://vk.com/dev/post
					/// </summary>
					public ref class VKWallPost sealed
					{
					public:
						property int64 id;

						property int64 owner_id;

						property int64 from_id;

						property int64 date;

						property Platform::String ^text;

						property int64 reply_owner_id;

						property int64 reply_post_id;

						property int32 friends_only;

						property VKComments ^comments;

						property VKLikes ^likes;

						property VKReposts ^reposts;

						property Platform::String ^post_type;

						property VKPostSource ^post_source;

						property Windows::Foundation::Collections::IVector<VKAttachment^> ^attachments;

						property VKGeo ^geo;

						property int64 signer_id;

						property Windows::Foundation::Collections::IVector<VKWallPost^> ^copy_history;

						property int32 can_pin;

						property int32 is_pinned;
					};

					public ref class VKComments sealed
					{
					public:
						property int32 count;
						property int32 can_post;

					};

					public ref class VKLikes sealed
					{
					public:
						property int32 count;
						property int32 user_likes;
						property int32 can_like;
						property int32 can_publish;
					};

					public ref class VKReposts sealed
					{
					public:
						property int32 count;
						property int32 user_reposted;
					};

					public ref class VKPostSource sealed
					{
					public:
						property Platform::String ^platform;
						property Platform::String ^type;
						property Platform::String ^data;
					};
				}
			}
		}
	}
}
