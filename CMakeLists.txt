project(tidyhtml5)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include(CheckTypeSize)
include(CheckIncludeFile)

include_directories(${tidyhtml5_SOURCE_DIR}/src)
include_directories(${tidyhtml5_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W")

set(LIBSRC  ${tidyhtml5_SOURCE_DIR}/src/access.c
            ${tidyhtml5_SOURCE_DIR}/src/attrs.c
            ${tidyhtml5_SOURCE_DIR}/src/istack.c
            ${tidyhtml5_SOURCE_DIR}/src/parser.c
            ${tidyhtml5_SOURCE_DIR}/src/tags.c
            ${tidyhtml5_SOURCE_DIR}/src/entities.c
            ${tidyhtml5_SOURCE_DIR}/src/lexer.c
            ${tidyhtml5_SOURCE_DIR}/src/pprint.c
            ${tidyhtml5_SOURCE_DIR}/src/clean.c
            ${tidyhtml5_SOURCE_DIR}/src/localize.c
            ${tidyhtml5_SOURCE_DIR}/src/config.c
            ${tidyhtml5_SOURCE_DIR}/src/alloc.c
            ${tidyhtml5_SOURCE_DIR}/src/attrask.c
            ${tidyhtml5_SOURCE_DIR}/src/attrdict.c
            ${tidyhtml5_SOURCE_DIR}/src/attrget.c
            ${tidyhtml5_SOURCE_DIR}/src/buffio.c
            ${tidyhtml5_SOURCE_DIR}/src/fileio.c
            ${tidyhtml5_SOURCE_DIR}/src/streamio.c
            ${tidyhtml5_SOURCE_DIR}/src/tagask.c
            ${tidyhtml5_SOURCE_DIR}/src/tmbstr.c
            ${tidyhtml5_SOURCE_DIR}/src/utf8.c
            ${tidyhtml5_SOURCE_DIR}/src/tidylib.c
            ${tidyhtml5_SOURCE_DIR}/src/mappedio.c
            ${tidyhtml5_SOURCE_DIR}/src/gdoc.c
)

set(LIBHDRS ${tidyhtml5_SOURCE_DIR}/include/buffio.h
            ${tidyhtml5_SOURCE_DIR}/include/platform.h
            ${tidyhtml5_SOURCE_DIR}/include/tidy.h
            ${tidyhtml5_SOURCE_DIR}/include/tidyenum.h
)

add_library(tidy-static STATIC ${LIBSRC})
set_target_properties(tidy-static PROPERTIES OUTPUT_NAME tidy)
set_target_properties(tidy-static PROPERTIES LINKER_LANGUAGE C)

add_executable(tidy ${tidyhtml5_SOURCE_DIR}/console/tidy.c)
target_link_libraries(tidy tidy-static)

add_executable(tab2space ${tidyhtml5_SOURCE_DIR}/console/tab2space.c)
target_link_libraries(tab2space tidy-static)

install(TARGETS tidy RUNTIME DESTINATION bin)
install(TARGETS tab2space RUNTIME DESTINATION bin)
install(TARGETS tidy-static ARCHIVE DESTINATION lib)
install(FILES ${LIBHDRS} DESTINATION include/tidy)
