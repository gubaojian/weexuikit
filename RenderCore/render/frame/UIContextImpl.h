//
// Created by furture on 2018/12/18.
//

#ifndef WEEX_UIKIT_UICONTEXTIMPL_H
#define WEEX_UIKIT_UICONTEXTIMPL_H
#include <render/widget/UIContext.h>

namespace weexuikit{

    struct PlatformContext{
        int64_t renderFrameKey;
        void* shareContext;
    };


    class Frame;

    class UIContextImpl : public UIContext  {

    public:
        UIContextImpl(Frame* frame);
        ~UIContextImpl();


    public:

        PlatformContext* getPlatformContext(){
            return mPlatformContext;
        }

        virtual void fireEvent(weexuikit::Node* node, const std::string& event, const std::map<std::string,std::string>& params) override;

        virtual weexuikit::GestureHandlerContext* getGestureHandlerContext() override{
            return gestureHandlerContext;
        }
        virtual weexuikit::TickerProvider* getTickerProvider() override{
            if(tickerProvider == nullptr){
                tickerProvider = new weexuikit::TickerProvider();
            }
            return tickerProvider;
        }

        virtual void markNeedsPaint() override{
            mNeedsPaint = true;
        }

        void setHasPaint(){
            mNeedsPaint = false;
        }

        bool needsPaint(){
            return  mNeedsPaint;
        }


    private:
        weexuikit::GestureHandlerContext* gestureHandlerContext;
        weexuikit::TickerProvider*  tickerProvider;
        PlatformContext* mPlatformContext;
        bool  mNeedsPaint;
        Frame* mFrame;
    };
}



#endif //WEEX_UIKIT_UICONTEXTIMPL_H
