###############################################################################
#  Copyright (c) 2014-2020 libbitcoin-database developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# libbitcoin-database project configuration.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(libbitcoin-database LANGUAGES C CXX)

enable_testing()

list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules" )
include(CheckIncludeFiles)
include(CheckSymbolExists)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
  set( CANONICAL_LIB_NAME libbitcoin-database )
else ()
  set( CANONICAL_LIB_NAME bitcoin-database )
  find_package( PkgConfig REQUIRED )

  set( prefix "${CMAKE_PREFIX_PATH}" )
  set( exec_prefix "\${prefix}" )
  set( libdir "\${exec_prefix}/lib" )
  set( includedir "\${exec_prefix}/include" )

  set( PACKAGE_VERSION "4.0.0" )
  set( VERSION "${PACKAGE_VERSION}" )
endif ()

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Add compiler options
#------------------------------------------------------------------------------
# Warn on all stuff.
add_compile_options( "-Wall" )

# Warn on extra stuff.
add_compile_options( "-Wextra" )

# Disallow warning on style order of declarations.
add_compile_options( "-Wno-reorder" )

# Suppress warning for incomplete field initialization.
add_compile_options( "-Wno-missing-field-initializers" )

# Conform to style.
add_compile_options( "-Wno-missing-braces" )

# Ignore comments within comments or commenting of backslash extended lines.
add_compile_options( "-Wno-comment" )

# Suppress warning for copy of implicitly generated copy constructor.
add_compile_options( "-Wno-deprecated-copy" )

# Conflict in stdlib under clang.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options( "-Wno-mismatched-tags" )
endif()

# Implement -Dpkgconfigdir and output ${pkgconfigdir}.
#------------------------------------------------------------------------------
set( pkgconfigdir "${libdir}/pkgconfig" CACHE PATH "Path to pkgconfig directory." )

# Implement -Dwith-tests and declare with-tests.
#------------------------------------------------------------------------------
set( with-tests "yes" CACHE BOOL "Compile with unit tests." )

# Implement -Dwith-tools and declare with-tools.
#------------------------------------------------------------------------------
set( with-tools "yes" CACHE BOOL "Compile with tools." )

# Implement -Denable-ndebug and define NDEBUG.
#------------------------------------------------------------------------------
set( enable-ndebug "yes" CACHE BOOL "Compile without debug assertions." )

if (enable-ndebug)
    add_definitions( -DNDEBUG )
endif()

# Inherit -Denable-shared and define BOOST_ALL_DYN_LINK.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

if (BUILD_SHARED_LIBS)
    set( Boost_USE_STATIC_LIBS "off" )
else()
    set( Boost_USE_STATIC_LIBS "on" )
endif()

# Find boost
#------------------------------------------------------------------------------
find_package( Boost 1.76.0 REQUIRED COMPONENTS
    unit_test_framework )

set( boost_unit_test_framework_LIBS "-lboost_unit_test_framework" )

if (enable-ndebug)
    set( Boost_LIBRARY_DIR "${Boost_LIBRARY_DIR_DEBUG}" )
else ()
    set( Boost_LIBRARY_DIR "${Boost_LIBRARY_DIR_RELEASE}" )
endif()

set( boost_CPPFLAGS "-I${Boost_INCLUDE_DIR}" )
set( boost_LDFLAGS "-L${Boost_LIBRARY_DIR}" )

# Find bitcoin-system
#------------------------------------------------------------------------------
find_package( Bitcoin-System 4.0.0 REQUIRED )

# Define project common includes directories
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    include_directories( SYSTEM
        ${bitcoin_system_INCLUDE_DIRS} )
else()
    include_directories( SYSTEM
        ${bitcoin_system_STATIC_INCLUDE_DIRS} )
endif()

# Define project common library directories
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    link_directories(
        ${bitcoin_system_LIBRARY_DIRS} )
else()
    link_directories(
        ${bitcoin_system_STATIC_LIBRARY_DIRS} )
endif()

# Define project common libraries/linker flags.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    link_libraries(
        "-fstack-protector"
        "-fstack-protector-all"
        ${bitcoin_system_LIBRARIES} )
else()
    link_libraries(
        "-fstack-protector"
        "-fstack-protector-all"
        ${bitcoin_system_STATIC_LIBRARIES} )
endif()

# Define ${CANONICAL_LIB_NAME} project.
#------------------------------------------------------------------------------
add_library( ${CANONICAL_LIB_NAME}
    "../../src/error.cpp"
    "../../src/settings.cpp"
    "../../src/file/rotator.cpp"
    "../../src/file/utilities.cpp"
    "../../src/locks/file_lock.cpp"
    "../../src/locks/flush_lock.cpp"
    "../../src/locks/interprocess_lock.cpp"
    "../../src/memory/map.cpp"
    "../../src/memory/mman-win32/mman.c"
    "../../src/memory/mman-win32/mman.h" )

# ${CANONICAL_LIB_NAME} project specific include directories.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    target_include_directories( ${CANONICAL_LIB_NAME} PRIVATE
        "../../include"
        ${bitcoin_system_INCLUDE_DIRS} )
else()
    target_include_directories( ${CANONICAL_LIB_NAME} PRIVATE
        "../../include"
        ${bitcoin_system_STATIC_INCLUDE_DIRS} )
endif()

target_include_directories( ${CANONICAL_LIB_NAME} PUBLIC
"../../include" )

# ${CANONICAL_LIB_NAME} project specific libraries/linker flags.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    target_link_libraries( ${CANONICAL_LIB_NAME}
        ${bitcoin_system_LIBRARIES} )
else()
    target_link_libraries( ${CANONICAL_LIB_NAME}
        ${bitcoin_system_STATIC_LIBRARIES} )
endif()

# Define libbitcoin-database-test project.
#------------------------------------------------------------------------------
if (with-tests)
    add_executable( libbitcoin-database-test
        "../../test/error.cpp"
        "../../test/main.cpp"
        "../../test/settings.cpp"
        "../../test/store.cpp"
        "../../test/test.cpp"
        "../../test/test.hpp"
        "../../test/file/rotator.cpp"
        "../../test/file/utilities.cpp"
        "../../test/locks/file_lock.cpp"
        "../../test/locks/flush_lock.cpp"
        "../../test/locks/interprocess_lock.cpp"
        "../../test/memory/accessor.cpp"
        "../../test/memory/map.cpp"
        "../../test/mocks/blocks.hpp"
        "../../test/mocks/chunk_storage.cpp"
        "../../test/mocks/chunk_storage.hpp"
        "../../test/mocks/chunk_store.hpp"
        "../../test/mocks/map_store.hpp"
        "../../test/primitives/arraymap.cpp"
        "../../test/primitives/hashmap.cpp"
        "../../test/primitives/head.cpp"
        "../../test/primitives/iterator.cpp"
        "../../test/primitives/linkage.cpp"
        "../../test/primitives/manager.cpp"
        "../../test/query/archive.cpp"
        "../../test/query/confirm.cpp"
        "../../test/query/context.cpp"
        "../../test/query/extent.cpp"
        "../../test/query/initialize.cpp"
        "../../test/query/optional.cpp"
        "../../test/query/translate.cpp"
        "../../test/query/validate.cpp"
        "../../test/tables/archives/header.cpp"
        "../../test/tables/archives/input.cpp"
        "../../test/tables/archives/output.cpp"
        "../../test/tables/archives/point.cpp"
        "../../test/tables/archives/puts.cpp"
        "../../test/tables/archives/transaction.cpp"
        "../../test/tables/archives/txs.cpp"
        "../../test/tables/caches/bootstrap.cpp"
        "../../test/tables/caches/buffer.cpp"
        "../../test/tables/caches/neutrino.cpp"
        "../../test/tables/caches/validated_bk.cpp"
        "../../test/tables/caches/validated_tx.cpp"
        "../../test/tables/indexes/address.cpp"
        "../../test/tables/indexes/height.cpp"
        "../../test/tables/indexes/spend.cpp"
        "../../test/tables/indexes/strong_tx.cpp" )

    add_test( NAME libbitcoin-database-test COMMAND libbitcoin-database-test
            --run_test=*
            --show_progress=no
            --detect_memory_leak=0
            --report_level=no
            --build_info=yes )

#     libbitcoin-database-test project specific include directories.
#------------------------------------------------------------------------------
    target_include_directories( libbitcoin-database-test PRIVATE
        "../../include" )

#     libbitcoin-database-test project specific libraries/linker flags.
#------------------------------------------------------------------------------
    target_link_libraries( libbitcoin-database-test
        ${CANONICAL_LIB_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

endif()

# Define initchain project.
#------------------------------------------------------------------------------
if (with-tools)
    add_executable( initchain
        "../../tools/initchain/initchain.cpp" )

#     initchain project specific include directories.
#------------------------------------------------------------------------------
    target_include_directories( initchain PRIVATE
        "../../include" )

#     initchain project specific libraries/linker flags.
#------------------------------------------------------------------------------
    target_link_libraries( initchain
        ${CANONICAL_LIB_NAME} )

endif()

# Manage pkgconfig installation.
#------------------------------------------------------------------------------
configure_file(
  "../../libbitcoin-database.pc.in"
  "libbitcoin-database.pc" @ONLY )

install( FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-database.pc"
    DESTINATION "${pkgconfigdir}" )

# Manage installation of docs.
#------------------------------------------------------------------------------
install( FILES
    "../../AUTHORS"
    "../../COPYING"
    "../../ChangeLog"
    "../../INSTALL"
    "../../NEWS"
    "../../README"
    DESTINATION share/doc/libbitcoin-database )

# Manage ${CANONICAL_LIB_NAME} installation.
#------------------------------------------------------------------------------
install( TARGETS ${CANONICAL_LIB_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include )

# Manage include installation.
#------------------------------------------------------------------------------
install( DIRECTORY "../../include/bitcoin"
    DESTINATION include )

