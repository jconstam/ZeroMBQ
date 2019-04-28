cmake_minimum_required( VERSION 3.5 )

set( PROJECT_NAME_LIBRARY "ZeroMBQ" )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

project( ${PROJECT_NAME_LIBRARY} ) 

set( SOURCES 
    ${PROJECT_SOURCE_DIR}/config.cpp
    ${PROJECT_SOURCE_DIR}/data.cpp
    ${PROJECT_SOURCE_DIR}/dataItem.cpp
    ${PROJECT_SOURCE_DIR}/slave.cpp
    ${PROJECT_SOURCE_DIR}/forwarder.cpp
)

find_package( jsoncpp REQUIRED )

include_directories( ${PROJECT_NAME_LIBRARY} ${PROJECT_SOURCE_DIR}/../include )
add_library( ${PROJECT_NAME_LIBRARY} SHARED ${SOURCES} )
target_link_libraries( ${PROJECT_NAME_LIBRARY} zmq jsoncpp )