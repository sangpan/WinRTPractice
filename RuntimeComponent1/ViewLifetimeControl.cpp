﻿#include "pch.h"
#include "ViewLifetimeControl.h"
#if __has_include("ViewLifetimeControl.g.cpp")
#include "ViewLifetimeControl.g.cpp"
#endif
using namespace winrt;
using namespace RuntimeComponent1;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Data;

namespace winrt::RuntimeComponent1::implementation
{
    // A ViewLifetimeControl is instantiated for every secondary view.ViewLifetimeControl's reference count
    // keeps track of when the secondary view thinks it's in use and when the main view is interacting with the secondary view (about to show
    // it to the user, etc.) When the reference count drops to zero, the secondary view is closed.
    // Instantiate views using "CreateForCurrentView".
    ViewLifetimeControl::ViewLifetimeControl(CoreWindow const& newWindow)
    {
        m_dispatcher = newWindow.Dispatcher();
        m_window = newWindow;
        m_viewId = ApplicationView::GetApplicationViewIdForWindow(newWindow);

        // This class will automatically tell the view when its time to close
        // or stay alive in a few cases
        RegisterForEvents();
    }

    // Register for events on the current view

    void ViewLifetimeControl::RegisterForEvents()
    {
        // A view is consolidated with other views when there's no way for the user to get to it (it's not in the list of recently used apps, cannot be
        // launched from Start, etc.) A view stops being consolidated when it's visible--at that point the user can interact with it, move it on or off screen, etc. 
        // It's generally a good idea to close a view after it has been consolidated, but keep it open while it's visible.
        m_consolidatedToken = ApplicationView::GetForCurrentView().Consolidated({ this, &ViewLifetimeControl::ViewConsolidated });
    }

    // Unregister for events. Call this method before closing the view to prevent leaks.
    void ViewLifetimeControl::UnregisterForEvents()
    {
        ApplicationView::GetForCurrentView().Consolidated(m_consolidatedToken);
    }

    void ViewLifetimeControl::ViewConsolidated(ApplicationView const&, ApplicationViewConsolidatedEventArgs const&)
    {
        // A view is consolidated with other views hen there's no way for the user to get to it (it's not in the list of recently used apps, cannot be
        // launched from Start, etc.) A view stops being consolidated when it's visible--at that point the user can interact with it, move it on or off screen, etc. 
        // It's generally a good idea to close a view after it has been consolidated, but keep it open while it's visible.
        StopViewInUse();
    }

    // Called when a view has been "consolidated" (no longer accessible to the user) 
    // and no other view is trying to interact with it. This should only be closed after the reference
    // count goes to 0 (including being consolidated). At the end of this, the view is closed. 
    void ViewLifetimeControl::FinalizeRelease()
    {
        bool justReleased = false;
        {
            auto lock = std::lock_guard(m_mutex);
            if (!m_released && m_refCount == 0)
            {
                m_released = true;
                justReleased = true;
            }
        } // lock

        // This assumes that released will never be made false after it
        // it has been set to true
        if (justReleased)
        {
            UnregisterForEvents();
            m_internalReleased(*this, nullptr);
        }
    }

    // Creates ViewLifetimeControl for the particular view.
    // Only do this once per view.
    RuntimeComponent1::ViewLifetimeControl ViewLifetimeControl::CreateForCurrentView()
    {
        return make<ViewLifetimeControl>(CoreWindow::GetForCurrentThread());
    }

    // For purposes of this sample, the collection of views
    // is bound to a UI collection. This property is available for binding
    hstring ViewLifetimeControl::Title()
    {
        // This is expected to only be updated on the thread that this object is bound to
        // Hence, it's not necessary to lock
        return m_title;
    }

    void ViewLifetimeControl::Title(hstring const& value)
    {
        // This is expected to only be updated on the thread that this object is bound to
        // Hence, it's not necessary to lock
        if (m_title != value)
        {
            m_title = value;
            m_propertyChanged(*this, PropertyChangedEventArgs(L"Title"));
        }
    }

    // Signals that the view is being interacted with by another view,
    // so it shouldn't be closed even if it becomes "consolidated"
    int32_t ViewLifetimeControl::StartViewInUse()
    {
        auto lock = std::lock_guard(m_mutex);
        if (m_released)
        {
            throw hresult_error(RO_E_CLOSED, L"The view is being disposed");
        }
        return ++m_refCount;
    }

    // Should come after any call to StartViewInUse
    // Signals that the another view has finished interacting with the view tracked
    // by this object
    int32_t ViewLifetimeControl::StopViewInUse()
    {
        auto lock = std::lock_guard(m_mutex);
        if (m_released)
        {
            throw hresult_error(RO_E_CLOSED, L"The view is being disposed");
        }
        if (m_refCount <= 0)
        {
            throw hresult_error(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), L"Object was released too many times");
        }

        int refCountCopy = --m_refCount;
        if (refCountCopy == 0)
        {
            // If no other view is interacting with this view, and
            // the view isn't accessible to the user, it's appropriate
            // to close it
            //
            // Before actually closing the view, make sure there are no
            // other important events waiting in the queue (this low-priority item
            // will run after other events)
            m_dispatcher.RunAsync(CoreDispatcherPriority::Low, { this, &ViewLifetimeControl::FinalizeRelease });
        }

        return refCountCopy;
    }

    // Signals to consumers that its time to close the view so that
    // they can clean up (including calling Window.Close() when finished)
    event_token ViewLifetimeControl::Released(TypedEventHandler<RuntimeComponent1::ViewLifetimeControl, IInspectable> const& handler)
    {
        auto lock = std::lock_guard(m_mutex);
        if (m_released)
        {
            throw hresult_error(RO_E_CLOSED, L"The view is being disposed");
        }

        return m_internalReleased.add(handler);
    }

    void ViewLifetimeControl::Released(event_token const& token)
    {
        auto lock = std::lock_guard(m_mutex);
        return m_internalReleased.remove(token);
    }

    event_token ViewLifetimeControl::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void ViewLifetimeControl::PropertyChanged(event_token const& token)
    {
        return m_propertyChanged.remove(token);
    }
}
