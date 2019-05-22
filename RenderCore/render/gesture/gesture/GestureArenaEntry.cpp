//
// Created by furture on 2018/10/11.
//

#include "GestureArenaEntry.h"
#include "GestureArenaManager.h"

namespace weexuikit {
    void GestureArenaEntry::resolve(GestureDisposition disposition) {
            mArena->_resolve(mPointer, mMember, disposition);
    }
}
