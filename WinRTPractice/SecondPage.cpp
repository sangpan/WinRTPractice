#include "pch.h"
#include "SecondPage.h"
#include "SecondPage.g.cpp"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.
using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::WinRTPractice::implementation
{ 
	SecondPage::SecondPage() {
		InitializeComponent();
	}

}


void winrt::WinRTPractice::implementation::SecondPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	try {
		Windows::UI::Xaml::Controls::Frame rootFrame{ nullptr };
		auto content = Window::Current().Content();
		if (content)
		{
			rootFrame = content.try_as<Windows::UI::Xaml::Controls::Frame>();
			rootFrame.GoBack();
		}
	}
    catch (hresult_error& ex)
    {
		auto msg = ex.message();
    }
}
