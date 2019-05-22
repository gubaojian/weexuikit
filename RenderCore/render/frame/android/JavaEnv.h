//
// Created by furture on 2019/2/3.
//

#ifndef WEEX_X_RENDER_JAVAENV_H
#define WEEX_X_RENDER_JAVAENV_H
#include <jni.h>

namespace WeexCore {

    namespace JavaEnv {

        void InitVM(JavaVM *vm);

        JavaVM* getJVM();


        JNIEnv*  getCurrentJavaEnv();
    }
}



#endif //WEEX_X_RENDER_JAVAENV_H
