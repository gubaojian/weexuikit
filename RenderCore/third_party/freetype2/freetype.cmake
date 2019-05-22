set(FREETYPE_SOURCES
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/autofit/autofit.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftbase.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftbbox.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftbitmap.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftfntfmt.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftfstype.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftgasp.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftglyph.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftinit.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftlcdfil.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftmm.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftstroke.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/ftsystem.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/base/fttype1.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/bdf/bdf.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/cff/cff.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/cid/type1cid.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/gzip/ftgzip.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/lzw/ftlzw.c
        ##${PROJECT_SOURCE_DIR}/third_party/freetype2/src/pcf/pcf.c
        ##${PROJECT_SOURCE_DIR}/third_party/freetype2/src/pfr/pfr.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/psaux/psaux.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/pshinter/pshinter.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/psnames/psnames.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/raster/raster.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/sfnt/sfnt.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/smooth/smooth.c
        ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/truetype/truetype.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/type1/type1.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/type42/type42.c
        ## ${PROJECT_SOURCE_DIR}/third_party/freetype2/src/winfonts/winfnt.c
        )


include_directories(${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/third_party/freetype2/include/)


#FIXME -DFT_CONFIG_OPTIONS_H=${PROJECT_SOURCE_DIR}/third_party/skia/third_party/freetype2/include/freetype-android/ftoption.h"

set_source_files_properties(${FREETYPE_SOURCES} PROPERTIES COMPILE_FLAGS "-DNDEBUG -DFT2_BUILD_LIBRARY")

add_library(freetype STATIC ${FREETYPE_SOURCES})
