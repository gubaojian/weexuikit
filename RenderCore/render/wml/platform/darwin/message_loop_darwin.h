// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_PLATFORM_DARWIN_MESSAGE_LOOP_DARWIN_H_
#define WEEX_UIKIT_WML_PLATFORM_DARWIN_MESSAGE_LOOP_DARWIN_H_

#include <CoreFoundation/CoreFoundation.h>

#include <atomic>

#include "wml/macros.h"
#include "wml/message_loop_impl.h"
#include "wml/platform/darwin/cf_utils.h"

namespace wml {

class MessageLoopDarwin : public MessageLoopImpl {
 private:
  std::atomic_bool running_;
  CFRef<CFRunLoopTimerRef> delayed_wake_timer_;
  CFRef<CFRunLoopRef> loop_;

  MessageLoopDarwin();

  ~MessageLoopDarwin() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(wml::TimePoint time_point) override;

  static void OnTimerFire(CFRunLoopTimerRef timer, MessageLoopDarwin* loop);

  WML_FRIEND_MAKE_REF_COUNTED(MessageLoopDarwin);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopDarwin);
  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoopDarwin);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_PLATFORM_DARWIN_MESSAGE_LOOP_DARWIN_H_
