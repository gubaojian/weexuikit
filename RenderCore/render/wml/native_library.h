// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_NATIVE_LIBRARY_H_
#define WEEX_UIKIT_WML_NATIVE_LIBRARY_H_

#include "wml/build_config.h"
#include "wml/macros.h"
#include "wml/memory/ref_counted.h"
#include "wml/memory/ref_ptr.h"

#if OS_WIN

#include <windows.h>

#endif  // OS_WIN

namespace wml {
class NativeLibrary : public wml::RefCountedThreadSafe<NativeLibrary> {
 public:
#if OS_WIN
  using Handle = HMODULE;
#else   // OS_WIN
  using Handle = void*;
#endif  // OS_WIN

  static wml::RefPtr<NativeLibrary> Create(const char* path);

  static wml::RefPtr<NativeLibrary> CreateWithHandle(
      Handle handle,
      bool close_handle_when_done);

  static wml::RefPtr<NativeLibrary> CreateForCurrentProcess();

  const uint8_t* ResolveSymbol(const char* symbol);

 private:
  Handle handle_ = nullptr;
  bool close_handle_ = true;

  NativeLibrary(const char* path);

  NativeLibrary(Handle handle, bool close_handle);

  ~NativeLibrary();

  Handle GetHandle() const;

  WML_DISALLOW_COPY_AND_ASSIGN(NativeLibrary);
  WML_FRIEND_REF_COUNTED_THREAD_SAFE(NativeLibrary);
  WML_FRIEND_MAKE_REF_COUNTED(NativeLibrary);
};

}  // namespace wml

#endif  // WEEX_UIKIT_WML_NATIVE_LIBRARY_H_
