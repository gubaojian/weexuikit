//
// Created by furture on 2019/2/18.
//

#include "Transition.h"
#include "TransformPropertyValue.h"
#include "LengthPropertyValue.h"
#include "FloatPropertyValue.h"
#include "ColorPropertyValue.h"
#include <render/core/parser/StyleParser.h>
#include <render/platform/common/log.h>
#include <render/widget/View.h>
#include <render/core/parser/TransformParser.h>


namespace weexuikit {


    static const std::map<std::string, std::function<PropertyValue*(Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)>> mTransitionFunctionsMap = {
            {Html::Style::STYLE_TRANSFORM, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::TransformOperations transformOperations = TransformParser::parseTransform(value);
                return new TransformPropertyValue(transtion, renderStyle->transform(), transformOperations);
            }},
            {Html::Style::STYLE_TRANSFORM, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::TransformOperations transformOperations = TransformParser::parseTransform(value);
                return new TransformPropertyValue(transtion, renderStyle->transform(), transformOperations);
            }},
            {Html::Style::STYLE_WIDTH, [](Transition* transtion,blink::RenderStyle* renderStyle, const std::string& value){
                blink::Length widthFrom = renderStyle->width();
                blink::Length withTo = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(widthFrom, withTo, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setWidth(length);
                });
            }},
            {Html::Style::STYLE_HEIGHT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->height();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setHeight(length);
                });
            }},
            {Html::Style::STYLE_TOP, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->top();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setTop(length);
                });
            }},
            {Html::Style::STYLE_BOTTOM, [](Transition* transtion,blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->bottom();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setBottom(length);
                });
            }},
            {Html::Style::STYLE_LEFT, [](Transition* transtion,blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->left();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setLeft(length);
                });
            }},
            {Html::Style::STYLE_RIGHT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->right();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setRight(length);
                });
            }},
            {Html::Style::STYLE_MARGIN_LEFT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->marginLeft();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setMarginLeft(length);
                });
            }},
            {Html::Style::STYLE_MARGIN_RIGHT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->marginRight();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setMarginRight(length);
                });
            }},
            {Html::Style::STYLE_MARGIN_BOTTOM, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->marginBottom();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setMarginBottom(length);
                });
            }},
            {Html::Style::STYLE_MARGIN_TOP, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->marginTop();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setMarginTop(length);
                });
            }},
            {Html::Style::STYLE_PADDING_LEFT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->paddingLeft();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setPaddingLeft(length);
                });
            }},
            {Html::Style::STYLE_PADDING_RIGHT, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->paddingRight();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setPaddingRight(length);
                });
            }},
            {Html::Style::STYLE_PADDING_BOTTOM, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->paddingBottom();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setPaddingBottom(length);
                });
            }},
            {Html::Style::STYLE_PADDING_TOP, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::Length from = renderStyle->paddingTop();
                blink::Length to = StyleParser::parseStringToLengthUnit(value);
                return new LengthPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Length& length){
                    renderStyle->setPaddingTop(length);
                });
            }},
            {Html::Style::STYLE_OPACITY, [](Transition* transtion,blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                float from = renderStyle->opacity();
                float to = StyleParser::parseStringToFloat(value.data());
                return new FloatPropertyValue(from, to, [](blink::RenderStyle* renderStyle, float value){
                    renderStyle->setOpacity(value);
                });
            }},
            {Html::Style::STYLE_FONT_SIZE, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                float from = renderStyle->fontSize();
                float to = StyleParser::parseStringByViewPortUnit(value);
                return new FloatPropertyValue(from, to, [](blink::RenderStyle* renderStyle, float value){
                    renderStyle->setFontSize(value);
                });
            }},
            {Html::Style::STYLE_BACKGROUND_COLOR, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::StyleColor styleColor = renderStyle->backgroundColor();
                blink::Color from = styleColor.color();
                blink::Color to = StyleParser::parseToBlinkColor(value);
                return new ColorPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Color& color){
                    renderStyle->setBackgroundColor(color);
                });
            }},
            {Html::Style::STYLE_BACKGROUND, [](Transition* transtion, blink::RenderStyle* renderStyle, const std::string& value)->PropertyValue*{
                blink::StyleColor styleColor = renderStyle->backgroundColor();
                blink::Color from = styleColor.color();
                blink::Color to = StyleParser::parseToBlinkColor(value);
                return new ColorPropertyValue(from, to, [](blink::RenderStyle* renderStyle, const blink::Color& color){
                    renderStyle->setBackgroundColor(color);
                });
            }}
    };


    static inline int64_t  parseTimeMillis(std::map<std::string, std::string>* styles, const char* key, int64_t defaultValue){
        auto it = styles->find(key);
        if(it == styles->end()){
            return defaultValue;
        }
        return  strtoll(it->second.data(), nullptr, 10);
    }

    static std::set<std::string> parseTransitionProperties(const std::string& propertiesStr){
        std::vector<std::string> tokens = StyleParser::parseTokensByComma(propertiesStr);
        std::set<std::string> properties;
        for(auto& token : tokens){
            StyleParser::trimStringSpace(token);
            if(token.size() == 0){
                continue;
            }
            properties.insert(token);
        }
        return properties;
    }

    static WTF::RefPtr<blink::TimingFunction> parseTimingFunction(std::string& timingFunction){
        if(timingFunction.find(Html::Style::STYLE_TRANSITION_TIME_FUNCTION_CUBIC_BEZIER) == 0){
            double x1, y1, x2, y2;
            sscanf(timingFunction.c_str(), "cubic-bezier(%lf,%lf,%lf,%lf)", &x1, &y1, &x2, &y2);
            return blink::CubicBezierTimingFunction::create(x1, y1, x2, y2);
        }
        if(timingFunction == Html::Style::STYLE_TRANSITION_TIME_FUNCTION_EASE){
            return blink::CubicBezierTimingFunction::preset(blink::CubicBezierTimingFunction::Ease);
        }else if(timingFunction == Html::Style::STYLE_TRANSITION_TIME_FUNCTION_EASE_IN){
            return blink::CubicBezierTimingFunction::preset(blink::CubicBezierTimingFunction::EaseIn);
        }else if(timingFunction ==  Html::Style::STYLE_TRANSITION_TIME_FUNCTION_EASE_OUT){
            return blink::CubicBezierTimingFunction::preset(blink::CubicBezierTimingFunction::EaseOut);
        }else if(timingFunction ==  Html::Style::STYLE_TRANSITION_TIME_FUNCTION_EASE_IN_OUT){
            return blink::CubicBezierTimingFunction::preset(blink::CubicBezierTimingFunction::EaseInOut);
        }else if(timingFunction == Html::Style::STYLE_TRANSITION_TIME_FUNCTION_LINEAR){
            return blink::LinearTimingFunction::shared();
        }
        return blink::LinearTimingFunction::shared();
    }


    Transition::Transition():mTicker(nullptr), mView(nullptr), mDuration(0){

    }

    Transition::~Transition() {
        if(mTicker.get() != nullptr){
            mTicker->stop(true);
        }
    }


    Transition* Transition::fromStyle(std::map<std::string, std::string>* styles, View* view) {
        auto it =  styles->find(Html::Style::STYLE_TRANSITION_PROPERTY);
        if(it == styles->end()){
            return nullptr;
        }
        std::set<std::string> properties = parseTransitionProperties(it->second);
        if(properties.size() == 0){
            return nullptr;
        }
        Transition* transition = new Transition();
        transition->mTransitionPropertyNames = std::move(properties);
        transition->mDelay = parseTimeMillis(styles, Html::Style::STYLE_TRANSITION_DELAY, 0);
        transition->mDuration = parseTimeMillis(styles, Html::Style::STYLE_TRANSITION_DURATION, 0);
        it = styles->find(Html::Style::STYLE_TRANSITION_TIMING_FUNCTION);
        if(it != styles->end()){
            transition->mTimingFunction = parseTimingFunction(it->second);
        }else{
            transition->mTimingFunction = blink::LinearTimingFunction::shared();
        }
        transition->mView = view;
        return transition;
    }


    void Transition::updateTranstionParams(std::map<std::string, std::string> *updateStyles) {
        auto it = updateStyles->find(Html::Style::STYLE_TRANSITION_DELAY);
        if(it != updateStyles->end()){
            mDelay = parseTimeMillis(updateStyles, Html::Style::STYLE_TRANSITION_DELAY, 0);
        }

        it = updateStyles->find(Html::Style::STYLE_TRANSITION_DURATION);
        if(it != updateStyles->end()){
            mDuration = parseTimeMillis(updateStyles, Html::Style::STYLE_TRANSITION_DURATION, 0);
        }

        it = updateStyles->find(Html::Style::STYLE_TRANSITION_TIMING_FUNCTION);
        if(it != updateStyles->end()){
            mTimingFunction = parseTimingFunction(it->second);
        }

        it = updateStyles->find(Html::Style::STYLE_TRANSITION_PROPERTY);
        if(it != updateStyles->end()){
            mTransitionPropertyNames = std::move(parseTransitionProperties(it->second));
        }
    }



    bool Transition::hasTransitionProperty(std::map<std::string, std::string> *updateStyles) {
        if(mDuration <= 0){
            return false;
        }

        for(auto transitionProperyName : mTransitionPropertyNames){
            auto it  = updateStyles->find(transitionProperyName);
            if(it != updateStyles->end()){
                return  true;
            }
        }
        return false;
    }


    void Transition::startTransition(std::map<std::string, std::string> *updateStyles) {

        std::map<std::string, std::string> transitionUpdateStyles;

        for(auto it = updateStyles->begin(); it != updateStyles->end(); it++){
            if(mTransitionPropertyNames.find(it->first) != mTransitionPropertyNames.end()){
                transitionUpdateStyles.insert(*it);
                updateStyles->erase(it);
            }
        }

        for(auto propertyValueIt = mTransitioPropertyValues.begin();
                propertyValueIt != mTransitioPropertyValues.end(); propertyValueIt++){
            if(mTransitionPropertyNames.find(propertyValueIt->first) != mTransitionPropertyNames.end()){
                mTransitioPropertyValues.erase(propertyValueIt);
                delete propertyValueIt->second;
            }
        }

        if(mTransitioPropertyValues.size() > 0) {
            onTransition(1);
            for (auto propertyValueIt = mTransitioPropertyValues.begin();
                 propertyValueIt != mTransitioPropertyValues.end(); propertyValueIt++) {
                delete propertyValueIt->second;
            }
            mTransitioPropertyValues.clear();
        }

        blink::RenderObject* renderObject = mView->getRenderObject();
        blink::RenderStyle* renderStyle = renderObject->style();
        for(auto transitionStyle : transitionUpdateStyles){
            auto functionIt = mTransitionFunctionsMap.find(transitionStyle.first);
            if(functionIt == mTransitionFunctionsMap.end()){
                continue;
            }
            PropertyValue* propertyValue = functionIt->second(this, renderStyle, transitionStyle.second);
            if(propertyValue != nullptr){
                mTransitioPropertyValues.insert({transitionStyle.first, propertyValue});
            }
        }

        if(mTicker.get() != nullptr){
            mTicker->stop(true);
        }
        mAnimationTicker = std::make_shared<weexuikit::AnimationTicker>();
        mAnimationTicker->duration = mDuration;
        Transition* weakSelf = this;
        mAnimationTicker->onAnimation = [weakSelf](float process){
            weakSelf->onTransition(process);
        };
        mTicker = mView->getUIContext()->getTickerProvider()->createTicker(mAnimationTicker);
        mAnimationTicker->mTicker = mTicker;
        mTicker->start();
    }


    View* Transition::getView() {
        return mView;
    }

    void Transition::onTransition(float process) {
        if(mTransitioPropertyValues.size() <= 0){
            return;
        }
        float timingProcess = process;
        if(mTimingFunction.get() != nullptr){
            timingProcess = mTimingFunction->evaluate(process, 0.001);
        }
        blink::RenderObject*  renderObject = mView->getRenderObject();
        RefPtr<blink::RenderStyle> renderStyle = blink::RenderStyle::clone(renderObject->style());
        for(auto propertyValueIt = mTransitioPropertyValues.begin(); propertyValueIt != mTransitioPropertyValues.end(); propertyValueIt++){
            PropertyValue* propertyValue = propertyValueIt->second;
            propertyValue->blendToStyle(timingProcess, renderStyle.get());
        }
        renderObject->setStyle(renderStyle);
        mView->getUIContext()->markNeedsPaint();
    }


}