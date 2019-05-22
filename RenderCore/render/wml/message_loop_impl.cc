// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define WML_USED_ON_EMBEDDER

#include "wml/message_loop_impl.h"

#include <algorithm>
#include <vector>

#include "wml/build_config.h"
#include "wml/logging.h"
#include "wml/trace_event.h"

#if OS_MACOSX
#include "wml/platform/darwin/message_loop_darwin.h"
#elif OS_ANDROID
#include "wml/platform/android/message_loop_android.h"
#elif OS_LINUX
#include "wml/platform/linux/message_loop_linux.h"
#elif OS_WIN
#include "wml/platform/win/message_loop_win.h"
#endif

namespace wml {

wml::RefPtr<MessageLoopImpl> MessageLoopImpl::Create() {
#if OS_MACOSX
  return wml::MakeRefCounted<MessageLoopDarwin>();
#elif OS_ANDROID
  return wml::MakeRefCounted<MessageLoopAndroid>();
#elif OS_LINUX
  return wml::MakeRefCounted<MessageLoopLinux>();
#elif OS_WIN
  return wml::MakeRefCounted<MessageLoopWin>();
#else
  return nullptr;
#endif
}

MessageLoopImpl::MessageLoopImpl() : order_(0), terminated_(false) {}

MessageLoopImpl::~MessageLoopImpl() = default;

void MessageLoopImpl::PostTask(wml::closure task, wml::TimePoint target_time) {
  WML_DCHECK_(task != nullptr);
  RegisterTask(task, target_time);
}

void MessageLoopImpl::RunExpiredTasksNow() {
  RunExpiredTasks();
}

void MessageLoopImpl::AddTaskObserver(intptr_t key, wml::closure callback) {
  WML_DCHECK_(callback != nullptr);
  WML_DCHECK_(MessageLoop::GetCurrent().GetLoopImpl().get() == this)
      << "Message loop task observer must be added on the same thread as the "
         "loop.";
  task_observers_[key] = std::move(callback);
}

void MessageLoopImpl::RemoveTaskObserver(intptr_t key) {
  WML_DCHECK_(MessageLoop::GetCurrent().GetLoopImpl().get() == this)
      << "Message loop task observer must be removed from the same thread as "
         "the loop.";
  task_observers_.erase(key);
}

void MessageLoopImpl::DoRun() {
  if (terminated_) {
    // Message loops may be run only once.
    return;
  }

  // Allow the implementation to do its thing.
  Run();

  // The loop may have been implicitly terminated. This can happen if the
  // implementation supports termination via platform specific APIs or just
  // error conditions. Set the terminated flag manually.
  terminated_ = true;

  // The message loop is shutting down. Check if there are expired tasks. This
  // is the last chance for expired tasks to be serviced. Make sure the
  // terminated flag is already set so we don't accrue additional tasks now.
  RunExpiredTasksNow();

  // When the message loop is in the process of shutting down, pending tasks
  // should be destructed on the message loop's thread. We have just returned
  // from the implementations |Run| method which we know is on the correct
  // thread. Drop all pending tasks on the floor.
  std::lock_guard<std::mutex> lock(delayed_tasks_mutex_);
    while(!delayed_tasks_.empty()){
        delayed_tasks_.pop();
    }
}

void MessageLoopImpl::DoTerminate() {
  terminated_ = true;
  Terminate();
}

void MessageLoopImpl::RegisterTask(wml::closure task,
                                   wml::TimePoint target_time) {
  WML_DCHECK_(task != nullptr);
  if (terminated_) {
    // If the message loop has already been terminated, PostTask should destruct
    // |task| synchronously within this function.
    return;
  }
  std::lock_guard<std::mutex> lock(delayed_tasks_mutex_);
  delayed_tasks_.push({++order_, std::move(task), target_time});
  WakeUp(delayed_tasks_.top().target_time);
}

void MessageLoopImpl::RunExpiredTasks() {
  TRACE_EVENT0("wml", "MessageLoop::RunExpiredTasks");
  std::vector<wml::closure> invocations;

  {
    std::lock_guard<std::mutex> lock(delayed_tasks_mutex_);

    if (delayed_tasks_.empty()) {
      return;
    }

    auto now = wml::TimePoint::Now();
    while (!delayed_tasks_.empty()) {
      const auto& top = delayed_tasks_.top();
      if (top.target_time > now) {
        break;
      }
      invocations.emplace_back(std::move(top.task));
      delayed_tasks_.pop();
    }

    WakeUp(delayed_tasks_.empty() ? wml::TimePoint::Max()
                                  : delayed_tasks_.top().target_time);
  }

  for (const auto& invocation : invocations) {
    invocation();
    for (const auto& observer : task_observers_) {
      observer.second();
    }
  }
}

}  // namespace wml
