// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define WML_USED_ON_EMBEDDER

#include "wml/thread.h"

#include "wml/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <memory>
#include <string>
#include <sys/resource.h>

#include "wml/message_loop.h"
#include "wml/synchronization/waitable_event.h"

namespace wml {

Thread::Thread(const std::string& name) : joined_(false) {
  wml::AutoResetWaitableEvent latch;
  wml::RefPtr<wml::TaskRunner> runner;
  thread_ = std::make_unique<std::thread>([&latch, &runner, name]() -> void {

    /**
    * https://android.googlesource.com/platform/frameworks/native/+/android-4.2.2_r1/include/utils/ThreadDefs.h
    * */
    #define ANDROID_PRIORITY_BACKGROUND     10
    #define ANDROID_PRIORITY_NORMAL     0
    #define ANDROID_PRIORITY_HIGHEST     -20
    if(name.find("Gpu") != std::string::npos){
        setpriority( PRIO_PROCESS, 0, ANDROID_PRIORITY_HIGHEST);;
    }else if(name.find("Frame") != std::string::npos){
        setpriority( PRIO_PROCESS, 0, ANDROID_PRIORITY_NORMAL);
    }else{
        setpriority(PRIO_PROCESS, 0, ANDROID_PRIORITY_BACKGROUND);
    }
    //FIXME Operations Add To UI Background CGroups

    SetCurrentThreadName(name);
    wml::MessageLoop::EnsureInitializedForCurrentThread();
    auto& loop = MessageLoop::GetCurrent();
    runner = loop.GetTaskRunner();
    latch.Signal();
    loop.Run();


  });
  latch.Wait();
  task_runner_ = runner;
}

Thread::~Thread() {
  Join();
}

wml::RefPtr<wml::TaskRunner> Thread::GetTaskRunner() const {
  return task_runner_;
}

void Thread::Join() {
  if (joined_) {
    return;
  }
  joined_ = true;
  task_runner_->PostTask([]() { MessageLoop::GetCurrent().Terminate(); });
  thread_->join();
}


#if defined(OS_WIN)
// The information on how to set the thread name comes from
// a MSDN article: http://msdn2.microsoft.com/en-us/library/xcb2z8hs.aspx
const DWORD kVCThreadNameException = 0x406D1388;
typedef struct tagTHREADNAME_INFO {
  DWORD dwType;      // Must be 0x1000.
  LPCSTR szName;     // Pointer to name (in user addr space).
  DWORD dwThreadID;  // Thread ID (-1=caller thread).
  DWORD dwFlags;     // Reserved for future use, must be zero.
} THREADNAME_INFO;
#endif

void Thread::SetCurrentThreadName(const std::string& name) {
  if (name == "") {
    return;
  }
#if OS_MACOSX
  pthread_setname_np(name.c_str());
#elif OS_LINUX || OS_ANDROID
  pthread_setname_np(pthread_self(), name.c_str());
#elif OS_WIN
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = name.c_str();
  info.dwThreadID = GetCurrentThreadId();
  info.dwFlags = 0;
  __try {
    RaiseException(kVCThreadNameException, 0, sizeof(info) / sizeof(DWORD),
                   reinterpret_cast<DWORD_PTR*>(&info));
  } __except (EXCEPTION_CONTINUE_EXECUTION) {
  }
#else
  WML_DLOG(INFO) << "Could not set the thread name to '" << name
                 << "' on this platform.";
#endif
}

}  // namespace wml
