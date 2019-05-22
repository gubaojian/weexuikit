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

#ifndef ImageResource_h
#define ImageResource_h

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

    class ImageResource {
        WTF_MAKE_NONCOPYABLE(ImageResource); WTF_MAKE_FAST_ALLOCATED;
    public:
        virtual ~ImageResource();

        static PassOwnPtr<ImageResource> create()
        {
            return adoptPtr(new ImageResource);
        }

        virtual bool hasImage() const {
            return mImageInfo != nullptr
                   && mImage.get() != nullptr
                   && !mImage->isNull()
                   && mImageInfo->hasImage();
        }

        ImageInfo* getImageInfo(){
            return mImageInfo;
        }

        void setImageUrl(std::string imageUrl);


        PassRefPtr<Image> imageForRender(int width, int height);

        virtual void setContainerSize(const IntSize &size){
            mContentSize =  size;
            mImageInfo->setContentSize(size);
        };

        IntSize getContentSize(){
            return mContentSize;
        }

        RefPtr<Image> getImage(){
            return mImage;
        }


        virtual LayoutSize imageSize(float multiplier) const { return getImageSize(multiplier, 0); }
        virtual LayoutSize intrinsicSize(float multiplier) const { return getImageSize(multiplier, 1); }


        protected:
            ImageResource();
            std::string mImageUrl;
            IntSize  mContentSize;
            ImageInfo* mImageInfo;
            RefPtr<Image> mImage;

        private:
            LayoutSize getImageSize(float multiplier,int sizeType) const;
    };

} // namespace blink

#endif // ImageResource_h
