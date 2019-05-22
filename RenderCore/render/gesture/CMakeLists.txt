set(WEEX_UIKIT_GESTURE_SOURCES
        geometry/VelocityTracker.cpp
        geometry/Geometry.cpp
        geometry/LeastSquaresSolver.cpp
        gesture/DragGestureRecognizer.cpp
        gesture/HorizontalDragGestureRecognizer.cpp
        gesture/PanGestureRecognizer.cpp
        gesture/VerticalDragGestureRecognizer.cpp
        gesture/ScaleGestureRecognizer.cpp
        gesture/EagerGestureRecognizer.cpp
        gesture/CombiningGestureArenaEntry.cpp
        gesture/CombiningGestureArenaMember.cpp
        gesture/GestureArenaTeam.cpp
        gesture/GestureArenaMember.cpp
        gesture/GestureRecognizer.cpp
        gesture/PointerEvent.cpp
        gesture/PointerEventListener.cpp
        gesture/OneSequenceGestureRecognizer.cpp
        gesture/PrimaryPointerGestureRecognizer.cpp
        gesture/TapGestureRecognizer.cpp
        gesture/GestureArena.cpp
        gesture/GestureArenaEntry.cpp
        gesture/GestureArenaManager.cpp
        gesture/GestureArenaManager.cpp
        gesture/PointerRouter.cpp
        gesture/GestureHandlerContext.cpp
        gesture/TapGestureRecognizer.cpp
        gesture/LongPressGestureRecognizer.cpp
        gesture/Timer.cpp

        animation/AnimationController.cpp
        animation/Curve.cpp
        foundation/ChangeNotifie.cpp
        foundation/BasicTypes.cpp
        foundation/TickerProvider.cpp
        physics/FrictionSimulation.cpp
        physics/Tolerance.cpp
        physics/Simulation.cpp
        physics/ClampedSimulation.cpp
        physics/SpringSimulation.cpp
        widget/ScrollActivity.cpp
        widget/ScrollMetrics.cpp
        animation/Curve.cpp
        widget/ScrollContext.cpp
        widget/Drag.cpp
        widget/ViewportOffset.cpp
        widget/ScrollPhysics.cpp
        widget/ScrollPosition.cpp
        widget/ScrollPositionWithSingleContext.cpp
        widget/Scrollable.cpp
        widget/BouncingScrollSimulation.cpp
        widget/ScrollableState.cpp)

add_library(gesture STATIC ${WEEX_UIKIT_GESTURE_SOURCES})

target_include_directories(gesture PUBLIC
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/render/gesture/)
