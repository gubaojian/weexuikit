//
// Created by furture on 2018/8/27.
//

#ifndef WEEXRENDERER_COLORMAP_H
#define WEEXRENDERER_COLORMAP_H
#include <string>
#include <map>
#include <render/platform/graphics/Color.h>

namespace weexuikit {

    class ColorMap {
    public:
        ColorMap();
        ~ColorMap();
        static ColorMap* getInstance();

        inline std::map<std::string,blink::RGBA32>* colorMap(){
            return mColorMap;
        };

    private:
        std::map<std::string,blink::RGBA32>* mColorMap;
        static ColorMap* mColorMapInstance;
    };

}


#endif //WEEXRENDERER_COLORMAP_H
