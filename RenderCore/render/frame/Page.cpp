//
// Created by furture on 2018/12/29.
//

#include "Page.h"
#include "TaskRunners.h"

namespace weexuikit{

    Page::Page() {
        mFrame = new Frame();
        mFrameView = new FrameView(mFrame);
        mFramePipeline = new FramePipeline(mFrame, mFrameView);
        mFrameController = new FrameController(TaskRunners::ui(), mFramePipeline);
    }

    Page::~Page() {
        if(mFrameController != nullptr){
            mFrameController->stop();
            delete mFrameController;
        }
        if(mFramePipeline != nullptr){
            delete mFramePipeline;
            mFramePipeline = nullptr;
        }
        if(mFrameView != nullptr){
            delete mFrameView;
            mFrameView = nullptr;
        }
        if(mFrame != nullptr){
            delete mFrame;
            mFrame = nullptr;
        }
    }
}