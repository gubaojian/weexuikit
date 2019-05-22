// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_PLATFORM_LINUX_MESSAGE_LOOP_LINUX_H_
#define WEEX_UIKIT_WML_PLATFORM_LINUX_MESSAGE_LOOP_LINUX_H_

#include <atomic>

#include "wml/macros.h"
#include "wml/message_loop_impl.h"
#include "wml/unique_fd.h"

namespace wml {

class MessageLoopLinux : public MessageLoopImpl {
 private:
  wml::UniqueFD epoll_fd_;
  wml::UniqueFD timer_fd_;
  bool running_;

  MessageLoopLinux();

  ~MessageLoopLinux() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(wml::TimePoint time_point) override;

  void OnEventFired();

  bool AddOrRemoveTimerSource(bool add);

  WML_FRIEND_MAKE_REF_COUNTED(MessageLoopLinux);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopLinux);
  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoopLinux);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_PLATFORM_LINUX_MESSAGE_LOOP_LINUX_H_
