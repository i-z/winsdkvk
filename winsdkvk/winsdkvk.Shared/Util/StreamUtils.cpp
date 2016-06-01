using namespace System;

#include "StreamUtils.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Diagnostics;
using namespace System::IO;
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

				void StreamUtils::CopyStream(Stream ^input, Stream ^output, Action<float64> ^progressCallback)
				{
					Debug::WriteLine("STREAMUTILS.COPYSTREAM: " + input->Length);
					Platform::Array<uint8> ^buffer = ref new Platform::Array<uint8>(32768);
					int32 read;
					int32 totalcopied = 0;
					while ((read = input->Read(buffer, 0, buffer->Length)) > 0)
					{
						output->Write(buffer, 0, read);
						totalcopied += read;

						Debug::WriteLine("STREAMUTILS.COPYSTREAM COPIED " + totalcopied + " out of " + input->Length);

						if (progressCallback != nullptr)
						{
							if (input->Length > 0)
							{
								progressCallback(((safe_cast<float64>(totalcopied)) * 100) / input->Length);
							}
						}
					}
				}

				MemoryStream ^StreamUtils::ReadFully(Stream ^input)
				{
					Platform::Array<uint8> ^buffer = ref new Platform::Array<uint8>(16 * 1024);
					MemoryStream ^ms = ref new MemoryStream();

					int32 read;
					while ((read = input->Read(buffer, 0, buffer->Length)) > 0)
					{
						ms->Write(buffer, 0, read);
					}
					return ms;

				}

				Platform::Array<uint8> ^StreamUtils::ReadFullyToByteArray(Stream ^input)
				{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (MemoryStream ms = new MemoryStream())
					{
						MemoryStream ^ms = ref new MemoryStream();
						input->CopyTo(ms);
						return ms->ToArray();
						delete ms;
					}
				}
			}
		}
	}
}
