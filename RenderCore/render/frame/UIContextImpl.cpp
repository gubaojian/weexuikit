//
// Created by furture on 2018/12/18.
//

#include "UIContextImpl.h"
#include "Frame.h"

namespace weexuikit{

    UIContextImpl::UIContextImpl(Frame* frame):mFrame(frame){
        tickerProvider = nullptr;
        mNeedsPaint = false;
        mPlatformContext = new PlatformContext();
        gestureHandlerContext = new weexuikit::GestureHandlerContext();
    }


    void UIContextImpl::fireEvent(weexuikit::Node *node, const std::string &event,
                                  const std::map<std::string, std::string> &params) {
        mFrame->fireEvent(node, event, params);
    }

    UIContextImpl::~UIContextImpl() {

        if (mPlatformContext != nullptr) {
            delete mPlatformContext;
            mPlatformContext = nullptr;
        }
        if (tickerProvider != nullptr) {
            delete tickerProvider;
            tickerProvider = nullptr;
        }
    }
}