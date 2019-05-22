#ifndef WEEX_UIKIT_GESTURE_STANDARD_EXTENSION_H
#define WEEX_UIKIT_GESTURE_STANDARD_EXTENSION_H
#include <algorithm>

namespace std {
    template<class T>  const T clamp( const T v, const T lo, const T hi ){
        if(v < lo ){
            return lo;
        }
        if(v > hi){
            return hi;
        }
        return v;
    }
}

#endif