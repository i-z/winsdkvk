#pragma once


namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKScope sealed
			{
			public:
				static property Platform::String ^NOTIFY        { Platform::String ^get() { return ref new Platform::String(L"notify"		);}};
				static property Platform::String ^FRIENDS       { Platform::String ^get() { return ref new Platform::String(L"friends"		);}};
				static property Platform::String ^PHOTOS        { Platform::String ^get() { return ref new Platform::String(L"photos"		);}};
				static property Platform::String ^AUDIO         { Platform::String ^get() { return ref new Platform::String(L"audio"		);}};
				static property Platform::String ^VIDEO         { Platform::String ^get() { return ref new Platform::String(L"video"		);}};
				static property Platform::String ^DOCS          { Platform::String ^get() { return ref new Platform::String(L"docs"			);}};
				static property Platform::String ^NOTES         { Platform::String ^get() { return ref new Platform::String(L"notes"		);}};
				static property Platform::String ^PAGES         { Platform::String ^get() { return ref new Platform::String(L"pages"		);}};
				static property Platform::String ^STATUS        { Platform::String ^get() { return ref new Platform::String(L"status"		);}};
				static property Platform::String ^WALL          { Platform::String ^get() { return ref new Platform::String(L"wall"			);}};
				static property Platform::String ^GROUPS        { Platform::String ^get() { return ref new Platform::String(L"groups"		);}};
				static property Platform::String ^MESSAGES      { Platform::String ^get() { return ref new Platform::String(L"messages"		);}};
				static property Platform::String ^NOTIFICATIONS { Platform::String ^get() { return ref new Platform::String(L"notifications");}};
				static property Platform::String ^STATS         { Platform::String ^get() { return ref new Platform::String(L"stats"		);}};
				static property Platform::String ^ADS           { Platform::String ^get() { return ref new Platform::String(L"ads"			);}};
				static property Platform::String ^OFFLINE       { Platform::String ^get() { return ref new Platform::String(L"offline"		);}};
				static property Platform::String ^NOHTTPS       { Platform::String ^get() { return ref new Platform::String(L"nohttps"		);}};
				static property Platform::String ^DIRECT        { Platform::String ^get() { return ref new Platform::String(L"direct"		);}};
				/// <summary>
				/// Converts integer permissions value into List of constants
				/// </summary>
				/// <param name="permissionsValue">Integer permissons value</param>
				/// <returns>List containing constant strings of permissions (scope)</returns>
				static Windows::Foundation::Collections::IVector<Platform::String^> ^ParseVKPermissionsFromInteger(int32 permissionsValue);
			};
		}
	}
}
