#include "pch.h"
#include "StringUtil.h"

#include <sstream>

using namespace Windows::Foundation::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				Platform::String ^StrUtil::ForUI(Platform::String ^backendTextString)
				{
					/*
					if (Platform::String::IsNullOrEmpty(backendTextString))
					{
						return "";
					}

					Platform::String ^res = backendTextString;

					res = res->Replace("\r\n", "\n");

					res = res->Replace("\n", "\r\n");

					res = WebUtility::HtmlDecode(res);

					return res->Trim();
					*/
					return "";
				}

				Platform::String ^StrUtil::MakeIntoOneLine(Platform::String ^str)
				{
					/*
					if (str == nullptr)
					{
						return "";
					}

					str = str->Replace(Environment::NewLine, " ");
					str = str->Replace("\n", " ");
					return str;
					*/
					return "";
				}

				Platform::String ^StrUtil::GetCommaSeparated(IVector<Platform::String^> ^ids)
				{
					std::wstringstream ss;
					for (auto str : ids)
						ss << str->Data() << ',';
					return ref new Platform::String(ss.str().data());
				}
			}
		}
	}
}
