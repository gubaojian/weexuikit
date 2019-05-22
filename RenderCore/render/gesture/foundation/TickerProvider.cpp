//
// Created by furture on 2018/10/23.
//

#include "TickerProvider.h"
#include <sys/types.h>
#include <unistd.h>

namespace weexuikit {

    void TickerProvider::checkTicker(const int64_t clockTimeMS) {
        if (mTickerList->size() == 0) {
            return;
        }
        // first loop
        int count = mTickerList->size();
        for (int i = 0; i < count; i++) {
            std::shared_ptr<Ticker> ticker = mTickerList->at(i);
            if (ticker != nullptr && ticker->isActive) {
                ticker->fireTick(clockTimeMS);
            }
        }
        //second loop clean
        for (int i = 0; i < count;) {
            if (i >= mTickerList->size()) {
                break;
            }
            std::shared_ptr<Ticker> ticker = mTickerList->at(i);
            if (ticker->isDone || ticker->isCanceled) {
                mTickerList->erase(std::remove(mTickerList->begin(), mTickerList->end(), ticker),
                                   mTickerList->end());
            } else {
                i++;
            }
        }
    }


    std::shared_ptr<Ticker> TickerProvider::createTicker(std::shared_ptr<TickerCallback> onTick) {
        std::shared_ptr<Ticker> ticker = std::make_shared<Ticker>(onTick);
        mTickerList->push_back(ticker);
        return ticker;
    }

    void TickerProvider::removeTicker(std::shared_ptr<Ticker> ticker) {
        ticker->isDone = true;
        ticker->isActive = false;
        ticker->isCanceled = true;
    }
}
