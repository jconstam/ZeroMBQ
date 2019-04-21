cmake_minimum_required( VERSION 3.5 )

set( PROJECT_NAME "ZeroMBQ" )

project( ${PROJECT_NAME} ) 

set( SOURCES 
    ${PROJECT_SOURCE_DIR}/main.cpp
)

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} zmq jsoncpp )