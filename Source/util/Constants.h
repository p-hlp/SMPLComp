
#pragma once
#include <cstdint>

namespace Constants
{
    namespace Colors
    {
        //Backgrounds
        constexpr uint32_t bg_App{ 0xff424242 };
        constexpr uint32_t bg_DarkGrey{ 0xff212121 };
        constexpr uint32_t bg_MidGrey{ 0xff616161 };
        constexpr uint32_t bg_LightGrey{ 0xff9e9e9e };

        //Gradients
        constexpr uint32_t gd_LightGreyStart{ 0xffeeeee };
        constexpr uint32_t gd_LightGreyEnd{ 0xffc4c4c4 };
        constexpr uint32_t gd_DarktGreyStart{ 0xff646464 };
        constexpr uint32_t gd_DarkGreyEnd{ 0xff464646 };

        //Misc
        constexpr uint32_t statusOutline{ 0xfffb8c00 };
        constexpr uint32_t knobShadow{ 0xff424242 };
    }

    namespace Margins
    {
        constexpr float small = 2.0f;
        constexpr float medium = 4.0f;
        constexpr float big = 8.0f;
    }

    namespace Parameter
    {
        constexpr float inputStart = -30.0f;
        constexpr float inputEnd = 30.0f;
        constexpr float inputInterval = 0.1f;

        constexpr float thresholdStart = -60.0f;
        constexpr float thresholdEnd = 0.0f;
        constexpr float thresholdInterval = 0.1f;

        constexpr float ratioStart = 1.0f;
        constexpr float ratioEnd = 24.0f;
        constexpr float ratioInterval = 0.05f;

        constexpr float kneeStart = 0.0f;
        constexpr float kneeEnd = 24.0f;
        constexpr float kneeInterval = 0.1f;

        constexpr float attackStart = 0.0f;
        constexpr float attackEnd = 100.0f;
        constexpr float attackInterval = 0.01f;

        constexpr float releaseStart = 5.0f;
        constexpr float releaseEnd = 1500.0f;
        constexpr float releaseInterval = 0.01f;

        constexpr float makeupStart = -30.0f;
        constexpr float makeupEnd = 30.0f;
        constexpr float makeupInterval = 0.1f;

        constexpr float mixStart = 0.0f;
        constexpr float mixEnd = 1.0f;
        constexpr float mixInterval = 0.001f;
    }
}
