// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_
#define WEEX_UIKIT_WML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_

#include <android/looper.h>

#include <atomic>

#include "wml/macros.h"
#include "wml/message_loop_impl.h"
#include "wml/unique_fd.h"

namespace wml {

struct UniqueLooperTraits {
  static ALooper* InvalidValue() { return nullptr; }
  static bool IsValid(ALooper* value) { return value != nullptr; }
  static void Free(ALooper* value) { ::ALooper_release(value); }
};

class MessageLoopAndroid : public MessageLoopImpl {
 private:
  wml::UniqueObject<ALooper*, UniqueLooperTraits> looper_;
  wml::UniqueFD timer_fd_;
  bool running_;

  MessageLoopAndroid();

  ~MessageLoopAndroid() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(wml::TimePoint time_point) override;

  void OnEventFired();

  WML_FRIEND_MAKE_REF_COUNTED(MessageLoopAndroid);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopAndroid);
  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoopAndroid);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_
