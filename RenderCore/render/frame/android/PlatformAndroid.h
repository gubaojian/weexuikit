//
// Created by furture on 2018/7/24.
//

#ifndef WEEX_UIKIT_PLATFORMANDROID_H
#define WEEX_UIKIT_PLATFORMANDROID_H
#include <render/public/platform/Platform.h>

namespace blink {


    class PlatformAndroid : public Platform{
    public:
        PlatformAndroid(){};
        ~PlatformAndroid(){}

        std::string defaultLocale() override;

        void getImageBitmap(const weexuikit::RequestImage& requestImage) override;
        void paintPlatformView(PaintPlatformView &viewInfo) override;
        void createPlatformView(const std::string& pageId, const std::string& ref, const std::string& type,
                                const std::map<std::string, std::string>& attrs,
                                const std::map<std::string, std::string>& style,
                                const std::set<std::string>& events)override;


        virtual void createExternalTexture(const std::string& pageId, const std::string& ref, const std::string &type,
                                           const std::map<std::string, std::string>& attr,
                                           const std::map<std::string, std::string>& style,
                                           const std::set<std::string>& events)override;


        virtual void paintExternalTexture(const std::string& pageId, const std::string& ref, SkCanvas* canvas,const LayoutRect& paintRect)override;


        virtual void deleteExternalTexture(const std::string& pageId, const std::string& ref)override;


    };
}


#endif //WEEX_UIKIT_PLATFORMANDROID_H
