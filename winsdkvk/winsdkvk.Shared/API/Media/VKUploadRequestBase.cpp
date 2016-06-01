#include "VKUploadRequestBase.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace winsdkvk::WindowsPhone::SDK::API::Networking;
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

					VKUploadRequestBase::VKUploadMediaOperation::VKUploadMediaOperation(Func<VKRequest^> ^getServerRequestFunc, Func<JToken^, VKRequest^> ^getSaveRequestFunc, Action<VKResponse^> ^successCallback, Action<VKError^> ^errorCallback, VKHttpOperation::FileParameter ^file)
					{
						_getSaveRequestFunc = getSaveRequestFunc;
						_getServerRequestFunc = getServerRequestFunc;

						_successCallback = successCallback;
						_errorCallback = errorCallback;

						_file = file;
					}

					void VKUploadRequestBase::VKUploadMediaOperation::Start()
					{
						State = VKOperationState::Executing;

						auto serverRequest = _getServerRequestFunc();

						serverRequest->Completed += [&] (s, o)
						{
								try
								{
									auto response = o::Response;

									auto httpRequest = WebRequest::CreateHttp(response->Content["response"]->Value<Platform::String^>("upload_url"));

									auto fileDict = ref new Dictionary<Platform::String^, VKHttpOperation::FileParameter^>();
									fileDict["file1"] = _file;
									auto uploadFileOperation = ref new VKJsonOperation(httpRequest, fileDict);

									uploadFileOperation->Completed += [&] (sender, args)
									{
											auto saveRequest = _getSaveRequestFunc(args::JsonResponse);

											saveRequest->Completed += [&] (saveSender, saveArgs)
											{

													State = VKOperationState::Finished;

													_successCallback(saveArgs::Response);
											};

											saveRequest->Error += [&] (saveSender, saveArgs)
											{
													_errorCallback(saveArgs::Error);
											};


									};

									uploadFileOperation->Failed += [&] (sender, args)
									{
											_errorCallback(args::Error);
									};

									uploadFileOperation->Start();
									_lastOperation = uploadFileOperation;


								}
								catch (HResult ^exc)
								{
									VKError ^error = ref new VKError(VKError::JSON_FAILED);
									error->HttpError = exc;
									error->ErrorMessage = exc->Message;
									_errorCallback(error);
								}

								serverRequest->Error += [&] (s1, o1)
								{
										_errorCallback(o1::Error);
								};

								_lastOperation = serverRequest->GetOperation();

								_lastOperation->Start();

						};
					}

					void VKUploadRequestBase::VKUploadMediaOperation::Cancel()
					{
						if (_lastOperation != nullptr)
						{
							_lastOperation->Cancel();
						}

						VKOperationBase::Cancel();
					}

					Networking::VKOperationBase ^VKUploadRequestBase::GetOperation()
					{
						auto file = ref new VK::WindowsPhone::SDK::API::Networking::VKHttpOperation::FileParameter(ref new Platform::Array<uint8>(0));

						return ref new VKUploadMediaOperation([&] ()
						{
							getServerRequest(), [&] (r)
							{
								getSaveRequest(r), OnSuccess, OnError, file;
							};
						});
					}

					void VKUploadRequestBase::OnError(VKError ^obj)
					{

					}

					void VKUploadRequestBase::OnSuccess(VKResponse ^obj)
					{
						throw ref new NotImplementedException();
					}

					VKUploadRequestBase::VKUploadRequestBase() : VKRequest(nullptr)
					{

					}
				}
			}
		}
	}
}
