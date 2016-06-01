#pragma once

using namespace System;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Linq;
using namespace System::Net;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace winsdkvk::WindowsPhone::SDK::Util;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKUriMapperHandler sealed abstract
			{
			public:
				static bool HandleUri(Uri ^uri);
			};
		}
	}
}
