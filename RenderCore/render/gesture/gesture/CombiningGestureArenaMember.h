//
// Created by furture on 2018/10/16.
//

#ifndef WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAMEMBER_H
#define WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAMEMBER_H
#include <vector>
#include <algorithm>
#include "GestureArenaMember.h"
#include "GestureArenaTeam.h"
#include "GestureArenaEntry.h"

namespace weexuikit {
    class CombiningGestureArenaMember : public GestureArenaMember {

    public:
        CombiningGestureArenaMember(GestureArenaTeam *owner, int pointer);


        void acceptGesture(int pointer) override;

        void rejectGesture(int pointer) override;

        void _close();

        GestureArenaEntry *_add(int pointer, GestureArenaMember *member);

        void _resolve(GestureArenaMember *member, GestureDisposition disposition);

    private:
        GestureArenaTeam *mOwner;
        std::vector<GestureArenaMember *> mMembers;
        int mPointer;
        bool mResolved;
        GestureArenaMember *mWinner;
        GestureArenaEntry *mEntry;
    };

}

#endif //WEEX_UIKIT_GESTURE_COMBININGGESTUREARENAMEMBER_H
