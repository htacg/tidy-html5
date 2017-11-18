##############################################################################
# @file CMakeLists.txt
# Build executables, static and dylibs, packages, build systems, etc., for
# HTML Tidy.
#
# Read this file or use cmake-gui (Windows) or ccmake (everything else) for
# guided build.
#
# @author  Geoff McLane [ubuntu@geoffair.info]
# @author  HTACG, et al (consult git log)
#
# @copyright
#          Copyright (c) 1998-2017 HTACG
# @copyright
#          See tidy.h for license.
#
# @date    Consult git log.
##############################################################################

cmake_minimum_required (VERSION 2.8.12)

set(LIB_NAME tidy)
set(LIBTIDY_DESCRIPTION "${LIB_NAME} - HTML syntax checker")
set(LIBTIDY_URL "http://www.html-tidy.org")

project (${LIB_NAME})


#################################################
# Setup
#################################################

#------------------------------------------------------------------------
# Release Information
#   Release version and date are found in `version.txt`; update *that*
#   file when required. It will be read into variable `versionFile`
#   (stripping any newlines or spaces). This file must be formatted into
#   two lines: the dot-separated MAJOR.MINOR.POINT version, followed by
#   the date separated YEAR.MONTH.DAY release date.
#------------------------------------------------------------------------
file(READ version.txt versionFile)

if (NOT versionFile)
    message(FATAL_ERROR "Unable to determine libtidy version. version.txt file is missing.")
endif()

string(STRIP "${versionFile}" VERSION_TEXT)
string(REGEX REPLACE "(.*)[\r\n|\n](.*)" "\\1" LIBTIDY_VERSION ${VERSION_TEXT})
string(REGEX REPLACE "(.*)[\r\n|\n](.*)" "\\2" LIBTIDY_DATE ${VERSION_TEXT})

# Establish version number
if (LIBTIDY_VERSION)
    string(REPLACE "." ";" VERSION_LIST ${LIBTIDY_VERSION})
    list(GET VERSION_LIST 0 TIDY_MAJOR_VERSION)
    list(GET VERSION_LIST 1 TIDY_MINOR_VERSION)
    list(GET VERSION_LIST 2 TIDY_POINT_VERSION)
else ()
    message(FATAL_ERROR "*** FAILED to get a VERSION from version.txt!")
endif ()   
 
# Establish version date
if (LIBTIDY_DATE)
    string(REPLACE "." ";" DATE_LIST ${LIBTIDY_DATE})
    list(GET DATE_LIST 0 tidy_YEAR)
    list(GET DATE_LIST 1 tidy_MONTH)
    list(GET DATE_LIST 2 tidy_DAY)
else ()
    message(FATAL_ERROR "*** FAILED to get a DATE from version.txt!")
endif ()


#------------------------------------------------------------------------
# Library Types and Linking
#   By default, *both* static and dynamic library types are built. The
#   shared library can be turned off if not needed. The console program
#   can be configured for static linking or dynamic linking.
#------------------------------------------------------------------------
set( LIB_TYPE STATIC )  # set default message

option( BUILD_SHARED_LIB "Set OFF to NOT build shared library"     ON  )

# Issue #326 - Allow linkage choice of console app tidy
option( TIDY_CONSOLE_SHARED "Set ON to link with shared(DLL) lib." OFF )

if (TIDY_CONSOLE_SHARED)
    if (NOT BUILD_SHARED_LIB)
        message(FATAL_ERROR "Enable shared build for this tidy linkage!")
    endif ()
endif ()


#------------------------------------------------------------------------
# Miscellaneous Options
#------------------------------------------------------------------------
option( BUILD_TAB2SPACE     "Set ON to build utility app, tab2space"  OFF )
option( BUILD_SAMPLE_CODE   "Set ON to build the sample code"         OFF )
option( TIDY_COMPAT_HEADERS "Set ON to include compatibility headers" OFF )


#------------------------------------------------------------------------
# Man Page
#   Allow building with non-default man page directory.
#------------------------------------------------------------------------
if (NOT MAN_INSTALL_DIR)
    set(MAN_INSTALL_DIR share/man/man1)
endif ()


#------------------------------------------------------------------------
# Localization
#   Allow building without extra language support.
#------------------------------------------------------------------------
option( SUPPORT_LOCALIZATIONS "Set OFF to build without additional languages." ON )

if (SUPPORT_LOCALIZATIONS)
    add_definitions ( -DSUPPORT_LOCALIZATIONS=1 )
else ()
    add_definitions ( -DSUPPORT_LOCALIZATIONS=0 )
endif ()


#------------------------------------------------------------------------
# Console Application
#   Allow building without console support, which mostly prevents
#   console strings from existing in the library. Note that this will
#   prevent the console application from being built, since it can't be
#   linked.
#------------------------------------------------------------------------
option( SUPPORT_CONSOLE_APP "Set OFF to build libraries only without console application support." ON )

if (SUPPORT_CONSOLE_APP)
    add_definitions ( -DSUPPORT_CONSOLE_APP=1 )
else ()
    add_definitions ( -DSUPPORT_CONSOLE_APP=0 )
endif ()


#------------------------------------------------------------------------
# Diagnostics
#   Enable building with logs, some memory diagnostics.
#------------------------------------------------------------------------
option( ENABLE_DEBUG_LOG    "Set ON to output debugging messages."          OFF )
option( ENABLE_ALLOC_DEBUG  "Set ON to output node allocation diagnostics." OFF )
option( ENABLE_MEMORY_DEBUG "Set ON to output some memory diagnostics."     OFF )

if ( ENABLE_DEBUG_LOG )
    add_definitions( -DENABLE_DEBUG_LOG )
    message(STATUS "*** Debug Logging is enabled.")  
else ()
    message(STATUS "*** Debug Logging is NOT enabled.")  
endif ()

if (ENABLE_ALLOC_DEBUG)
    add_definitions ( -DDEBUG_ALLOCATION )  # see lexer.c for details
    message(STATUS "*** Note, lexer.c node allocation diagnostics are ON")
endif ()
    
if (ENABLE_MEMORY_DEBUG)
    add_definitions ( -DDEBUG_MEMORY )  # see alloc.c for details
    message(STATUS "*** Note, alloc.c memory diagnostics are ON")
endif ()
    
if (WIN32)
    option( ENABLE_CRTDBG_MEMORY "Set ON to enable the Windows CRT debug library." OFF )
    
    if (ENABLE_CRTDBG_MEMORY)
        add_definitions ( -D_CRTDBG_MAP_ALLOC )  # see tidy.c for details
        message(STATUS "*** Note, tidy.c Windows CRT memory debug is ON")
    endif ()
endif ()


#------------------------------------------------------------------------
# Complier Flags
#   Setup other compiler-specific and platform-specific compiler flags.
#------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
    set( WARNING_FLAGS -Wall )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
   set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif() 

if(WIN32 AND MSVC)
    # C4996: The compiler encountered a deprecated declaration.
    # C4090: 'function' : different 'const' qualifiers
    # C4244: '=' : conversion from '__int64' to 'uint', possible loss of data
    # C4267: 'function' : conversion from 'size_t' to 'uint', possible loss of data
    foreach(warning 4996 4090 4244 4267)
        set(WARNING_FLAGS "${WARNING_FLAGS} /wd${warning}")
    endforeach()
    
    set( MSVC_FLAGS "-DNOMINMAX -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D__CRT_NONSTDC_NO_WARNINGS" )

    # to distinguish between debug and release lib in windows
    set( CMAKE_DEBUG_POSTFIX "d" ) # little effect in unix
else()
    # add any gcc flags
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LD_FLAGS}" )


#------------------------------------------------------------------------
# Static Windows Runtime
#   Option to statically link to the Windows runtime. Maybe only 
#   applies to WIN32/MSVC.
#------------------------------------------------------------------------
if (MSVC)
    option( USE_STATIC_RUNTIME "Set ON to change /MD(DLL) to /MT(static)" OFF )
    if (USE_STATIC_RUNTIME)
        set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            )
        foreach(CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        endforeach()    
        message(STATUS "Using /MT STATIC runtime")
    else ()
        message(STATUS "Using /MD DYNAMIC runtime")
    endif ()
endif ()


#------------------------------------------------------------------------
# Macro Values
#   These additional macros are set in Tidy's source code. It is *very*
#   seldom that you would ever have to change any of these in order to
#   achieve a functioning build.
#------------------------------------------------------------------------
add_definitions ( -DLIBTIDY_VERSION="${LIBTIDY_VERSION}" )
add_definitions ( -DRELEASE_DATE="${tidy_YEAR}/${tidy_MONTH}/${tidy_DAY}" )

# Optionally specify an extra version point for pre-release/debug versions.
if (TIDY_RC_NUMBER)
    add_definitions ( -DRC_NUMBER="${TIDY_RC_NUMBER}" )
endif ()

# If your OS doesn't have native ISO2022 support, then build with this flag.
if (NO_NATIVE_ISO2022_SUPPORT)
    add_definitions ( -DNO_NATIVE_ISO2022_SUPPORT=1 )
endif ()

# If your OS doesn't have library function access(), build with this flag.
if (NO_ACCESS_SUPPORT)
    add_definitions ( -DNO_ACCESS_SUPPORT=1 )
endif ()

# Delete me? Not used in Tidy source!
add_definitions ( -DHAVE_CONFIG_H ) 


#------------------------------------------------------------------------
# Runtime Configuration File Support
#   By default on Unix-like systems when building for the console program,
#   support runtime configuration files in /etc/ and in ~/. To prevent this,
#   set ENABLE_CONFIG_FILES to NO. Specify -DTIDY_CONFIG_FILE and/or 
#   -DTIDY_USER_CONFIG_FILE to override the default paths in tidyplatform.h.
# @note: this section refactored to support #584.
#------------------------------------------------------------------------
if ( UNIX AND SUPPORT_CONSOLE_APP )

  option ( ENABLE_CONFIG_FILES "Set to OFF to disable Tidy runtime configuration file support" ON )

    # All Unixes support getpwnam(); undef'd in tidyplatform.h if necessary.
    add_definitions( -DSUPPORT_GETPWNAM=1 )

else ()

  option ( ENABLE_CONFIG_FILES "Set to ON to enable Tidy runtime configuration file support" OFF )
  
  if ( SUPPORT_GETPWNAM )
    add_definitions( -DSUPPORT_GETPWNAM=1 )
  endif ()
  
endif ()

if ( ENABLE_CONFIG_FILES )

    message(STATUS "*** Building support for runtime configuration files.")

    add_definitions( -DTIDY_ENABLE_CONFIG_FILES )
    
    # define a default here so we can pass to XSL.
    if ( NOT TIDY_CONFIG_FILE )
        set( TIDY_CONFIG_FILE "/etc/tidy.conf" )
    endif ()

    # define a default here so we can pass to XSL.
    if ( NOT TIDY_USER_CONFIG_FILE )
        set( TIDY_USER_CONFIG_FILE "~/.tidyrc" )
    endif ()

    # do *not* add these unless ENABLE_CONFIG_FILES!
    add_definitions( -DTIDY_CONFIG_FILE="${TIDY_CONFIG_FILE}" )
    add_definitions( -DTIDY_USER_CONFIG_FILE="${TIDY_USER_CONFIG_FILE}" )

endif ()
  

#------------------------------------------------------------------------
# Shared Library
#   Setup whether or not we will build the shared library.
#------------------------------------------------------------------------
if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message(STATUS "*** Also building DLL library ${LIB_TYPE}, version ${LIBTIDY_VERSION}, date ${LIBTIDY_DATE}")
else()
   message(STATUS "*** Only building static library ${LIB_TYPE}, version ${LIBTIDY_VERSION}, date ${LIBTIDY_DATE}")
endif()


#################################################
# Build
#################################################

#------------------------------------------------------------------------
# File Locations and File Lists
#   Setup whether or not we will build the shared library.
#------------------------------------------------------------------------
include_directories ( "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src" )

set ( SRCDIR src )
set ( INCDIR include )

set ( CFILES
        ${SRCDIR}/access.c       ${SRCDIR}/attrs.c        ${SRCDIR}/istack.c
        ${SRCDIR}/parser.c       ${SRCDIR}/tags.c         ${SRCDIR}/entities.c
        ${SRCDIR}/lexer.c        ${SRCDIR}/pprint.c       ${SRCDIR}/charsets.c
        ${SRCDIR}/clean.c        ${SRCDIR}/message.c      ${SRCDIR}/config.c
        ${SRCDIR}/alloc.c        ${SRCDIR}/attrdict.c     ${SRCDIR}/buffio.c
        ${SRCDIR}/fileio.c       ${SRCDIR}/streamio.c     ${SRCDIR}/tagask.c
        ${SRCDIR}/tmbstr.c       ${SRCDIR}/utf8.c         ${SRCDIR}/tidylib.c
        ${SRCDIR}/mappedio.c     ${SRCDIR}/gdoc.c         ${SRCDIR}/language.c
        ${SRCDIR}/messageobj.c   ${SRCDIR}/sprtf.c )
        
set ( HFILES
        ${INCDIR}/tidyplatform.h ${INCDIR}/tidy.h         ${INCDIR}/tidyenum.h
        ${INCDIR}/tidybuffio.h )

if (TIDY_COMPAT_HEADERS)
    set ( HFILES ${HFILES}      ${INCDIR}/buffio.h        ${INCDIR}/platform.h )
endif ()

set ( LIBHFILES
        ${SRCDIR}/access.h       ${SRCDIR}/attrs.h        ${SRCDIR}/attrdict.h ${SRCDIR}/charsets.h
        ${SRCDIR}/clean.h        ${SRCDIR}/config.h       ${SRCDIR}/entities.h
        ${SRCDIR}/fileio.h       ${SRCDIR}/forward.h      ${SRCDIR}/lexer.h
        ${SRCDIR}/mappedio.h     ${SRCDIR}/message.h      ${SRCDIR}/parser.h
        ${SRCDIR}/pprint.h       ${SRCDIR}/streamio.h     ${SRCDIR}/tags.h
        ${SRCDIR}/tmbstr.h       ${SRCDIR}/utf8.h         ${SRCDIR}/tidy-int.h
        ${SRCDIR}/version.h      ${SRCDIR}/gdoc.h         ${SRCDIR}/language.h
        ${SRCDIR}/language_en.h  ${SRCDIR}/sprtf.h )
  

#------------------------------------------------------------------------
# Target Locations
#------------------------------------------------------------------------
if (NOT LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR lib${LIB_SUFFIX})
endif ()

if (NOT BIN_INSTALL_DIR)
    set(BIN_INSTALL_DIR bin)
endif ()

if (NOT INCLUDE_INSTALL_DIR)
    set(INCLUDE_INSTALL_DIR include)
endif ()


#------------------------------------------------------------------------
# Static Library
#   The static library always builds.
#------------------------------------------------------------------------
set(name tidy-static)
add_library ( ${name} STATIC ${CFILES} ${HFILES} ${LIBHFILES} )
set_target_properties( ${name} PROPERTIES 
                       OUTPUT_NAME ${LIB_NAME}s )
if (NOT TIDY_CONSOLE_SHARED) # user wants default static linkage
    list ( APPEND add_LIBS ${name} )
endif ()    
install(TARGETS ${name}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        )
install( FILES ${HFILES} DESTINATION ${INCLUDE_INSTALL_DIR} )


#------------------------------------------------------------------------
# Dynamic Library
#   If the user option is still on.
#------------------------------------------------------------------------
if (BUILD_SHARED_LIB)
    set(name tidy-share)
    if (UNIX AND APPLE)
        set(CMAKE_MACOSX_RPATH 1)
    endif ()
    add_library ( ${name} SHARED ${CFILES} ${HFILES} ${LIBHFILES} )
    set_target_properties( ${name} PROPERTIES 
                                   OUTPUT_NAME ${LIB_NAME} )
    set_target_properties( ${name} PROPERTIES
                                   VERSION   ${LIBTIDY_VERSION}
                                   SOVERSION ${TIDY_MAJOR_VERSION} )
    set_target_properties( ${name} PROPERTIES 
                                   COMPILE_FLAGS "-DBUILD_SHARED_LIB" )
    set_target_properties( ${name} PROPERTIES 
                                   COMPILE_FLAGS "-DBUILDING_SHARED_LIB" )
    install(TARGETS ${name}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        )
    if (TIDY_CONSOLE_SHARED) # user wants shared/dll linkage
        list ( APPEND add_LIBS ${name} )
    endif ()    
endif ()


#------------------------------------------------------------------------
# Main Executable
#   The main executable will be linked with either the static or the
#   shared library.
#------------------------------------------------------------------------
if (SUPPORT_CONSOLE_APP)
    set(name ${LIB_NAME})
    set ( BINDIR console )
    add_executable( ${name} ${BINDIR}/tidy.c )
    target_link_libraries( ${name} ${add_LIBS} )
    if (MSVC)
        set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
    endif ()
    if (NOT TIDY_CONSOLE_SHARED)
        set_target_properties( ${name} PROPERTIES 
                                       COMPILE_FLAGS "-DTIDY_STATIC" )
    endif ()
    install (TARGETS ${name} DESTINATION bin)
endif ()


#------------------------------------------------------------------------
# Miscellaneous Targets
#------------------------------------------------------------------------
if (BUILD_TAB2SPACE)
    set(name tab2space)
    add_executable( ${name} ${BINDIR}/tab2space.c )
    if (MSVC)
        set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
    endif ()
    # no INSTALL of this 'local' tool - use depreciated
endif ()

if (BUILD_SAMPLE_CODE)
    set(name test71)
    set(dir console)
    add_executable( ${name} ${dir}/${name}.cxx )
    if (MSVC)
        set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
    endif ()
    target_link_libraries( ${name} ${add_LIBS} )
    # no INSTALL of this 'local' sample
endif ()


#################################################
# Create man pages
#################################################

if (UNIX AND SUPPORT_CONSOLE_APP)
    find_program( XSLTPROC_FOUND xsltproc )
    if (XSLTPROC_FOUND)
        ## NOTE: man name must match exe ie currently `${LIB_NAME}.1` not `tidy.1`
        ## also could use `manpath` command output to determine target install path
        set(TIDY_MANFILE ${LIB_NAME}.1)
        message(STATUS "*** Generating man ${TIDY_MANFILE} custom commands...")
        set(TIDY1XSL ${CMAKE_CURRENT_BINARY_DIR}/tidy1.xsl)
        set(TIDYHELP ${CMAKE_CURRENT_BINARY_DIR}/tidy-help.xml)
        set(TIDYCONFIG ${CMAKE_CURRENT_BINARY_DIR}/tidy-config.xml)
        add_custom_target(man ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}")
        
        ## Populate the @VARIABLES@ in the input file.
        configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/man/tidy1.xsl.in
            ${TIDY1XSL}
        )
 
        # Run the built EXE to generate xml output .
        add_custom_command(
            TARGET man
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME} -xml-help > ${TIDYHELP}
            COMMENT "Generate ${TIDYHELP}"
            VERBATIM
        )

        # Run the built EXE to generate more xml output.
        add_custom_command(
            TARGET man
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME} -xml-config > ${TIDYCONFIG}
            COMMENT "Generate ${TIDYCONFIG}"
            VERBATIM
        )

        # Run xsltproc to generate the install files.
        add_custom_command(
            TARGET man
            DEPENDS ${TIDYHELP}
            COMMAND xsltproc ARGS ${TIDY1XSL} ${TIDYHELP} > ${CMAKE_CURRENT_BINARY_DIR}/${TIDY_MANFILE}
            COMMENT "Generate ${TIDY_MANFILE}"
            VERBATIM
        )

        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${TIDY_MANFILE} DESTINATION ${MAN_INSTALL_DIR})

    else ()
        message(STATUS "*** NOTE: xsltproc NOT FOUND! Can NOT generate man page.")
        message(STATUS "*** You need to install xsltproc in your system.")
    endif ()
endif ()


#################################################
# Create MSI,EXE, DMG, DEB/RPM
#   TODO: Check each of these builds
#################################################

set(BITNESS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(BITNESS 64)
endif()


#------------------------------------------------------------------------
# System Runtime Libraries
#   Need to ensure that system DLLs get included in a binary 
#   distribution, but since it can miss some - seems incomplete - make
#   optional.
#------------------------------------------------------------------------
option( ADD_SYSTEM_RUNTIMES "Set ON to include system runtime DLLS in distribution" OFF )
if (MSVC AND ADD_SYSTEM_RUNTIMES)
    if (NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
      # Visual Studio Express does include redistributable components so
      # squelch the warning.
      set (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
    endif ()
    set (CMAKE_INSTALL_DEBUG_LIBRARIES OFF)
    include (InstallRequiredSystemLibraries)
endif ()


#------------------------------------------------------------------------
# Windows
#   MSI - this needs WiX Tooset installed and a path to candle.exe
#   EXE - this needs NSIS tools to be in path
#------------------------------------------------------------------------
if (WIN32)
    set(CPACK_GENERATOR "NSIS;WIX;ZIP")
    set(CPACK_SOURCE_GENERATOR "ZIP")
    set(CPACK_WIX_UPGRADE_GUID "D809598A-B513-4752-B268-0BAC403B00E4")
elseif ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set(CPACK_GENERATOR "productbuild")
    set(CPACK_SOURCE_GENERATOR "TGZ")
else ()
    set(CPACK_GENERATOR "DEB;RPM")
    set(CPACK_SOURCE_GENERATOR "TGZ")
endif ()


#------------------------------------------------------------------------
# General
#------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME "${LIB_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${LIBTIDY_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "HTML Tidy Advocacy Community Group")
set(CPACK_PACKAGE_CONTACT "maintainer@htacg.org")

set(CPACK_PACKAGE_VERSION ${LIBTIDY_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "${TIDY_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${TIDY_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${TIDY_POINT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README/README.html")

# use one compatible license file for all
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/README/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README/README.html")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/README/README.html")


#------------------------------------------------------------------------
# Debian
#------------------------------------------------------------------------
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${LIBTIDY_URL})
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc")
set(CPACK_DEBIAN_PACKAGE_SECTION "Libraries")
set(CPACK_SOURCE_IGNORE_FILES
  "${PROJECT_SOURCE_DIR}/build"
  )


#------------------------------------------------------------------------
# RPM config
#------------------------------------------------------------------------
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/share/man" "/usr/share/man/man1")

set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/;${CMAKE_CURRENT_SOURCE_DIR}/build/;${CMAKE_CURRENT_SOURCE_DIR}/.git/")

if (NOT WIN32 AND NOT APPLE)
set( CPACK_PACKAGE_FILE_NAME "${LIB_NAME}-${CPACK_PACKAGE_VERSION}-${BITNESS}bit" )
endif ()

include(CPack)

#------------------------------------------------------------------------
# pkg-config
#------------------------------------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}.pc.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}.pc"
    @ONLY
    )
    
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}.pc"
    DESTINATION "${LIB_INSTALL_DIR}/pkgconfig"
    )

# eof
