# CMakeLists.txt - 20150130 - 20140801 - for github htacg/tidy-html5
cmake_minimum_required (VERSION 2.8)

project (tidy5)

# ### NOTE: *** Adjust version.txt when required ***
# read 'version' file into a variable (stripping any newlines or spaces)
file(READ version.txt versionFile)
if (NOT versionFile)
    message(FATAL_ERROR "Unable to determine libtidy version. version.txt file is missing.")
endif()
string(STRIP "${versionFile}" versionFile)
string(REGEX REPLACE "(.*)[\r\n|\n](.*)" "\\1" LIBTIDY_VERSION ${versionFile})
string(REGEX REPLACE "(.*)[\r\n|\n](.*)" "\\2" LIBTIDY_DATE ${versionFile})

# establish version number
string(REPLACE "." ";" VERSION_LIST ${LIBTIDY_VERSION})
list(GET VERSION_LIST 0 TIDY_MAJOR_VERSION)
list(GET VERSION_LIST 1 TIDY_MINOR_VERSION)
list(GET VERSION_LIST 2 TIDY_POINT_VERSION)

# establish version date
string(REPLACE "." ";" VERSION_LIST ${LIBTIDY_DATE})
list(GET VERSION_LIST 0 tidy_YEAR)
list(GET VERSION_LIST 1 tidy_MONTH)
list(GET VERSION_LIST 2 tidy_DAY)

# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Set ON to build Shared (DLL) Library"   OFF )
option( BUILD_TAB2SPACE  "Set ON to build utility app, tab2space" OFF )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "*** Have SIZEOF void * = 8, so 64-bit")
    set( IS_64_BIT 1 )
else ()
    message(STATUS "*** SIZEOF void * != 8, so not 64-bit")
endif ()

if(CMAKE_COMPILER_IS_GNUCXX)
    set( WARNING_FLAGS -Wall )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
   set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif() 

if(WIN32 AND MSVC)
    # turn off various warnings
    set(WARNING_FLAGS "${WARNING_FLAGS} /wd4996")
    # C4090: 'function' : different 'const' qualifiers
    # C4244: '=' : conversion from '__int64' to 'uint', possible loss of data
    # C4267: 'function' : conversion from 'size_t' to 'uint', possible loss of data
    # foreach(warning 4244 4251 4267 4275 4290 4786 4305)
    foreach(warning 4090 4244 4267)
        set(WARNING_FLAGS "${WARNING_FLAGS} /wd${warning}")
    endforeach()
    set( MSVC_FLAGS "-DNOMINMAX -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D__CRT_NONSTDC_NO_WARNINGS" )
    if (IS_64_BIT)
        set( MSVC_FLAGS "${MSVC_FLAGS} -DWIN64" )
    endif ()
    # if (${MSVC_VERSION} EQUAL 1600)
    #    set( MSVC_LD_FLAGS "/FORCE:MULTIPLE" )
    # endif (${MSVC_VERSION} EQUAL 1600)
    # set( NOMINMAX 1 )
    # to distinguish between debug and release lib in windows
    set( CMAKE_DEBUG_POSTFIX "d" ) # little effect in unix
else()
    # add any gcc flags
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LD_FLAGS}" )

add_definitions ( -DHAVE_CONFIG_H )
add_definitions ( -DSUPPORT_UTF16_ENCODINGS=1 )
add_definitions ( -DSUPPORT_ASIAN_ENCODINGS=1 )
add_definitions ( -DSUPPORT_ACCESSIBILITY_CHECKS=1 )
add_definitions ( -DRELEASE_DATE="${tidy_YEAR}/${tidy_MONTH}/${tidy_DAY}" )
add_definitions ( -DLIBTIDY_VERSION="${LIBTIDY_VERSION}" )

if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message("*** Building DLL library ${LIB_TYPE}, version ${LIBTIDY_VERSION}")
else(BUILD_SHARED_LIB)
   message("*** Building static library ${LIB_TYPE}, version ${LIBTIDY_VERSION}")
endif(BUILD_SHARED_LIB)

include_directories ( "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src" )

##############################################################################
### tidy library
# file locations
set ( SRCDIR src )
set ( INCDIR include )
# file lists
set ( CFILES
        ${SRCDIR}/access.c       ${SRCDIR}/attrs.c        ${SRCDIR}/istack.c
        ${SRCDIR}/parser.c       ${SRCDIR}/tags.c         ${SRCDIR}/entities.c
        ${SRCDIR}/lexer.c        ${SRCDIR}/pprint.c       ${SRCDIR}/charsets.c ${SRCDIR}/clean.c
        ${SRCDIR}/localize.c     ${SRCDIR}/config.c       ${SRCDIR}/alloc.c
        ${SRCDIR}/attrask.c      ${SRCDIR}/attrdict.c     ${SRCDIR}/attrget.c
        ${SRCDIR}/buffio.c       ${SRCDIR}/fileio.c       ${SRCDIR}/streamio.c
        ${SRCDIR}/tagask.c       ${SRCDIR}/tmbstr.c       ${SRCDIR}/utf8.c
        ${SRCDIR}/tidylib.c      ${SRCDIR}/mappedio.c     ${SRCDIR}/gdoc.c )
set ( HFILES
        ${INCDIR}/platform.h     ${INCDIR}/tidy.h         ${INCDIR}/tidyenum.h
        ${INCDIR}/buffio.h )
set ( LIBHFILES
        ${SRCDIR}/access.h       ${SRCDIR}/attrs.h        ${SRCDIR}/attrdict.h ${SRCDIR}/charsets.h
        ${SRCDIR}/clean.h        ${SRCDIR}/config.h       ${SRCDIR}/entities.h
        ${SRCDIR}/fileio.h       ${SRCDIR}/forward.h      ${SRCDIR}/lexer.h
        ${SRCDIR}/mappedio.h     ${SRCDIR}/message.h      ${SRCDIR}/parser.h
        ${SRCDIR}/pprint.h       ${SRCDIR}/streamio.h     ${SRCDIR}/tags.h
        ${SRCDIR}/tmbstr.h       ${SRCDIR}/utf8.h         ${SRCDIR}/tidy-int.h
        ${SRCDIR}/version.h      ${SRCDIR}/gdoc.h  )
if (MSVC)
    list(APPEND CFILES ${SRCDIR}/sprtf.c)
    list(APPEND LIBHFILES ${SRCDIR}/sprtf.h)
endif ()
set(name lib-tidy)
add_library ( ${name} ${LIB_TYPE} ${CFILES} ${HFILES} ${LIBHFILES} )
set_target_properties( ${name} PROPERTIES 
    OUTPUT_NAME tidy5
    )
set_target_properties( ${name} PROPERTIES
                               VERSION   ${LIBTIDY_VERSION}
                               SOVERSION ${TIDY_MAJOR_VERSION} )
if (BUILD_SHARED_LIB)
set_target_properties( ${name} PROPERTIES 
    COMPILE_FLAGS "-DBUILD_SHARED_LIB"
    )
set_target_properties( ${name} PROPERTIES 
    COMPILE_FLAGS "-DBUILDING_SHARED_LIB"
    )
endif ()                               
list ( APPEND add_LIBS ${name} )
install(TARGETS ${name}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
install( FILES ${HFILES} DESTINATION include )

##########################################################
### main executable
set(name tidy5)
set ( BINDIR console )
add_executable( ${name} ${BINDIR}/tidy.c )
target_link_libraries( ${name} ${add_LIBS} )
if (MSVC)
    set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
endif ()
if (BUILD_SHARED_LIB)
set_target_properties( ${name} PROPERTIES 
    COMPILE_FLAGS "-DBUILD_SHARED_LIB"
    )
endif ()                               
install (TARGETS ${name} DESTINATION bin)

if (BUILD_TAB2SPACE)
    set(name tab2space)
    add_executable( ${name} ${BINDIR}/tab2space.c )
    if (MSVC)
        set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
    endif ()
    # no INSTALL of this 'local' tool
endif ()

# eof

