set(WML_HEADERS
        ${PROJECT_SOURCE_DIR}/render/wml/build_config.h
        ${PROJECT_SOURCE_DIR}/render/wml/compiler_specific.h
        ${PROJECT_SOURCE_DIR}/render/wml/arraysize.h
        ${PROJECT_SOURCE_DIR}/render/wml/closure.h
        ${PROJECT_SOURCE_DIR}/render/wml/eintr_wrapper.h
        ${PROJECT_SOURCE_DIR}/render/wml/export.h
        ${PROJECT_SOURCE_DIR}/render/wml/file.h
        ${PROJECT_SOURCE_DIR}/render/wml/log_level.h
        ${PROJECT_SOURCE_DIR}/render/wml/log_settings.h
        ${PROJECT_SOURCE_DIR}/render/wml/logging.h
        ${PROJECT_SOURCE_DIR}/render/wml/macros.h
        ${PROJECT_SOURCE_DIR}/render/wml/make_copyable.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/ref_ptr.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/ref_ptr_internal.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/thread_checker.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/weak_ptr.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/ref_counted_internal.h
        ${PROJECT_SOURCE_DIR}/render/wml/memory/ref_counted.h
        ${PROJECT_SOURCE_DIR}/render/wml/message_loop_impl.h
        )

set(WML_SOURCES
        ${PROJECT_SOURCE_DIR}/render/wml/log_settings.cc
        ${PROJECT_SOURCE_DIR}/render/wml/log_settings_state.cc
        ${PROJECT_SOURCE_DIR}/render/wml/logging.cc
        ${PROJECT_SOURCE_DIR}/render/wml/memory/weak_ptr_internal.cc
        ${PROJECT_SOURCE_DIR}/render/wml/message_loop.cc
        ${PROJECT_SOURCE_DIR}/render/wml/message_loop_impl.cc
        ${PROJECT_SOURCE_DIR}/render/wml/synchronization/waitable_event.cc
        ${PROJECT_SOURCE_DIR}/render/wml/task_runner.cc
        ${PROJECT_SOURCE_DIR}/render/wml/thread.cc
        ${PROJECT_SOURCE_DIR}/render/wml/time/time_delta.h
        ${PROJECT_SOURCE_DIR}/render/wml/time/time_point.cc
        ${PROJECT_SOURCE_DIR}/render/wml/trace_event.cc
        ${PROJECT_SOURCE_DIR}/render/wml/unique_fd.cc
        ${PROJECT_SOURCE_DIR}/render/wml/platform/android/message_loop_android.cc
        ${PROJECT_SOURCE_DIR}/render/wml/platform/linux/timerfd.cc
)

include_directories(${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/render/)

set_source_files_properties(${WML_HEADERS}  ${WML_SOURCES} PROPERTIES COMPILE_FLAGS "-DNDEBUG")

add_library(wml STATIC ${WML_HEADERS} ${WML_SOURCES})