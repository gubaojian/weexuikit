//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_STYLEUPDATER_H
#define WEEXRENDERER_STYLEUPDATER_H
#include <render/core/rendering/style/RenderStyle.h>
#include <string>
#include <set>
#include <map>

namespace weexuikit {

    namespace StyleUpdater {

        void updateRenderStyleFontFamily(blink::RenderStyle* renderStyle, const WTF::AtomicString& fontFamily);

        RefPtr<blink::RenderStyle> createInteritRenderStyle(RefPtr<blink::RenderStyle> parentStyle);

        RefPtr<blink::RenderStyle> createRenderStyle(RefPtr<blink::RenderStyle> parentStyle, std::map<std::string, std::string> *styles);

        RefPtr<blink::RenderStyle> newRenderStyleUpdates(blink::RenderStyle *renderStyle,
                                                         std::map<std::string, std::string> *styles);



    };
}


#endif //WEEXRENDERER_STYLEUPDATER_H
