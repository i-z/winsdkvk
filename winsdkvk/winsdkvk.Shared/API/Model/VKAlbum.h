#pragma once
#include "VKPrivacy.h"

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
					public ref class VKAlbum sealed
					{

					public:
						property Platform::String ^id;

						property Platform::String ^thumb_id;

						property Platform::String ^owner_id;

					private:
						Platform::String ^_title;
					public:
						property Platform::String ^title
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}


					private:
						Platform::String ^_description;
					public:
						property Platform::String ^description
						{
							Platform::String ^get();
							void set(Platform::String ^value);
						}

						property Platform::String ^created;

						property Platform::String ^updated;

						property int32 size;

						property Platform::String ^thumb_src;

						property VKPrivacy ^privacy_view;

						property VKPrivacy ^privacy_comment;

					};
				}
			}
		}
	}
}
