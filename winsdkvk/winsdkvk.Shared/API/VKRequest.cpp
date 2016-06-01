#include "pch.h"
#include "VKRequest.h"

#include "../VKSDK.h"
#include "VKRequestParameters.h"
#include "VKResultCode.h"
#include "VKCaptchaUserRequest.h"
#include "VKValidationRequest.h"
#include "Util/VKHttpRequestHelper.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				/*
				VKExecuteRequest::VKExecuteRequest(Platform::String ^executeCode) : VKRequest("execute", "code", executeCode)
				{
				}
				*/

				IVKLogger ^VKRequest::Logger::get()
				{
					return VKSDK::Logger;
				}

				VKRequest ^VKRequest::Dispatch(ISerializable ^srlz, VKRequestParameters ^parameters, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc)
				{
					auto request = ref new VKRequest(parameters);

					request->Dispatch(srlz, callback, customDeserializationFunc);

					return request;
				}

				VKRequest::VKRequest(VKRequestParameters ^parameters)
				{
					InitializeWith(parameters);
				}

				VKRequest::VKRequest(Platform::String ^methodName, const Platform::Array<Platform::String^> ^parameters)
				{
					auto vkParameters = ref new VKRequestParameters(methodName, parameters);
					InitializeWith(vkParameters);
				}

				void VKRequest::InitializeWith(VKRequestParameters ^parameters)
				{
					if (parameters == nullptr)
					{
						throw ref new Platform::InvalidArgumentException("parameters");
					}

					_parameters = parameters;
				}

				TaskBR ^VKRequest::DispatchAsync(CustomDeserializationFunc ^customDeserializationFunc)
				{
					/*
						auto tc = ref new TaskCompletionSource<VKBackendResult^>();

						Dispatch([&] (res)
						{
								tc->TrySetResult(res);
						}, customDeserializationFunc);

						return tc->Task;
						*/
					return nullptr;
				}

				void VKRequest::Dispatch(ISerializable ^srlz, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc)
				{
					if (callback == nullptr)
					{
						throw ref new Platform::InvalidArgumentException("callback");
					}

					Platform::Collections::Map<Platform::String^, Platform::String^> ^parametersDict = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
					if (_parameters->Parameters != nullptr)
					{
						for (auto p : _parameters->Parameters)
						{
							parametersDict->Insert(p->Key, p->Value);
						}
					}

					DoDispatch(srlz, parametersDict, callback, customDeserializationFunc);
				}

				void VKRequest::DoDispatch(ISerializable ^srlz, Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^> ^parametersDict, TaskBR ^callback, CustomDeserializationFunc ^customDeserializationFunc)
				{
					if (!parametersDict->HasKey(ref new Platform::String(L"v")))
					{
						parametersDict->Insert(ref new Platform::String(L"v"), ref new Platform::String(API_VERSION));
					}

					auto accessToken = VKSDK::GetAccessToken();

					if (accessToken != nullptr)
					{
						parametersDict->Insert(ref new Platform::String(L"access_token"), accessToken->AccessToken);
					}

					auto dispatchUri = ref new Platform::String(REQUEST_BASE_URI_PREFIX) +_parameters->MethodName;


					Util::VKHttpRequestHelper::DispatchHTTPRequest(dispatchUri, parametersDict, ref new Util::HttpResultCallback([this, parametersDict, srlz, customDeserializationFunc, accessToken, callback] (Util::VKHttpResult ^httpResult)
					{
							if (httpResult->IsSucceeded)
							{
								auto backendResult = GetBackendResultFromString(srlz, httpResult->Data, customDeserializationFunc);

								if (backendResult->ResultCode == VKResultCode::UserAuthorizationFailed && accessToken != nullptr)
								{
									VKError ^tempVar = ref new VKError();
									tempVar->error_code = safe_cast<int32>(VKResultCode::UserAuthorizationFailed);
									VKSDK::SetAccessTokenError(tempVar);
								}
								else if (backendResult->ResultCode == VKResultCode::CaptchaRequired)
								{
									auto captchaRequest = ref new VKCaptchaUserRequest();
									captchaRequest->CaptchaSid = backendResult->Error->captcha_sid;
									captchaRequest->Url = backendResult->Error->captcha_img;

									VKSDK::InvokeCaptchaRequest(captchaRequest, ref new EventHandler<API::VKCaptchaUserResponse^>([&] (Platform::Object ^sndr, API::VKCaptchaUserResponse ^captchaResponse)
									{
											if (!captchaResponse->IsCancelled)
											{
												auto parametersWithCaptcha = ref new Map<Platform::String^, Platform::String^>();
												Platform::Collections::Map<Platform::String^, Platform::String^> ^parametersDict = nullptr;
												for (auto p : parametersDict)
												{
													parametersWithCaptcha->Insert(p->Key, p->Value);
												}

												parametersWithCaptcha->Insert(L"captcha_sid", captchaResponse->Request->CaptchaSid);
												parametersWithCaptcha->Insert(L"captcha_key", captchaResponse->EnteredString);

												DoDispatch(srlz, parametersWithCaptcha, callback, customDeserializationFunc);
											}
											else
											{
												InvokeSafely(ref new Action([&] ()
												{
													VKBackendResult ^tempVar2 = ref new VKBackendResult();
													tempVar2->ResultCode = VKResultCode::CaptchaControlCancelled;
													callback(tempVar2);
												}));
											}
									}));

								}
								else if (backendResult->ResultCode == VKResultCode::ValidationRequired)
								{
									auto validationRequest = ref new VKValidationRequest();
									validationRequest->ValidationUri = backendResult->Error->redirect_uri;

									VKSDK::InvokeValidationRequest(validationRequest, ref new EventHandler<API::VKValidationResponse^>([&] (Platform::Object ^sndr, VKValidationResponse^ vr)
									{
											if (vr->IsSucceeded)
											{
												DoDispatch(srlz, parametersDict, callback, customDeserializationFunc);
											}
											else
											{
												InvokeSafely(ref new Action([&] ()
												{
													VKBackendResult ^tempVar3 = ref new VKBackendResult();
													tempVar3->ResultCode = VKResultCode::ValidationCanceslledOrFailed;
													callback(tempVar3);
												}));
											}
									}));
								}
								else
								{
									InvokeSafely(ref new Action([&] ()
									{
										callback(backendResult);
									}));
								}
							}
							else
							{
								auto backendResult = ref new VKBackendResult();
								backendResult->ResultCode = VKResultCode::CommunicationFailed;
								InvokeSafely(ref new Action([&] ()
								{
									callback(backendResult);
								}));
							}
					}));

				}

				void VKRequest::InvokeSafely(Action ^action)
				{
					try
					{
						action();
					}
					catch (Platform::Exception ^e1)
					{
					}
				}

				VKBackendResult ^VKRequest::GetBackendResultFromString(ISerializable ^srlz, Platform::String ^dataString, CustomDeserializationFunc ^customDeserializationFunc)
				{
					auto result = ref new VKBackendResult();
					result->ResultString = dataString;

					std::wstring datastr = dataString->Data();

					if (datastr.find(ERROR_PREFIX_GENERAL) == 0)
					{
						try
						{
							auto error = ref new ErrorRoot();
							error->Deserialize(dataString);
							result->Error = error->error;

							VKResultCode resultCode = VKResultCode::UnknownError;

							if (result->Error->error_code > 1 && result->Error->error_code < 18)
							{
								resultCode = (VKResultCode)result->Error->error_code;
								result->ResultCode = resultCode;
							}
						}
						catch (Platform::Exception ^e1)
						{
							result->ResultCode = VKResultCode::UnknownError;
						}
					}
					else
					{
						result->ResultCode = VKResultCode::Succeeded;

						if (customDeserializationFunc != nullptr)
						{
							try
							{
								auto data = customDeserializationFunc(dataString);
								result->Data = data;
							}
							catch (Platform::Exception ^exc)
							{
								Logger->Error("VKRequest custom deserialization function failed on dataString=" + dataString, exc);
								result->ResultCode = VKResultCode::DeserializationError;
							}
						}
						else
						{
							try
							{
								srlz->Deserialize(dataString);
								result->Data = srlz;
							}
							catch (Platform::Exception ^exc)
							{
								Logger->Error("VKRequest deserialization failed on dataString=" + dataString, exc);
								result->ResultCode = VKResultCode::DeserializationError;
							}
						}
					}
					return result;
				}

				void VKRequest::ErrorRoot::Deserialize(Platform::String ^data)
				{
				}

				Platform::String ^ VKRequest::ErrorRoot::Serialize()
				{
					return L"";
				}
			}
		}
	}
}
