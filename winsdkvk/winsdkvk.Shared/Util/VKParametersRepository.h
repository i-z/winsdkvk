#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				/// <summary>
				/// Holds parameters for data exchange between pages
				/// </summary>
				private ref class VKParametersRepository
				{
				private:
					static Dictionary<Platform::String^, Platform::Object^> ^_parametersDict = ref new Dictionary<Platform::String^, Platform::Object^>();

				public:
					static void SetParameterForId(Platform::String ^paramId, Platform::Object ^parameter);

					static Platform::Object ^GetParameterForIdAndReset(Platform::String ^paramId);

					static bool Contains(Platform::String ^key);
				};
			}
		}
	}
}
