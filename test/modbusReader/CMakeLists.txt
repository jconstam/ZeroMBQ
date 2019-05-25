set( MODBUS_READER_SOURCES
    ${SOURCES_ROOT}/data.cpp

    ${MODBUS_READER_ROOT}/modbusReader.cpp
)

find_package( PkgConfig REQUIRED )
pkg_check_modules( JSONCPP REQUIRED jsoncpp )
pkg_check_modules( LIBMODBUS REQUIRED libmodbus )

set( MODBUS_READER_PROJECT_NAME "ModbusReader" )
include_directories( ${MODBUS_READER_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include ${JSONCPP_INCLUDE_DIRS} ${LIBMODBUS_INCLUDE_DIRS} )
add_executable( ${MODBUS_READER_PROJECT_NAME} ${MODBUS_READER_SOURCES} )
target_link_libraries( ${MODBUS_READER_PROJECT_NAME} zmq jsoncpp modbus )

add_test( modbusReader_noTCPPort ${MODBUS_READER_PROJECT_NAME} )
set_tests_properties( modbusReader_noTCPPort PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_noTCPPort PROPERTIES FAIL_REGULAR_EXPRESSION "Error: TCP port not specified.\nUse \"-p\"." )

add_test( modbusReader_badTCPPort ${MODBUS_READER_PROJECT_NAME} -p blah )
set_tests_properties( modbusReader_badTCPPort PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_badTCPPort PROPERTIES FAIL_REGULAR_EXPRESSION "Invalid TCP port \"blah\"\n" )

add_test( modbusReader_badTCPPort2 ${MODBUS_READER_PROJECT_NAME} -p 1234567887654321 )
set_tests_properties( modbusReader_badTCPPort2 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_badTCPPort2 PROPERTIES FAIL_REGULAR_EXPRESSION "Invalid TCP port \"1234567887654321\"\n" )

add_test( modbusReader_noBaseRegister ${MODBUS_READER_PROJECT_NAME} -p 54321 )
set_tests_properties( modbusReader_noBaseRegister PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_noBaseRegister PROPERTIES FAIL_REGULAR_EXPRESSION "Error: base register not specified.\nUse \"-r\"." )

add_test( modbusReader_badBaseRegister ${MODBUS_READER_PROJECT_NAME} -p 54321 -r blah )
set_tests_properties( modbusReader_badBaseRegister PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_badBaseRegister PROPERTIES FAIL_REGULAR_EXPRESSION "Invalid base register \"blah\"\n" )

add_test( modbusReader_badBaseRegister2 ${MODBUS_READER_PROJECT_NAME} -p 54321 -r 7654321 )
set_tests_properties( modbusReader_badBaseRegister2 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( modbusReader_badBaseRegister2 PROPERTIES FAIL_REGULAR_EXPRESSION "Invalid base register \"7654321\"\n" )
