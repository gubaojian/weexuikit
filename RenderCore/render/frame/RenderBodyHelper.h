//
// Created by furture on 2018/7/23.
//

#ifndef WEEX_UIKIT_BODY_HELPER_H
#define WEEX_UIKIT_BODY_HELPER_H


#include <render/core/rendering/RenderView.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <render/core/node/NodeStyles.h>
#include <string>
#include <set>
#include <map>

namespace weexuikit {

    namespace Body{

        blink::RenderView* createRenderView(int width, int height);

        void cleanBoxOuterStyle(std::map<std::string, std::string> *styles);
    }

}

#endif //WEEX_UIKIT_DOCUMENT_H_H
