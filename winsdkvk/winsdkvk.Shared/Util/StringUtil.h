#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				private ref class StrUtil sealed
				{
				public:
					static Platform::String ^ForUI(Platform::String ^backendTextString);
					static Platform::String ^MakeIntoOneLine(Platform::String ^str);
					static Platform::String ^GetCommaSeparated(Windows::Foundation::Collections::IVector<Platform::String^> ^ids);
				};
			}
		}
	}
}
