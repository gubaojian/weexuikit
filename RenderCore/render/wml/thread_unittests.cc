// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"

#include "wml/thread.h"

TEST(Thread, CanStartAndEnd) {
  wml::Thread thread;
  ASSERT_TRUE(thread.GetTaskRunner());
}

TEST(Thread, CanStartAndEndWithExplicitJoin) {
  wml::Thread thread;
  ASSERT_TRUE(thread.GetTaskRunner());
  thread.Join();
}

TEST(Thread, HasARunningMessageLoop) {
  wml::Thread thread;
  bool done = false;
  thread.GetTaskRunner()->PostTask([&done]() { done = true; });
  thread.Join();
  ASSERT_TRUE(done);
}
