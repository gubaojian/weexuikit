// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_WML_FILE_H_
#define WEEX_UIKIT_WML_FILE_H_

#include "wml/macros.h"
#include "wml/unique_fd.h"

namespace wml {

enum class OpenPermission {
  kRead = 1,
  kWrite = 1 << 1,
  kReadWrite = kRead | kWrite,
  kExecute,
};

wml::UniqueFD OpenFile(const char* path,
                       OpenPermission permission,
                       bool is_directory = false);

wml::UniqueFD OpenFile(const wml::UniqueFD& base_directory,
                       const char* path,
                       OpenPermission permission,
                       bool is_directory = false);

wml::UniqueFD Duplicate(wml::UniqueFD::element_type descriptor);

bool IsDirectory(const wml::UniqueFD& directory);

// Returns whether the given path is a file.
bool IsFile(const std::string& path);

}  // namespace wml

#endif  // WEEX_UIKIT_WML_FILE_H_
