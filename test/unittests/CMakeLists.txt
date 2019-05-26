# Download and unpack googletest at configure time
configure_file( CMakeLists.txt.in googletest-download/CMakeLists.txt )
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . RESULT_VARIABLE result WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if( result )
  message( FATAL_ERROR "CMake step for googletest failed: ${result}" )
endif()
execute_process( COMMAND ${CMAKE_COMMAND} --build . RESULT_VARIABLE result WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message( FATAL_ERROR "Build step for googletest failed: ${result}" )
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory( ${CMAKE_CURRENT_BINARY_DIR}/googletest-src ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL )

set( UNITTEST_SOURCES
    ${SOURCES_ROOT}/data.cpp
    ${SOURCES_ROOT}/dataPoint.cpp

    ${UNITTEST_ROOT}/dataTest.cpp
    ${UNITTEST_ROOT}/dataPointTest.cpp
)

find_package( PkgConfig REQUIRED )
pkg_check_modules( JSONCPP REQUIRED jsoncpp )
pkg_check_modules( LIBMODBUS REQUIRED libmodbus )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g -O0" )

set( UNITTEST_PROJECT_NAME "ZeroMBQTest" )
include_directories( ${UNITTEST_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include ${JSONCPP_INCLUDE_DIRS} ${LIBMODBUS_INCLUDE_DIRS} )
add_executable( ${UNITTEST_PROJECT_NAME} ${UNITTEST_SOURCES} )
target_link_libraries( ${UNITTEST_PROJECT_NAME} gtest_main zmq jsoncpp modbus )

add_test( unittests ${UNITTEST_PROJECT_NAME} )
add_test( unittest_coverage 
          gcovr 
          --root ${PROJECT_SOURCE_DIR}/.. 
          --exclude .*test.* 
          --sort-percentage 
          --keep 
          --print-summary 
          --fail-under-line 38 
          --fail-under-branch 26 
          --html -o ${CMAKE_CURRENT_BINARY_DIR}/${UNITTEST_PROJECT_NAME}.html
          )