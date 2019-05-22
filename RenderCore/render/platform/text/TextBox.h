// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEEX_UIKIT_PLATFORM_TEXT_TEXTBOX_H_
#define WEEX_UIKIT_PLATFORM_TEXT_TEXTBOX_H_

#include "render/platform/text/TextDirection.h"
#include "third_party/skia/include/core/SkRect.h"

namespace blink {

class TextBox {
 public:
  TextBox() : is_null(true) {}
  TextBox(SkRect r, TextDirection direction)
      : sk_rect(std::move(r)), direction(direction), is_null(false) {}

  SkRect sk_rect;
  TextDirection direction;
  bool is_null;
};

}  // namespace blink

#endif  // WEEX_UIKIT_PLATFORM_TEXT_TEXTBOX_H_
