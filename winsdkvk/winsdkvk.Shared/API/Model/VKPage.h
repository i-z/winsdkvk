#pragma once

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
					public ref class VKPage sealed
					{
					public:
						property int64 id;
						property int64 group_id;
						property int64 creator_id;
						property Platform::String ^title;
						property int32 current_user_can_edit;
						property int32 current_user_can_edit_access;
						property int32 who_can_view;
						property int32 who_can_edit;
						property int32 edited;
						property int32 created;
						property int64 editor_id;
						property int32 views;
						property Platform::String ^parent;
						property Platform::String ^parent2;
						property Platform::String ^source;
						property Platform::String ^html;
						property Platform::String ^view_url;
					};
				}
			}
		}
	}
}
