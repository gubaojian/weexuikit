//
//  PlatformIOS.hpp
//  weexuikit
//
//  Created by qz on 10/26/18.
//

#ifndef PlatformIOS_hpp
#define PlatformIOS_hpp

#include <stdio.h>

#include <render/public/platform/Platform.h>

namespace blink {
    
    class PlatformIOS : public Platform{
    public:
        PlatformIOS(){};
        ~PlatformIOS(){}
        
        std::string defaultLocale() override;
        SkBitmap getImageBitmap(ImageInfo *imageInfo) override;
        
    };
}



#endif /* PlatformIOS_hpp */
