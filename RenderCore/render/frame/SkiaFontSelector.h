//
// Created by furture on 2018/8/7.
//

#ifndef WEEX_UIKIT_SKIAFONTSELECTOR_H
#define WEEX_UIKIT_SKIAFONTSELECTOR_H
#include <render/platform/fonts/FontData.h>
#include <render/platform/fonts/FontSelector.h>
#include <render/platform/fonts/FontCacheKey.h>
#include <render/platform/fonts/SimpleFontData.h>
#include <map>

namespace weexuikit {

    typedef HashMap<blink::FontCacheKey, RefPtr<blink::SimpleFontData>, blink::FontCacheKeyHash, blink::FontCacheKeyTraits> FontPlatformDataCache;

    class SkiaFontSelector : public blink::FontSelector {
    public:

        static PassRefPtr<SkiaFontSelector> create() {
            return adoptRef(new SkiaFontSelector());
        }

        PassRefPtr<blink::FontData> getFontData(const blink::FontDescription& fontDescription, const AtomicString& familyName);
        void willUseFontData(const blink::FontDescription&,  const AtomicString& familyName, UChar32);
        unsigned version() const;
        void fontCacheInvalidated();

        void addFont(std::string& fontFamily, std::string& fontPath);

        bool hasFont(std::string& fontFamily, std::string& fontPath);

    private:
        sk_sp<SkTypeface> getFontTypeface(const blink::FontDescription &fontDescription, const AtomicString &familyName);

        FontPlatformDataCache fontPlatformDataCache;
        HashMap<AtomicString, AtomicString> fontFamilyPathConfig;
    };
}


#endif //WEEX_UIKIT_SKIAFONTSELECTOR_H
