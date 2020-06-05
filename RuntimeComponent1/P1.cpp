#include "pch.h"
#include "P1.h"
#include "P1.g.cpp"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;

namespace winrt::RuntimeComponent1::implementation
{
    P1::P1()
    {
        InitializeComponent();
    }
	void P1::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e) {
		auto argument = unbox_value_or<hstring>(e.Parameter(), hstring());

	}
}


void winrt::RuntimeComponent1::implementation::P1::btn1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	Windows::UI::Xaml::Controls::Frame rootFrame{ nullptr };
	auto content = Window::Current().Content();
	if (content)
	{
		rootFrame = content.try_as<Windows::UI::Xaml::Controls::Frame>();
		rootFrame.GoBack();
	}
	//Window::Current().Close();
}
