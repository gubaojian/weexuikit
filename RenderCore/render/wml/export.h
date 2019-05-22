// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_EXPORT_H_
#define WEEX_UIKIT_WML_EXPORT_H_

#include "wml/build_config.h"

#if OS_WIN
#define WML_EXPORT __declspec(dllimport)
#else
#define WML_EXPORT __attribute__((visibility("default")))
#endif

#endif  // WEEX_UIKIT_WML_EXPORT_H_
