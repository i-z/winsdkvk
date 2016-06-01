using namespace System;

#include "VKObject.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{

			VKObject ^VKObject::GetRegisteredObject(int64 registeredObjectId)
			{
				VKObject ^obj = nullptr;
				RegisteredObjects->TryGetValue(registeredObjectId, obj);
				return obj;
			}

			int64 VKObject::RegisterObject()
			{
				while (true)
				{
					auto buffer = ref new Platform::Array<uint8>(sizeof(int64));
					Rand->NextBytes(buffer);
					int64 nextRand = BitConverter::ToInt64(buffer, 0);

					if (RegisteredObjects->ContainsKey(nextRand) || nextRand == 0)
					{
						continue;
					}

					RegisteredObjects->Add(nextRand, this);
					_registeredObjectId = nextRand;

					return nextRand;
				}
			}

			void VKObject::UnregisterObject()
			{
				RegisteredObjects->Remove(_registeredObjectId);
				_registeredObjectId = 0;
			}
		}
	}
}
