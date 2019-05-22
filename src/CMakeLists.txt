cmake_minimum_required( VERSION 3.5 )

set( PROJECT_NAME_LIBRARY "ZeroMBQ" )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

project( ${PROJECT_NAME_LIBRARY} ) 

set( SOURCES 
    ${PROJECT_SOURCE_DIR}/config.cpp
    ${PROJECT_SOURCE_DIR}/data.cpp
    ${PROJECT_SOURCE_DIR}/dataPoint.cpp
    ${PROJECT_SOURCE_DIR}/modbusMap.cpp
    ${PROJECT_SOURCE_DIR}/subscriber.cpp
)

find_package( PkgConfig REQUIRED )
pkg_check_modules( JSONCPP REQUIRED jsoncpp )
pkg_check_modules( LIBMODBUS REQUIRED libmodbus )

include_directories( ${PROJECT_NAME_LIBRARY} ${PROJECT_SOURCE_DIR}/../include ${JSONCPP_INCLUDE_DIRS} ${LIBMODBUS_INCLUDE_DIRS} )
add_library( ${PROJECT_NAME_LIBRARY} SHARED ${SOURCES} )
target_link_libraries( ${PROJECT_NAME_LIBRARY} zmq jsoncpp modbus )