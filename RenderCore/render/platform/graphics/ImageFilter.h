// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_PLATFORM_GRAPHICS_IMAGEFILTER_H_
#define WEEX_UIKIT_PLATFORM_GRAPHICS_IMAGEFILTER_H_

#include "render/platform/geometry/FloatRect.h"

class SkImageFilter;

namespace blink {

PLATFORM_EXPORT FloatRect mapImageFilterRect(SkImageFilter*, const FloatRect&);

}  // namespace blink

#endif  // WEEX_UIKIT_PLATFORM_GRAPHICS_IMAGEFILTER_H_
