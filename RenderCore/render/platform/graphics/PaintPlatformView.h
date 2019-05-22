//
// Created by furture on 2019/1/9.
//

#ifndef WEEX_UIKIT_SYNVIEW_H
#define WEEX_UIKIT_SYNVIEW_H

#include <string>
#include <render/platform/geometry/LayoutRect.h>

namespace blink {

    #define  SYN_VIEW_OFFSET   100

    struct PaintPlatformView {
        std::string pageId;
        std::string ref;
        LayoutRect paintRect;
        bool  attached;
    };
}



#endif //WEEX_UIKIT_SYNVIEW_H
