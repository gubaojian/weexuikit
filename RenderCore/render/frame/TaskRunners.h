//
// Created by furture on 2018/12/27.
//

#ifndef WEEX_UIKIT_TASKRUNNERS_H
#define WEEX_UIKIT_TASKRUNNERS_H
#include <wml/task_runner.h>
#include <render/wml/thread.h>

namespace weexuikit {

    namespace TaskRunners {
        /**
         * Main UI Thread Task Runnder
         * */
        wml::RefPtr<wml::TaskRunner> ui();

        /**
         * IO Thread Task Runner Such As ImageTexture
         * */
        wml::RefPtr<wml::TaskRunner> io();

    };

}

#endif //WEEX_UIKIT_TASKRUNNERS_H
