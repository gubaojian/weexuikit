/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WEEX_UIKIT_PUBLIC_PLATFORM_PLATFORM_H_
#define WEEX_UIKIT_PUBLIC_PLATFORM_PLATFORM_H_

#include <string>
#include <map>
#include <render/platform/graphics/PaintPlatformView.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <set>
#include "render/frame/RequestImage.h"
#include "render/public/platform/WebCommon.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "render/platform/graphics/ImageInfo.h"
#include "render/platform/fonts/FontSelector.h"

namespace blink {
class WebDiscardableMemory;

class Platform {
 public:
      // HTML5 Database ------------------------------------------------------
      typedef int FileHandle;

      BLINK_PLATFORM_EXPORT static void initialize(Platform*);
      BLINK_PLATFORM_EXPORT static void shutdown();
      BLINK_PLATFORM_EXPORT static Platform* current();

      // Allocates discardable memory. May return 0, even if the platform supports
      // discardable memory. If nonzero, however, then the WebDiscardableMmeory is
      // returned in an locked state. You may use its underlying data() member
      // directly, taking care to unlock it when you are ready to let it become
      // discardable.
      virtual WebDiscardableMemory* allocateAndLockDiscardableMemory(size_t bytes) {
        return 0;
      }

     // System --------------------------------------------------------------

     // Returns a value such as "en-US".
     virtual std::string defaultLocale() { return "zh-CN"; }

     virtual void getImageBitmap(const weexuikit::RequestImage& requestImage)=0;

     virtual void paintPlatformView(PaintPlatformView &syncView)=0;

     virtual void createPlatformView(const std::string& pageId, const std::string& ref, const std::string& type,
                                     const std::map<std::string, std::string>& attrs,
                                     const std::map<std::string, std::string>& style,
                                     const std::set<std::string>& events)=0;

    /**
     * called in io thread
     * */
    virtual void createExternalTexture(const std::string& pageId, const std::string& ref,const std::string &type,
             const std::map<std::string, std::string>& attr,
             const std::map<std::string, std::string>& style,
             const std::set<std::string> &events)=0;


    virtual void paintExternalTexture(const std::string& pageId, const std::string& ref, SkCanvas* canvas, const LayoutRect& paintRect)=0;


    virtual void deleteExternalTexture(const std::string& pageId, const std::string& ref)=0;



    PassRefPtr<FontSelector> fontSelector() {
        return mFontSelector;
    }

    void setFontSelector(PassRefPtr<FontSelector> selector) {
        mFontSelector = selector;
    }

    virtual ~Platform() {}

private:
    RefPtr<FontSelector> mFontSelector;
};

}  // namespace blink

#endif  // WEEX_UIKIT_PUBLIC_PLATFORM_PLATFORM_H_
