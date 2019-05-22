// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <TargetConditionals.h>
#include "txt/platform.h"

#if TARGET_OS_EMBEDDED || TARGET_OS_SIMULATOR
#include <UIKit/UIKit.h>
#define FONT_CLASS UIFont
#else  // TARGET_OS_EMBEDDED
#include <AppKit/AppKit.h>
#define FONT_CLASS NSFont
#endif  // TARGET_OS_EMBEDDED

namespace txt {

bool IsPlatformVersionAtLeast(size_t major, size_t minor=0, size_t patch=0) {
    const NSOperatingSystemVersion version = {
        .majorVersion = static_cast<NSInteger>(major),
        .minorVersion = static_cast<NSInteger>(minor),
        .patchVersion = static_cast<NSInteger>(patch),
    };
    return [[NSProcessInfo processInfo] isOperatingSystemAtLeastVersion:version];
}
    
std::string GetDefaultFontFamily() {
    if (IsPlatformVersionAtLeast(9)) {
        return [FONT_CLASS systemFontOfSize:14].familyName.UTF8String;
    } else {
        return "Helvetica";
    }
}

}  // namespace txt
