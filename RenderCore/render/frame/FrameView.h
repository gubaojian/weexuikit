//
// Created by furture on 2018/12/30.
//

#ifndef WEEX_UIKIT_FRAMEVIEW_H
#define WEEX_UIKIT_FRAMEVIEW_H


#include "Frame.h"

namespace weexuikit{

    class FrameView {

        public:
            FrameView(Frame* frame);
            ~FrameView();

        public:
            /**
             * hitTest
             * */
            Node* hitTestNode(int type, int x, int y);

            /**
             * dispatch Touch Event
             * */
            void onTouch(weexuikit::PointerEvent::PointerAction action, int pointerId, float x, float y,
                         int64_t timeStamp);


        public:
            blink::RenderObject* hitTestRenderObject(int type, int x, int y);

        private:
            void dispatchTouchEvent(weexuikit::PointerEvent &pointerEvent);



        private:
            Frame* mFrame;
            std::map<int,blink::RenderObject*> mTouchDispatchPaths;
            std::map<int,std::pair<float, float>> mTouchPointerLocations;
            std::vector<weexuikit::PointerEvent> mTouchEvents;

    };
}



#endif //WEEX_UIKIT_FRAMEVIEW_H
