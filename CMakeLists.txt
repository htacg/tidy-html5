# CMakeLists.txt - 20140801 - for github tidy

cmake_minimum_required (VERSION 2.8)

project (tidy5)

# ### NOTE: *** Adjust when required ***
set( TIDY_MAJOR_VERSION 1 )
set( TIDY_MINOR_VERSION 0 )
set( TIDY_MICRO_VERSION 0 )
set( LIBTIDY_VERSION "${TIDY_MAJOR_VERSION}.${TIDY_MINOR_VERSION}.${TIDY_MICRO_VERSION}" )
# establish version date
set( tidy_YEAR  2014 )
set( tidy_MONTH 08 )
set( tidy_DAY   06 )

# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Build Shared Library" OFF )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "*** Have SIZEOF void * = 8, so 64-bit")
    set( IS_64_BIT 1 )
else ()
    message(STATUS "*** SIZEOF void * != 8, so not 64-bit")
endif ()

# to distinguish between debug and release lib in windows
if (WIN32)
    set( CMAKE_DEBUG_POSTFIX "d" ) # little effect in unix
endif (WIN32)

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
    set( NOMINMAX 1 )
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
# to distinguish between debug and release lib
if (WIN32)
   set( CMAKE_DEBUG_POSTFIX "d" )
endif(WIN32)

if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message("*** Building DLL library ${LIB_TYPE}")
else(BUILD_SHARED_LIB)
   message("*** Building static library ${LIB_TYPE}")
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
if (BUILD_SHARED_LIB)
    set(name tidy-shared)
else ()
    set(name tidy-static)
endif ()
add_library ( ${name} ${LIB_TYPE} ${CFILES} ${HFILES} ${LIBHFILES} )
list ( APPEND add_LIBS ${name} )
if (NOT MSVC)
    set_target_properties( ${name} PROPERTIES
                                   VERSION   ${LIBTIDY_VERSION}
                                   SOVERSION ${TIDY_MAJOR_VERSION} )
endif ()
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
install (TARGETS ${name} DESTINATION bin)

set(name tab2space)
add_executable( ${name} ${BINDIR}/tab2space.c )
if (MSVC)
    set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
endif ()
# no INSTALL of this 'lcoal' tool

# eof
