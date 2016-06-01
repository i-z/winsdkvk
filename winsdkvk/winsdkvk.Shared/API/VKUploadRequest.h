#pragma once
//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace winsdkvk { namespace WindowsPhone { namespace SDK { namespace API { generic<typename T>ref class VKBackendResult; } } } }

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace API
			{
				public ref class VKUploadRequest
				{

				private:
					ref class VKUploadServerAddress
					{
					public:
						property Platform::String ^upload_url;
					};

				private:
					ref class VKUploadResponseData
					{
					public:
						property Platform::String ^server;

						property Platform::String ^photo;

						property Platform::String ^photos_list;

						property Platform::String ^hash;

						property Platform::String ^aid;

						property int64 uid;

						property int64 gid;
					};

				private:
					enum class UploadType
					{
						PhotoAlbumUpload,
						PhotoWallUpload,
						PhotoProfileUpload,
						PhotoMessageUpload
					};

				private:
					UploadType _uploadType = safe_cast<UploadType>(0);

					int64 _albumId = 0;

					int64 _ownerId = 0;

					int64 _groupId = 0;

				protected:
					VKUploadRequest();

				public:
					static VKUploadRequest ^CreatePhotoAlbumUploadRequest(int64 albumId, int64 groupId = 0);

					static VKUploadRequest ^CreatePhotoWallUploadRequest(int64 ownerId = 0);

					static VKUploadRequest ^CreatePhotoProfileUploadRequest(int64 ownerId);

					static VKUploadRequest ^CreatePhotoMessageUploadRequest();

					void Dispatch(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback);

				private:
					void DispatchPhotoWallUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback);

					void DispatchPhotoProfileUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback);

					void DispatchPhotoMessageUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback);

					void DispatchPhotoAlbumUpload(Stream ^photoStream, Action<float64> ^progressCallback, Action<VKBackendResult<VKPhoto^>^> ^callback);

					void UploadPhoto(Stream ^photoStream, Platform::String ^getServerMethodName, Dictionary<Platform::String^, Platform::String^> ^parameters, Platform::String ^saveMethodName, bool saveReturnsList, Action<VKBackendResult<VKPhoto^>^> ^callback, Action<float64> ^progressCallback);
				};
			}
		}
	}
}
