// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_PLATFORM_DARWIN_PLATFORM_VERSION_H_
#define WEEX_UIKIT_WML_PLATFORM_DARWIN_PLATFORM_VERSION_H_

#include <sys/types.h>
#include "wml/macros.h"

namespace wml {

bool IsPlatformVersionAtLeast(size_t major, size_t minor = 0, size_t patch = 0);

}  // namespace wml

#endif  // WEEX_UIKIT_WML_PLATFORM_DARWIN_PLATFORM_VERSION_H_
