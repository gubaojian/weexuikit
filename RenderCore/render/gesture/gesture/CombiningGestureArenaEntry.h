//
// Created by furture on 2018/10/16.
//

#ifndef WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAENTRY_H
#define WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAENTRY_H
#include "GestureArenaEntry.h"
#include "CombiningGestureArenaMember.h"

namespace weexuikit {
    class CombiningGestureArenaEntry : public GestureArenaEntry {

    public:
        CombiningGestureArenaEntry(CombiningGestureArenaMember *combiner,
                                   GestureArenaMember *member);

        void resolve(GestureDisposition disposition) override;

    private:
        CombiningGestureArenaMember *mCombiner;
        GestureArenaMember *mGestureArenamember;
    };
}


#endif //WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAENTRY_H
