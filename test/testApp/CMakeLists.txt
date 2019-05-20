set( TEST_APP_SOURCES
    ${TEST_APP_ROOT}/main.cpp
)

find_package( PkgConfig REQUIRED )
pkg_check_modules( JSONCPP REQUIRED jsoncpp )
pkg_check_modules( LIBMODBUS REQUIRED libmodbus )

set( TEST_APP_PROJECT_NAME "ZeroMBQTestApp" )
include_directories( ${TEST_APP_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include ${JSONCPP_INCLUDE_DIRS} ${LIBMODBUS_INCLUDE_DIRS} )
add_executable( ${TEST_APP_PROJECT_NAME} ${TEST_APP_SOURCES} )
target_link_libraries( ${TEST_APP_PROJECT_NAME} ZeroMBQ )

add_test( testApp_NoParam ${TEST_APP_PROJECT_NAME} )
set_tests_properties( testApp_NoParam PROPERTIES WILL_FAIL TRUE )
set_tests_properties( testApp_NoParam PROPERTIES FAIL_REGULAR_EXPRESSION "Usage: ZeroMBQTestApp <configFile>.\n" )