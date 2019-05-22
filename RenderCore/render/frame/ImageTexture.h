//
// Created by furture on 2018/12/27.
//

#ifndef WEEX_UIKIT_IMAGE_TEXTURE_H
#define WEEX_UIKIT_IMAGE_TEXTURE_H


#include <third_party/skia/src/gpu/GrDrawOpTest.h>
#include <third_party/skia/include/core/SkImage.h>
#include <set>


namespace weexuikit{

    enum class ImageState{
        Loading,
        Textured,
        Failed
    };

    class ImageTexture {


        public:
            ImageTexture();
            ~ImageTexture();

        public:

           inline ImageState getState(){
               return mState;
           }

           inline void setState(ImageState state){
               mState = state;
           }

           inline sk_sp<SkImage> getImage(){
               return mImage;
           }

           inline bool isMatchKey(std::string& imageKey){
               return mState == ImageState::Textured
                      && mImage.get() != nullptr
                      && mImageKey == imageKey;
           }

           inline void setImage(sk_sp<SkImage> image){
               mImage = image;
               mState = ImageState::Textured;
           }

           inline std::string& getImageKey(){
               return mImageKey;
           }

           inline void setImageKey(std::string imageKey){
               mImageKey = imageKey;
           }

           std::set<std::string> getWatchPageIds(){
               return mWatchPageIds;
           }

           void clearWatchPageIds(){
               mWatchPageIds.clear();
           }

           void  addWatchPageId(const std::string& pageId){
               mWatchPageIds.insert(pageId);
           }

        private:
            std::set<std::string> mWatchPageIds;
            sk_sp<SkImage> mImage;
            ImageState mState;
            std::string mImageKey;
    };

}


#endif //WEEX_UIKIT_IMAGECACHE_H
