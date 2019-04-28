cmake_minimum_required( VERSION 3.5 )

enable_testing( )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

set( SOURCES_ROOT ${PROJECT_SOURCE_DIR}/../src )
set( UNITTEST_ROOT ${PROJECT_SOURCE_DIR}/unittests )
set( PUBLISHER_ROOT ${PROJECT_SOURCE_DIR}/publisher )

add_subdirectory( ${UNITTEST_ROOT} )
add_subdirectory( ${PUBLISHER_ROOT} )