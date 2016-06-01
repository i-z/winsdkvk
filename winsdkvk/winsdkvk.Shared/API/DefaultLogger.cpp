#include "pch.h"
#include "DefaultLogger.h"

#include <sstream>

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{

				void DefaultLogger::Info(Platform::String ^info, const Platform::Array<Platform::Object^> ^formatParameters)
				{
					if (info == nullptr || info == "")
					{
						return;
					}

					Platform::String ^strToLog = info;

					std::wstringstream ss;
					ss << info->Data() << L": ";

					if (formatParameters != nullptr && formatParameters->Length > 0)
					{
						for (auto p : formatParameters)
						{
							ss << p->ToString()->Data() << L", ";
						}
					}

					SYSTEMTIME lt;
					GetLocalTime(&lt);
					wchar_t time[256];
					swprintf_s(time, L"%d:%d:%d:", lt.wHour, lt.wMinute, lt.wSecond);

					Platform::String ^debugLogMsg = ref new Platform::String(time) + strToLog;

					WriteDebugString("INFO", strToLog);
				}

				void DefaultLogger::Warning(Platform::String ^warning)
				{
					if (warning == "")
					{
						return;
					}

					WriteDebugString("WARNING", warning);
				}

				void DefaultLogger::Error(Platform::String ^error, Platform::Exception ^exc)
				{
					if (error == "")
					{
						return;
					}

					if (exc->HResult != 0)
					{
						error += GetExceptionData(exc);
					}

					WriteDebugString("ERROR", error);
				}

				void DefaultLogger::WriteDebugString(Platform::String ^logType, Platform::String ^strToLog)
				{
					//Platform::String ^debugLogMsg = DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss:fff") + ": " + logType + " " + strToLog;

					//Debug::WriteLine(debugLogMsg->Substring(0, Math::Min(500, debugLogMsg->Length)));
					OutputDebugString((logType + ">>>>>> " + strToLog)->Data());
				}

				Platform::String ^DefaultLogger::GetExceptionData(Platform::Exception ^e)
				{
					Platform::String ^excData = "e.Message = " + e->Message; //+ "\ne.Stack = " + e->StackTrace;
					/*
					if (e->InnerException != nullptr)
					{
						return excData + "\n" + GetExceptionData(e->InnerException);
					}
					*/
					return excData;
				}
			}
		}
	}
}
