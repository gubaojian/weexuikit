//
//  UIContext.hpp
//  widget
//
//  Created by furture on 2018/10/30.
//

#ifndef WEEXRENDERER_UICONTEXT_H
#define WEEXRENDERER_UICONTEXT_H
#include <render/gesture/gesture/PointerEvent.h>
#include <render/gesture/gesture/GestureHandlerContext.h>
#include <render/gesture/foundation/TickerProvider.h>
#include <render/core/node/Node.h>


class UIContext{
    
    public:
        virtual weexuikit::GestureHandlerContext* getGestureHandlerContext()=0;
        virtual weexuikit::TickerProvider* getTickerProvider()=0;
        virtual void markNeedsPaint()=0;
        virtual void fireEvent(weexuikit::Node* node, const std::string& event, const std::map<std::string,std::string>& params)=0;
};

#endif /* UIContext_hpp */
