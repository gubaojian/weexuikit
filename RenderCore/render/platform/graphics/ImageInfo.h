//
// Created by furture on 2018/7/18.
//

#ifndef WEEXRENDER_IMAGEINFO_H
#define WEEXRENDER_IMAGEINFO_H

#include "render/platform/geometry/IntSize.h"
#include<string>
#include <atomic>
#include <third_party/skia/src/core/SkNextID.h>
#include <sstream>
#include <render/frame/JenkinsHash.h>


namespace blink {



    enum ImageScaleType{
        STRETCH,
        CENTER_CROP,
        CENTER_FIT
    };

    static inline uint32_t hashString(const std::string& str){
        uint32_t key  =  android::JenkinsHashMixBytes(7, (uint8_t *)str.data(), str.length());
        key  = android::JenkinsHashWhiten(key);
        return key;
    }


    class ImageInfo {

    public:
        ImageInfo(){ //FIXME Refactor
            imageUrl = "";
            mUseSourceSize = false;
            mImageHashKey = 0;
            mPlaceHolderHashKey = 0;
            contentSize = {0, 0};
            imageSize = {0, 0};
            opaque = false;
            renderCtx = nullptr;
            scaleType = STRETCH;
            nodePtr = nullptr;
        };
        void setImageUrl(std::string url){
            this->imageUrl = url;
            this->mImageKey.clear();
        }

        std::string &getPlaceholder(){
            return placeholder;
        }

        void setPlaceholder(std::string placeholderStr){
            this->placeholder = placeholderStr;
        }

        std::string &getImageUrl(){
            return imageUrl;
        }

        std::string& getImageKey(){
            if(mImageKey.length() <= 0){
                std::ostringstream os;
                os << imageUrl;
                os << "|";
                os << contentSize.width();
                os << "|";
                os << contentSize.height();
                mImageKey = os.str();
                mImageHashKey = hashString(mImageKey);
            }
            return mImageKey;
        }

        inline uint32_t getImageHashKey(){
            return mImageHashKey;
        }

        std::string& getPlaceHolderKey(){
            if(mPlaceHolderKey.length() <= 0){
                std::ostringstream os;
                os << placeholder;
                os << "|";
                os << contentSize.width();
                os << "|";
                os << contentSize.height();
                mPlaceHolderKey = os.str();
                mPlaceHolderHashKey = hashString(mPlaceHolderKey);
            }
            return mPlaceHolderKey;
        }

        inline int32_t  getPlaceHolderHashKey(){
            return mPlaceHolderHashKey;
        }

        void setContentSize(const IntSize& size){
            contentSize = size;
        }

        IntSize &getContentSize(){
            return contentSize;
        }

        void setImageSize(IntSize& size){
            imageSize = size;
        }

        IntSize &getImageSize(){
            return imageSize;
        }

        void setOpaque(bool op){
            this->opaque = op;
        }

        bool  getOpaque(){
            return opaque;
        }

        ImageScaleType getScaleType(){
            return scaleType;
        }

        void setScaleType(ImageScaleType scaleType_){
            this->scaleType = scaleType_;
        }



        bool hasImage(){
            return imageUrl.length() > 0 || placeholder.length() > 0;
        }

        void* getRenderCtx(){
            return renderCtx;
        }

        void setRenderCtx(void* ctx){
            this->renderCtx = ctx;
        }

        void* getNode(){
            return nodePtr;
        }

        void setNode(void* node){
           this->nodePtr = node;
        }

        bool getUseSourceSize(){
            return mUseSourceSize;
        }

        void setUseSourceSize(bool sourceSize){
            mUseSourceSize = sourceSize;
        }

    private:
        bool mUseSourceSize;
        std::string mImageKey; //FIXME Reduce Hash
        uint32_t mImageHashKey;
        std::string mPlaceHolderKey;
        uint32_t mPlaceHolderHashKey;
        std::string imageUrl;
        std::string placeholder;
        IntSize  contentSize;
        IntSize  imageSize;
        ImageScaleType scaleType;
        bool  opaque;
        void* renderCtx;
        void* nodePtr;
    };


}

#endif //WEEXRENDER_IMAGEINFO_H
