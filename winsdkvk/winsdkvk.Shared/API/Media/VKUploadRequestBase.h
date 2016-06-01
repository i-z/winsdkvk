#pragma once

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				namespace Media
				{
					public ref class VKUploadRequestBase abstract : VKRequest
					{
					private:
						ref class VKUploadMediaOperation : VKOperationBase
						{
						private:
							VKOperationBase ^_lastOperation;

							Func<VKRequest^> ^_getServerRequestFunc;
							Func<JToken^, VKRequest^> ^_getSaveRequestFunc;

							Action<VKResponse^> ^_successCallback;
							Action<VKError^> ^_errorCallback;

							VKHttpOperation::FileParameter ^_file;

						public:
							VKUploadMediaOperation(Func<VKRequest^> ^getServerRequestFunc, Func<JToken^, VKRequest^> ^getSaveRequestFunc, Action<VKResponse^> ^successCallback, Action<VKError^> ^errorCallback, VKHttpOperation::FileParameter ^file);

							virtual void Start() override;

							virtual void Cancel() override;

						};

					protected:
						virtual VKRequest ^getServerRequest() abstract;

						virtual VKRequest ^getSaveRequest(JToken ^response) abstract;

					public:
						virtual Networking::VKOperationBase ^GetOperation() override;

					private:
						void OnError(VKError ^obj);

						void OnSuccess(VKResponse ^obj);

					public:
						VKUploadRequestBase();

					};
				}
			}
		}
	}
}
