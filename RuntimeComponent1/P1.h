#pragma once
#include "P1.g.h"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.

namespace winrt::RuntimeComponent1::implementation
{
    struct P1 : P1T<P1>
    {
        P1() = default;

        void btn1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}
namespace winrt::RuntimeComponent1::factory_implementation
{
    struct P1 : P1T<P1, implementation::P1>
    {
    };
}
