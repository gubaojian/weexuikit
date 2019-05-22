// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_MACROS_H_
#define WEEX_UIKIT_WML_MACROS_H_

#ifndef WML_USED_ON_EMBEDDER

#define WML_EMBEDDER_ONLY [[deprecated]]

#else  // WML_USED_ON_EMBEDDER

#define WML_EMBEDDER_ONLY

#endif  // WML_USED_ON_EMBEDDER

#define WML_DISALLOW_COPY(TypeName) TypeName(const TypeName&) = delete

#define WML_DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

#define WML_DISALLOW_MOVE(TypeName) \
  TypeName(TypeName&&) = delete;    \
  TypeName& operator=(TypeName&&) = delete

#define WML_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;          \
  TypeName& operator=(const TypeName&) = delete

#define WML_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;               \
  TypeName(TypeName&&) = delete;                    \
  TypeName& operator=(const TypeName&) = delete;    \
  TypeName& operator=(TypeName&&) = delete

#define WML_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                               \
  WML_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName)

#endif  // WEEX_UIKIT_WML_MACROS_H_
