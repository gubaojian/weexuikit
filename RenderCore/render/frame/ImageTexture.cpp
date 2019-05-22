//
// Created by furture on 2018/12/27.
//

#include "ImageTexture.h"

namespace weexuikit{

    ImageTexture::ImageTexture() {
        mState = ImageState::Loading;
        mImage.reset(nullptr);
    }

    ImageTexture::~ImageTexture() {
        mImage.reset(nullptr);
        mState = ImageState::Failed;
    }
}