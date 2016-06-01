#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			public ref class VKAppPlatform
			{
			public:
				ref class InAppPurchaseData
				{
				public:
					ref class ReceiptData
					{
					public:
						property Platform::String ^receipt_data;
						property Decimal price_value;
						property Platform::String ^currency;
						property int32 quantity;
					};

				public:
					property Platform::String ^Receipt;
					property Decimal Price;
					property Platform::String ^Currency;

					InAppPurchaseData(Platform::String ^receiptStr, Platform::String ^price);

				private:
					Decimal ParsePriceStr(Platform::String ^price);


					/// <summary>
					/// Convert string value to decimal ignore the culture.
					/// </summary>
					/// <param name="value">The value.</param>
					/// <returns>Decimal value.</returns>
				public:
					static Decimal ToDecimal(Platform::String ^value);
					/// <summary>
					/// Swaps the char.
					/// </summary>
					/// <param name="value">The value.</param>
					/// <param name="from">From.</param>
					/// <param name="to">To.</param>
					/// <returns></returns>
					static Platform::String ^SwapChar(Platform::String ^value, char16 from, char16 to);

				internal:
					Platform::String ^ToJsonString();
				};


			private:
				static VKAppPlatform ^_instance;

			public:
				static property VKAppPlatform ^Instance
				{
					VKAppPlatform ^get();
				}

			protected:
				VKAppPlatform();

			public:
				void ReportInAppPurchase(InAppPurchaseData ^inAppPurchaseData);

			private:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: private async void SendPurchaseData(InAppPurchaseData inAppPurchaseData)
				void SendPurchaseData(InAppPurchaseData ^inAppPurchaseData);

			};
		}
	}
}
