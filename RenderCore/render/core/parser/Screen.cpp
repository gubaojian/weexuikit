//
// Created by furture on 2018/8/7.
//

#include "Screen.h"

#include <string>
#include <cmath>
#include <cstdlib>

namespace weexuikit {

    namespace Screen {

        float mDeviceWidth;
        float mDeviceHeight;
        float mDeviceDensity;
        float mViewPort = 750.0f;

        const std::string WX("wx");
        const std::string PX("px");
        const std::string UNDEFINE("undefined");
        const std::string SCALE("scale");
        const std::string AUTO_UNIT("auto");
        const std::string NONE("none");

        inline std::string &Trim(std::string &s) {
            if (s.empty()) {
                return s;
            }
            s.erase(0, s.find_first_not_of(" "));
            s.erase(s.find_last_not_of(" ") + 1);
            return s;
        }

        inline float getFloat(const char *src) {
            char *end;
            float ret = strtof(src, &end);
            if (*end != '\0') {
                ret = NAN;
            }
            return ret;
        }

        inline float getFloat(const float &src, const float &viewport) {
            if (isnan(src))
                return NAN;

            float realPx = (src * mDeviceWidth / viewport);
            return realPx;
        }

        inline float getFloat(const std::string &src, const float &viewport) {
            float ret = NAN;
            if (UNDEFINE == src
                || AUTO_UNIT == src
                || NONE == src
                || src.empty()) {
                return ret;
            }
            float original_value = getFloat(src.c_str());
            ret = getFloat(original_value, viewport);
            return ret;
        }

        inline bool endWidth(const std::string &src, const std::string &suffix) {
            return src.size() > suffix.size() &&
                   src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
        }


        inline float transferWx(const std::string &stringWithWXPostfix, const float &viewport) {
            std::string temp = stringWithWXPostfix;
            if (endWidth(stringWithWXPostfix, WX)) {
                temp = stringWithWXPostfix.substr(0, stringWithWXPostfix.size() - WX.size());
            }
            float f = getFloat(temp.c_str());
            float density = mDeviceDensity;
            return density * f * viewport / mDeviceWidth;
        }

        float getFloatByViewport(std::string src, const float viewport) {
            float ret = NAN;
            if (UNDEFINE == src
                || AUTO_UNIT == src
                || NONE == src
                || src.empty()) {
                return ret;
            }
            Trim(src);
            if (endWidth(src, WX)) {
                ret = getFloat(transferWx(src, viewport), viewport);
            } else if (endWidth(src, PX)) {
                ret = getFloat(src.substr(0, src.size() - PX.size()), viewport);
            } else {
                ret = getFloat(src, viewport);
            }
            return roundf(ret);
        }

        float devicePixelsToUnit(float pixels){
            return pixels/mDeviceWidth*mViewPort;
        }

        float dpiToDevicePixels(float dpiValue){
            return roundf(dpiValue*Screen::mDeviceDensity);
        }
    }
}
