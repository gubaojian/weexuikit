//
// Created by furture on 2018/7/13.
//

#include "SkiaFontSelector.h"
#include "RenderBodyHelper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <render/platform/Partitions.h>
#include <render/core/rendering/RenderView.h>
#include <render/core/rendering/RenderText.h>
#include <render/core/rendering/RenderImage.h>
#include <render/core/rendering/RenderImageResource.h>
#include <render/core/rendering/RenderParagraph.h>
#include <render/core/rendering/RenderInline.h>
#include <render/platform/geometry/IntSize.h>
#include <render/core/rendering/SubtreeLayoutScope.h>
#include <render/core/rendering/RenderBlock.h>
#include <render/core/rendering/style/RenderStyle.h>
#include <render/core/rendering/RenderFlexibleBox.h>
#include <render/core/rendering/PaintInfo.h>
#include <third_party/skia/include/core/SkTypeface.h>
#include <third_party/skia/include/ports/SkFontMgr.h>
#include <third_party/skia/include/core/SkCanvas.h>
#include <third_party/skia/include/core/SkSurface.h>
#include <third_party/skia/include/core/SkRRect.h>
#include <third_party/skia/src/image/SkImage_Base.h>
#include "render/wtf/MainThread.h"
#include "render/wtf/WTF.h"
#include "render/wtf/text/AtomicString.h"
#include "render/wtf/text/TextEncoding.h"
#include <render/public/RendererEngine.h>
#include <render/platform/text/LocaleToScriptMapping.h>
#include <render/core/rendering/LayerPaintingInfo.h>
#include <render/core/rendering/style/ShadowList.h>
#include <map>
#include <render/core/node/Node.h>
#include <render/core/parser/Screen.h>
#include <render/core/parser/StyleParser.h>

namespace weexuikit{

    namespace Body {


        //"sans-serif-monospace"
        //"monospace"
        static blink::FontFamily createDefaultFontFamily(){
            blink::FontFamily  fontFamily;
            fontFamily.setFamily({Html::Font::STYLE_FONT_NAME_SANS_SERIF});

            PassRefPtr<blink::SharedFontFamily> serif = blink::SharedFontFamily::create();
            serif->setFamily({Html::Font::STYLE_FONT_NAME_SERIF});
            fontFamily.appendFamily(serif);

            PassRefPtr<blink::SharedFontFamily> serifMonospace = blink::SharedFontFamily::create();
            serifMonospace->setFamily({Html::Font::STYLE_FONT_NAME_SERIF_MONOSPACE});
            fontFamily.appendFamily(serifMonospace);

            return  fontFamily;
        }

        blink::RenderView* createRenderView(int viewWidth, int viewHeight){
            blink::RenderView* renderView = new blink::RenderView();
            PassRefPtr<blink::FontSelector> fontSelector = blink::Platform::current()->fontSelector();
            AtomicString local(blink::Platform::current()->defaultLocale().c_str());
            PassRefPtr<blink::RenderStyle> renderViewStyle = blink::RenderStyle::createDefaultStyle();
            renderViewStyle->setDisplay(blink::EDisplay::FLEX);
            renderViewStyle->setMaxWidth({Screen::mDeviceWidth, blink::LengthType::Fixed});
            if(viewWidth > 0){
                renderViewStyle->setWidth({viewWidth, blink::LengthType::Fixed});
                renderViewStyle->setFlexDirection(blink::EFlexDirection::FlowColumn);
            }else{
                renderViewStyle->setWidth({blink::LengthType::Auto});
                renderViewStyle->setFlexDirection(blink::EFlexDirection::FlowRow);
            }
            renderViewStyle->setLocale(local);

            blink::FontDescription description;
            description.setLocale(local);
            description.setScript(blink::localeToScriptCodeForFontSelection(renderViewStyle->locale()));
            description.setComputedSize(32);
            blink::FontFamily  fontFamily = createDefaultFontFamily();
            description.setFamily(fontFamily);
            description.setSpecifiedSize(32);
            description.setOrientation(blink::FontOrientation::Horizontal);
            description.setNonCJKGlyphOrientation(blink::NonCJKGlyphOrientation::NonCJKGlyphOrientationVerticalRight);
            description.setGenericFamily(blink::FontDescription::GenericFamilyType::MonospaceFamily);


            renderViewStyle->setFontDescription(description);
            renderViewStyle->setFontSize(32);
            renderViewStyle->font().update(fontSelector);
            renderView->setStyle(renderViewStyle);
            if(viewWidth <= 0){
                viewWidth = Screen::mDeviceWidth;
            }
            renderView->setFrameViewSize({viewWidth, viewHeight});
            return renderView;
        }


        /**
         * clean the outer style, layout engine has done for body.
         * */
        void cleanBoxOuterStyle(std::map<std::string, std::string> *styles){
            styles->erase(Html::Style::STYLE_LEFT);
            styles->erase(Html::Style::STYLE_RIGHT);
            styles->erase(Html::Style::STYLE_BOTTOM);
            styles->erase(Html::Style::STYLE_TOP);
            styles->erase(Html::Style::STYLE_MARGIN_TOP);
            styles->erase(Html::Style::STYLE_MARGIN_LEFT);
            styles->erase(Html::Style::STYLE_MARGIN_RIGHT);
            styles->erase(Html::Style::STYLE_MARGIN_BOTTOM);
            styles->erase(Html::Style::STYLE_MARGIN);
        }
    }
}
