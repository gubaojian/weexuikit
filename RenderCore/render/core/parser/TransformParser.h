//
// Created by furture on 2019/2/18.
//

#ifndef WEEX_UIKIT_TRANSFORMPARSER_H
#define WEEX_UIKIT_TRANSFORMPARSER_H
#include <render/platform/transforms/TransformOperations.h>

namespace weexuikit{

    namespace TransformParser {

        blink::TransformOperations parseTransform(const std::string& transform);

        void parseTransformOrigin(blink::RenderStyle* renderStyle, const std::string& transformOrigin);

        void parseTransformStyle(blink::RenderStyle* renderStyle, const std::string& transformStyle);

    }
}



#endif //WEEX_UIKIT_TRANSFORMPARSER_H
