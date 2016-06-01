#include "pch.h"
#include "VKExecute.h"

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				void VKExecute::ExecuteOnUIThread(Action ^action)
				{
							#if defined(SILVERLIGHT)
					if (Deployment::Current->Dispatcher.CheckAccess())
					{
						action();
					}
					else
					{
						Deployment::Current->Dispatcher.BeginInvoke(action);
					}
							#else
					auto d = Windows::ApplicationModel::Core::CoreApplication::MainView::CoreWindow::Dispatcher;

					if (d->HasThreadAccess)
					{
						action();
					}
					else
					{
						d->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [&] ()
						{
								action();
						});
					}
							#endif
				}
			}
		}
	}
}
