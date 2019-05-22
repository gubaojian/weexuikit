// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/unique_fd.h"

#include "wml/eintr_wrapper.h"

namespace wml {
namespace internal {

#if OS_WIN

namespace win {

void UniqueFDTraits::Free(HANDLE fd) {
  CloseHandle(fd);
}

}  // namespace win

#else  // OS_WIN

namespace unixFD {

void UniqueFDTraits::Free(int fd) {
  close(fd);
}

}  // namespace unix

#endif  // OS_WIN

}  // namespace internal
}  // namespace wml
