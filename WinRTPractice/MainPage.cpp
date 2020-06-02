#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
//#include "../RuntimeComponent1/Class.h"
#include <winrt/RuntimeComponent1.h>
using namespace winrt;
using namespace Windows::UI::Xaml;

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

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        RuntimeComponent1::Class a;
        a.showP1();

        //myButton().Content(box_value(L"Clicked"));
    }
}
