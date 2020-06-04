#pragma once
#include <winrt/Windows.UI.Core.h>
#include "Class.g.h"

namespace winrt::RuntimeComponent1::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
        static Windows::UI::Core::CoreDispatcher MainDispatcher;    //must USE STATIC
    public:
        fire_and_forget showAppView();
        fire_and_forget showAppView2();

        void showP1();
    };
}

namespace winrt::RuntimeComponent1::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
