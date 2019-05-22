// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_LOG_SETTINGS_H_
#define WEEX_UIKIT_WML_LOG_SETTINGS_H_

#include "wml/log_level.h"

#include <string>

namespace wml {

// Settings which control the behavior of WML logging.
struct LogSettings {
  // The minimum logging level.
  // Anything at or above this level will be logged (if applicable).
  // Anything below this level will be silently ignored.
  //
  // The log level defaults to 0 (LOG_INFO).
  //
  // Log messages for WML_VLOG(x) (from wml/logging.h) are logged
  // at level -x, so setting the min log level to negative values enables
  // verbose logging.
  LogSeverity min_log_level = LOG_INFO;
};

// Gets the active log settings for the current process.
void SetLogSettings(const LogSettings& settings);

// Sets the active log settings for the current process.
LogSettings GetLogSettings();

// Gets the minimum log level for the current process. Never returs a value
// higher than LOG_FATAL.
int GetMinLogLevel();

}  // namespace wml

#endif  // WEEX_UIKIT_WML_LOG_SETTINGS_H_
