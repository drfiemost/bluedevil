cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(bluedevil)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options("$<$<CONFIG:DEBUG>:-Wall;-Wextra;-pedantic>")
endif()

find_package(KDE4 REQUIRED)

set(CMAKE_BLUEDEVIL_VERSION_MAJOR 2)
set(CMAKE_BLUEDEVIL_VERSION_MINOR 1)
set(CMAKE_BLUEDEVIL_VERSION_PATCH 0)
set(CMAKE_BLUEDEVIL_VERSION_STRING  "${CMAKE_BLUEDEVIL_VERSION_MAJOR}.${CMAKE_BLUEDEVIL_VERSION_MINOR}.${CMAKE_BLUEDEVIL_VERSION_PATCH}")
configure_file(version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.h)

include(KDE4Defaults)
include(MacroOptionalAddSubdirectory)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
find_package(SharedMimeInfo REQUIRED)

include_directories(${KDE4_INCLUDES} ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(bluedevil)
add_subdirectory(src)

include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

check_cxx_compiler_flag(-fvisibility=hidden _HAVE_VISIBILITY)
if (_HAVE_VISIBILITY AND NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

  check_cxx_compiler_flag(-fvisibility-inlines-hidden _HAVE_VISIBILITY_INLINES)
  if (_HAVE_VISIBILITY_INLINES)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
  endif (_HAVE_VISIBILITY_INLINES)
endif (_HAVE_VISIBILITY AND NOT WIN32)

set(INSTALL_TARGETS_DEFAULT_ARGS  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
                                  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
                                  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT Devel )


set(GENERIC_LIB_VERSION "2.1")
set(GENERIC_LIB_SOVERSION "2")
set(VERSION ${GENERIC_LIB_VERSION})

option(LIBBLUEDEVIL_BUILD_API_DOCS "Build libbluedevil API documentation")

##################  apidox ################################
if(LIBBLUEDEVIL_BUILD_API_DOCS)
  find_package(Doxygen)

  if(DOXYGEN_EXECUTABLE)
    if(EXISTS "${QT_DOC_DIR}/html/qt.tags")
      set(QT_TAG_STRING "${QT_DOC_DIR}/html/qt.tags=${QT_DOC_DIR}/html")
    endif()

    configure_file(${libbluedevil_SOURCE_DIR}/.Doxyfile.cmake ${libbluedevil_BINARY_DIR}/Doxyfile)

    add_custom_target(
      apidox ALL
      COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    )
  endif(DOXYGEN_EXECUTABLE)
endif(LIBBLUEDEVIL_BUILD_API_DOCS)
