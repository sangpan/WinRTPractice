#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/RuntimeComponent1.h>
#include "SecondPage.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;

namespace winrt::WinRTPractice::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    // Call Xaml From Window Component (Library)
    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        RuntimeComponent1::Class a;
        a.showP1();
    }

    // Call Xaml in App
    void MainPage::myButton3_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        Frame().Navigate(xaml_typename<winrt::WinRTPractice::SecondPage>());
        Window;
    }
}

