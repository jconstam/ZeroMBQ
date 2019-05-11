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

set( UNITTEST_PROJECT_NAME "ZeroMBQTest" )
include_directories( ${UNITTEST_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include )
add_executable( ${UNITTEST_PROJECT_NAME} ${UNITTEST_SOURCES} )
target_link_libraries( ${UNITTEST_PROJECT_NAME} gtest_main )
add_test( unittests ${UNITTEST_PROJECT_NAME} )