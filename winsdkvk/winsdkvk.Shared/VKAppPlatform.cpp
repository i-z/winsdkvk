using namespace System;

#include "VKAppPlatform.h"
#include "VKSDK.h"

using namespace Newtonsoft::Json;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::Globalization;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace winsdkvk::WindowsPhone::SDK::API;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{

			VKAppPlatform::InAppPurchaseData::InAppPurchaseData(Platform::String ^receiptStr, Platform::String ^price)
			{
				if (Platform::String::IsNullOrWhiteSpace(receiptStr))
				{
					throw ref new ArgumentException("Invalid receipt string");
				}

				if (Platform::String::IsNullOrWhiteSpace(price))
				{
					throw ref new ArgumentException("Invalid price string");
				}

				Receipt = receiptStr;



				auto regionInfo = System::Globalization::RegionInfo::CurrentRegion;

				Currency = regionInfo->ISOCurrencySymbol;

				Price = ParsePriceStr(price);
			}

			Decimal VKAppPlatform::InAppPurchaseData::ParsePriceStr(Platform::String ^price)
			{
				// since we don't know the exact culture here, we do our best
				auto parsedValue = ToDecimal(price);
				return parsedValue;
			}

			Decimal VKAppPlatform::InAppPurchaseData::ToDecimal(Platform::String ^value)
			{
				Decimal number;
				value = ref new Platform::String(value->Where([&] (Platform::Object ^c)
				{
					return char16::IsPunctuation(c) || char16::IsNumber(c);
				}).ToArray());
				Platform::String ^tempValue = value;

				auto punctuation = value->Where([&] (Platform::Object ^x)
				{
					char16::IsPunctuation(x);
				}).Distinct();
				int32 count = punctuation->Count();

				NumberFormatInfo ^format = CultureInfo::InvariantCulture->NumberFormat;
				switch (count)
				{
					case 0:
						break;
					case 1:
						tempValue = value->Replace(",", ".");
						break;
					case 2:
						if (punctuation->ElementAt(0) == '.')
						{
							tempValue = SwapChar(value, '.', ',');
						}
						break;
					default:
						throw ref new InvalidCastException();
				}

				number = Decimal::Parse(tempValue, format);
				return number;
			}

			Platform::String ^VKAppPlatform::InAppPurchaseData::SwapChar(Platform::String ^value, char16 from, char16 to)
			{
				if (value == nullptr)
				{
					throw ref new ArgumentNullException("value");
				}

				StringBuilder ^builder = ref new StringBuilder();

				for (auto item : value)
				{
					char16 c = item;
					if (c == from)
					{
						c = to;
					}
					else if (c == to)
					{
						c = from;
					}

					builder->Append(c);
				}
				return builder->ToString();
			}

			Platform::String ^VKAppPlatform::InAppPurchaseData::ToJsonString()
			{
				auto rd = ref new ReceiptData();
				rd->receipt_data = Receipt;
				rd->price_value = Price;
				rd->currency = Currency;
				rd->quantity = 1;

				auto jsonStr = JsonConvert::SerializeObject(rd);

				return jsonStr;
			}

			VKAppPlatform ^VKAppPlatform::Instance::get()
			{
				if (_instance == nullptr)
				{
					_instance = ref new VKAppPlatform();
				}

				return _instance;
			}

			VKAppPlatform::VKAppPlatform()
			{
			}

			void VKAppPlatform::ReportInAppPurchase(InAppPurchaseData ^inAppPurchaseData)
			{
				if (inAppPurchaseData == nullptr)
				{
					throw ref new ArgumentNullException("inAppPurchaseData");
				}

				SendPurchaseData(inAppPurchaseData);
			}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private async void SendPurchaseData(InAppPurchaseData inAppPurchaseData)
			void VKAppPlatform::SendPurchaseData(InAppPurchaseData ^inAppPurchaseData)
			{
				auto vkSaveTransationRequest = ref new VKRequest("apps.saveTransaction", "platform", "winphone", "app_id", VKSDK::Instance->CurrentAppID, "device_id", VKSDK::DeviceId, "receipt", inAppPurchaseData->ToJsonString());

				bool success = false;

				int32 it = 0;

				while (!success && it < 3)
				{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
					auto result = await vkSaveTransationRequest->DispatchAsync<Platform::Object^>([&] (jsonStr)
					{
						ref new Platform::Object();
					});

					success = result->ResultCode == VKResultCode::Succeeded;

					it++;

					if (!success)
					{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
						await Task::Delay(4000);
					}
				}
			}
		}
	}
}
