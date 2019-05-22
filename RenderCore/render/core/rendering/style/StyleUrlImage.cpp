/*
 * Copyright (C) 2000 Lars Knoll (knoll@kde.org)
 *           (C) 2000 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2003, 2005, 2006, 2007, 2008 Apple Inc. All rights reserved.
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

#include <render/core/rendering/image/ImageResource.h>
#include <render/core/rendering/style/StyleUrlImage.h>
#include <render/core/rendering/RenderObject.h>
#include <render/platform/common/log.h>


namespace blink {

    StyleUrlImage::StyleUrlImage(PassOwnPtr<ImageResource>  imageResource)
        : mImageResource(imageResource)
    {

    }

    StyleUrlImage::~StyleUrlImage()
    {


    }

    bool StyleUrlImage::hasResourceImageCanRender(const blink::RenderObject *render)const{
        if(render->getNode() != nullptr){
            mImageResource->getImageInfo()->setNode(render->getNode());
        }
        PassRefPtr<Image>  image =  mImageResource->imageForRender(-1, -1);
        return image->canRender();
    }


    bool StyleUrlImage::canRender(const RenderObject& renderer) const
    {
        return StyleUrlImage::hasResourceImageCanRender(&renderer);
    }

    bool StyleUrlImage::isLoaded() const
    {
        return mImageResource->hasImage();
    }



    LayoutSize StyleUrlImage::imageSize(const RenderObject* renderer) const
    {
        return mImageResource->getContentSize();
    }

    bool StyleUrlImage::imageHasRelativeHeight() const {
        return false;
    }

    bool StyleUrlImage::imageHasRelativeWidth() const {
        return false;
    }


    void StyleUrlImage::computeIntrinsicDimensions(const RenderObject* renderObject, Length& intrinsicWidth, Length& intrinsicHeight, FloatSize& intrinsicRatio)
    {
        if(mImageResource->hasImage()){
            mImageResource->getImage()->computeIntrinsicDimensions(intrinsicWidth, intrinsicHeight, intrinsicRatio);
        }
    }

    bool StyleUrlImage::usesImageContainerSize() const
    {
        if(mImageResource->hasImage()){
            mImageResource->getImage()->usesContainerSize();
        }
        return true;
    }

    void StyleUrlImage::setContainerSizeForRenderer(const RenderObject* renderer, const IntSize& imageContainerSize)
    {
        if(mImageResource->hasImage()){
            mImageResource->getImage()->setContainerSize(imageContainerSize);
        }
    }

    void StyleUrlImage::addClient(RenderObject* renderer)
    {

    }

    void StyleUrlImage::removeClient(RenderObject* renderer)
    {

    }

    PassRefPtr<Image> StyleUrlImage::image(RenderObject* renderer, const IntSize& size)
    {
        if(renderer->getNode() != nullptr){
            mImageResource->getImageInfo()->setNode(renderer->getNode());
        }
        return mImageResource->imageForRender(size.width(), size.height());
    }

    bool StyleUrlImage::knownToBeOpaque(const RenderObject* renderer) const
    {
        if(mImageResource->hasImage()) {
            return mImageResource->getImage()->currentFrameKnownToBeOpaque();
        }
        return false;
    }

}
