//
// Created by furture on 2018/10/11.
//

#include "GestureArenaManager.h"

namespace weexuikit {
    GestureArenaEntry *GestureArenaManager::add(int pointer, GestureArenaMember *member) {
        GestureArena *arena = nullptr;
        auto findIt = mArenas.find(pointer);
        if (findIt != mArenas.end()) {
            arena = findIt->second;
        }
        if (arena == nullptr) {
            arena = new GestureArena();
            mArenas[pointer] = arena;
        }
        arena->add(member);
        return new GestureArenaEntry(this, pointer, member);
    }


    void GestureArenaManager::close(int pointer) {
        GestureArena *state = mArenas[pointer];
        if (state == nullptr)
            return; // This arena either never existed or has been resolved.
        state->isOpen = false;
        _tryToResolveArena(pointer, state);
    }


    void GestureArenaManager::sweep(int pointer) {
        GestureArena *state = mArenas[pointer];
        if (state == nullptr)
            return; // This arena either never existed or has been resolved.
        assert(!state->isOpen);
        if (state->isHeld) {
            state->hasPendingSweep = true;
            return; // This arena is being held for a long-lived member.
        }
        mArenas.erase(pointer);
        if (state->members->size() > 0) {
            // First member wins.
            state->members->at(0)->acceptGesture(pointer);
            // Give all the other members the bad news.
            for (int i = 1; i < state->members->size(); i++)
                (*state->members)[i]->rejectGesture(pointer);
        }
    }

    void GestureArenaManager::hold(int pointer) {
        GestureArena *state = mArenas[pointer];
        if (state == nullptr)
            return; // This arena either never existed or has been resolved.
        state->isHeld = true;
    }

    void GestureArenaManager::release(int pointer) {
        GestureArena *state = mArenas[pointer];
        if (state == nullptr)
            return; // This arena either never existed or has been resolved.
        state->isHeld = false;
        if (state->hasPendingSweep)
            sweep(pointer);
    }


    void GestureArenaManager::_resolve(int pointer, GestureArenaMember *member,
                                       GestureDisposition disposition) {
        GestureArena *state = mArenas[pointer];
        if (state == nullptr)
            return; // This arena has already resolved.
        if (disposition == GestureDisposition::rejected) {
            std::vector<GestureArenaMember *> *members = state->members;
            members->erase(std::remove(members->begin(), members->end(), member), members->end());
            member->rejectGesture(pointer);
            if (!state->isOpen)
                _tryToResolveArena(pointer, state);
        } else {
            assert(disposition == GestureDisposition::accepted);
            if (state->isOpen) {
                if (state->eagerWinner == nullptr) {
                    state->eagerWinner = member;
                }
            } else {
                _resolveInFavorOf(pointer, state, member);
            }
        }
    }


    void GestureArenaManager::_tryToResolveArena(int pointer, GestureArena *state) {
        assert(mArenas[pointer] == state);
        assert(!state->isOpen);
        if (state->members->size() == 1) {
            _resolveByDefault(pointer, state);
        } else if (state->members->size() == 0) {
            mArenas.erase(pointer);
        } else if (state->eagerWinner != nullptr) {
            _resolveInFavorOf(pointer, state, state->eagerWinner);
        }
    }


    void GestureArenaManager::_resolveByDefault(int pointer, GestureArena *state) {
        if (mArenas.at(pointer) == nullptr)
            return; // Already resolved earlier.
        assert(mArenas[pointer] == state);
        assert(!state->isOpen);
        std::vector<GestureArenaMember *> *members = state->members;
        assert(members->size() == 1);
        mArenas.erase(pointer);
        (*state->members).at(0)->acceptGesture(pointer);
    }


    void GestureArenaManager::_resolveInFavorOf(int pointer, GestureArena *state,
                                                GestureArenaMember *member) {
        assert(state == mArenas[pointer]);
        assert(state != nullptr);
        assert(state->eagerWinner == nullptr || state->eagerWinner == member);
        assert(!state->isOpen);
        mArenas.erase(pointer);
        std::vector<GestureArenaMember *> *members = state->members;
        for (GestureArenaMember *rejectedMember : *members) {
            if (rejectedMember != member)
                rejectedMember->rejectGesture(pointer);
        }
        member->acceptGesture(pointer);
    }
}
