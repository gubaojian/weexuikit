// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_MESSAGE_LOOP_H_
#define WEEX_UIKIT_WML_MESSAGE_LOOP_H_

#include "wml/macros.h"
#include "wml/task_runner.h"

namespace wml {

class TaskRunner;
class MessageLoopImpl;

class MessageLoop {
 public:
  WML_EMBEDDER_ONLY
  static MessageLoop& GetCurrent();

  bool IsValid() const;

  void Run();

  void Terminate();

  void AddTaskObserver(intptr_t key, wml::closure callback);

  void RemoveTaskObserver(intptr_t key);

  wml::RefPtr<wml::TaskRunner> GetTaskRunner() const;

  // Exposed for the embedder shell which allows clients to poll for events
  // instead of dedicating a thread to the message loop.
  void RunExpiredTasksNow();

  static void EnsureInitializedForCurrentThread();

  static bool IsInitializedForCurrentThread();

  ~MessageLoop();

 private:
  friend class TaskRunner;
  friend class MessageLoopImpl;

  wml::RefPtr<MessageLoopImpl> loop_;
  wml::RefPtr<wml::TaskRunner> task_runner_;

  MessageLoop();

  wml::RefPtr<MessageLoopImpl> GetLoopImpl() const;

  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoop);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_MESSAGE_LOOP_H_
