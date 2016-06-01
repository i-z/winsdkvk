using namespace System;

#include "VKParametersRepository.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Diagnostics;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading::Tasks;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				void VKParametersRepository::SetParameterForId(Platform::String ^paramId, Platform::Object ^parameter)
				{
					Debug::Assert(!Platform::String::IsNullOrEmpty(paramId));

					_parametersDict[paramId] = parameter;
				}

				Platform::Object ^VKParametersRepository::GetParameterForIdAndReset(Platform::String ^paramId)
				{
					if (_parametersDict->ContainsKey(paramId))
					{
						auto result = _parametersDict[paramId];

						_parametersDict->Remove(paramId);

						return result;
					}

					return nullptr;
				}

				bool VKParametersRepository::Contains(Platform::String ^key)
				{
					return _parametersDict->ContainsKey(key);
				}
			}
		}
	}
}
