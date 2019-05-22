//
// Created by furture on 2018/8/25.
//

#ifndef WEEXRENDERER_WIDGETFACTORY_H
#define WEEXRENDERER_WIDGETFACTORY_H
#include "View.h"
#include "UIContext.h"

namespace weexuikit {

    class ViewFactory {

    public:
        static View* createView(const std::string& pageId, const std::string &ref, const std::string &type,
                                std::map<std::string, std::string> *styles,
                                std::map<std::string, std::string> *attrs,
                                std::set<std::string> *events,
                                UIContext *context, blink::RenderObject *parent, int index);
    };

}

#endif //WEEXRENDERER_NODEFACTORY_H
