/*
 * Copyright (C) 1999 Lars Knoll <knoll@kde.org>
 * Copyright (C) 1999 Antti Koivisto <koivisto@kde.org>
 * Copyright (C) 2000 Dirk Mueller <mueller@kde.org>
 * Copyright (C) 2006 Allan Sandfeld Jensen <kde@carewolf.com>
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 * Copyright (C) 2003, 2004, 2005, 2006, 2008, 2009, 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2010 Google Inc. All rights reserved.
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
#include "render/core/rendering/RenderImageResource.h"
#include "render/core/rendering/RenderImage.h"
#include "render/core/rendering/RenderObject.h"
#include "render/public/platform/Platform.h"
#include "third_party/skia/include/core/SkBitmap.h"


namespace blink {

RenderImageResource::RenderImageResource()
    : m_renderer(0)
{
    m_imageInfo = new ImageInfo();
}

RenderImageResource::~RenderImageResource()
{
    delete  m_imageInfo;
    m_imageInfo = nullptr;
}

void RenderImageResource::initialize(RenderObject* renderer)
{
    ASSERT(!m_renderer);
    ASSERT(renderer);
    m_renderer = renderer;
}

void RenderImageResource::shutdown()
{
    ASSERT(m_renderer);
}

    PassRefPtr<Image> RenderImageResource::imageForRenderTest(StaticTextureImage*  bitmap){
        RefPtr<Image> refPtr = adoptRef(bitmap);
        return refPtr;
    }

PassRefPtr<Image> RenderImageResource::imageForRender(int width, int height){
            if(hasImage()){
                return m_imageRef;
            }
            if(!m_imageInfo->hasImage()){
                return Image::nullImage();
            }
            m_imageInfo->setContentSize(contentSize);
            m_imageInfo->setImageUrl(imageUrl);
            m_imageRef = StaticTextureImage::create(m_imageInfo);
           return m_imageRef;
}

void RenderImageResource::setImageUrl(std::string url){
    imageUrl = url;
    m_imageInfo->setImageUrl(url);
}



void RenderImageResource::resetAnimation()
{
    ASSERT(m_renderer);

    if (!hasImage())
        return;
    //image()->resetAnimation();

    //m_renderer->setShouldDoFullPaintInvalidation();
}



LayoutSize RenderImageResource::getImageSize(float multiplier, int type) const
{
    if (!hasImage())
        return LayoutSize();
    return LayoutSize(contentSize.width(), contentSize.height());
}

} // namespace blink
