//
// Created by furture on 2018/10/11.
//

#include "PointerRouter.h"

namespace weexuikit {


    void PointerRouter::addRoute(int pointer, PointerRoute *route) {
        std::set<PointerRoute *> *routes = nullptr;
        auto it = mRouteMap.find(pointer);
        if (it != mRouteMap.end()) {
            routes = it->second;
        } else {
            routes = new std::set<PointerRoute *>();
            mRouteMap.insert({pointer, routes});
        }
        auto findRoute = routes->find(route);
        if (findRoute != routes->end()) {
            return;
        }
        routes->insert(route);
    }

    void PointerRouter::removeRoute(int pointer, PointerRoute *route) {
        std::set<PointerRoute *> *routes = nullptr;
        auto it = mRouteMap.find(pointer);
        if (it == mRouteMap.end()) {
            return;
        }
        routes = it->second;
        routes->erase(route);
        if (routes->size() == 0) {
            mRouteMap.erase(pointer);
            delete routes;
        }
    }


    void PointerRouter::addGlobalRoute(PointerRoute *route) {
        auto routeIt = mGlobalRoutes.find(route);
        if (routeIt != mGlobalRoutes.end()) {
            return;
        }
        mGlobalRoutes.insert(route);
    }


    void PointerRouter::removeGlobalRoute(PointerRoute *route) {
        mGlobalRoutes.erase(route);
    }

    void PointerRouter::_dispatch(const PointerEvent &event, PointerRoute *route) {
        route->route(event);
    }


    void PointerRouter::route(const PointerEvent &event) {
        std::set<PointerRoute *> *routes = nullptr;
        auto it = mRouteMap.find(event.pointer);
        if (it != mRouteMap.end()) {
            routes = it->second;
        }
        std::set<PointerRoute *> globalRoutes = mGlobalRoutes;
        if (routes != nullptr) {
            std::set<PointerRoute *> routeList = *routes;
            for (PointerRoute *route : routeList) {
                _dispatch(event, route);
            }
        }
        for (PointerRoute *route : globalRoutes) {
            _dispatch(event, route);
        }
    }
}
