//
// Created by furture on 2018/8/20.
//

#ifndef WEEXRENDERER_STYLEPARSER_H
#define WEEXRENDERER_STYLEPARSER_H

#include <render/core/rendering/style/RenderStyleConstants.h>
#include <render/core/node/NodeStyles.h>
#include <render/platform/graphics/Color.h>
#include <render/core/rendering/style/StyleColor.h>
#include <render/core/rendering/style/ShadowData.h>
#include <functional>
#include <render/platform/fonts/FontTraits.h>
#include <render/platform/text/TextDirection.h>
#include <render/platform/Length.h>
#include <render/platform/graphics/GradientGeneratedImage.h>
#include <render/core/rendering/style/RenderStyle.h>
#include <render/core/rendering/style/ShadowList.h>
#include <sstream>

namespace weexuikit {


    namespace StyleParser {

        blink::Length parseFlexBasis(const std::string &flex_basis);

        blink::TextDirection parseTextDirection(const std::string &valueStr);

        blink::FontStyle  parseFontStyle(const std::string &valueStr);

        blink::FontWeight parseFontWeight(const std::string &valueStr);

        blink::EBoxSizing parseBoxSizing(const std::string &value);

        blink::TextDecoration parseTextDecoration(const std::string &value);

        blink::TextDecorationStyle parseTextDecorationStyle(const std::string &value);

        blink::TextOverflow parseTextOverflow(const std::string &value);

        blink::EWhiteSpace parseWhiteSpace(const std::string &value);

        blink::EWordBreak parseWordBreak(const std::string &value);

        blink::EOverflow parseOverflow(const std::string &value);

        blink::EOverflowWrap parseOverflowWrap(const std::string &value);

        blink::ETextAlign parseTextAlign(const std::string &value);

        blink::TextJustify parseTextJustify(const std::string &value);

        blink::EVisibility parseVisibility(const std::string &value);

        blink::EVerticalAlign parseVerticalAlign(const std::string &value);

        blink::EJustifyContent parseJustifyContent(const std::string &value);

        blink::EAlignContent parseAlignContent(const std::string &value);

        blink::ItemPosition parseItemPosition(const std::string &value);

        blink::EPosition parsePosition(const std::string &value);

        blink::EDisplay  parseDisplay(const std::string &value);

        blink::EFlexWrap parseFlexWrap(const std::string &value);

        blink::EFlexDirection parseFlexDirection(const std::string &value);

        blink::EBorderStyle  parseBorderStyle(const std::string &borderStyleStr);

        bool parseBorderStyleCallbackIfSuccess(const std::string &borderStyleStr,
                                               std::function<void(blink::EBorderStyle)> func);

        void parserBorderStyleFromTokens(std::vector<std::string> &tokens,
                                         std::function<void(blink::EBorderStyle)> func);

        void parserBorderColorFromTokens(std::vector<std::string> &tokens,
                                         std::function<void(const blink::StyleColor &)> func);


        blink::Color parseToBlinkColor(const std::string &colorStr);

        bool parseToBlinkColorCallbackIfSuccess(const std::string &color,
                                                std::function<void(const blink::Color &)> func);

        blink::StyleColor parseStyleColor(const std::string &colorStr);

        blink::ShadowDataVector parseBoxShadow(const std::string &shadow);

        std::vector<std::string> parserTokenBySpace(const std::string &value);

        PassRefPtr<blink::Image> parseGradientImage(std::string &backgroundImage,
                                                    const blink::IntSize &size);

        void parseBackground(blink::RenderStyle* renderStyle, const std::string& background);

        void parseBackgroundImage(blink::RenderStyle* renderStyle, const std::string& backgroudImage);

        void parseBackgroundRepeat(blink::RenderStyle* renderStyle, const std::string& backgroundRepeat);

        void parseBackgroundSize(blink::RenderStyle* renderStyle, const std::string& backgroundSize);

        void parseBackgroundPosition(blink::RenderStyle* renderStyle, const std::string& backgroundPosition);

        std::string parseFunctionName(const std::string &function);
        std::vector<std::string> parseFunctionArgs(const std::string &function);

        std::vector<std::string> parseTokensByComma(const std::string &function);



        void parseToTrimString(std::string &str);

        int parseStringToInt(const char *str);

        float parseStringToFloat(const char *str);

        double parseStringToDouble(std::string& str);

        double parseStringToDeg(std::string& str);

        float parseStringByViewPortUnit(const std::string &str);

        blink::Length parseStringToLengthUnit(const std::string &str);


        static inline void trimStringSpace(std::string& str){
            int pos = str.find(' ');
            while(pos != std::string::npos){
                str.erase(pos, 1);
                pos = str.find(' ');
            }
        }

        template < typename T > std::string valueToString( const T& n )
        {
            std::ostringstream oss ;
            oss << n ;
            return  oss.str() ;
        }

    }
}


#endif //WEEXRENDERER_STYLEPARSER_H
