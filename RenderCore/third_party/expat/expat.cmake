set(EXPAT_HEADERS
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/expat_config.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/ascii.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/asciitab.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/expat.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/expat_external.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/iasciitab.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/internal.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/latin1tab.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/nametab.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/utf8tab.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmlrole.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmltok.h
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmltok_impl.h
)

set(EXPAT_SOURCES
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmlparse.c
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmlrole.c
        ${PROJECT_SOURCE_DIR}/third_party/expat/files/lib/xmltok.c
)

include_directories(${PROJECT_SOURCE_DIR}/third_party/expat/files/lib)


set_source_files_properties(${EXPAT_SOURCES} PROPERTIES COMPILE_FLAGS "-DHAVE_EXPAT_CONFIG_H -DHAVE_SYS_UIO_H -DXML_STATIC ")


add_library(expat STATIC ${EXPAT_HEADERS} ${EXPAT_SOURCES})
