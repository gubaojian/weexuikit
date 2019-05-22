// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_MESSAGE_LOOP_IMPL_H_
#define WEEX_UIKIT_WML_MESSAGE_LOOP_IMPL_H_

#include <atomic>
#include <deque>
#include <map>
#include <mutex>
#include <queue>
#include <utility>

#include "wml/closure.h"
#include "wml/macros.h"
#include "wml/memory/ref_counted.h"
#include "wml/message_loop.h"
#include "wml/time/time_point.h"

namespace wml {

class MessageLoopImpl : public wml::RefCountedThreadSafe<MessageLoopImpl> {
 public:
  static wml::RefPtr<MessageLoopImpl> Create();

  virtual ~MessageLoopImpl();

  virtual void Run() = 0;

  virtual void Terminate() = 0;

  virtual void WakeUp(wml::TimePoint time_point) = 0;

  void PostTask(wml::closure task, wml::TimePoint target_time);

  void AddTaskObserver(intptr_t key, wml::closure callback);

  void RemoveTaskObserver(intptr_t key);

  void DoRun();

  void DoTerminate();

  // Exposed for the embedder shell which allows clients to poll for events
  // instead of dedicating a thread to the message loop.
  void RunExpiredTasksNow();

 protected:
  MessageLoopImpl();

 private:
  struct DelayedTask {
    size_t order;
    wml::closure task;
    wml::TimePoint target_time;

    DelayedTask(size_t p_order,
                wml::closure p_task,
                wml::TimePoint p_target_time)
        : order(p_order), task(std::move(p_task)), target_time(p_target_time) {}
  };

  struct DelayedTaskCompare {
    bool operator()(const DelayedTask& a, const DelayedTask& b) {
      return a.target_time == b.target_time ? a.order > b.order
                                            : a.target_time > b.target_time;
    }
  };

  using DelayedTaskQueue = std::
      priority_queue<DelayedTask, std::deque<DelayedTask>, DelayedTaskCompare>;

  std::map<intptr_t, wml::closure> task_observers_;
  std::mutex delayed_tasks_mutex_;
  DelayedTaskQueue delayed_tasks_;
  size_t order_;
  std::atomic_bool terminated_;

  void RegisterTask(wml::closure task, wml::TimePoint target_time);

  void RunExpiredTasks();

  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoopImpl);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_MESSAGE_LOOP_IMPL_H_
