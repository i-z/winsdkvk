#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public interface class IVKLogger
				{
					void Info(Platform::String ^info, const Platform::Array<Platform::Object^> ^formatParameters);
					void Warning(Platform::String ^warning);
					void Error(Platform::String ^error, Platform::Exception ^exc);
				};

			}
		}
	}
}
