// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_LOGGING_H_
#define WEEX_UIKIT_WML_LOGGING_H_

#include <sstream>

#include "wml/log_level.h"
#include "wml/macros.h"

namespace wml {

class LogMessageVoidify {
 public:
  void operator&(std::ostream&) {}
};

class LogMessage {
 public:
  LogMessage(LogSeverity severity,
             const char* file,
             int line,
             const char* condition);
  ~LogMessage();

  std::ostream& stream() { return stream_; }

 private:
  std::ostringstream stream_;
  const LogSeverity severity_;
  const char* file_;
  const int line_;

  WML_DISALLOW_COPY_AND_ASSIGN(LogMessage);
};

// Gets the WML_VLOG default verbosity level.
int GetVlogVerbosity();

// Returns true if |severity| is at or above the current minimum log level.
// LOG_FATAL and above is always true.
bool ShouldCreateLogMessage(LogSeverity severity);

}  // namespace wml

#define WML_LOG_STREAM(severity) \
  ::wml::LogMessage(::wml::LOG_##severity, __FILE__, __LINE__, nullptr).stream()

#define WML_LAZY_STREAM(stream, condition) \
  !(condition) ? (void)0 : ::wml::LogMessageVoidify() & (stream)

#define WML_EAT_STREAM_PARAMETERS(ignored) \
  true || (ignored)                        \
      ? (void)0                            \
      : ::wml::LogMessageVoidify() &       \
            ::wml::LogMessage(::wml::LOG_FATAL, 0, 0, nullptr).stream()

#define WML_LOG_IS_ON(severity) \
  (::wml::ShouldCreateLogMessage(::wml::LOG_##severity))

#define WML_LOG(severity) \
  WML_LAZY_STREAM(WML_LOG_STREAM(severity), WML_LOG_IS_ON(severity))

#define WML_CHECK(condition)                                              \
  WML_LAZY_STREAM(                                                        \
      ::wml::LogMessage(::wml::LOG_FATAL, __FILE__, __LINE__, #condition) \
          .stream(),                                                      \
      !(condition))

#define WML_VLOG_IS_ON(verbose_level) \
  ((verbose_level) <= ::wml::GetVlogVerbosity())

// The VLOG macros log with negative verbosities.
#define WML_VLOG_STREAM(verbose_level) \
  ::wml::LogMessage(-verbose_level, __FILE__, __LINE__, nullptr).stream()

#define WML_VLOG(verbose_level) \
  WML_LAZY_STREAM(WML_VLOG_STREAM(verbose_level), WML_VLOG_IS_ON(verbose_level))

#ifndef NDEBUG
#define WML_DLOG(severity) WML_LOG(severity)
#define WML_DCHECK_(condition) WML_CHECK(condition)
#else
#define WML_DLOG(severity) WML_EAT_STREAM_PARAMETERS(true)
#define WML_DCHECK_(condition) WML_EAT_STREAM_PARAMETERS(condition)
#endif

#define WML_NOTREACHED() WML_DCHECK_(false)

#define WML_NOTIMPLEMENTED() \
  WML_LOG(ERROR) << "Not implemented in: " << __PRETTY_FUNCTION__

#endif  // WEEX_UIKIT_WML_LOGGING_H_
