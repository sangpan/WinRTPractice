#pragma once
#include "SecondPage.g.h"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.


namespace winrt::WinRTPractice::implementation
{
    struct SecondPage : SecondPageT<SecondPage>
    {
        SecondPage();

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}
namespace winrt::WinRTPractice::factory_implementation
{
    struct SecondPage : SecondPageT<SecondPage, implementation::SecondPage>
    {
    };
}
