//
// Created by furture on 2019/2/18.
//

#ifndef WEEX_UIKIT_TRANSITION_H
#define WEEX_UIKIT_TRANSITION_H
#include "PropertyValue.h"
#include <render/core/node/Node.h>
#include <render/platform/animation/TimingFunction.h>
#include <string>
#include <map>
#include <set>
#include <cstdint>
#include <render/gesture/foundation/TickerProvider.h>

namespace weexuikit {


    class View;

    class Transition {

        public:
            Transition();
            ~Transition();

        public:
            static Transition* fromStyle(std::map<std::string,std::string>* styles, View* view);

        public:
            void updateTranstionParams(std::map<std::string,std::string>* updateStyles);

            bool hasTransitionProperty(std::map<std::string,std::string>* updateStyles);

            void startTransition(std::map<std::string,std::string>* updateStyles);


        public:
            View* getView();

        public:
            void onTransition(float process);

        private:
            int64_t mDuration;
            int64_t mDelay;
            std::set<std::string> mTransitionPropertyNames;
            std::map<std::string,PropertyValue*> mTransitioPropertyValues;
            std::map<std::string, std::string> mTargetStyles;
            WTF::RefPtr<blink::TimingFunction> mTimingFunction;
            std::shared_ptr<weexuikit::AnimationTicker> mAnimationTicker;
            std::shared_ptr<weexuikit::Ticker>  mTicker;
            View* mView;
    };
}



#endif //WEEX_UIKIT_TRANSITION_H
