set( PUBLISHER_SOURCES
    ${SOURCES_ROOT}/data.cpp

    ${PUBLISHER_ROOT}/publisher.cpp
)

set( PUBLISHER_PROJECT_NAME "Publisher" )
include_directories( ${PUBLISHER_PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../include )
add_executable( ${PUBLISHER_PROJECT_NAME} ${PUBLISHER_SOURCES} )

add_test( publisher ${PUBLISHER_PROJECT_NAME} )