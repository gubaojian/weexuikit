// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define WML_USED_ON_EMBEDDER

#include "wml/task_runner.h"

#include <utility>

#include "wml/logging.h"
#include "wml/message_loop.h"
#include "wml/message_loop_impl.h"

namespace wml {

TaskRunner::TaskRunner(wml::RefPtr<MessageLoopImpl> loop)
    : loop_(std::move(loop)) {}

TaskRunner::~TaskRunner() = default;

void TaskRunner::PostTask(wml::closure task) {
  loop_->PostTask(std::move(task), wml::TimePoint::Now());
}

void TaskRunner::PostTaskForTime(wml::closure task,
                                 wml::TimePoint target_time) {
  loop_->PostTask(std::move(task), target_time);
}

void TaskRunner::PostDelayedTask(wml::closure task, wml::TimeDelta delay) {
  loop_->PostTask(std::move(task), wml::TimePoint::Now() + delay);
}

bool TaskRunner::RunsTasksOnCurrentThread() {
  if (!wml::MessageLoop::IsInitializedForCurrentThread()) {
    return false;
  }
  return MessageLoop::GetCurrent().GetLoopImpl() == loop_;
}

void TaskRunner::RunNowOrPostTask(wml::RefPtr<wml::TaskRunner> runner,
                                  wml::closure task) {
  WML_DCHECK_(runner);
  if (runner->RunsTasksOnCurrentThread()) {
    task();
  } else {
    runner->PostTask(std::move(task));
  }
}

}  // namespace wml
