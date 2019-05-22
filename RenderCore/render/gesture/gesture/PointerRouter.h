//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_POINTERROUTER_H
#define WEEX_UIKIT_GESTURE_POINTERROUTER_H
#include "PointerEvent.h"
#include "PointerRoute.h"
#include <map>
#include <set>
#include <vector>
#include <functional>
/// A routing table for [PointerEvent] events.
namespace weexuikit {

    class PointerRouter {


    public:
        /// Adds a route to the routing table.
        ///
        /// Whenever this object routes a [PointerEvent] corresponding to
        /// pointer, call route.
        ///
        /// Routes added reentrantly within [PointerRouter.route] will take effect when
        /// routing the next event.
        void addRoute(int pointer, PointerRoute *route);


        /// Removes a route from the routing table.
        ///
        /// No longer call route when routing a [PointerEvent] corresponding to
        /// pointer. Requires that this route was previously added to the router.
        ///
        /// Routes removed reentrantly within [PointerRouter.route] will take effect
        /// immediately.
        void removeRoute(int pointer, PointerRoute *route);

        /// Adds a route to the global entry in the routing table.
        ///
        /// Whenever this object routes a [PointerEvent], call route.
        ///
        /// Routes added reentrantly within [PointerRouter.route] will take effect when
        /// routing the next event.
        void addGlobalRoute(PointerRoute *route);


        /// Removes a route from the global entry in the routing table.
        ///
        /// No longer call route when routing a [PointerEvent]. Requires that this
        /// route was previously added via [addGlobalRoute].
        ///
        /// Routes removed reentrantly within [PointerRouter.route] will take effect
        /// immediately.
        void removeGlobalRoute(PointerRoute *route);


        void _dispatch(const PointerEvent &event, PointerRoute *route);

        /// Calls the routes registered for this pointer event.
        ///
        /// Routes are called in the order in which they were added to the
        /// PointerRouter object.
        void route(const PointerEvent &event);


    private:
        std::map<int, std::set<PointerRoute *> *> mRouteMap;
        std::set<PointerRoute *> mGlobalRoutes;
    };
}


#endif //WEEX_UIKIT_GESTURE_POINTERROUTER_H
