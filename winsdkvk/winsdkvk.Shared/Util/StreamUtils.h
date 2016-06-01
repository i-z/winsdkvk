#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{
				public ref class StreamUtils sealed abstract
				{
				public:
					static void CopyStream(Stream ^input, Stream ^output, Action<float64> ^progressCallback = nullptr);

					static MemoryStream ^ReadFully(Stream ^input);

					static Platform::Array<uint8> ^ReadFullyToByteArray(Stream ^input);
				};
			}
		}
	}
}
