//
// Created by furture on 2018/4/17.
//

#ifndef WEEX_UIKIT_ENGINE_H
#define WEEX_UIKIT_ENGINE_H

#include "platform/Platform.h"

namespace blink {

    void initEngine();


// Once shutdown, the Platform passed to initialize will no longer
// be accessed. No other WebKit objects should be in use when this function is
// called. Any background threads created by WebKit are promised to be
// terminated by the time this function returns.
   void shutdownEngine();
}



#endif //WEEX_UIKIT_ENGINE_H
