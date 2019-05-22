/*
 * Copyright (C) 1999 Lars Knoll <knoll@kde.org>
 * Copyright (C) 1999 Antti Koivisto <koivisto@kde.org>
 * Copyright (C) 2006 Allan Sandfeld Jensen <kde@carewolf.com>
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 * Copyright (C) 2004, 2005, 2006, 2007, 2009, 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2010 Patrick Gansterer <paroga@paroga.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef RenderImageResource_h
#define RenderImageResource_h

#include "render/wtf/WTF.h"
#include "render/wtf/FastAllocBase.h"
#include "render/wtf/Forward.h"
#include "render/wtf/Noncopyable.h"
#include "render/wtf/PassOwnPtr.h"
#include "render/platform/graphics/Image.h"
#include "render/platform/graphics/ImageInfo.h"
#include "render/platform/graphics/StaticTextureImage.h"
#include "render/platform/geometry/LayoutSize.h"



namespace blink {

class RenderObject;

class RenderImageResource {
    WTF_MAKE_NONCOPYABLE(RenderImageResource);
    WTF_MAKE_FAST_ALLOCATED;
public:
    virtual ~RenderImageResource();

    static PassOwnPtr<RenderImageResource> create()
    {
        return adoptPtr(new RenderImageResource);
    }

    virtual void initialize(RenderObject*);
    virtual void shutdown();

    IntSize getContentSize(){
        return contentSize;
    }
    void setImageUrl(std::string imageUrl);
    virtual bool hasImage() const {
        return m_imageInfo != nullptr  && m_imageRef.get() != nullptr && m_imageInfo->hasImage();
    }

    ImageInfo* getImageInfo(){
        return m_imageInfo;
    }


    void resetAnimation();
    PassRefPtr<blink::Image> imageForRenderTest(blink::StaticTextureImage*);
    PassRefPtr<Image> imageForRender(int/* width */, int/* height */);
    virtual bool errorOccurred() const { return !hasImage(); }

    virtual void setContainerSizeForRenderer(const IntSize& size){
        contentSize =  size;
        m_imageInfo->setContentSize(size);
    };

    virtual bool imageHasRelativeWidth() const {
        return false;
    }
    virtual bool imageHasRelativeHeight() const {
        return false;
    }

    virtual LayoutSize imageSize(float multiplier) const { return getImageSize(multiplier, 0); }
    virtual LayoutSize intrinsicSize(float multiplier) const { return getImageSize(multiplier, 1); }


protected:
    RenderImageResource();
    RenderObject* m_renderer;
    std::string imageUrl;
    IntSize  contentSize;
    ImageInfo* m_imageInfo;
    RefPtr<Image> m_imageRef;

private:
    LayoutSize getImageSize(float multiplier,int sizeType) const;
};

} // namespace blink

#endif // RenderImage_h
