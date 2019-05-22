//
// Created by furture on 2018/12/30.
//

#ifndef WEEX_UIKIT_FRAME_CONTROLLER_H
#define WEEX_UIKIT_FRAME_CONTROLLER_H

#include <render/wml/message_loop.h>
#include "FramePipeline.h"

namespace weexuikit{

    class FrameController {

       public:
          FrameController(wml::RefPtr<wml::TaskRunner> taskRunners, FramePipeline* framePipeline);
          ~FrameController();

       public:
           void requestFrame();
           void stop();

       private:
           FramePipeline* mFramePipeline;
           wml::RefPtr<wml::TaskRunner> mTaskRunners;
           volatile bool mRequestFrame;
           bool mStop;

    };
}



#endif //WEEX_UIKIT_FRAME_CONTROLLER_H
