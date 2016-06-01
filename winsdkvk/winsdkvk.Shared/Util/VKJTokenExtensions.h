#pragma once


namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				public ref class VKJTokenExtensions sealed abstract
				{
					/// <summary>
					/// Parse bool from JToken with given name.
					/// </summary>
					/// <param name="json">Server response with format - field: 1</param>
					/// <param name="name">Name of field to read</param>
					/// <returns></returns>
				public:
					static bool ValueVKBool(JToken ^json, Platform::String ^name);
				};
			}
		}
	}
}
