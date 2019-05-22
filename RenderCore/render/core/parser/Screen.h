//
// Created by furture on 2018/8/7.
//

#ifndef WEEX_UIKIT_UNITUTILS_H
#define WEEX_UIKIT_UNITUTILS_H
#include <string>

namespace weexuikit {

    namespace Screen {
        extern  float mDeviceWidth;
        extern  float mDeviceHeight;
        extern  float mDeviceDensity;
        extern  float mViewPort;


        float getFloatByViewport(std::string src, const float viewport = 750.0f);

        float devicePixelsToUnit(float pixels);

        float dpiToDevicePixels(float dpiValue);
    }
}


#endif //WEEX_UIKIT_UNITUTILS_H
