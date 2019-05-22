/*
 * Copyright (C) 2008, 2012 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WEEX_UIKIT_PLATFORM_GRAPHICS_GRADIENTGENERATEDIMAGE_H_
#define WEEX_UIKIT_PLATFORM_GRAPHICS_GRADIENTGENERATEDIMAGE_H_
#include "render/wtf/WTF.h"
#include "render/wtf/FastAllocBase.h"
#include "render/wtf/Forward.h"
#include "render/wtf/Noncopyable.h"
#include "render/wtf/PassOwnPtr.h"
#include "render/platform/geometry/IntSize.h"
#include "render/platform/graphics/Image.h"
#include "render/platform/graphics/GeneratedImage.h"
#include "render/platform/graphics/Gradient.h"

namespace blink {

class PLATFORM_EXPORT GradientGeneratedImage : public GeneratedImage{
 public:
  static PassRefPtr<GradientGeneratedImage> create(PassRefPtr<Gradient> generator, const IntSize& size);

 protected:
  virtual void draw(GraphicsContext*,
                    const FloatRect&,
                    const FloatRect&,
                    CompositeOperator,
                    WebBlendMode) override;
  virtual void drawPattern(GraphicsContext*,
                           const FloatRect&,
                           const FloatSize&,
                           const FloatPoint&,
                           CompositeOperator,
                           const FloatRect&,
                           WebBlendMode,
                           const IntSize& repeatSpacing) override;

private:
  GradientGeneratedImage(PassRefPtr<Gradient> generator, const IntSize& size)
      : m_gradient(generator) {
    m_size = size;
  }

  RefPtr<Gradient> m_gradient;
};

}  // namespace blink

#endif  // WEEX_UIKIT_PLATFORM_GRAPHICS_GRADIENTGENERATEDIMAGE_H_
