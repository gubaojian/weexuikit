//
// Created by furture on 2018/10/16.
//

#include "CombiningGestureArenaEntry.h"

namespace weexuikit {
    CombiningGestureArenaEntry::CombiningGestureArenaEntry(CombiningGestureArenaMember *combiner,
                                                           GestureArenaMember *member)
            : GestureArenaEntry(
            nullptr, 0, member), mCombiner(combiner), mGestureArenamember(member) {
    }

    void CombiningGestureArenaEntry::resolve(GestureDisposition disposition) {
            mCombiner->_resolve(mGestureArenamember, disposition);
    }
}