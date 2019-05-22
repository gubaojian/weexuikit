# set(HARFBUZZ_HEADERS
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-blob.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-buffer.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-common.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-deprecated.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-face.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-font.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-icu.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-font.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-layout.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-math.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-tag.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-var.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-set.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-shape-plan.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-shape.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-unicode.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-version.h
#          ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb.h
# )

# FILE(GLOB headers ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/*.hh)

set(HARFBUZZ_SOURCES
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-blob.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-buffer-serialize.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-buffer.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-common.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-face.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-var.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-font.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-icu.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-font.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-layout.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-map.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-math.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-arabic.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-default.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-hangul.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-hebrew.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-indic-table.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-indic.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-myanmar.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-thai.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-tibetan.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-use-table.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-complex-use.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-fallback.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape-normalize.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-shape.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-ot-tag.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-set.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-shape-plan.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-shape.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-shaper.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-unicode.cc
         ${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src/hb-warning.cc
)

include_directories(${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src)
include_directories(${PROJECT_SOURCE_DIR}/third_party/icu/)
add_library(harfbuzz STATIC ${HARFBUZZ_SOURCES})
target_compile_definitions(harfbuzz PRIVATE NDEBUG HAVE_OT HAVE_ICU HAVE_ICU_BUILTIN HB_NO_MT)
