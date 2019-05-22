//
// Created by furture on 2018/12/30.
//

#include "FrameController.h"
namespace weexuikit{

    static const int  DEFAULT_FRAME = 1000/60;


    FrameController::FrameController(wml::RefPtr<wml::TaskRunner> taskRunners,
                                     weexuikit::FramePipeline *framePipeline) {
        mTaskRunners = taskRunners;
        mFramePipeline = framePipeline;
        mStop = false;
        mRequestFrame = false;
    }

    FrameController::~FrameController() {
        mFramePipeline = nullptr;
    }

    void FrameController::requestFrame() {
        if(!mRequestFrame){
            mRequestFrame = true;
            mTaskRunners->PostTask([&]{
                mRequestFrame = false;
                if(mStop){
                    return;
                }
                mFramePipeline->onFrame();
            });
        }
    }

    void FrameController::stop() {
        mStop = true;
    }


}
