using namespace System;

#include "VKUploadRequest.h"
#include "VKBackendResult.h"
#include "VKRequestParameters.h"
#include "VKRequest.h"
#include "VKResultCode.h"

using namespace Newtonsoft::Json;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace System::IO;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace winsdkvk::WindowsPhone::SDK::API::Model;
using namespace winsdkvk::WindowsPhone::SDK::Util;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{

				VKUploadRequest::VKUploadRequest()
				{
				}

				VKUploadRequest ^VKUploadRequest::CreatePhotoAlbumUploadRequest(int64 albumId, int64 groupId)
				{
					auto uploadRequest = ref new VKUploadRequest();

					uploadRequest->_uploadType = UploadType::PhotoAlbumUpload;
					uploadRequest->_albumId = albumId;
					uploadRequest->_groupId = groupId;

					return uploadRequest;
				}

				VKUploadRequest ^VKUploadRequest::CreatePhotoWallUploadRequest(int64 ownerId)
				{
					auto uploadRequest = ref new VKUploadRequest();

					uploadRequest->_uploadType = UploadType::PhotoWallUpload;
					uploadRequest->_ownerId = ownerId;

					return uploadRequest;
				}

				VKUploadRequest ^VKUploadRequest::CreatePhotoProfileUploadRequest(int64 ownerId)
				{
					auto uploadRequest = ref new VKUploadRequest();

					uploadRequest->_uploadType = UploadType::PhotoProfileUpload;
					uploadRequest->_ownerId = ownerId;

					return uploadRequest;
				}

				VKUploadRequest ^VKUploadRequest::CreatePhotoMessageUploadRequest()
				{
					auto uploadRequest = ref new VKUploadRequest();

					uploadRequest->_uploadType = UploadType::PhotoMessageUpload;

					return uploadRequest;
				}

				void VKUploadRequest::Dispatch(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback)
				{
					switch (_uploadType)
					{
						case UploadType::PhotoAlbumUpload:
							DispatchPhotoAlbumUpload(photoStream, progressCallback, callback);
							break;
						case UploadType::PhotoMessageUpload:
							DispatchPhotoMessageUpload(photoStream, progressCallback, callback);
							break;
						case UploadType::PhotoProfileUpload:
							DispatchPhotoProfileUpload(photoStream, progressCallback, callback);
							break;
						case UploadType::PhotoWallUpload:
							DispatchPhotoWallUpload(photoStream, progressCallback, callback);
							break;
					}
				}

				void VKUploadRequest::DispatchPhotoWallUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback)
				{
					auto parameters = ref new Dictionary<Platform::String^, Platform::String^>();
					if (_ownerId != 0)
					{
						Platform::String ^paramName = _ownerId < 0 ? "group_id" : "user_id";

						parameters[paramName] = Math::Abs(_ownerId).ToString();
					}

					UploadPhoto(photoStream, "photos.getWallUploadServer", parameters, "photos.saveWallPhoto", true, callback, progressCallback);
				}

				void VKUploadRequest::DispatchPhotoProfileUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback)
				{
					auto parameters = ref new Dictionary<Platform::String^, Platform::String^>();

					UploadPhoto(photoStream, "photos.getProfileUploadServer", parameters, "photos.saveProfilePhoto", false, callback, progressCallback);
				}

				void VKUploadRequest::DispatchPhotoMessageUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback)
				{
					auto parameters = ref new Dictionary<Platform::String^, Platform::String^>();

					UploadPhoto(photoStream, "photos.getMessagesUploadServer", parameters, "photos.saveMessagesPhoto", true, callback, progressCallback);
				}

				void VKUploadRequest::DispatchPhotoAlbumUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback)
				{
					auto parameters = ref new Dictionary<Platform::String^, Platform::String^>();

					parameters["album_id"] = _albumId.ToString();

					if (_groupId != 0)
					{
						parameters["group_id"] = _groupId.ToString();
					}


					UploadPhoto(photoStream, "photos.getUploadServer", parameters, "photos.save", true, callback, progressCallback);
				}

				void VKUploadRequest::UploadPhoto(Stream ^photoStream, Platform::String ^getServerMethodName, Dictionary<Platform::String^, Platform::String^> ^parameters, Platform::String ^saveMethodName, bool saveReturnsList, Action<VKBackendResult<VKPhoto^>^> ^callback, Action<float64> ^progressCallback)
				{

					auto vkParams = ref new VKRequestParameters(getServerMethodName, parameters);

					auto getServerRequest = ref new VKRequest(vkParams);

					getServerRequest->Dispatch<VKUploadServerAddress^>([&] (res)
					{
						   if (res->ResultCode == VKResultCode::Succeeded)
						   {
							   auto uploadUrl = res::Data->upload_url;

							   VKHttpRequestHelper::Upload(uploadUrl, photoStream, "file1", "image", [&] (uploadRes)
							   {
										if (uploadRes::IsSucceeded)
										{
											auto serverPhotoHashJson = uploadRes::Data;

											auto uploadData = JsonConvert::DeserializeObject<VKUploadResponseData^>(serverPhotoHashJson);

											if (!Platform::String::IsNullOrWhiteSpace(uploadData->server))
											{
												parameters["server"] = uploadData->server;
											}
											if (!Platform::String::IsNullOrWhiteSpace(uploadData->photos_list))
											{
												parameters["photos_list"] = uploadData->photos_list;
											}
											if (!Platform::String::IsNullOrWhiteSpace(uploadData->hash))
											{
												parameters["hash"] = uploadData->hash;
											}
											if (!Platform::String::IsNullOrWhiteSpace(uploadData->photo))
											{
												parameters["photo"] = uploadData->photo;
											}

											auto saveWallPhotoVKParams = ref new VKRequestParameters(saveMethodName, parameters);

											auto saveWallPhotoRequest = ref new VKRequest(saveWallPhotoVKParams);

											saveWallPhotoRequest->Dispatch(callback, [&] (jsonStr)
											{
													if (saveReturnsList)
													{
														auto resp = JsonConvert::DeserializeObject<GenericRoot<List<VKPhoto^>^>^>(jsonStr);

														return resp->response.First();
													}
													else
													{
														auto resp = JsonConvert::DeserializeObject<GenericRoot<VKPhoto^>^>(jsonStr);

														return resp->response;
													}
											});

										}
										else
										{
											VKBackendResult<VKPhoto^> ^tempVar = ref new VKBackendResult<VKPhoto^>();
											tempVar->ResultCode = VKResultCode::UnknownError;
											callback(tempVar);
										}
							   }, progressCallback, "Image.jpg");
						   }
						   else
						   {
							   VKBackendResult<VKPhoto^> ^tempVar2 = ref new VKBackendResult<VKPhoto^>();
							   tempVar2->ResultCode = res::ResultCode;
							   tempVar2->Error = res::Error;
							   callback(tempVar2);
						   }
					});
				}
			}
		}
	}
}
