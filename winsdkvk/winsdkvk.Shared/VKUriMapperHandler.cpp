using namespace System;

#include "VKUriMapperHandler.h"
#include "VKSDK.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Linq;
using namespace System::Net;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace winsdkvk::WindowsPhone::SDK::Util;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{

			bool VKUriMapperHandler::HandleUri(Uri ^uri)
			{
				auto tempUriStr = uri->ToString();

				if (tempUriStr->StartsWith("/Protocol"))
				{
					auto outerQueryParamsString = VKUtil::GetParamsOfQueryString(tempUriStr);

					if (!Platform::String::IsNullOrEmpty(outerQueryParamsString))
					{
						auto outerQueryParams = VKUtil::ExplodeQueryString(outerQueryParamsString);
						if (outerQueryParams->ContainsKey("encodedLaunchUri"))
						{
							auto launchUriEncoded = outerQueryParams["encodedLaunchUri"];

							auto launchUriDecoded = WebUtility::UrlDecode(launchUriEncoded);

							if (launchUriDecoded->StartsWith("vk") && launchUriDecoded->Contains("://authorize"))
							{
								launchUriDecoded = launchUriDecoded->Replace("authorize/#", "authorize/?");

								auto innerQueryParamsString = VKUtil::GetParamsOfQueryString(launchUriDecoded);

								VKSDK::ProcessLoginResult(innerQueryParamsString, false, nullptr);

								return true;
							}
							else
							{
								// default start
								return true;
							}
						}
					}
				}
				return false;
			}
		}
	}
}
