//
// Created by furture on 2018/10/11.
//

#include "OneSequenceGestureRecognizer.h"

namespace weexuikit {


    OneSequenceGestureRecognizer::OneSequenceGestureRecognizer(
            GestureHandlerContext *gestureContext) : GestureRecognizer(gestureContext) {
        mEntries = new std::map<int, GestureArenaEntry *>();
        mTrackedPointers = new std::set<int>;
        mTeam = nullptr;
    }


    OneSequenceGestureRecognizer::~OneSequenceGestureRecognizer() {
        if (mEntries != nullptr) {
            delete mEntries;
            mEntries = nullptr;
        }
        if (mTrackedPointers != nullptr) {
            delete mTrackedPointers;
            mTrackedPointers = nullptr;
        }
        if (mTeam != nullptr) {
            mTeam = nullptr;
        }
    }


    void OneSequenceGestureRecognizer::resolve(GestureDisposition disposition) {
        std::map<int, GestureArenaEntry *> *localEntries = mEntries;
        for (auto it = localEntries->begin(); it != localEntries->end(); it++) {
            it->second->resolve(disposition);
        }
        mEntries->clear();
    }

    void OneSequenceGestureRecognizer::dispose() {
        resolve(GestureDisposition::rejected);
        std::set<int> trackedPointers = *mTrackedPointers;
        for (int pointer : trackedPointers) {
            mGestureHandlerContext->pointerRouter->removeRoute(pointer, this);
        }
        mTrackedPointers->clear();
        assert(mEntries->size() == 0);
        GestureRecognizer::dispose();
    }


    void OneSequenceGestureRecognizer::route(const PointerEvent &event) {
        this->handleEvent(event);
    }


    GestureArenaEntry *OneSequenceGestureRecognizer::_addPointerToArena(int pointer) {
        if (mTeam != nullptr)
            return mTeam->add(pointer, this);
        return mGestureHandlerContext->gestureArena->add(pointer, this);
    }


    void OneSequenceGestureRecognizer::startTrackingPointer(int pointer) {
        mGestureHandlerContext->pointerRouter->addRoute(pointer, this);
        mTrackedPointers->insert(pointer);
        (*mEntries)[pointer] = _addPointerToArena(pointer);
    }

    void OneSequenceGestureRecognizer::stopTrackingPointer(int pointer) {
        if (mTrackedPointers->find(pointer) != mTrackedPointers->end()) {
            mGestureHandlerContext->pointerRouter->removeRoute(pointer, this);
            mTrackedPointers->erase(pointer);
            if (mTrackedPointers->size() == 0)
                didStopTrackingLastPointer(pointer);
        }
    }

    void OneSequenceGestureRecognizer::stopTrackingIfPointerNoLongerDown(PointerEvent event) {
        if (event.isCancelEvent() || event.isUpEvent()) {
            stopTrackingPointer(event.pointer);
        }
    }
}