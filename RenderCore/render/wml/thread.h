// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_THREAD_H_
#define WEEX_UIKIT_WML_THREAD_H_

#include <atomic>
#include <memory>
#include <thread>

#include "wml/macros.h"
#include "wml/task_runner.h"

namespace wml {

class Thread {
 public:
  explicit Thread(const std::string& name = "");

  ~Thread();

  wml::RefPtr<wml::TaskRunner> GetTaskRunner() const;

  void Join();


 private:
  std::unique_ptr<std::thread> thread_;
  wml::RefPtr<wml::TaskRunner> task_runner_;
  std::atomic_bool joined_;

  static void SetCurrentThreadName(const std::string& name);

  WML_DISALLOW_COPY_AND_ASSIGN(Thread);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_THREAD_H_
