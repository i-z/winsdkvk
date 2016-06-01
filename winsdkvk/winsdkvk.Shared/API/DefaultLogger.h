#pragma once
#include "IVKLogger.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class DefaultLogger sealed : IVKLogger
				{
				public:
					virtual void Info(Platform::String ^info, const Platform::Array<Platform::Object^> ^formatParameters) sealed;
					virtual void Warning(Platform::String ^warning) sealed;
					virtual void Error(Platform::String ^error, Platform::Exception ^exc) sealed;

				private:
					void WriteDebugString(Platform::String ^logType, Platform::String ^strToLog);
					Platform::String ^GetExceptionData(Platform::Exception ^e);
				};
			}
		}
	}
}
