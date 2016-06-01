#pragma once

#include "VKRequestParameters.h"
#include "IVKLogger.h"
#include "ISerializable.h"
#include "VKError.h"
#include "VKBackendResult.h"

#define REQUEST_BASE_URI_FRM L"https://api.vk.com/method/{0}"
#define REQUEST_BASE_URI_PREFIX L"https://api.vk.com/method/"
#define ERROR_PREFIX_GENERAL L"({\"error\":{)"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public delegate Platform::Object ^CustomDeserializationFunc(Platform::String^);

				public delegate void TaskBR(VKBackendResult^);

				public delegate void Action();

				public ref class VKRequest sealed
				{
				private:
					ref class ErrorRoot : ISerializable
					{
					public:
						property VKError ^error;

						virtual void Deserialize(Platform::String ^data);
						virtual Platform::String ^Serialize();
					};

					VKRequestParameters ^_parameters;

					static property IVKLogger ^Logger
					{
						IVKLogger ^get();
					}

				public:

					static VKRequest ^Dispatch(ISerializable ^srlz, VKRequestParameters ^parameters, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc);

					VKRequest(VKRequestParameters ^parameters);

					VKRequest(Platform::String ^methodName, const Platform::Array<Platform::String^> ^parameters);

					TaskBR ^DispatchAsync(CustomDeserializationFunc ^customDeserializationFunc);

					void Dispatch(ISerializable ^srlz, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc);

				private:
					void InitializeWith(VKRequestParameters ^parameters);

					void DoDispatch(ISerializable ^srlz, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parametersDict, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc);

					static void InvokeSafely(Action ^action);

					static VKBackendResult ^GetBackendResultFromString(ISerializable ^srlz, Platform::String ^dataString, CustomDeserializationFunc ^customDeserializationFunc);
				};

				public ref class GenericRoot sealed
				{
				public:
					property Platform::Object ^response;
				};

				/*
				public ref class VKExecuteRequest : VKRequest sealed
				{
				public:
					VKExecuteRequest(Platform::String ^executeCode);
				};
				*/
			}
		}
	}
}
