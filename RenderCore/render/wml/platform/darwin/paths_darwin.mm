// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/paths.h"

#include <Foundation/Foundation.h>

namespace wml {
namespace paths {

std::pair<bool, std::string> GetExecutableDirectoryPath() {
  return {true, GetDirectoryName([NSBundle mainBundle].executablePath.UTF8String)};
}

}  // namespace paths
}  // namespace wml
