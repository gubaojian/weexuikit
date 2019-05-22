//
// Created by furture on 2019/1/1.
//

#include "LocalJStringUTF8.h"

namespace weexuikit {

    LocalJStringUTF8::LocalJStringUTF8(JNIEnv *env, const std::string &str) {
        mEnv  = env;
        mString = env->NewStringUTF(str.c_str());
    }

    LocalJStringUTF8::~LocalJStringUTF8() {
        mEnv->DeleteLocalRef(mString);
    }


    jstring LocalJStringUTF8::getJStr() {
        return mString;
    }


}