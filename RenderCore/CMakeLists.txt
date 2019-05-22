cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME RenderCore)
project(${PROJECT_NAME})

enable_language(ASM)
set(CMAKE_CXX_STANDARD 14)
set_property(DIRECTORY . PROPERTY FOLDER "RenderCore")
add_definitions(-DNDEBUG)


set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME MATCHES "iOS")
  set(IOS ON)
  message(STATUS "************iOS Platform ${CMAKE_BUILD_TYPE} Build************")
  if (CMAKE_OSX_ARCHITECTURES)
    if (CMAKE_OSX_ARCHITECTURES MATCHES ".*arm.*")
      set(IOS_ARM ON)
    elseif (CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
      set(IOS_X86 ON)
    endif()
  endif()
else()
  set(ANDROID ON)
  message(STATUS "************Android Platform ${CMAKE_BUILD_TYPE} Build************")
endif()


if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "************CMake Debug Build************")
  set(UIKIT_DEBUG_BUILD ON)
else()
  message(STATUS "************CMake Release Build************")
  set(UIKIT_DEBUG_BUILD OFF)
  add_definitions(-DSK_RELEASE)
endif()

if(IOS)
  set(CMAKE_SUPPRESS_REGENERATION true)
  set(CMAKE_CXX_FLAGS
          "${CMAKE_CXX_FLAGS} \
    -w -fstrict-aliasing \
    -fPIC -Werror -fvisibility=hidden \
    -Wno-unused-parameter -g -std=c++11 \
    -Wno-missing-field-initializers \
    -Wno-unused-variable \
    -Wno-sign-compare \
    -s"
          )
  set(CMAKE_C_FLAGS
          "${CMAKE_C_FLAGS} \
    -Wno-missing-field-initializers \
    -Wno-unused-variable \
    -Wno-sign-compare \
    -s"
          )
else()
  if(UIKIT_DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pipe -fno-exceptions -fno-rtti")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
  else()
    set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} \
    -fPIC -pipe -DNDEBUG -fvisibility=hidden \
    -g -Os -ffunction-sections -fdata-sections -Wl,--gc-sections \
    -DSK_RELEASE -DNDEBUG -fno-exceptions -fno-rtti")
    set(CMAKE_C_FLAGS
            "${CMAKE_C_FLAGS} \
     -std=c99 -DNDEBUG -fvisibility=hidden -g -Os -ffunction-sections \
     -fdata-sections -Wl,--gc-sections")
  endif()
endif()


add_subdirectory(third_party)
add_subdirectory(render)

set(SOURCE_FILES
        render/frame/SkiaFontSelector.cpp
        render/frame/RenderBodyHelper.cpp
        render/frame/Frame.cpp
        render/frame/FrameController.cpp
        render/frame/FramePipeline.cpp
        render/frame/FrameView.cpp
        render/frame/SkiaRender.cpp
        render/frame/UIContextImpl.cpp
        render/frame/SkiaShareContext.cpp
        render/frame/ImageManager.cpp
        render/frame/ImageTexture.cpp
        render/frame/JenkinsHash.cpp
        render/frame/TaskRunners.cpp
        render/frame/UIEngine.cpp
        render/frame/DomBridge.cpp
        render/frame/ImageBridge.cpp
        render/frame/PlatformBridge.cpp
        render/frame/Page.cpp
        render/frame/PageManager.cpp
        render/frame/Window.cpp
        render/frame/WindowManager.cpp
        render/frame/RequestImage.cpp
        render/frame/TextureManager.cpp
        )
set(HEADERS_FILES
        render/frame/SkiaFontSelector.h
        render/frame/RenderBodyHelper.h
        render/frame/Frame.h
        render/frame/FrameView.h
        render/frame/FramePipeline.h
        render/frame/FrameController.h
        render/frame/SkiaRender.h
        render/frame/UIContextImpl.h
        render/frame/SkiaShareContext.h
        render/frame/ImageManager.h
        render/frame/ImageTexture.h
        render/frame/JenkinsHash.h
        render/frame/TaskRunners.h
        render/frame/UIEngine.h
        render/frame/DomBridge.h
        render/frame/ImageBridge.h
        render/frame/PlatformBridge.h
        render/frame/Page.h
        render/frame/PageManager.h
        render/frame/Window.h
        render/frame/WindowManager.h
        render/frame/RequestImage.h
        render/frame/TextureManager.h
        )

if(ANDROID)
  set(SOURCE_FILES ${SOURCE_FILES}
          render/frame/android/RenderBridge.cpp
          render/frame/android/AndroidSkiaRender.cpp
          render/frame/android/RenderJava.cpp
          render/frame/android/PlatformAndroid.cpp
          render/frame/android/EglManager.cpp
          render/frame/android/string/LocalCStringUTF8.cpp
          render/frame/android/string/LocalJStringUTF8.cpp
          )
else()
  FILE(GLOB ios_headers ${PROJECT_SOURCE_DIR}/render/frame/ios/*.h)
  FILE(GLOB ios_source ${PROJECT_SOURCE_DIR}/render/frame/ios/*.cpp ${PROJECT_SOURCE_DIR}/render/frame/ios/*.mm)
  set(HEADERS_FILES ${HEADERS_FILES} ${ios_headers})
  set(SOURCE_FILES ${SOURCE_FILES} ${ios_source})
endif()

if(ANDROID)
  add_library(weexrender SHARED ${SOURCE_FILES})
  target_link_libraries(weexrender widget core wml icu android jnigraphics atomic log EGL GLESv2)
else()
  add_library(weexrender STATIC ${SOURCE_FILES} ${HEADERS_FILES})
  target_link_libraries(weexrender widget core wml skia)
endif()

## sky icu
message("source dir ${PROJECT_SOURCE_DIR}")
target_include_directories(weexrender PRIVATE
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/../RenderiOS/RenderiOS/SDWebImage/
        ${PROJECT_SOURCE_DIR}/third_party/icu/
        ${PROJECT_SOURCE_DIR}/render/widget/
        ${PROJECT_SOURCE_DIR}/../src/main/cpp/
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/android
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/c
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/codec
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/config
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/core
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/effects
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/encode
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/gpu
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/gpu/gl
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/gpu/mock
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/pathops
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/ports
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/private
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/svg
        ${PROJECT_SOURCE_DIR}/third_party/skia/include/utils
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/lazy/
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/core
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/codec
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/svg
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/shaders
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/utils
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/sfnt
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/opts
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/xml
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/gpu
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/image
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/images
        ${PROJECT_SOURCE_DIR}/third_party/skia/src/sksl
        ${PROJECT_SOURCE_DIR}/third_party/icu
        ${PROJECT_SOURCE_DIR}/third_party/txt/src/
        )