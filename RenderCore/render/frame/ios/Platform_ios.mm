//
//  PlatformIOS.cpp
//  weexuikit
//
//  Created by qz on 10/26/18.
//

#include <UIKit/UIKit.h>

#import "UIImageView+WebCache.h"
#include "Platform_ios.h"
#include <third_party/skia/include/core/SkImage.h>
#include <third_party/skia/include/utils/mac/SkCGUtils.h>

namespace blink {
    
    std::string PlatformIOS::defaultLocale() {
        return "zh-CN";
    }
    
    SkBitmap PlatformIOS::getImageBitmap(ImageInfo *imageInfo) {
        SkBitmap bitmap;
        std::string imageurl = imageInfo->getImageUrl();
        NSString *ocurlstring = @(imageurl.c_str());
        if (![ocurlstring hasPrefix:@"https:"]) {
            ocurlstring = [@"https:" stringByAppendingString:ocurlstring];
        }
        NSURL *url = [NSURL URLWithString:ocurlstring];
        UIImageView *imageView = [UIImageView new];
        [imageView sd_setImageWithURL:url placeholderImage:[UIImage imageNamed:@"1.jpg"]];
        CGImageRef ref = imageView.image.CGImage;
        
//        __block CGImageRef ref;
//        SDWebImageManager *manager = [SDWebImageManager sharedManager] ;
//        [manager downloadImageWithURL:url options:0 progress:^(NSInteger   receivedSize, NSInteger expectedSize) {
//        }  completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType,   BOOL finished, NSURL *imageURL) {
//            if (image) {
//                ref = [image CGImage];
//            }
//        }];
                
//        UIImage *uiimage = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
//        CGImageRef ref = [uiimage CGImage];
        
        if (!SkCreateBitmapFromCGImage(&bitmap, ref)) {
            return bitmap;
        }
        return bitmap;
    }
    
}
