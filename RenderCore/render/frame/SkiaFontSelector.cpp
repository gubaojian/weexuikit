//
// Created by furture on 2018/8/7.
//

#include <third_party/skia/include/core/SkStream.h>
#include <third_party/skia/include/core/SkTypeface.h>
#include <third_party/skia/include/ports/SkFontMgr.h>
#include <render/platform/fonts/FontTraits.h>
#include <render/platform/fonts/FontDescription.h>
#include <render/platform/fonts/FontPlatformData.h>
#include <render/platform/fonts/SimpleFontData.h>


#include "SkiaFontSelector.h"


namespace weexuikit {



    PassRefPtr<blink::FontData> SkiaFontSelector::getFontData(const blink::FontDescription &fontDescription,
                                       const AtomicString &familyName) {
        blink::FontFaceCreationParams creationParams(familyName);
        blink::FontCacheKey key = fontDescription.cacheKey(creationParams);
        RefPtr<blink::SimpleFontData> fontData = fontPlatformDataCache.get(key);
        if(fontData == nullptr){
            sk_sp<SkTypeface> typeface = getFontTypeface(fontDescription, familyName);
            if(typeface == nullptr || !typeface){
                return nullptr;
            }
            bool synthetic_bold =
                    (fontDescription.weight() >= blink::FontWeight600 && !typeface->isBold()) ||
                    fontDescription.isSyntheticBold();
            bool synthetic_italic =
                    (fontDescription.style() && !typeface->isItalic()) ||
                    fontDescription.isSyntheticItalic();
            blink::FontPlatformData platform_data(typeface, familyName.utf8().data(),
                                                  fontDescription.effectiveFontSize(),
                                                  synthetic_bold, synthetic_italic,
                                                  fontDescription.orientation(),
                                                  fontDescription.useSubpixelPositioning());
            fontData = blink::SimpleFontData::create(platform_data, blink::CustomFontData::create());
            fontPlatformDataCache.set(key, fontData);
        }
        return fontData;
    }

    sk_sp<SkTypeface> SkiaFontSelector::getFontTypeface(const blink::FontDescription &fontDescription, const AtomicString &familyName){
        auto it = fontFamilyPathConfig.find(familyName);
        if(it == fontFamilyPathConfig.end()){
            return nullptr;
        }
        AtomicString fontPath = it->value;
        sk_sp<SkTypeface> typeface = SkFontMgr::RefDefault()->makeFromFile(fontPath.utf8().data());
        return typeface;
    }

    void SkiaFontSelector::addFont(std::string& fontFamily, std::string& fontPath) {
        AtomicString fontFamilyKey = WTF::String::fromUTF8(fontFamily.c_str());
        AtomicString fontPathValue = WTF::String::fromUTF8(fontPath.c_str());
        fontFamilyPathConfig.set(fontFamilyKey, fontPathValue);
        fontPlatformDataCache.clear();
    }

    bool SkiaFontSelector::hasFont(std::string &fontFamily, std::string &fontPath) {
        AtomicString fontFamilyKey = WTF::String::fromUTF8(fontFamily.c_str());
        AtomicString fontPathValue = WTF::String::fromUTF8(fontPath.c_str());
        auto it = fontFamilyPathConfig.find(fontFamilyKey);
        bool hasFontFamily = false;
        if(it != fontFamilyPathConfig.end()){
            hasFontFamily = (fontPathValue == it->value);
        }
        return hasFontFamily;
    }

    void SkiaFontSelector::willUseFontData(const blink::FontDescription &,
                                           const AtomicString &familyName, UChar32) {

    }



    unsigned SkiaFontSelector::version() const {
        return 0;
    }

    void SkiaFontSelector::fontCacheInvalidated() {

    }
}
