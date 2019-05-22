set(WXIGET_HEADERS
    ${PROJECT_SOURCE_DIR}/render/widget/ViewFactory.h
    ${PROJECT_SOURCE_DIR}/render/widget/View.h
    ${PROJECT_SOURCE_DIR}/render/widget/TextView.h
    ${PROJECT_SOURCE_DIR}/render/widget/LinkView.h
    ${PROJECT_SOURCE_DIR}/render/widget/ParaView.h
    ${PROJECT_SOURCE_DIR}/render/widget/ImageView.h
    ${PROJECT_SOURCE_DIR}/render/widget/SpanView.h
    ${PROJECT_SOURCE_DIR}/render/widget/ScrollerView.h
    ${PROJECT_SOURCE_DIR}/render/widget/AnimationView.h
    ${PROJECT_SOURCE_DIR}/render/widget/PlatformView.h
    ${PROJECT_SOURCE_DIR}/render/widget/TextureView.h
    ${PROJECT_SOURCE_DIR}/render/widget/SliderView.h
    ${PROJECT_SOURCE_DIR}/render/widget/UIContext.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/Transition.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/PropertyValue.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/LengthPropertyValue.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/TransformPropertyValue.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/FloatPropertyValue.h
    ${PROJECT_SOURCE_DIR}/render/widget/transition/ColorPropertyValue.h
)

set(WIDGET_SOURCES
        ${PROJECT_SOURCE_DIR}/render/widget/ViewFactory.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/View.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/TextView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/LinkView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/ParaView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/ImageView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/SpanView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/ScrollerView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/AnimationView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/PlatformView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/TextureView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/SliderView.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/UIContext.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/Transition.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/PropertyValue.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/LengthPropertyValue.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/TransformPropertyValue.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/FloatPropertyValue.cpp
        ${PROJECT_SOURCE_DIR}/render/widget/transition/ColorPropertyValue.cpp
 )

add_library(widget STATIC ${WXIGET_HEADERS} ${WIDGET_SOURCES})
target_link_libraries(widget core gesture)
target_include_directories(widget PRIVATE
    ${PROJECT_SOURCE_DIR}/render/)
