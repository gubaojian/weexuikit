// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_TASK_RUNNER_H_
#define WEEX_UIKIT_WML_TASK_RUNNER_H_

#include "wml/closure.h"
#include "wml/macros.h"
#include "wml/memory/ref_counted.h"
#include "wml/memory/ref_ptr.h"
#include "wml/time/time_point.h"

namespace wml {

class MessageLoopImpl;

class TaskRunner : public wml::RefCountedThreadSafe<TaskRunner> {
 public:
  virtual void PostTask(wml::closure task);

  virtual void PostTaskForTime(wml::closure task, wml::TimePoint target_time);

  virtual void PostDelayedTask(wml::closure task, wml::TimeDelta delay);

  virtual bool RunsTasksOnCurrentThread();

  virtual ~TaskRunner();

  static void RunNowOrPostTask(wml::RefPtr<wml::TaskRunner> runner,
                               wml::closure task);

 protected:
  TaskRunner(wml::RefPtr<MessageLoopImpl> loop);

 private:
  wml::RefPtr<MessageLoopImpl> loop_;

  WML_FRIEND_MAKE_REF_COUNTED(TaskRunner);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(TaskRunner);
  WML_DISALLOW_COPY_AND_ASSIGN(TaskRunner);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_TASK_RUNNER_H_
