#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class VKRequestParameters sealed
				{
				public:
					property Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^Parameters;
					property Platform::String ^MethodName;

					VKRequestParameters(Platform::String ^methodName, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters);
					VKRequestParameters(Platform::String ^methodName, const Platform::Array<Platform::String^> ^parameters);

				private:
					void InitializeWith(Platform::String ^methodName, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parameters);
				};

				public ref class VKRequestParam sealed
				{
				public:
					property Platform::String ^key;
					property Platform::String ^value;
				};
			}
		}
	}
}
