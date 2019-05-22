//
// Created by furture on 2018/12/27.
//

#include "TaskRunners.h"

namespace weexuikit {

    namespace TaskRunners {

        extern wml::RefPtr<wml::TaskRunner> mImageTaskRunner;
        extern std::shared_ptr<wml::Thread> mImageTaskThread;
        extern wml::RefPtr<wml::TaskRunner> mFrameTaskRunner;

        wml::RefPtr<wml::TaskRunner> ui(){
            return mFrameTaskRunner;
        }

        /**
         * IO Thread Task Runner Such As ImageTexture
         * */
        wml::RefPtr<wml::TaskRunner> io(){
            return mImageTaskRunner;
        }
    };

}