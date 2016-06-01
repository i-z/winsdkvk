#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				public ref class VKExecute
				{
				public:
					static void ExecuteOnUIThread(Action ^action);
				};
			}
		}
	}
}
