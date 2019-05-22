//
// Created by furture on 2019/1/1.
//

#ifndef WEEX_UIKIT_LOCALCSTRINGUTF8_H
#define WEEX_UIKIT_LOCALCSTRINGUTF8_H


#include <jni.h>
#include <string>

namespace weexuikit {

    class LocalJStringUTF8 {
        public:
            LocalJStringUTF8(JNIEnv* env, const std::string& str);
            ~LocalJStringUTF8();

            jstring getJStr();

        private:
            jstring mString;
            JNIEnv* mEnv;
    };
}



#endif //WEEX_UIKIT_LOCALCSTRINGUTF8_H
