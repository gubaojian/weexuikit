// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/file.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "wml/eintr_wrapper.h"

namespace wml {

wml::UniqueFD OpenFile(const char* path,
                       OpenPermission permission,
                       bool is_directory) {
  return OpenFile(wml::UniqueFD{AT_FDCWD}, path, permission, is_directory);
}

wml::UniqueFD OpenFile(const wml::UniqueFD& base_directory,
                       const char* path,
                       OpenPermission permission,
                       bool is_directory) {
  if (path == nullptr) {
    return wml::UniqueFD{};
  }

  int flags = 0;
  switch (permission) {
    case OpenPermission::kRead:
      flags = O_RDONLY;
      break;
    case OpenPermission::kWrite:
      flags = O_WRONLY;
      break;
    case OpenPermission::kReadWrite:
      flags = O_RDWR;
      break;
    case OpenPermission::kExecute:
      flags = O_RDONLY;
      break;
  }

  if (is_directory) {
    flags |= O_DIRECTORY;
  }

  return wml::UniqueFD{
      WML_HANDLE_EINTR(::openat(base_directory.get(), path, flags))};
}

wml::UniqueFD Duplicate(wml::UniqueFD::element_type descriptor) {
  return wml::UniqueFD{WML_HANDLE_EINTR(::dup(descriptor))};
}

bool IsDirectory(const wml::UniqueFD& directory) {
  if (!directory.is_valid()) {
    return false;
  }

  struct stat stat_result = {};

  if (::fstat(directory.get(), &stat_result) != 0) {
    return false;
  }

  return S_ISDIR(stat_result.st_mode);
}

bool IsFile(const std::string& path) {
  struct stat buf;
  if (stat(path.c_str(), &buf) != 0)
    return false;
  return S_ISREG(buf.st_mode);
}

}  // namespace wml
