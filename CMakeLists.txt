# CMakeLists.txt - 20150130 - 20140801 - for github htacg/tidy-html5
cmake_minimum_required (VERSION 2.8)

project (tidy5)

# ### NOTE: *** Adjust version.txt when required ***
# read 'version' file into a variable (stripping any newlines or spaces)
file(READ version.txt versionFile)
if (NOT versionFile)
    message(FATAL_ERROR "Unable to determine libtidy version. version.txt file is missing.")
endif()
string(STRIP "${versionFile}" LIBTIDY_VERSION)
string(REPLACE "." ";" VERSION_LIST ${LIBTIDY_VERSION})
list(GET VERSION_LIST 0 TIDY_MAJOR_VERSION)
list(GET VERSION_LIST 1 TIDY_MINOR_VERSION)
list(GET VERSION_LIST 2 TIDY_POINT_VERSION)

# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Set ON to build Shared (DLL) Library"       OFF )
option( BUILD_TAB2SPACE  "Set ON to build utility app, tab2space"     OFF )
option( BUILD_SAMPLE_CODE "Set ON to build the sample code"           OFF )
option( BUILD_DOCUMENTATION "Set ON to build the documentation"       OFF )

if (BUILD_DOCUMENTATION)
    message(STATUS "*** BUILD_DOCUMENTATION ON - Nothing else will be built.")
else()
    message(STATUS "*** BUILD_DOCUMENTATION OFF")
    set( BUILD_TIDY ON )
endif()

if (BUILD_TIDY)
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

    #==========================================================
    # Create man pages
    #==========================================================
    if (UNIX)
        find_program( XSLTPROC_FOUND xsltproc )
        if (XSLTPROC_FOUND)
            ## NOTE: man name must match exe ie currently `tidy5.1` not `tidy.1`
            ## also could use `manpath` command output to determine target install path
            message("*** Generating man ***")
            set(TIDY_MANFILE tidy5.1)
            set(TIDY1XSL ../../documentation/tidy1.xsl)
            set(TIDYHELP ${CMAKE_BINARY_DIR}/tidy-help.xml)
            set(TIDYCONFIG ../../documentation/tidy-config.xml)
            add_custom_target(man ALL DEPENDS "${CMAKE_BINARY_DIR}/tidy5")
 
            # run built EXE to generate xml output 
            add_custom_command(
                TARGET man
                COMMAND ${CMAKE_BINARY_DIR}/tidy5 -xml-help > ${TIDYHELP}
                COMMENT "Generate ${TIDYHELP}"
                VERBATIM
            )

            # run built EXE to generate more xml output 
            add_custom_command(
                TARGET man
                COMMAND ${CMAKE_BINARY_DIR}/tidy5 -xml-config > ${TIDYCONFIG}
                COMMENT "Generate ${TIDYHELP}"
                VERBATIM
            )

            # run xsltproc to generate the install files..
            add_custom_command(
                TARGET man
                DEPENDS ${TIDYHELP}
                COMMAND xsltproc ARGS ${TIDY1XSL} ${TIDYHELP} > ${CMAKE_BINARY_DIR}/${TIDY_MANFILE}
                COMMENT "Generate ${TIDY_MANFILE}"
                VERBATIM
            )

            install(FILES ${CMAKE_BINARY_DIR}/${TIDY_MANFILE} DESTINATION local/man/man1)
        else()
            message(WARNING, "Manual page won't be installed because xsltproc could not be found and is required.")
        endif ()
    endif ()

endif() # BUILD_TIDY


##########################################################
### Build the documentation project
##########################################################
if (BUILD_DOCUMENTATION)

    find_program( XSLTPROC_FOUND xsltproc )
    find_program( DOXYGEN_FOUND doxygen )
    if (XSLTPROC_FOUND AND DOXYGEN_FOUND)
    
        message("*** Building the Doxygen Project ***")

        set( TIDY_EXE tidy5 )
        find_program( TIDY_FOUND ${TIDY_EXE} "./" )
        
        if( TIDY_FOUND )
            message(STATUS "Using ${TIDY_EXE} at ${TIDY_FOUND}")
        else()
            find_program( TIDY_FOUND ${TIDY_EXE} )    
            if( TIDY_FOUND )
                message(STATUS "Using ${TIDY_EXE} at ${TIDY_FOUND}")
            else()
                MESSAGE(FATAL_ERROR "${TIDY_EXE} could not be found. Aborting.")
            endif()
        endif()
                       
        set( WRK_DIR ../../documentation )
        # relative to WRK_DIR!
        set( EXP_DIR ./examples )
        set( OUT_DIR ./temp )
        set( DXY_DIR ./temp/tidylib_api )

        # Build that parameters that will be passed to doxygen via stdin.
        file( READ documentation/doxygen.cfg PARAMS )
        set( PARAMS "${PARAMS}PROJECT_NUMBER=${LIBTIDY_VERSION}\n" )
        set( PARAMS "${PARAMS}GENERATE_TAGFILE=${DXY_DIR}/tidy.tags\n" )
        set( PARAMS "${PARAMS}HTML_EXTRA_FILES= ./examples/tidy5.help.txt ./examples/tidy5.config.txt\n" )    
        file( WRITE documentation/doxygen_temp.cfg ${PARAMS} ) # delete later

        # Ensure OUT_DIR exists
        file( MAKE_DIRECTORY documentation/${OUT_DIR} )

        add_custom_target( documentation ALL )
        
        #=========================================
        # Generate files.
        #=========================================

        add_custom_command(
            TARGET documentation
            COMMENT "Build Documentation"
            VERBATIM
            WORKING_DIRECTORY ${WRK_DIR}

            COMMAND ${TIDY_FOUND} -xml-config > ${OUT_DIR}/tidy-config.xml     # delete later
            COMMAND xsltproc ARGS quickref.xsl ${OUT_DIR}/tidy-config.xml > ${OUT_DIR}/quickref.html
            COMMAND xsltproc ARGS quickref.include.xsl ${OUT_DIR}/tidy-config.xml > ${EXP_DIR}/quickref_include.html # delete later

            COMMAND ${TIDY_FOUND} -h > ${EXP_DIR}/tidy5.help.txt               # delete later
            COMMAND ${TIDY_FOUND} -help-config > ${EXP_DIR}/tidy5.config.txt   # delete later
            COMMAND cp ARGS ../LICENSE.md ${EXP_DIR}                           # delete later
        )

        #=========================================
        # Run Doxygen.
        #=========================================
        add_custom_command(
            TARGET documentation
            COMMENT "Run Doxygen"
            VERBATIM
            WORKING_DIRECTORY ${WRK_DIR}
            COMMAND cat doxygen_temp.cfg | doxygen - > /dev/null      
        )

        #=========================================
        # Cleanup.
        #=========================================
        add_custom_command(
            TARGET documentation
            COMMENT "Cleanup"
            VERBATIM
            WORKING_DIRECTORY ${WRK_DIR}
            COMMAND rm doxygen_temp.cfg
            COMMAND rm ${OUT_DIR}/tidy-config.xml
            COMMAND rm ${EXP_DIR}/quickref_include.html
            COMMAND rm ${EXP_DIR}/tidy5.help.txt
            COMMAND rm ${EXP_DIR}/tidy5.config.txt
            COMMAND rm ${EXP_DIR}/LICENSE.md
        )
        

        install(CODE "MESSAGE(\"Build output can be found in ${OUT_DIR}.\")")
    
    else()
        if(NOT XSLTPROC_FOUND)
            MESSAGE(FATAL_ERROR "Documentation requires xsltproc to be installed. Aborting.")
        endif()
        if(NOT DOXYGEN_FOUND)
            MESSAGE(FATAL_ERROR "Documentation requires doxygen to be installed. Aborting.")
        endif()
    endif()

endif() #BUILD_DOCUMENTATION

##########################################################
### Create MSI,EXE, DMG, DEB/RPM
### TODO: Check each of these builds
##########################################################
set(BITNESS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(BITNESS 64)
endif()
if (WIN32)
    # MSI - this needs WiX Tooset installed and a path to candle.exe
    # EXE - this needs NSIS tools to be in path
    set(CPACK_GENERATOR "NSIS;WIX")
    set(CPACK_SOURCE_GENERATOR "ZIP")
    set(CPACK_WIX_UPGRADE_GUID "D809598A-B513-4752-B268-0BAC403B00E4")
elseif ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set(CPACK_GENERATOR "PackageMake")
    set(CPACK_SOURCE_GENERATOR "TGZ")
else ()
    set(CPACK_GENERATOR "DEB;RPM")
    set(CPACK_SOURCE_GENERATOR "TGZ")
endif ()

set(CPACK_PACKAGE_NAME "Tidy5")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Tidy5 - HTML syntax checker")
set(CPACK_PACKAGE_VENDOR "HTML Tidy Advocacy Community Group")
set(CPACK_PACKAGE_CONTACT "maintainer@htacg.org")

set(CPACK_PACKAGE_VERSION ${LIBTIDY_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "${TIDY_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${TIDY_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${TIDY_POINT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.html")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.html")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README.html")

## debian config
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://www.html-tidy.org/")
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc")
set(CPACK_DEBIAN_PACKAGE_SECTION "Libraries")

set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_SOURCE_DIR}/test/;${CMAKE_SOURCE_DIR}/build/;${CMAKE_SOURCE_DIR}/.git/")

if (NOT WIN32 AND NOT APPLE)
set( CPACK_PACKAGE_FILE_NAME "tidy5-${CPACK_PACKAGE_VERSION}-${BITNESS}bit" )
endif ()

include(CPack)

# eof
