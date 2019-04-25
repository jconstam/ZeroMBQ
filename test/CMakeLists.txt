cmake_minimum_required( VERSION 3.5 )

set( UNITTEST_PROJECT_NAME "ZeroMBQTest" )
enable_testing( )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

set( UNITTEST_ROOT ${PROJECT_SOURCE_DIR}/unittests )
set( SOURCES_ROOT ${PROJECT_SOURCE_DIR}/../src )

add_subdirectory( ${UNITTEST_ROOT} )