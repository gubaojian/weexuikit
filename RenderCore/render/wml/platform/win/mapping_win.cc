// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/mapping.h"

#include <fcntl.h>
#include <io.h>
#include <windows.h>

#include <type_traits>

#include "wml/file.h"
#include "wml/platform/win/wstring_conversion.h"

namespace wml {

Mapping::Mapping() = default;

Mapping::~Mapping() = default;

FileMapping::FileMapping(const std::string& path, bool executable)
    : FileMapping(OpenFile(path.c_str(),
                           executable ? OpenPermission::kExecute
                                      : OpenPermission::kRead,
                           false),
                  executable) {}

FileMapping::FileMapping(const wml::UniqueFD& fd, bool executable)
    : size_(0), mapping_(nullptr) {
  if (!fd.is_valid()) {
    return;
  }

  if (auto size = ::GetFileSize(fd.get(), nullptr)) {
    if (size > 0) {
      size_ = size;
    } else {
      return;
    }
  }

  const DWORD protect = executable ? PAGE_EXECUTE_READ : PAGE_READONLY;

  mapping_handle_.reset(::CreateFileMapping(fd.get(),  // hFile
                                            nullptr,   // lpAttributes
                                            protect,   // flProtect
                                            0,         // dwMaximumSizeHigh
                                            0,         // dwMaximumSizeLow
                                            nullptr    // lpName
                                            ));

  if (!mapping_handle_.is_valid()) {
    return;
  }

  const DWORD desired_access = executable ? FILE_MAP_ALL_ACCESS : FILE_MAP_READ;

  mapping_ = reinterpret_cast<uint8_t*>(
      MapViewOfFile(mapping_handle_.get(), desired_access, 0, 0, size_));
}

FileMapping::~FileMapping() {
  if (mapping_ != nullptr) {
    UnmapViewOfFile(mapping_);
  }
}

size_t FileMapping::GetSize() const {
  return size_;
}

const uint8_t* FileMapping::GetMapping() const {
  return mapping_;
}

}  // namespace wml
