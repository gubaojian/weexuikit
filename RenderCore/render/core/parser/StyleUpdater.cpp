//
// Created by furture on 2018/8/25.
//

#include "StyleUpdater.h"
#include "Screen.h"
#include "StyleParser.h"
#include "TransformParser.h"
#include <render/core/node/NodeStyles.h>
#include <render/core/rendering/style/ShadowList.h>
#include <render/public/platform/Platform.h>
#include <render/core/rendering/style/StyleGradientImage.h>
#include <render/platform/fonts/FontDescription.h>
#include <render/platform/common/log.h>
#include <unordered_map>

namespace weexuikit{


    static std::unordered_map<std::string, std::function<void(blink::RenderStyle* renderStyle, std::string &value)>> styleParserFunctions ={
            {Html::Style::STYLE_BACKGROUND, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleParser::parseBackground(renderStyle, value);
            }},
            {Html::Style::STYLE_BACKGROUND_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBackgroundColor({StyleParser::parseStyleColor(value)});
            }},
            {Html::Style::STYLE_BACKGROUND_IMAGE, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleParser::parseBackgroundImage(renderStyle,value);
            }},
            {Html::Style::STYLE_BACKGROUND_REPEAT, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleParser::parseBackgroundRepeat(renderStyle, value);
            }},
            {Html::Style::STYLE_BACKGROUND_SIZE, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleParser::parseBackgroundSize(renderStyle, value);
            }},
            {Html::Style::STYLE_BACKGROUND_POSITION, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleParser::parseBackgroundPosition(renderStyle, value);
            }},
            {Html::Style::STYLE_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueWidthFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueWidthFloat)){
                    renderStyle->setWidth({valueWidthFloat, blink::LengthType::Fixed});
                    if(renderStyle->minWidth().type() == blink::RenderStyle::initialMinSize().type()){
                        renderStyle->setMinWidth({blink::LengthType::Fixed});
                    }
                }
            }},
            {Html::Style::STYLE_MIN_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueWidthFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueWidthFloat)){
                    renderStyle->setMinWidth({valueWidthFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MAX_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueWidthFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueWidthFloat)){
                    renderStyle->setMaxWidth({valueWidthFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_HEIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueHeightFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueHeightFloat)){
                    renderStyle->setHeight({valueHeightFloat, blink::LengthType::Fixed});
                    if(renderStyle->minHeight().type() == blink::RenderStyle::initialMinSize().type()){
                        renderStyle->setMinHeight({blink::LengthType::Fixed});
                    }
                }
            }},
            {Html::Style::STYLE_MIN_HEIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueHeightFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueHeightFloat)){
                    renderStyle->setMinHeight({valueHeightFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MAX_HEIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueHeightFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueHeightFloat)){
                    renderStyle->setMaxHeight({valueHeightFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_LEFT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setLeft({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_RIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setRight({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_BOTTOM, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setBottom({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_TOP, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setTop({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MARGIN_TOP, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setMarginTop({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MARGIN_LEFT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setMarginLeft({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MARGIN_RIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setMarginRight({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MARGIN_BOTTOM, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setMarginBottom({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_MARGIN, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setMarginTop({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setMarginLeft({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setMarginRight({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setMarginBottom({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_PADDING_TOP, [](blink::RenderStyle* renderStyle,const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setPaddingTop({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_PADDING_LEFT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setPaddingLeft({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_PADDING_RIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setPaddingRight({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_PADDING_BOTTOM, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setPaddingBottom({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_PADDING, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setPaddingTop({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setPaddingLeft({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setPaddingRight({valueFloat, blink::LengthType::Fixed});
                    renderStyle->setPaddingBottom({valueFloat, blink::LengthType::Fixed});
                }
            }},
            {Html::Style::STYLE_BORDER_TOP_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderTopStyle(StyleParser::parseBorderStyle(value));
            }},
            {Html::Style::STYLE_BORDER_TOP_WIDTH, [](blink::RenderStyle* renderStyle, std::string &value){
                int borderWidth = StyleParser::parseStringByViewPortUnit(value);
                if(borderWidth > 0){
                    renderStyle->setBorderTopWidth(borderWidth);
                }
            }},
            {Html::Style::STYLE_BORDER_TOP_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderTopColor(StyleParser::parseStyleColor(value));
            }},
            {Html::Style::STYLE_BORDER_TOP, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() > 0){
                    renderStyle->setBorderTopWidth(
                            StyleParser::parseStringByViewPortUnit(tokens.at(0)));
                }
                if(tokens.size() > 1){
                    renderStyle->setBorderTopStyle(StyleParser::parseBorderStyle(tokens.at(1)));
                }
                if(tokens.size() > 2){
                    renderStyle->setBorderTopColor(StyleParser::parseStyleColor(tokens.at(2)));
                }
            }},
            {Html::Style::STYLE_BORDER_RIGHT_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderRightStyle(StyleParser::parseBorderStyle(value));
            }},
            {Html::Style::STYLE_BORDER_RIGHT_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                int borderWidth = StyleParser::parseStringByViewPortUnit(value);
                if(borderWidth > 0){
                    renderStyle->setBorderRightWidth(borderWidth);
                }
            }},
            {Html::Style::STYLE_BORDER_RIGHT_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderRightColor(StyleParser::parseStyleColor(value));
            }},
            {Html::Style::STYLE_BORDER_RIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() > 0){
                    renderStyle->setBorderRightWidth(
                            StyleParser::parseStringByViewPortUnit(tokens.at(0)));
                }
                if(tokens.size() > 1){
                    renderStyle->setBorderRightStyle(StyleParser::parseBorderStyle(tokens.at(1)));
                }
                if(tokens.size() > 2){
                    renderStyle->setBorderRightColor(StyleParser::parseStyleColor(tokens.at(2)));
                }
            }},
            {Html::Style::STYLE_BORDER_BOTTOM_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderBottomStyle(StyleParser::parseBorderStyle(value));
            }},
            {Html::Style::STYLE_BORDER_BOTTOM_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                int borderWidth = StyleParser::parseStringByViewPortUnit(value);
                if(borderWidth > 0){
                    renderStyle->setBorderBottomWidth(borderWidth);
                }
            }},
            {Html::Style::STYLE_BORDER_BOTTOM_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderBottomColor(StyleParser::parseStyleColor(value));
            }},
            {Html::Style::STYLE_BORDER_BOTTOM, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() > 0){
                    renderStyle->setBorderBottomWidth(
                            StyleParser::parseStringByViewPortUnit(tokens.at(0)));
                }
                if(tokens.size() > 1){
                    renderStyle->setBorderBottomStyle(StyleParser::parseBorderStyle(tokens.at(1)));
                }
                if(tokens.size() > 2){
                    renderStyle->setBorderBottomColor(StyleParser::parseStyleColor(tokens.at(2)));
                };
            }},
            {Html::Style::STYLE_BORDER_LEFT_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderLeftStyle(StyleParser::parseBorderStyle(value));
            }},
            {Html::Style::STYLE_BORDER_LEFT_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                int borderWidth = StyleParser::parseStringByViewPortUnit(value);
                if(borderWidth > 0){
                    renderStyle->setBorderLeftWidth(borderWidth);
                }
            }},
            {Html::Style::STYLE_BORDER_LEFT_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setBorderLeftColor(StyleParser::parseStyleColor(value));
            }},
            {Html::Style::STYLE_BORDER_LEFT, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() > 0){
                    renderStyle->setBorderLeftWidth(
                            StyleParser::parseStringByViewPortUnit(tokens.at(0)));
                }
                if(tokens.size() > 1){
                    renderStyle->setBorderLeftStyle(StyleParser::parseBorderStyle(tokens.at(1)));
                }
                if(tokens.size() > 2){
                    renderStyle->setBorderLeftColor(StyleParser::parseStyleColor(tokens.at(2)));
                }
            }},
            {Html::Style::STYLE_BORDER_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::StyleColor styleColor = StyleParser::parseStyleColor(value);
                renderStyle->setBorderLeftColor(styleColor);
                renderStyle->setBorderRightColor(styleColor);
                renderStyle->setBorderTopColor(styleColor);
                renderStyle->setBorderBottomColor(styleColor);
            }},
            {Html::Style::STYLE_BORDER_WIDTH, [](blink::RenderStyle* renderStyle, const std::string &value){
                int borderWidth = StyleParser::parseStringByViewPortUnit(value);
                if(borderWidth > 0){
                    renderStyle->setBorderBottomWidth(borderWidth);
                    renderStyle->setBorderTopWidth(borderWidth);
                    renderStyle->setBorderLeftWidth(borderWidth);
                    renderStyle->setBorderRightWidth(borderWidth);
                }
            }},
            {Html::Style::STYLE_BORDER_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EBorderStyle borderStyle = StyleParser::parseBorderStyle(value);
                renderStyle->setBorderTopStyle(borderStyle);
                renderStyle->setBorderBottomStyle(borderStyle);
                renderStyle->setBorderLeftStyle(borderStyle);
                renderStyle->setBorderRightStyle(borderStyle);
            }},
            {Html::Style::STYLE_BORDER_RADIUS, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::Length length = {StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed};
                renderStyle->setBorderRadius({length, length});
            }},
            {Html::Style::STYLE_BORDER_TOP_LEFT_RADIUS, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::Length length = {StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed};
                renderStyle->setBorderTopLeftRadius({length, length});
            }},
            {Html::Style::STYLE_BORDER_TOP_RIGHT_RADIUS, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::Length length = {StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed};
                renderStyle->setBorderTopRightRadius({length, length});
            }},
            {Html::Style::STYLE_BORDER_BOTTOM_LEFT_RADIUS, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::Length length = {StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed};
                renderStyle->setBorderBottomLeftRadius({length, length});
            }},
            {Html::Style::STYLE_BORDER_BOTTOM_RIGHT_RADIUS, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::Length length = {StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed};
                renderStyle->setBorderBottomRightRadius({length, length});
            }},
            {Html::Style::STYLE_BORDER, [](blink::RenderStyle* renderStyle, std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                StyleParser::parserBorderStyleFromTokens(tokens,
                                                         [&](blink::EBorderStyle borderStyle) {
                                                             renderStyle->setBorderTopStyle(
                                                                     borderStyle);
                                                             renderStyle->setBorderBottomStyle(
                                                                     borderStyle);
                                                             renderStyle->setBorderLeftStyle(
                                                                     borderStyle);
                                                             renderStyle->setBorderRightStyle(
                                                                     borderStyle);
                                                         });
                StyleParser::parserBorderColorFromTokens(tokens,
                                                         [&](const blink::StyleColor &styleColor) {
                                                             renderStyle->setBorderLeftColor(
                                                                     styleColor);
                                                             renderStyle->setBorderRightColor(
                                                                     styleColor);
                                                             renderStyle->setBorderTopColor(
                                                                     styleColor);
                                                             renderStyle->setBorderBottomColor(
                                                                     styleColor);
                                                         });
                if(tokens.size() > 0){
                    int borderWidth = StyleParser::parseStringByViewPortUnit(tokens.at(0));
                    if(borderWidth > 0){
                        renderStyle->setBorderBottomWidth(borderWidth);
                        renderStyle->setBorderTopWidth(borderWidth);
                        renderStyle->setBorderLeftWidth(borderWidth);
                        renderStyle->setBorderRightWidth(borderWidth);
                    }
                }
            }},
            {Html::Style::STYLE_DISPLAY, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setDisplay(StyleParser::parseDisplay(value));
            }},
            {Html::Style::STYLE_POSITION, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setPosition(StyleParser::parsePosition(value));
            }},
            {Html::Style::STYLE_FLEX_DIRECTION, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setFlexDirection(StyleParser::parseFlexDirection(value));
            }},
            {Html::Style::STYLE_FLEX_FLOW, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() > 0){
                    renderStyle->setFlexDirection(
                            StyleParser::parseFlexDirection(tokens.at(0).c_str()));
                }
                if(tokens.size() > 1){
                    renderStyle->setFlexWrap(StyleParser::parseFlexWrap(tokens.at(1)));
                }
            }},
            {Html::Style::STYLE_FLEX_GROW, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setFlexGrow(StyleParser::parseStringToFloat(value.c_str()));
            }},
            {Html::Style::STYLE_FLEX_SHRINK, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setFlexShrink(StyleParser::parseStringToFloat(value.c_str()));
            }},
            {Html::Style::STYLE_FLEX_BASIS, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setFlexBasis(StyleParser::parseFlexBasis(value));
            }},
            {Html::Style::STYLE_FLEX_WRAP, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EFlexWrap  flexWrap = StyleParser::parseFlexWrap(value);
                renderStyle->setFlexWrap(flexWrap);
            }},
            {Html::Style::STYLE_FLEX_FLEX, [](blink::RenderStyle* renderStyle, const std::string &value){
                std::vector<std::string> tokens = StyleParser::parserTokenBySpace(value);
                if(tokens.size() == 1){
                    float flex = StyleParser::parseStringToFloat(value.c_str());
                    renderStyle->setFlexGrow(flex);
                    renderStyle->setFlexShrink(flex);
                    renderStyle->setFlexBasis({0, blink::LengthType::Fixed});
                }else if(tokens.size() == 2){
                    renderStyle->setFlexGrow(StyleParser::parseStringToFloat(tokens.at(0).c_str()));
                    renderStyle->setFlexShrink(StyleParser::parseStringToFloat(tokens.at(1).c_str()));
                    renderStyle->setFlexBasis({0, blink::LengthType::Fixed});
                }else if(tokens.size() == 3){
                    renderStyle->setFlexGrow(StyleParser::parseStringToFloat(tokens.at(0).c_str()));
                    renderStyle->setFlexShrink(StyleParser::parseStringToFloat(tokens.at(1).c_str()));
                    renderStyle->setFlexBasis(StyleParser::parseFlexBasis(tokens.at(2)));
                }
            }},
            {Html::Style::STYLE_FLEX_WRAP, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EFlexWrap  flexWrap = StyleParser::parseFlexWrap(value);
                renderStyle->setFlexWrap(flexWrap);
            }},
            {Html::Style::STYLE_ALIGN_ITEMS, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setAlignItems(StyleParser::parseItemPosition(value));
            }},
            {Html::Style::STYLE_ALIGN_CONTENT, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setAlignContent(StyleParser::parseAlignContent(value));
            }},
            {Html::Style::STYLE_JUSTIFY_CONTENT, [](blink::RenderStyle* renderStyle,const std::string &value){
                renderStyle->setJustifyContent(StyleParser::parseJustifyContent(value));
            }},
            {Html::Style::STYLE_ALIGN_SELF, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setAlignSelf(StyleParser::parseItemPosition(value));
            }},
            {Html::Style::STYLE_ORDER, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setOrder(StyleParser::parseStringToInt(value.c_str()));
            }},
            {Html::Style::STYLE_FONT_SIZE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setFontSize(StyleParser::parseStringByViewPortUnit(value));
            }},
            {Html::Style::STYLE_FONT_WEIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::FontWeight fontWeight = StyleParser::parseFontWeight(value);
                renderStyle->setFontWeight(fontWeight);
            }},
            {Html::Style::STYLE_FONT_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::FontStyle fontStyle = StyleParser::parseFontStyle(value);
                blink::FontDescription fontDescription = renderStyle->fontDescription();
                fontDescription.setStyle(fontStyle);
            }},
            {Html::Style::STYLE_FONT_FAMILY, [](blink::RenderStyle* renderStyle, const std::string &value){
                StyleUpdater::updateRenderStyleFontFamily(renderStyle, WTF::String::fromUTF8(value));
            }},
            {Html::Style::STYLE_FONT_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setColor(StyleParser::parseToBlinkColor(value));
            }},
            {Html::Style::STYLE_LINE_HEIGHT, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setLineHeight({StyleParser::parseStringByViewPortUnit(value), blink::LengthType::Fixed});
            }},
            {Html::Style::STYLE_LINES, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setMaxLines(StyleParser::parseStringToInt(value.c_str()));
            }},
            {Html::Style::STYLE_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setColor(StyleParser::parseToBlinkColor(value));
            }},
            {Html::Style::STYLE_VERTICAL_ALIGN, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setVerticalAlign(StyleParser::parseVerticalAlign(value));
            }},
            {Html::Style::STYLE_OPACITY, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setOpacity(StyleParser::parseStringToFloat(value.c_str()));
            }},
            {Html::Style::STYLE_Z_INDEX, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setZIndex(StyleParser::parseStringToInt(value.c_str()));
            }},
            {Html::Style::STYLE_VISIBILITY, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setVisibility(StyleParser::parseVisibility(value));
            }},
            {Html::Style::STYLE_TEXT_ALIGN, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setTextAlign(StyleParser::parseTextAlign(value));
            }},
            {Html::Style::STYLE_TEXT_JUSTIFY, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setTextJustify(StyleParser::parseTextJustify(value));
            }},
            {Html::Style::STYLE_TEXT_INDENT, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setTextIndent(StyleParser::parseStringToLengthUnit(value));
            }},
            {Html::Style::STYLE_BOX_SHADOW, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::ShadowDataVector shadows = StyleParser::parseBoxShadow(value);
                renderStyle->setBoxShadow(blink::ShadowList::adopt(shadows));
            }},
            {Html::Style::STYLE_TEXT_SHADOW, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::ShadowDataVector shadows = StyleParser::parseBoxShadow(value);
                renderStyle->setTextShadow(blink::ShadowList::adopt(shadows));
            }},
            {Html::Style::STYLE_OVERFLOW_WRAP, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setOverflowWrap(StyleParser::parseOverflowWrap(value));
            }},
            {Html::Style::STYLE_OVERFLOW_X, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setOverflowX(StyleParser::parseOverflow(value));
            }},
            {Html::Style::STYLE_OVERFLOW_Y, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setOverflowY(StyleParser::parseOverflow(value));
            }},
            {Html::Style::STYLE_OVERFLOW, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EOverflow  overflow = StyleParser::parseOverflow(value);
                renderStyle->setOverflowY(overflow);
                renderStyle->setOverflowX(overflow);
            }},
            {Html::Style::STYLE_WORD_BREAK, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EWordBreak wordBreak = StyleParser::parseWordBreak(value);
                renderStyle->setWordBreak(wordBreak);
            }},
            {Html::Style::STYLE_WHITE_SPACE, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setWhiteSpace(StyleParser::parseWhiteSpace(value));
            }},
            {Html::Style::STYLE_TEXT_OVERFLOW, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::TextOverflow textOverflow = StyleParser::parseTextOverflow(value);
                if(textOverflow == blink::TextOverflow::TextOverflowEllipsis){
                    if(renderStyle->ellipsis().isEmpty()){
                        renderStyle->setEllipsis(Html::Attr::Value::VALUE_ELLIPSIS);
                    }
                }
                renderStyle->setTextOverflow(textOverflow);
            }},
            {Html::Style::STYLE_TEXT_DIRECTION, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::TextDirection textDirection = StyleParser::parseTextDirection(value);
                renderStyle->setDirection(textDirection);
            }},
            {Html::Style::STYLE_TEXT_DECORATION_COLOR, [](blink::RenderStyle* renderStyle, const std::string &value){
                renderStyle->setTextDecorationColor(StyleParser::parseStyleColor(value));
            }},
            {Html::Style::STYLE_TEXT_DECORATION_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::TextDecorationStyle textDecorationStyle = StyleParser::parseTextDecorationStyle(
                        value);
                renderStyle->setTextDecorationStyle(textDecorationStyle);
            }},
            {Html::Style::STYLE_TEXT_DECORATION, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::TextDecoration textDecoration = StyleParser::parseTextDecoration(value);
                renderStyle->setTextDecoration(textDecoration);
                renderStyle->applyTextDecorations();
            }},
            {Html::Style::STYLE_LETTER_SPACING, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setLetterSpacing(StyleParser::parseStringByViewPortUnit(value));
                }
            }},
            {Html::Style::STYLE_WORD_SPACING, [](blink::RenderStyle* renderStyle, const std::string &value){
                float valueFloat = StyleParser::parseStringByViewPortUnit(value);
                if(!isnan(valueFloat)){
                    renderStyle->setWordSpacing(StyleParser::parseStringByViewPortUnit(value));
                }
            }},
            {Html::Style::STYLE_BOX_SIZING, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::EBoxSizing boxSizing = StyleParser::parseBoxSizing(value);
                renderStyle->setBoxSizing(boxSizing);
            }},
            {Html::Style::STYLE_TRANSFORM, [](blink::RenderStyle* renderStyle, const std::string &value){
                blink::TransformOperations transformOperations = TransformParser::parseTransform(value);
                renderStyle->setTransform(transformOperations);
            }},
            {Html::Style::STYLE_TRANSFORM_ORIGIN, [](blink::RenderStyle* renderStyle, const std::string &value){
                TransformParser::parseTransformOrigin(renderStyle, value);
            }},
            {Html::Style::STYLE_TRANSFORM_STYLE, [](blink::RenderStyle* renderStyle, const std::string &value){
                TransformParser::parseTransformStyle(renderStyle, value);
            }}
    };


    static void applyRenderStyle(RefPtr<blink::RenderStyle> renderStyle, std::map<std::string, std::string> *styles) {
        for (std::map<std::string,std::string>::iterator  it = styles->begin(); it != styles->end(); ++it) {
            auto find = styleParserFunctions.find(it->first);
            if(find != styleParserFunctions.end()){
                find->second(renderStyle.get(), it->second);
            }else{
                if(it->first.find(Html::Style::STYLE_ACTIVE_SUFFIX) > 0){
                    renderStyle->setAffectedByActive();
                }
            }
        }
    }

    RefPtr<blink::RenderStyle> StyleUpdater::createInteritRenderStyle(RefPtr<blink::RenderStyle> parentStyle){
        RefPtr<blink::RenderStyle> renderStyle = blink::RenderStyle::createDefaultStyle();
        renderStyle->setMaxWidth({Screen::mDeviceWidth, blink::LengthType::Fixed});
        renderStyle->inheritFrom(parentStyle.get());
        return renderStyle;
    }

    RefPtr<blink::RenderStyle> StyleUpdater::createRenderStyle(RefPtr<blink::RenderStyle> parentStyle, std::map<std::string, std::string> *styles) {
        RefPtr<blink::RenderStyle> renderStyle = blink::RenderStyle::createDefaultStyle();
        renderStyle->inheritFrom(parentStyle.get());
        applyRenderStyle(renderStyle, styles);
        return renderStyle;
    }

    RefPtr<blink::RenderStyle> StyleUpdater::newRenderStyleUpdates(blink::RenderStyle *renderStyle,  std::map<std::string, std::string> *styles) {
        if(styles->size() == 0){

        }
        RefPtr<blink::RenderStyle> clone = blink::RenderStyle::clone(renderStyle);
        if(styles != nullptr){
            applyRenderStyle(renderStyle, styles);
        }
        return renderStyle;
    }



    void StyleUpdater::updateRenderStyleFontFamily(blink::RenderStyle* renderStyle, const WTF::AtomicString& fontFamilyName){
        blink::FontDescription fontDescription = renderStyle->fontDescription();
        blink::FontFamily fontFamily;
        fontFamily.setFamily(fontFamilyName);
        fontDescription.setFamily(fontFamily);
        renderStyle->setFontDescription(fontDescription);
        renderStyle->font().update(blink::Platform::current()->fontSelector());
    }

}
