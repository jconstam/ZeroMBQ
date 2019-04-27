set( PUBLISHER_SOURCES
    ${SOURCES_ROOT}/data.cpp

    ${PUBLISHER_ROOT}/publisher.cpp
)

set( PUBLISHER_PROJECT_NAME "Publisher" )
include_directories( ${PUBLISHER_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include )
add_executable( ${PUBLISHER_PROJECT_NAME} ${PUBLISHER_SOURCES} )
target_link_libraries( ${PUBLISHER_PROJECT_NAME} zmq )

add_test( publisher_noTCPPort ${PUBLISHER_PROJECT_NAME} )
set_tests_properties( publisher_noTCPPort PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_noTCPPort PROPERTIES FAIL_REGULAR_EXPRESSION "Error: TCP port not specified.\nUse \"-p\"." )

add_test( publisher_badTCPPort ${PUBLISHER_PROJECT_NAME} -p blah )
set_tests_properties( publisher_badTCPPort PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_badTCPPort PROPERTIES FAIL_REGULAR_EXPRESSION "Invalid TCP port \"blah\"\n" )

add_test( publisher_noZMQTag ${PUBLISHER_PROJECT_NAME} -p 1234 )
set_tests_properties( publisher_noZMQTag PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_noZMQTag PROPERTIES FAIL_REGULAR_EXPRESSION "Error: ZeroMQ tag not specified.\nUse \"-t\"\n" )

add_test( publisher_noDataType ${PUBLISHER_PROJECT_NAME} -p 1234 -t TestTag )
set_tests_properties( publisher_noDataType PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_noDataType PROPERTIES FAIL_REGULAR_EXPRESSION "Error: data type not specified.\nUse \"-y\"." )

add_test( publisher_noValueUInt16 ${PUBLISHER_PROJECT_NAME} -p 1234 -t TestTag -y uint16 )
set_tests_properties( publisher_noValueUInt16 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_noValueUInt16 PROPERTIES FAIL_REGULAR_EXPRESSION "Error: data value not specified.\nUse \"-v\"." )

add_test( publisher_noValueUInt32 ${PUBLISHER_PROJECT_NAME} -p 1234 -t TestTag -y uint32 )
set_tests_properties( publisher_noValueUInt32 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_noValueUInt32 PROPERTIES FAIL_REGULAR_EXPRESSION "Error: data value not specified.\nUse \"-v\"." )

add_test( publisher_badUInt16 ${PUBLISHER_PROJECT_NAME} -p 1234 -t TestTag -y uint16 -v 12345678 )
set_tests_properties( publisher_badUInt16 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_badUInt16 PROPERTIES FAIL_REGULAR_EXPRESSION "Error: could not parse value \"12345678\" as a uint16\n" )

add_test( publisher_badUInt32 ${PUBLISHER_PROJECT_NAME} -p 1234 -t TestTag -y uint32 -v 1234567887654321 )
set_tests_properties( publisher_badUInt32 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( publisher_badUInt32 PROPERTIES FAIL_REGULAR_EXPRESSION "Error: could not parse value \"1234567887654321\" as a uint32\n" )