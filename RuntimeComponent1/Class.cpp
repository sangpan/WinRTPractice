#include "pch.h"
#include "Class.h"
#include "Class.g.cpp"

#include "P1.h"
#include <winrt/Windows.System.Diagnostics.h>
//#include <winrt/base.h>
#include "ViewLifetimeControl.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;


using namespace Windows::UI::WindowManagement;
using namespace Windows::UI::Xaml::Hosting;

using namespace Windows::ApplicationModel::Core;


using namespace Windows::Foundation::Collections;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Core;
using namespace Windows::System::Diagnostics;

using namespace Windows::System;

namespace winrt::RuntimeComponent1::implementation
{
    
    Windows::UI::Core::CoreDispatcher Class::MainDispatcher{ nullptr };

    int32_t Class::MyProperty()
    {
        return 0;
    }

    void Class::MyProperty(int32_t /* value */)
    {
    }
    // ApplicationView
    fire_and_forget Class::showAppView()
    {
        if (!MainDispatcher)
        {
            MainDispatcher = Window::Current().Dispatcher();
        }
        winrt::apartment_context ui_thread;
        //auto lifetime = get_strong();
        co_await resume_foreground(CoreApplication::CreateNewView().Dispatcher());
        //auto newViewControl = ViewLifetimeControl::CreateForCurrentView();
        //newViewControl.Title(DEFAULT_TITLE);
        // Increment the ref count because we just created the view and we have a reference to it                
        //newViewControl.StartViewInUse();
        Controls::Frame frame;
        frame.Navigate(xaml_typename<RuntimeComponent1::P1>());
        Window::Current().Content(frame);
        // This is a change from 8.1: In order for the view to be displayed later it needs to be activated.
        Window::Current().Activate();
        //ApplicationView::GetForCurrentView().Title(newViewControl.Title());
        // Be careful! This collection is bound to the main thread,
        // so make sure to update it only from that thread.
        //co_await resume_foreground(MainDispatcher);


        // We are now back in the main window.
        //SampleState::SecondaryViews.Append(newViewControl);
        //bool viewShown = await ApplicationViewSwitcher.TryShowAsStandaloneAsync(newViewId);
        auto newWindow = CoreWindow::GetForCurrentThread();
        //m_dispatcher = newWindow.Dispatcher();
        //m_window = newWindow;
        int32_t m_viewId = ApplicationView::GetApplicationViewIdForWindow(newWindow);
        //bool viewShown = co_await ApplicationViewSwitcher::TryShowAsStandaloneAsync(
            //m_viewId);
        //newViewControl.StartViewInUse();

        bool viewShown = co_await ApplicationViewSwitcher::TryShowAsStandaloneAsync(
            m_viewId);
        //newViewControl.StopViewInUse();

    }
    fire_and_forget Class::showAppView2()
    {
        co_return;
    }
    // appWindow
    IAsyncAction showTestPage() {
        // Create a new window
        auto appWindow = co_await AppWindow::TryCreateAsync();
        // Clean up when the window is closed
        //appWindow.Closed({ get_weak(), &Scenario1_SecondaryWindow::OnWindowClosed });
        // Navigate the frame to the page we want to show in the new window
        Windows::UI::Xaml::Controls::Frame appWindowFrame{};
        appWindowFrame.Navigate(xaml_typename<RuntimeComponent1::P1>());
        // Attach the XAML content to our window
        ElementCompositionPreview::SetAppWindowContent(appWindow, appWindowFrame);
        appWindow.TryShowAsync();

        co_return;
    }
	void Class::showP1()
	{
        // Use AppWindow
        //showTestPage();

        //Use ApplicationView
        //showAppView();
        //showAppView2();

        // Change Just Current Frame
        Frame rootFrame{ nullptr };
        auto content = Window::Current().Content();
        if (content)
        {
            rootFrame = content.try_as<Frame>();
        }
         hstring parameter = L"The information that you wish to send to the next page.";

        if (rootFrame == nullptr)
        {
            // Create a Frame to act as the navigation context and associate it with
            // a SuspensionManager key
            rootFrame = Frame();
            if (rootFrame.Content() == nullptr)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter

                rootFrame.Navigate(xaml_typename<RuntimeComponent1::P1>(), box_value(parameter));
            }
            // Place the frame in the current Window
            //Window::Current().Content(rootFrame);
            // Ensure the current window is active
            Window::Current().Activate();
        }
        else {
            rootFrame.Navigate(xaml_typename<RuntimeComponent1::P1>(), box_value(parameter));
        }
    }
}
