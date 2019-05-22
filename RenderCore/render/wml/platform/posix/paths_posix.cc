// Copyright 2018 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/paths.h"

#include <limits.h>
#include <unistd.h>

#include "wml/logging.h"

namespace wml {
namespace paths {

namespace {

constexpr char kFileURLPrefix[] = "file://";
constexpr size_t kFileURLPrefixLength = sizeof(kFileURLPrefix) - 1;

std::string GetCurrentDirectory() {
  char buffer[PATH_MAX];
  WML_CHECK(getcwd(buffer, sizeof(buffer)));
  return std::string(buffer);
}

}  // namespace

std::string AbsolutePath(const std::string& path) {
  if (path.size() > 0) {
    if (path[0] == '/') {
      // Path is already absolute.
      return path;
    }
    return GetCurrentDirectory() + "/" + path;
  } else {
    // Path is empty.
    return GetCurrentDirectory();
  }
}

std::string GetDirectoryName(const std::string& path) {
  size_t separator = path.rfind('/');
  if (separator == 0u)
    return "/";
  if (separator == std::string::npos)
    return std::string();
  return path.substr(0, separator);
}

std::string FromURI(const std::string& uri) {
  if (uri.substr(0, kFileURLPrefixLength) != kFileURLPrefix)
    return uri;

  std::string file_path = uri.substr(kFileURLPrefixLength);
  return SanitizeURIEscapedCharacters(file_path);
}

}  // namespace paths
}  // namespace wml
