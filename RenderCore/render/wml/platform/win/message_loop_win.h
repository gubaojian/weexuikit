// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_PLATFORM_WIN_MESSAGE_LOOP_WIN_H_
#define WEEX_UIKIT_WML_PLATFORM_WIN_MESSAGE_LOOP_WIN_H_

#include <atomic>

#include <windows.h>

#include "wml/macros.h"
#include "wml/message_loop_impl.h"
#include "wml/unique_object.h"

namespace wml {

class MessageLoopWin : public MessageLoopImpl {
 private:
  struct UniqueHandleTraits {
    static HANDLE InvalidValue() { return NULL; }
    static bool IsValid(HANDLE value) { return value != NULL; }
    static void Free(HANDLE value) { CloseHandle(value); }
  };

  bool running_;
  wml::UniqueObject<HANDLE, UniqueHandleTraits> timer_;

  MessageLoopWin();

  ~MessageLoopWin() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(wml::TimePoint time_point) override;

  WML_FRIEND_MAKE_REF_COUNTED(MessageLoopWin);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopWin);
  WML_DISALLOW_COPY_AND_ASSIGN(MessageLoopWin);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_PLATFORM_GENERIC_MESSAGE_LOOP_GENERIC_H_
