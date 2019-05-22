//
// Created by furture on 2018/10/16.
//

#include "GestureArenaTeam.h"
#include "CombiningGestureArenaMember.h"

namespace weexuikit {

    GestureArenaEntry *GestureArenaTeam::add(int pointer, GestureArenaMember *member) {
        CombiningGestureArenaMember *combiningGestureArenaMember = nullptr;
        auto combinerIt = mCombiners.find(pointer);
        if (combinerIt != mCombiners.end()) {
            combiningGestureArenaMember = combinerIt->second;
        } else {
            combiningGestureArenaMember = new CombiningGestureArenaMember(this, pointer);
            mCombiners.insert({pointer, combiningGestureArenaMember});
        }
        return combiningGestureArenaMember->_add(pointer, member);
    }


    CombiningGestureArenaMember *GestureArenaTeam::removeCombiners(int pointer) {
        auto it = mCombiners.find(pointer);
        if (it != mCombiners.end()) {
            mCombiners.erase(it);
        }
        return it->second;
    }
}