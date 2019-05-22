//
// Created by furture on 2018/8/20.
//

#include "StyleParser.h"
#include "Screen.h"
#include "ColorMap.h"
#include <string>
#include <sstream>
#include <map>
#include <render/core/rendering/style/StyleGradientImage.h>
#include <render/core/rendering/style/StyleUrlImage.h>
#include <render/core/rendering/image/ImageResource.h>
#include <render/platform/common/log.h>
#include <render/core/rendering/style/ShadowList.h>


namespace weexuikit{


 namespace  StyleParser {

     /**
         * Converts an angle measured in degrees to an approximately
         * equivalent angle measured in radians.  The conversion from
         * degrees to radians is generally inexact.
         *
         * @param   angdeg   an angle, in degrees
         * @return  the measurement of the angle {@code angdeg}
         *          in radians.
         * @since   1.2
         */
     static inline double toRadians(double angdeg) {
         return angdeg / 180.0 * M_PI;
     }

     /**
      * Converts an angle measured in radians to an approximately
      * equivalent angle measured in degrees.  The conversion from
      * radians to degrees is generally inexact; users should
      * <i>not</i> expect {@code cos(toRadians(90.0))} to exactly
      * equal {@code 0.0}.
      *
      * @param   angrad   an angle, in radians
      * @return  the measurement of the angle {@code angrad}
      *          in degrees.
      * @since   1.2
      */
     static inline double radiansToDegrees(double angrad) {
         return angrad * 180.0 / M_PI;
     }

     static inline double turnToDegrees(double turn) {
         return turn * 360.0;
     }


     blink::Length parseFlexBasis(const std::string &flex_basis) {
         if (flex_basis == Html::Style::STYLE_FLEX_AUTO) {
             return {blink::LengthType::Auto};
         }
         float length = parseStringByViewPortUnit(flex_basis);
         return blink::Length(length, blink::LengthType::Fixed);
     }

     blink::TextDirection parseTextDirection(const std::string &valueStr) {
         blink::TextDirection textDirection = blink::TextDirection::LTR;
         if (Html::Style::STYLE_TEXT_DIRECTION_LTR == valueStr) {
             textDirection = blink::TextDirection::LTR;;
         } else if (Html::Style::STYLE_TEXT_DIRECTION_RTL == valueStr) {
             textDirection = blink::TextDirection::RTL;;
         }
         return textDirection;
     }


     blink::FontStyle parseFontStyle(const std::string &valueStr) {
         blink::FontStyle fontStyle = blink::FontStyle::FontStyleNormal;
         if (Html::Style::STYLE_FONT_STYLE_ITALIC == valueStr) {
             fontStyle = blink::FontStyle::FontStyleItalic;
         }
         return fontStyle;
     }

     blink::FontWeight parseFontWeight(const std::string &valueStr) {
         blink::FontWeight fontWeight = blink::FontWeightNormal;
         if (Html::Style::STYLE_FONT_WEIGHT_NORMAL == valueStr) {
             fontWeight = blink::FontWeightNormal;
         } else if (Html::Style::STYLE_FONT_WEIGHT_BOLD == valueStr) {
             fontWeight = blink::FontWeightBold;
         } else if (Html::Style::STYLE_FONT_WEIGHT_100 == valueStr) {
             fontWeight = blink::FontWeight100;
         } else if (Html::Style::STYLE_FONT_WEIGHT_200 == valueStr) {
             fontWeight = blink::FontWeight200;
         } else if (Html::Style::STYLE_FONT_WEIGHT_300 == valueStr) {
             fontWeight = blink::FontWeight300;
         } else if (Html::Style::STYLE_FONT_WEIGHT_400 == valueStr) {
             fontWeight = blink::FontWeight400;
         } else if (Html::Style::STYLE_FONT_WEIGHT_500 == valueStr) {
             fontWeight = blink::FontWeight500;
         } else if (Html::Style::STYLE_FONT_WEIGHT_600 == valueStr) {
             fontWeight = blink::FontWeight600;
         } else if (Html::Style::STYLE_FONT_WEIGHT_700 == valueStr) {
             fontWeight = blink::FontWeight700;
         } else if (Html::Style::STYLE_FONT_WEIGHT_800 == valueStr) {
             fontWeight = blink::FontWeight800;
         } else if (Html::Style::STYLE_FONT_WEIGHT_900 == valueStr) {
             fontWeight = blink::FontWeight900;
         }
         return fontWeight;
     }

     blink::EBoxSizing parseBoxSizing(const std::string &value) {
         blink::EBoxSizing boxSizing = blink::BORDER_BOX;
         if (value == Html::Style::STYLE_BOX_SIZING_BORDER_BOX) {
             boxSizing = blink::BORDER_BOX;
         } else if (value == Html::Style::STYLE_BOX_SIZING_CONTENT_BOX) {
             boxSizing = blink::CONTENT_BOX;
         }
         return boxSizing;
     }

     blink::TextDecoration parseTextDecoration(const std::string &value) {
         blink::TextDecoration textDecoration = blink::TextDecorationNone;
         if (value == Html::Style::STYLE_TEXT_DECORATION_NONE) {
             textDecoration = blink::TextDecorationNone;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_UNDERLINE) {
             textDecoration = blink::TextDecorationUnderline;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_OVERLINE) {
             textDecoration = blink::TextDecorationOverline;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_LINE_THROUGH) {
             textDecoration = blink::TextDecorationLineThrough;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_BLINK) {
             textDecoration = blink::TextDecorationBlink;
         }
         return textDecoration;
     }

     blink::TextDecorationStyle parseTextDecorationStyle(const std::string &value) {
         blink::TextDecorationStyle textDecorationStyle = blink::TextDecorationStyleSolid;
         if (value == Html::Style::STYLE_TEXT_DECORATION_STYLE_SOLID) {
             textDecorationStyle = blink::TextDecorationStyleSolid;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_STYLE_DOUBLE) {
             textDecorationStyle = blink::TextDecorationStyleDouble;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_STYLE_DASHED) {
             textDecorationStyle = blink::TextDecorationStyleDashed;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_STYLE_DOTTED) {
             textDecorationStyle = blink::TextDecorationStyleDotted;
         } else if (value == Html::Style::STYLE_TEXT_DECORATION_STYLE_WAVY) {
             textDecorationStyle = blink::TextDecorationStyleWavy;
         }
         return textDecorationStyle;
     }

     blink::TextOverflow parseTextOverflow(const std::string &value) {
         blink::TextOverflow textOverflow = blink::TextOverflowClip;
         if (value == Html::Style::STYLE_TEXT_OVERFLOW_CLIP) {
             textOverflow = blink::TextOverflowClip;
         } else if (value == Html::Style::STYLE_TEXT_OVERFLOW_ELLIPSIS) {
             textOverflow = blink::TextOverflowEllipsis;
         }
         return textOverflow;
     }

     blink::EWhiteSpace parseWhiteSpace(const std::string &value) {
         blink::EWhiteSpace whiteSpace = blink::NORMAL;
         if (value == Html::Style::STYLE_WHITE_SPACE_NORMAL) {
             whiteSpace = blink::NORMAL;
         } else if (value == Html::Style::STYLE_WHITE_SPACE_PRE) {
             whiteSpace = blink::PRE;
         } else if (value == Html::Style::STYLE_WHITE_SPACE_NO_WRAP) {
             whiteSpace = blink::NOWRAP;
         } else if (value == Html::Style::STYLE_WHITE_SPACE_PRE_WRAP) {
             whiteSpace = blink::PRE_WRAP;
         } else if (value == Html::Style::STYLE_WHITE_SPACE_PRE_LINE) {
             whiteSpace = blink::PRE_LINE;
         }
         return whiteSpace;
     }

     blink::EWordBreak parseWordBreak(const std::string &value) {
         blink::EWordBreak wordBreak = blink::NormalWordBreak;
         if (value == Html::Style::STYLE_WORD_BREAK_NORMAL) {
             wordBreak = blink::NormalWordBreak;
         } else if (value == Html::Style::STYLE_WORD_BREAK_BREAK_ALL) {
             wordBreak = blink::BreakAllWordBreak;
         } else if (value == Html::Style::STYLE_WORD_BREAK_KEEP_ALL) {
             wordBreak = blink::BreakWordBreak;
         }
         return wordBreak;
     }

     blink::EOverflow parseOverflow(const std::string &value) {
         blink::EOverflow overflow = blink::OVISIBLE;
         if (value == Html::Style::STYLE_OVERFLOW_VISIBLE) {
             overflow = blink::OVISIBLE;
         } else if (value == Html::Style::STYLE_OVERFLOW_HIDDEN) {
             overflow = blink::OHIDDEN;
         } else if (value == Html::Style::STYLE_OVERFLOW_AUTO) {
             overflow = blink::OAUTO;
         } else if (value == Html::Style::STYLE_OVERFLOW_OVERLAY) {
             overflow = blink::OOVERLAY;
         }
         return overflow;
     }

     blink::EOverflowWrap parseOverflowWrap(const std::string &value) {
         blink::EOverflowWrap overflowWrap = blink::NormalOverflowWrap;
         if (value == Html::Style::STYLE_OVERFLOW_WRAP_NORMAL) {
             overflowWrap = blink::NormalOverflowWrap;
         } else if (value == Html::Style::STYLE_OVERFLOW_WRAP_BREAK_WORLD) {
             overflowWrap = blink::BreakOverflowWrap;
         }
         return overflowWrap;
     }

     blink::ETextAlign parseTextAlign(const std::string &value) {
         blink::ETextAlign textAlign;
         if (value == Html::Style::STYLE_TEXT_ALIGN_START) {
             textAlign = blink::TASTART;
         } else if (value == Html::Style::STYLE_TEXT_ALIGN_END) {
             textAlign = blink::TAEND;
         } else if (value == Html::Style::STYLE_TEXT_ALIGN_LEFT) {
             textAlign = blink::LEFT;
         } else if (value == Html::Style::STYLE_TEXT_ALIGN_RIGHT) {
             textAlign = blink::RIGHT;
         } else if (value == Html::Style::STYLE_TEXT_ALIGN_CENTER) {
             textAlign = blink::CENTER;
         }
         return textAlign;
     }

     blink::TextJustify parseTextJustify(const std::string &value){
         if(value == Html::Style::STYLE_TEXT_JUSTIFY_AUTO){
             return blink::TextJustify::TextJustifyAuto;
         }else if(value == Html::Style::STYLE_TEXT_JUSTIFY_NONE){
             return blink::TextJustify::TextJustifyNone;
         }else if(value == Html::Style::STYLE_TEXT_JUSTIFY_INTER_WORD){
             return blink::TextJustify::TextJustifyInterWord;
         }else if(value == Html::Style::STYLE_TEXT_JUSTIFY_DISTRIBUTE){
             return blink::TextJustify::TextJustifyDistribute;
         }
         return blink::TextJustify::TextJustifyAuto;
     }

     blink::EVisibility parseVisibility(const std::string &value) {
         blink::EVisibility visibility;
         if (value == Html::Style::STYLE_VISIBILITY_HIDDEN) {
             visibility = blink::HIDDEN;
         } else if (value == Html::Style::STYLE_VISIBILITY_COLLAPSE) {
             visibility = blink::COLLAPSE;
         } else if (value == Html::Style::STYLE_VISIBILITY_VISIBLE) {
             visibility = blink::VISIBLE;
         }
         return visibility;
     }

     blink::EVerticalAlign parseVerticalAlign(const std::string &value) {
         blink::EVerticalAlign verticalAlign;
         if (value == Html::Style::STYLE_VERTICAL_ALIGN_BASELINE_MIDDLE
             || value == Html::Style::STYLE_VERTICAL_ALIGN_BASELINE_MIDDLE_MIDDLE_LINE) {
             verticalAlign = blink::BASELINE_MIDDLE;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_BASELINE) {
             verticalAlign = blink::BASELINE;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_MIDDLE) {
             verticalAlign = blink::MIDDLE;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_BOTTOM) {
             verticalAlign = blink::BOTTOM;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_TOP) {
             verticalAlign = blink::TOP;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_SUB) {
             verticalAlign = blink::SUB;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_SUPER) {
             verticalAlign = blink::SUPER;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_TEXT_BOTTOM
                    || value == Html::Style::STYLE_VERTICAL_ALIGN_TEXT_BOTTOM_MIDDLE_LINE) {
             verticalAlign = blink::TEXT_BOTTOM;
         } else if (value == Html::Style::STYLE_VERTICAL_ALIGN_TEXT_TOP
                    || value == Html::Style::STYLE_VERTICAL_ALIGN_TEXT_TOP_MIDDLE_LINE) {
             verticalAlign = blink::TEXT_TOP;
         }
         return verticalAlign;
     }

     blink::EJustifyContent parseJustifyContent(const std::string &value) {
         blink::EJustifyContent justifyContent;
         if (value == Html::Style::STYLE_JUSTIFY_CONTENT_CENTER) {
             justifyContent = blink::JustifyCenter;
         } else if (value == Html::Style::STYLE_JUSTIFY_CONTENT_FLEX_END
                    || value == Html::Style::STYLE_JUSTIFY_CONTENT_FLEX_END_MIDDLE_LINE) {
             justifyContent = blink::JustifyFlexEnd;
         } else if (value == Html::Style::STYLE_JUSTIFY_CONTENT_FLEX_START
                    || value == Html::Style::STYLE_JUSTIFY_CONTENT_FLEX_START_MIDDLE_LINE) {
             justifyContent = blink::JustifyFlexStart;
         } else if (value == Html::Style::STYLE_JUSTIFY_CONTENT_SPACE_BETWEEN
                    || value == Html::Style::STYLE_JUSTIFY_CONTENT_SPACE_BETWEEN_MIDDLE_LINE) {
             justifyContent = blink::JustifySpaceBetween;
         } else if (value == Html::Style::STYLE_JUSTIFY_CONTENT_SPACE_AROUND
                    || value == Html::Style::STYLE_JUSTIFY_CONTENT_SPACE_AROUND_MIDDLE_LINE) {
             justifyContent = blink::JustifySpaceAround;
         }
         return justifyContent;
     }

     blink::EAlignContent parseAlignContent(const std::string &value) {
         blink::EAlignContent alignContent = blink::AlignContentFlexStart;
         if (value == Html::Style::STYLE_ALIGN_CONTENT_FLEX_START
             || value == Html::Style::STYLE_ALIGN_CONTENT_FLEX_START_MIDDLE_LINE) {
             alignContent = blink::AlignContentFlexStart;
         } else if (value == Html::Style::STYLE_ALIGN_CONTENT_FLEX_END
                    || value == Html::Style::STYLE_ALIGN_CONTENT_FLEX_END_MIDDLE_LINE) {
             alignContent = blink::AlignContentFlexEnd;
         } else if (value == Html::Style::STYLE_ALIGN_CONTENT_CENTER) {
             alignContent = blink::AlignContentCenter;
         } else if (value == Html::Style::STYLE_ALIGN_CONTENT_SPACE_AROUND
                    || value == Html::Style::STYLE_ALIGN_CONTENT_SPACE_AROUND_MIDDLE_LINE) {
             alignContent = blink::AlignContentSpaceAround;
         } else if (value == Html::Style::STYLE_ALIGN_CONTENT_SPACE_BETWEEN
                    || value == Html::Style::STYLE_ALIGN_CONTENT_SPACE_BETWEEN_MIDDLE_LINE) {
             alignContent = blink::AlignContentSpaceBetween;
         } else if (value == Html::Style::STYLE_ALIGN_CONTENT_STRETCH) {
             alignContent = blink::AlignContentStretch;
         }
         return alignContent;
     }

     blink::ItemPosition parseItemPosition(const std::string &value) {
         blink::ItemPosition itemPosition = blink::ItemPosition::ItemPositionAuto;;
         if (value == Html::Style::STYLE_ITEM_POSITION_NORMAL) {
             itemPosition = blink::ItemPosition::ItemPositionAuto;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_BASE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionBaseline;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_LAST_BASE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionLastBaseline;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_CENTER) {
             itemPosition = blink::ItemPosition::ItemPositionCenter;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_END) {
             itemPosition = blink::ItemPosition::ItemPositionEnd;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_FLEX_END
                    || value == Html::Style::STYLE_ITEM_POSITION_FLEX_END_MIDDLE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionFlexEnd;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_FLEX_START
                    || value == Html::Style::STYLE_ITEM_POSITION_FLEX_START_MIDDLE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionFlexStart;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_LEFT) {
             itemPosition = blink::ItemPosition::ItemPositionLeft;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_RIGHT) {
             itemPosition = blink::ItemPosition::ItemPositionRight;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_START) {
             itemPosition = blink::ItemPosition::ItemPositionStart;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_STRETCH) {
             itemPosition = blink::ItemPosition::ItemPositionStretch;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_SELF_START
                    || value == Html::Style::STYLE_ITEM_POSITION_SELF_START_MIDDLE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionSelfStart;
         } else if (value == Html::Style::STYLE_ITEM_POSITION_SELF_END
                    || value == Html::Style::STYLE_ITEM_POSITION_SELF_END_MIDDLE_LINE) {
             itemPosition = blink::ItemPosition::ItemPositionSelfEnd;
         }
         return itemPosition;
     }

     blink::EPosition parsePosition(const std::string &value) {
         blink::EPosition position = blink::EPosition::StaticPosition;;
         if (value == Html::Style::STYLE_POSITION_ABSOLUTE) {
             position = blink::EPosition::AbsolutePosition;
         } else if (value == Html::Style::STYLE_POSITION_STATIC) {
             position = blink::EPosition::StaticPosition;
         } else if (value == Html::Style::STYLE_POSITION_RELATIVE) {
             position = blink::EPosition::RelativePosition;
         }
         return position;
     }

     blink::EDisplay parseDisplay(const std::string &value) {
         blink::EDisplay display = blink::EDisplay::FLEX;
         if (value == Html::Style::STYLE_DISPLAY_PARAGRAPH) {
             display = blink::EDisplay::PARAGRAPH;
         } else if (value == Html::Style::STYLE_DISPLAY_FLEX) {
             display = blink::EDisplay::FLEX;
         } else if (value == Html::Style::STYLE_DISPLAY_INLINE_FLEX) {
             display = blink::EDisplay::INLINE_FLEX;
         } else if (value == Html::Style::STYLE_DISPLAY_INLINE) {
             display = blink::EDisplay::INLINE;
         } else if (value == Html::Style::STYLE_DISPLAY_NONE) {
             display = blink::EDisplay::NONE;
         }
         return display;
     }

     blink::EFlexWrap parseFlexWrap(const std::string &value) {
         blink::EFlexWrap flexWrap = blink::EFlexWrap::FlexNoWrap;
         if (value == Html::Style::STYLE_FLEX_WRAP_NO_WRAP) {
             flexWrap = blink::EFlexWrap::FlexNoWrap;
         } else if (value == Html::Style::STYLE_FLEX_WRAP_REVERSE
                    || value == Html::Style::STYLE_FLEX_WRAP_REVERSE_MIDDLE_LINE) {
             flexWrap = blink::EFlexWrap::FlexWrapReverse;
         } else if (value == Html::Style::STYLE_FLEX_WRAP_WRAP) {
             flexWrap = blink::EFlexWrap::FlexWrap;
         }
         return flexWrap;
     }

     blink::EFlexDirection parseFlexDirection(const std::string &value) {
         blink::EFlexDirection direction = blink::EFlexDirection::FlowRow;
         if (value == Html::Style::STYLE_FLEX_DIRECTION_ROW_REVERSE
             || value == Html::Style::STYLE_FLEX_DIRECTION_ROW_REVERSE_MIDDLE_LINE) {
             direction = blink::EFlexDirection::FlowRowReverse;
         } else if (value == Html::Style::STYLE_FLEX_DIRECTION_ROW) {
             direction = blink::EFlexDirection::FlowRow;
         } else if (value == Html::Style::STYLE_FLEX_DIRECTION_COLUMN_REVERSE
                    || value == Html::Style::STYLE_FLEX_DIRECTION_COLUMN_REVERSE_MIDDLE_LINE) {
             direction = blink::EFlexDirection::FlowColumnReverse;
         } else if (value == Html::Style::STYLE_FLEX_DIRECTION_COLUMN) {
             direction = blink::EFlexDirection::FlowColumn;
         }
         return direction;
     }


     blink::EBorderStyle parseBorderStyle(const std::string &borderStyleStr) {
         blink::EBorderStyle borderStyle = blink::EBorderStyle::BNONE;
         parseBorderStyleCallbackIfSuccess(borderStyleStr,
                                           [&](blink::EBorderStyle parsedStyle) {
                                               borderStyle = parsedStyle;
                                           });
         return borderStyle;
     }

     bool parseBorderStyleCallbackIfSuccess(const std::string &borderStyleStr,
                                            std::function<void(blink::EBorderStyle)> func) {
         if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_SOLID) {
             func(blink::EBorderStyle::SOLID);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_DOUBLE) {
             func(blink::EBorderStyle::DOUBLE);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_DASHED) {
             func(blink::EBorderStyle::DASHED);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_DOTTED) {
             func(blink::EBorderStyle::DOTTED);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_RIDGE) {
             func(blink::EBorderStyle::RIDGE);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_OUTSET) {
             func(blink::EBorderStyle::OUTSET);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_GROOVE) {
             func(blink::EBorderStyle::GROOVE);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_INSET) {
             func(blink::EBorderStyle::INSET);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_HIDDEN) {
             func(blink::EBorderStyle::BHIDDEN);
             return true;
         } else if (borderStyleStr == Html::Style::STYLE_BORDER_STYLE_NONE) {
             func(blink::EBorderStyle::BNONE);
             return true;
         }
         return false;
     }

     void parserBorderStyleFromTokens(std::vector<std::string> &tokens,
                                      std::function<void(blink::EBorderStyle)> func) {
         auto it = tokens.begin();
         while (it != tokens.end()) {
             std::string token = *it;
             bool success = parseBorderStyleCallbackIfSuccess(token, func);
             if (success) {
                 tokens.erase(it);
                 break;
             } else {
                 it++;
             }
         }
     }

     void parserBorderColorFromTokens(std::vector<std::string> &tokens,
                                      std::function<void(const blink::StyleColor &)> func) {
         auto it = tokens.begin();
         while (it != tokens.end()) {
             std::string token = *it;
             bool success = parseToBlinkColorCallbackIfSuccess(token,
                                                               [&](const blink::Color &color) {
                                                                   func(blink::StyleColor(color));
                                                               });
             if (success) {
                 tokens.erase(it);
                 break;
             } else {
                 it++;
             }
         }
     }

     blink::Color parseToBlinkColor(const std::string &colorStr) {
         blink::Color color = blink::Color::white;
         parseToBlinkColorCallbackIfSuccess(colorStr, [&](const blink::Color &parsedColor) {
             color = parsedColor;
         });
         return color;
     }

     bool parseToBlinkColorCallbackIfSuccess(const std::string &colorStr,
                                             std::function<void(const blink::Color &)> func) {
         if (colorStr.length() <= 0) {
             return false;
         }
         if (colorStr[0] == '#') {
             if (colorStr.length() == 7) {  //#rrggbb
                 std::string red, green, blue;
                 red += colorStr[1];
                 red += colorStr[2];
                 green += colorStr[3];
                 green += colorStr[4];
                 blue += colorStr[5];
                 blue += colorStr[6];
                 int colorR = strtol(red.c_str(), nullptr, 16);
                 int colorG = strtol(green.c_str(), nullptr, 16);
                 int colorB = strtol(blue.c_str(), nullptr, 16);
                 func(blink::Color(colorR, colorG, colorB));
                 return true;
             } else if (colorStr.length() == 9) {//#rrggbbaa
                 std::string red, green, blue, alpha;
                 red += colorStr[1];
                 red += colorStr[2];
                 green += colorStr[3];
                 green += colorStr[4];
                 blue += colorStr[5];
                 blue += colorStr[6];
                 alpha += colorStr[7];
                 alpha += colorStr[8];
                 int colorR = strtol(red.c_str(), nullptr, 16);
                 int colorG = strtol(green.c_str(), nullptr, 16);
                 int colorB = strtol(blue.c_str(), nullptr, 16);
                 int colorA = strtol(blue.c_str(), nullptr, 16);
                 func(blink::Color(colorR, colorG, colorB, colorA));
                 return true;
             } else if (colorStr.length() == 4) {//#rgb
                 std::string red, green, blue;
                 red += colorStr[1];
                 red += colorStr[1];
                 green += colorStr[2];
                 green += colorStr[2];
                 blue += colorStr[3];
                 blue += colorStr[3];
                 int colorR = strtol(red.c_str(), nullptr, 16);
                 int colorG = strtol(green.c_str(), nullptr, 16);
                 int colorB = strtol(blue.c_str(), nullptr, 16);
                 func(blink::Color(colorR, colorG, colorB));
                 return true;
             }
         }
         if (colorStr.find(Html::Style::STYLE_RGBA) != std::string::npos) {
             std::string red, green, blue, alpha;
             int offset = strlen(Html::Style::STYLE_RGBA_PREFIX);
             int pos = colorStr.find(Html::Style::STYLE_RGBA_SEPARATOR);
             if (pos > 0) {
                 red = colorStr.substr(offset, pos - offset);
             }
             offset = pos + 1;
             pos = colorStr.find(Html::Style::STYLE_RGBA_SEPARATOR, offset);
             if (pos > 0) {
                 green = colorStr.substr(offset, pos - offset);
             }
             offset = pos + 1;
             pos = colorStr.find(Html::Style::STYLE_RGBA_SEPARATOR, offset);
             if (pos > 0) {
                 blue = colorStr.substr(offset, pos - offset);
             }
             offset = pos + 1;
             pos = colorStr.size() - 1;
             if (pos > offset) {
                 alpha = colorStr.substr(offset, pos - offset);
             }
             blink::Color color = blink::Color(parseStringToInt(red.c_str()),
                                               parseStringToInt(green.c_str()),
                                               parseStringToInt(blue.c_str()),
                                               (int) (255 * parseStringToFloat(alpha.c_str())));
             func(color);
             return true;
         }

         if (colorStr.find(Html::Style::STYLE_RGB) != std::string::npos) {
             std::string red, green, blue;
             int offset = strlen(Html::Style::STYLE_RGB_PREFIX);
             int pos = colorStr.find(Html::Style::STYLE_RGB_SEPARATOR);
             if (pos > 0) {
                 red = colorStr.substr(offset, pos - offset);
             }
             offset = pos + 1;
             pos = colorStr.find(Html::Style::STYLE_RGB_SEPARATOR, offset);
             if (pos > 0) {
                 green = colorStr.substr(offset, pos - offset);
             }
             offset = pos + 1;
             pos = colorStr.size() - 1;
             if (pos > offset) {
                 blue = colorStr.substr(offset, pos - offset);
             }
             func(blink::Color(parseStringToInt(red.c_str()), parseStringToInt(green.c_str()),
                               parseStringToInt(blue.c_str())));
             return true;
         }
         std::map<std::string, blink::RGBA32>::iterator it = ColorMap::getInstance()->colorMap()->find(
                 colorStr);
         if (it != ColorMap::getInstance()->colorMap()->end()) {
             func(blink::Color(it->second));
             return true;
         }
         return false;
     }


     blink::StyleColor parseStyleColor(const std::string &colorStr) {
         blink::StyleColor color(parseToBlinkColor(colorStr));
         return color;
     }


     static std::string parseShadowColor(std::string &shadow) {
         std::string color;
         int pos = shadow.find('#');
         if ((pos >= 0)) {
             int end = shadow.find(' ', pos + 1);
             if (end < 0) {
                 end = shadow.length();
             }
             int len = 0;
             if (end > 0) {
                 len = end - pos + 1;
             } else {
                 len = shadow.length() - pos;
             }
             color = shadow.substr(pos, len);
             shadow.erase(pos, len);
             return color;
         }
         pos = shadow.find(Html::Style::STYLE_RGB);
         if (pos >= 0) {
             int end = shadow.find(')', pos + 1);
             int len = 0;
             if (end > 0) {
                 len = end - pos + 1;
             } else {
                 len = shadow.length() - pos;
             }
             color = shadow.substr(pos, len);
             shadow.erase(pos, len);
             return color;
         }
         return color;
     }

     static std::string parseShadowStyle(std::string &shadow) {
         std::string style;
         int pos = shadow.find(Html::Style::STYLE_BOX_SHADOW_INSET);
         if ((pos >= 0)) {
             int len = strlen(Html::Style::STYLE_BOX_SHADOW_INSET);
             style = shadow.substr(pos, len);
             shadow.erase(pos, len);
             return style;
         }
         pos = shadow.find(Html::Style::STYLE_BOX_SHADOW_OUTSET);
         if (pos >= 0) {
             int len = strlen(Html::Style::STYLE_BOX_SHADOW_OUTSET);
             style = shadow.substr(pos, len);
             shadow.erase(pos, len);
             return style;
         }
         return style;
     }

     blink::ShadowDataVector parseBoxShadow(const std::string &data) {
         std::string boxshadow = data;
         blink::ShadowDataVector shadowDataVector;
         bool next = true;
         while(next && boxshadow.size() > 0){
             std::string colorStr = parseShadowColor(boxshadow);
             std::size_t  pos = boxshadow.find(',');
             std::string oneShadow;
             if(pos != std::string::npos){
                 oneShadow = boxshadow.substr(0, pos);
                 boxshadow.erase(0, pos + 1);
             }else{
                 next = false;
                 oneShadow = boxshadow;
             }
             std::string style = parseShadowStyle(oneShadow);
             std::vector<std::string> oneShadowTokens = parserTokenBySpace(oneShadow);


             float x = 0;
             float y = 0;
             float blur = 0;
             float spread = 0;
             blink::Color color = blink::Color::black;
             blink::ShadowStyle shadowStyle = blink::ShadowStyle::Normal;
             if (colorStr.length() > 0) {
                 color = parseToBlinkColor(colorStr);
             }else{
                 for(std::string oneShadowToken : oneShadowTokens){
                     parseToBlinkColorCallbackIfSuccess(oneShadowToken, [&](const blink::Color &parsedColor) {
                         color = parsedColor;
                         colorStr = oneShadowToken;
                     });
                 }
                 if(colorStr.size() > 0){
                     oneShadowTokens.erase(std::remove(oneShadowTokens.begin(), oneShadowTokens.end(), colorStr));
                 }
             }

             if (style.length() > 0) {
                 if (style == Html::Style::STYLE_BOX_SHADOW_INSET) {
                     shadowStyle = blink::ShadowStyle::Inset;
                 }
             }

             if (oneShadowTokens.size() == 4) {
                 x = parseStringToFloat(oneShadowTokens.at(0).data());
                 y = parseStringToFloat(oneShadowTokens.at(1).data());
                 blur = parseStringToFloat(oneShadowTokens.at(2).data());
                 spread = parseStringToFloat(oneShadowTokens.at(3).data());
             } else if (oneShadowTokens.size() == 3) {
                 x = parseStringToFloat(oneShadowTokens.at(0).data());
                 y = parseStringToFloat(oneShadowTokens.at(1).data());
                 blur = parseStringToFloat(oneShadowTokens.at(2).data());
             } else if (oneShadowTokens.size() == 2) {
                 x = parseStringToFloat(oneShadowTokens.at(0).data());
                 y = parseStringToFloat(oneShadowTokens.at(1).data());
             } else if (oneShadowTokens.size() == 1) {
                 x = parseStringToFloat(oneShadowTokens.at(0).data());
             }
             blink::ShadowData shadowData({x, y}, blur, spread, shadowStyle, color);
             shadowDataVector.append(shadowData);
         }
         return shadowDataVector;
     }

     std::vector<std::string> parserTokenBySpace(const std::string &value) {
         std::stringstream sstream(value);
         std::vector<std::string> tokens;
         std::string token;
         while (sstream >> token) {
             tokens.push_back(token);
         }
         return tokens;
     }


     PassRefPtr<blink::Image> parseGradientImage(std::string &backgroundImage, const blink::IntSize &size) {
         parseToTrimString(backgroundImage);
         std::string functionName = parseFunctionName(backgroundImage);
         std::vector<std::string> functionArgs = parseFunctionArgs(backgroundImage);
         if (functionName != Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR || functionArgs.size() != 3) {
             return blink::Image::nullImage();
         }

         const std::string &direction = functionArgs.at(0);
         blink::FloatPoint p0;
         blink::FloatPoint p1;
         if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT) {
             p0.set(0, 0);
             p1.set(size.width(), 0);
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT) {
             p0.set(size.width(), 0);
             p1.set(0, 0);
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM) {
             p0.set(0, 0);
             p1.set(0, size.height());
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP) {
             p0.set(0, size.height());
             p1.set(0, 0);
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM_RIGHT
                    || direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT_BOTTOM) {
             p0.set(0, 0);
             p1.set(size.width(), size.height());
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM_LEFT
                    || direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT_BOTTOM) {
             p0.set(size.width(), 0);
             p1.set(0, size.height());
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP_RIGHT
                    || direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT_TOP) {
             p0.set(0, size.height());
             p1.set(size.width(), 0);
         } else if (direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP_LEFT
                    || direction == Html::Style::STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT_TOP) {
             p0.set(size.width(), size.height());
             p1.set(0, 0);
         } else {
             p0.set(0, 0);
             p1.set(size.width(), 0);
         }
         blink::Color startColor = parseToBlinkColor(functionArgs.at(1));
         blink::Color endColor = parseToBlinkColor(functionArgs.at(2));
         PassRefPtr<blink::Gradient> gradientRef = blink::Gradient::create(p0, p1);
         gradientRef->addColorStop(0.0f, startColor);
         gradientRef->addColorStop(1.0f, endColor);
         return blink::GradientGeneratedImage::create(gradientRef, size);
     }


     /**
      * http://www.w3school.com.cn/cssref/pr_background.asp
      * */
     void parseBackground(blink::RenderStyle *renderStyle, const std::string &background) {
         std::vector<std::string> tokens = parserTokenBySpace(background);
         if (tokens.size() == 1) {
             bool isBackgroundColor = parseToBlinkColorCallbackIfSuccess(tokens.at(0),
                                                                         [&](const blink::Color &parsedColor) {
                                                                             renderStyle->setBackgroundColor(
                                                                                     parsedColor);
                                                                         });
             if (!isBackgroundColor) {
                 parseBackgroundImage(renderStyle, tokens.at(0));
             }
         } else if (tokens.size() == 2) {
             bool isBackgroundColor = parseToBlinkColorCallbackIfSuccess(tokens.at(0),
                                                                         [&](const blink::Color &parsedColor) {
                                                                             renderStyle->setBackgroundColor(
                                                                                     parsedColor);
                                                                         });
             if (isBackgroundColor) {
                 parseBackgroundImage(renderStyle, tokens.at(1));
             } else {
                 parseBackgroundImage(renderStyle, tokens.at(0));
                 parseBackgroundRepeat(renderStyle, tokens.at(1));
             }
         } else if (tokens.size() == 3) {
             bool isBackgroundColor = parseToBlinkColorCallbackIfSuccess(tokens.at(0),
                                                                         [&](const blink::Color &parsedColor) {
                                                                             renderStyle->setBackgroundColor(
                                                                                     parsedColor);
                                                                         });
             if (isBackgroundColor) {
                 parseBackgroundImage(renderStyle, tokens.at(1));
                 parseBackgroundRepeat(renderStyle, tokens.at(2));
             } else {
                 parseBackgroundImage(renderStyle, tokens.at(0));
                 parseBackgroundRepeat(renderStyle, tokens.at(1));
             }
         }
     }

     /**
      * http://www.w3school.com.cn/jsref/prop_style_background.asp
      * */
     void parseBackgroundImage(blink::RenderStyle *renderStyle, const std::string &backgroundImage) {
         std::string functionName = parseFunctionName(backgroundImage);
         if (functionName.length() == 0) {
             return;
         }
         parseToTrimString(functionName);
         std::vector<std::string> functionArgs = parseFunctionArgs(backgroundImage);
         if (functionName == Html::Style::STYLE_BACKGROUND_IMAGE_URL) {
             if (functionArgs[0].length() == 0) {
                 return;
             }
             std::string imageUrl = functionArgs[0];
             if (imageUrl.at(0) == '\''
                 && imageUrl.length() > 2
                 && imageUrl.at(imageUrl.length() - 1) == '\'') {
                 imageUrl = imageUrl.substr(1, imageUrl.length() - 1);
             }
             PassOwnPtr<blink::ImageResource> imageResource = blink::ImageResource::create();
             imageResource->setImageUrl(imageUrl);
             imageResource->getImageInfo()->setUseSourceSize(true);
             PassRefPtr<blink::StyleUrlImage> styleFetchedImage = blink::StyleUrlImage::create(
                     imageResource);
             PassRefPtr<blink::StyleImage> styleImage = styleFetchedImage;
             renderStyle->accessBackgroundLayers().setImage(styleImage);
         } else {
             PassRefPtr<blink::StyleImage> styleImage = blink::StyleGradientImage::create(backgroundImage);
             renderStyle->accessBackgroundLayers().setImage(styleImage);
             renderStyle->accessBackgroundLayers().setAttachment(blink::EFillAttachment::LocalBackgroundAttachment);
             renderStyle->accessBackgroundLayers().setRepeatX(blink::EFillRepeat::NoRepeatFill);
             renderStyle->accessBackgroundLayers().setRepeatY(blink::EFillRepeat::NoRepeatFill);
         }
     }

     void parseBackgroundRepeat(blink::RenderStyle *renderStyle, const std::string &backgroundRepeat) {
         if (Html::Style::STYLE_BACKGROUND_REPEAT_REPEAT == backgroundRepeat) {
             renderStyle->accessBackgroundLayers().setRepeatX(blink::EFillRepeat::RepeatFill);
             renderStyle->accessBackgroundLayers().setRepeatY(blink::EFillRepeat::RepeatFill);
         } else if (Html::Style::STYLE_BACKGROUND_REPEAT_REPEAT_X == backgroundRepeat) {
             renderStyle->accessBackgroundLayers().setRepeatX(blink::EFillRepeat::RepeatFill);
             renderStyle->accessBackgroundLayers().setRepeatY(blink::EFillRepeat::NoRepeatFill);
         } else if (Html::Style::STYLE_BACKGROUND_REPEAT_REPEAT_Y == backgroundRepeat) {
             renderStyle->accessBackgroundLayers().setRepeatX(blink::EFillRepeat::NoRepeatFill);
             renderStyle->accessBackgroundLayers().setRepeatY(blink::EFillRepeat::RepeatFill);
         } else if (Html::Style::STYLE_BACKGROUND_REPEAT_NO_REPEAT == backgroundRepeat) {
             renderStyle->accessBackgroundLayers().setRepeatX(blink::EFillRepeat::NoRepeatFill);
             renderStyle->accessBackgroundLayers().setRepeatY(blink::EFillRepeat::NoRepeatFill);
         }
     }

     /**
      * reference: http://www.w3school.com.cn/cssref/pr_background-size.asp
      * */
     void parseBackgroundSize(blink::RenderStyle *renderStyle, const std::string &backgroundSize) {
         if (backgroundSize == Html::Style::STYLE_BACKGROUND_SIZE_CONTAIN) {
             renderStyle->accessBackgroundLayers().setSizeType(blink::EFillSizeType::Contain);
         } else if (backgroundSize == Html::Style::STYLE_BACKGROUND_SIZE_COVER) {
             renderStyle->accessBackgroundLayers().setSizeType(blink::EFillSizeType::Cover);
         } else {
             std::vector<std::string> tokens = parserTokenBySpace(backgroundSize);
             if (tokens.size() == 2) {
                 blink::LengthSize size(parseStringToLengthUnit(tokens.at(0)),
                                        parseStringToLengthUnit(tokens.at(1)));
                 blink::FillSize fillSize(blink::EFillSizeType::SizeLength, size);
                 renderStyle->accessBackgroundLayers().setSize(fillSize);
             } else if (tokens.size() == 1) {
                 blink::LengthSize size(parseStringToLengthUnit(tokens.at(0)), blink::Length());
                 blink::FillSize fillSize(blink::EFillSizeType::SizeLength, size);
                 renderStyle->accessBackgroundLayers().setSize(fillSize);
             }
         }
     }


     static blink::Length parseBackgroundSizeToLength(std::string &backgroundSize, bool &isXPosition) {
         if (backgroundSize == Html::Style::STYLE_BACKGROUND_POSITION_CENTER) {
             return blink::Length(50, blink::LengthType::Percent);
         } else if (backgroundSize == Html::Style::STYLE_BACKGROUND_POSITION_LEFT) {
             return blink::Length(0, blink::LengthType::Percent);
         } else if (backgroundSize == Html::Style::STYLE_BACKGROUND_POSITION_RIGHT) {
             return blink::Length(100, blink::LengthType::Percent);
         } else if (backgroundSize == Html::Style::STYLE_BACKGROUND_POSITION_TOP) {
             isXPosition = false;
             return blink::Length(0, blink::LengthType::Percent);
         } else if (backgroundSize == Html::Style::STYLE_BACKGROUND_POSITION_BOTTOM) {
             isXPosition = false;
             return blink::Length(100, blink::LengthType::Percent);
         } else {
             return parseStringToLengthUnit(backgroundSize);
         }
     }

     /**
      * http://www.runoob.com/cssref/pr-background-position.html
      * */
     void parseBackgroundPosition(blink::RenderStyle *renderStyle, const std::string &backgroundPosition) {
         std::vector<std::string> tokens = parserTokenBySpace(backgroundPosition);
         if (tokens.size() == 1) {
             bool isXPosition = true;
             blink::Length length = parseBackgroundSizeToLength(tokens.at(0), isXPosition);
             if (isXPosition) {
                 renderStyle->accessBackgroundLayers().setXPosition(length);
                 blink::Length yPosition(50, blink::LengthType::Percent);
                 renderStyle->accessBackgroundLayers().setYPosition(yPosition);
             } else {
                 renderStyle->accessBackgroundLayers().setYPosition(length);
                 blink::Length yPosition(50, blink::LengthType::Percent);
                 renderStyle->accessBackgroundLayers().setXPosition(yPosition);
             }
         } else if (tokens.size() == 2) {
             bool isXPosition = true;
             blink::Length length = parseBackgroundSizeToLength(tokens.at(0), isXPosition);
             if (isXPosition) {
                 renderStyle->accessBackgroundLayers().setXPosition(length);
                 renderStyle->accessBackgroundLayers().setYPosition(
                         parseBackgroundSizeToLength(tokens.at(1), isXPosition));
             } else {
                 renderStyle->accessBackgroundLayers().setYPosition(length);
                 renderStyle->accessBackgroundLayers().setXPosition(
                         parseBackgroundSizeToLength(tokens.at(1), isXPosition));
             }
         }
     }


     std::string parseFunctionName(const std::string &function) {
         int pos = function.find_first_of('(');
         if (pos < 0) {
             return "";
         }
         return function.substr(0, pos);
     }

     std::vector<std::string> parseFunctionArgs(const std::string &function) {
         std::vector<std::string> tokens;
         int pos = function.find_first_of('(');
         int end = function.find(')', pos + 1);
         if (pos < 0 || end < 0 || (end - pos) <= 0) {
             return tokens;
         }
         int commaStart = pos + 1;
         int commaEnd = function.find(',', commaStart);
         while (commaEnd > 0) {
             tokens.push_back(function.substr(commaStart, commaEnd - commaStart));
             commaStart = commaEnd + 1;
             commaEnd = function.find(',', commaStart);
         }
         tokens.push_back(function.substr(commaStart, end - commaStart));
         return tokens;
     }

     std::vector<std::string> parseTokensByComma(const std::string &function) {
         std::vector<std::string> tokens;
         int commaStart = 0;
         int commaEnd = function.find(',', commaStart);
         while (commaEnd > 0) {
             tokens.push_back(function.substr(commaStart, commaEnd - commaStart));
             commaStart = commaEnd + 1;
             commaEnd = function.find(',', commaStart);
         }
         tokens.push_back(function.substr(commaStart, function.size() - commaStart));
         return tokens;
     }

     void parseToTrimString(std::string &str) {
         int pos = str.find(' ');
         while (pos != std::string::npos) {
             str.erase(pos, 1);
             pos = str.find(' ');
         }
     }

     int parseStringToInt(const char *str) {
         return strtol(str, nullptr, 10);
     }

     float parseStringToFloat(const char *str) {
         return strtof(str, nullptr);
     }


     double parseStringToDouble(std::string& str){
         return strtod(str.data(), nullptr);
     }

     double parseStringToDeg(std::string& str){
         if(str.find(Html::Unit::DEG) != std::string::npos){
             return parseStringToDouble(str);
         }else if(str.find(Html::Unit::TURN) != std::string::npos){
             return turnToDegrees(parseStringToDouble(str));
         }else{
             return radiansToDegrees(parseStringToDouble(str));
         }
     }

     float parseStringByViewPortUnit(const std::string &str) {
         std::string unit = str;
         return Screen::getFloatByViewport(unit, Screen::mViewPort);
     }

     blink::Length parseStringToLengthUnit(const std::string &str) {
         int pos = str.find(Html::Unit::PERCENT);
         if (pos != std::string::npos) {
             std::string percent = str.substr(0, pos);
             return blink::Length(parseStringToFloat(percent.c_str()), blink::LengthType::Percent);
         } else {
             float length = Screen::getFloatByViewport(str, Screen::mViewPort);
             if (!isnan(length)) {
                 return blink::Length(length, blink::LengthType::Fixed);
             }
         }
         return blink::Length(blink::LengthType::Auto);
     }
   }
}
