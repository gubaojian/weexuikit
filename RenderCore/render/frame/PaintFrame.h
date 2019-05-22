//
// Created by furture on 2019/1/9.
//

#ifndef WEEX_UIKIT_PAINTFRAME_H
#define WEEX_UIKIT_PAINTFRAME_H

#include <third_party/skia/include/core/SkPicture.h>
#include <render/platform/graphics/PaintPlatformView.h>

namespace weexuikit {

    struct PaintFrame {
        sk_sp<SkPicture> frameRecords;
        std::vector<blink::PaintPlatformView> synViews;
    };
}


#endif //WEEX_UIKIT_PAINTFRAME_H
