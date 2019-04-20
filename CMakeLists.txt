cmake_minimum_required( VERSION 3.5 )

set( PROJECT_NAME "ZeroMBQ" )

project( ${PROJECT_NAME} ) 

set( SOURCE_PATH ${PROJECT_SOURCE_DIR}/src )

set( SOURCES 
    ${SOURCE_PATH}/main.cpp
)

add_executable( ${PROJECT_NAME} ${SOURCES} )