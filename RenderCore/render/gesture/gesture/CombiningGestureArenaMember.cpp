//
// Created by furture on 2018/10/16.
//

#include "CombiningGestureArenaMember.h"
#include "CombiningGestureArenaEntry.h"

namespace weexuikit {
    CombiningGestureArenaMember::CombiningGestureArenaMember(GestureArenaTeam *owner, int pointer) {
        this->mOwner = owner;
        this->mPointer = pointer;
    }

    void CombiningGestureArenaMember::acceptGesture(int pointer) {
        assert(mPointer == pointer);
        assert(mWinner != nullptr || mMembers.size() > 0);
        _close();
        if (mWinner == nullptr) {
            mWinner = mOwner->mCaptain;
        }
        if (mWinner == nullptr) {
            mWinner = mMembers[0];
        }
        for (GestureArenaMember *member : mMembers) {
            if (member != mWinner)
                member->rejectGesture(pointer);
        }
        mWinner->acceptGesture(pointer);
    }

    void CombiningGestureArenaMember::rejectGesture(int pointer) {
        assert(mPointer == pointer);
        _close();
        for (GestureArenaMember *member : mMembers) {
            member->rejectGesture(pointer);
        }
    }

    void CombiningGestureArenaMember::_close() {
        assert(!mResolved);
        mResolved = true;
        CombiningGestureArenaMember *combiner = mOwner->removeCombiners(mPointer);
        assert(combiner == this);
    }

    GestureArenaEntry *CombiningGestureArenaMember::_add(int pointer, GestureArenaMember *member) {
        assert(!mResolved);
        assert(mPointer == pointer);
        mMembers.push_back(member);
        if (mEntry == nullptr) {
            mOwner->mGestureContext->gestureArena->add(pointer, this);
        }
        return new CombiningGestureArenaEntry(this, member);

    }

    void CombiningGestureArenaMember::_resolve(GestureArenaMember *member,
                                               GestureDisposition disposition) {
        if (mResolved)
            return;
        if (disposition == GestureDisposition::rejected) {
            mMembers.erase(std::remove(mMembers.begin(), mMembers.end(), member), mMembers.end());
            member->rejectGesture(mPointer);
            if (mMembers.size() == 0)
                mEntry->resolve(disposition);
        } else {
            assert(disposition == GestureDisposition::accepted);
            if (mWinner == nullptr) {
                mWinner = mOwner->mCaptain;
            }
            if (mWinner == nullptr) {
                mWinner = mMembers[0];
            }
            mEntry->resolve(disposition);
        }
    }
}
