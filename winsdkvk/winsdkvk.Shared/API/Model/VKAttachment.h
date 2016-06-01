#pragma once
#include "VKPhoto.h"
#include "VKDocument.h"
#include "VKVideo.h"
#include "VKNote.h"
#include "VKPoll.h"
#include "VKPage.h"
#include "VKLink.h"
//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKAudio; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKDocument; } } } } }
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { namespace Model { ref class VKWallPost; } } } } }

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
					public ref class VKAttachment sealed
					{
					public:
						property Platform::String ^type;

						property VKAudio ^audio;
						property VKVideo ^video;
						property VKPhoto ^photo;
						property VKPoll ^poll;
						property VKDocument ^doc;
						property VKLink ^link;
						property VKWallPost ^wall;
						property VKNote ^note;
						property VKPage ^Page;

					};
				}
			}
		}
	}
}
