#include "pch.h"
#include "VKScope.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			IVector<Platform::String^> ^VKScope::ParseVKPermissionsFromInteger(int32 permissionsValue)
			{
				auto res = ref new Vector<Platform::String^>();
				if ((permissionsValue & 1) > 0)
				{
					res->Append(NOTIFY);
				}
				if ((permissionsValue & 2) > 0)
				{
					res->Append(FRIENDS);
				}
				if ((permissionsValue & 4) > 0)
				{
					res->Append(PHOTOS);
				}
				if ((permissionsValue & 8) > 0)
				{
					res->Append(AUDIO);
				}
				if ((permissionsValue & 16) > 0)
				{
					res->Append(VIDEO);
				}
				if ((permissionsValue & 128) > 0)
				{
					res->Append(PAGES);
				}
				if ((permissionsValue & 1024) > 0)
				{
					res->Append(STATUS);
				}
				if ((permissionsValue & 2048) > 0)
				{
					res->Append(NOTES);
				}
				if ((permissionsValue & 4096) > 0)
				{
					res->Append(MESSAGES);
				}
				if ((permissionsValue & 8192) > 0)
				{
					res->Append(WALL);
				}
				if ((permissionsValue & 32768) > 0)
				{
					res->Append(ADS);
				}
				if ((permissionsValue & 65536) > 0)
				{
					res->Append(OFFLINE);
				}
				if ((permissionsValue & 131072) > 0)
				{
					res->Append(DOCS);
				}
				if ((permissionsValue & 262144) > 0)
				{
					res->Append(GROUPS);
				}
				if ((permissionsValue & 524288) > 0)
				{
					res->Append(NOTIFICATIONS);
				}
				if ((permissionsValue & 1048576) > 0)
				{
					res->Append(STATS);
				}
				return res;
			}
		}
	}
}
