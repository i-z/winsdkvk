#include "pch.h"
#include "VKRequestParameters.h"

#include "Util/VKUtil.h"

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

				VKRequestParameters::VKRequestParameters(Platform::String ^methodName, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters)
				{
					InitializeWith(methodName, parameters);
				}

				VKRequestParameters::VKRequestParameters(Platform::String ^methodName, const Platform::Array<Platform::String^> ^parameters)
				{
					auto dictParameters = Util::VKUtil::DictionaryFrom(parameters);

					InitializeWith(methodName, dictParameters);
				}

				void VKRequestParameters::InitializeWith(Platform::String ^methodName, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters)
				{
					if (methodName == "")
					{
						throw ref new Platform::InvalidArgumentException("methodName");
					}

					MethodName = methodName;
					Parameters = parameters;
				}
			}
		}
	}
}
