#pragma once
#include "VKPlace.h"

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
					public ref class VKGeo sealed
					{
					public:
						property Platform::String ^type;
						property Platform::String ^coordinates;

						property Place ^place;
					};
				}
			}
		}
	}
}
