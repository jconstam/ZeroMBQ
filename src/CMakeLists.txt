cmake_minimum_required( VERSION 3.5 )

set( PROJECT_NAME "ZeroMBQ" )

set( CMAKE_CXX_STANDARD 11 )

project( ${PROJECT_NAME} ) 

set( SOURCES 
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/config.cpp
    ${PROJECT_SOURCE_DIR}/data.cpp
    ${PROJECT_SOURCE_DIR}/dataItem.cpp
    ${PROJECT_SOURCE_DIR}/slave.cpp
)

find_package( jsoncpp REQUIRED )

include_directories( ${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include )
add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} zmq jsoncpp )