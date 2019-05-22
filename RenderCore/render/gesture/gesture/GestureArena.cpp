//
// Created by furture on 2018/10/11.
//

#include "GestureArena.h"


namespace weexuikit {

    GestureArena::GestureArena() {
        members = new std::vector<GestureArenaMember *>;
        eagerWinner = nullptr;
    }

    GestureArena::~GestureArena() {
        if (members != nullptr) {
            delete members;
            members = nullptr;
        }
    }
}
