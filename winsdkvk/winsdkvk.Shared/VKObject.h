#pragma once

using namespace System;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKObject
			{
			private:
				static initonly Dictionary<int64, VKObject^> ^RegisteredObjects = ref new Dictionary<int64, VKObject^>();
				int64 _registeredObjectId = 0;

				/// <summary>
				/// Returns object saved in local cache.
				/// </summary>
				/// <param name="registeredObjectId">Registered object id</param>
				/// <returns>Object saved via RegisterObject() method</returns>
			public:
				static VKObject ^GetRegisteredObject(int64 registeredObjectId);

			internal:
				Random ^Rand = ref new Random();

				/// <summary>
				/// Saves object in local cache for future use. Always call UnregisterObject() after use.
				/// </summary>
				/// <returns></returns>
			public:
				int64 RegisterObject();


				void UnregisterObject();
			};
		}
	}
}
