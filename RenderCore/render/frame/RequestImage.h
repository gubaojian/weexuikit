//
// Created by furture on 2019/1/1.
//

#ifndef WEEX_UIKIT_REQUESTIMAGE_H
#define WEEX_UIKIT_REQUESTIMAGE_H

#include <string>

namespace weexuikit {

    struct RequestImage {
        std::string pageId;
        std::string ref;
        std::string url;
        int width;
        int height;
        int64_t callbackId;
    };
}


#endif //WEEX_UIKIT_REQUESTIMAGE_H
