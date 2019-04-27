#include <iostream>
#include <zmq.hpp>

#include <unistd.h>

#include <data.hpp>

using namespace std;

#define CHECK_PARAMETER_SET( param, badValue, name, flag )      \
    if( ( param ) == ( badValue ) ) \
    { \
        fprintf( stderr, "Error: %s not specified.\nUse \"-%s\".", ( name ), ( flag ) ); \
        exit( EXIT_FAILURE ); \
    }

#define CHECK_VALUE_RANGE( typeString, maxValue, minValue, type, typeName, value ) \
    { \
        long int testValue = strtol( ( typeString ).c_str( ), NULL, 0 ); \
        if( testValue > ( maxValue ) || testValue < ( minValue ) ) \
        { \
            fprintf( stderr, "Error: could not parse value \"%s\" as a %s\n", typeString.c_str( ), typeName ); \
            exit( EXIT_FAILURE ); \
        } \
        else \
        { \
            ( value ) = ( type )( testValue ); \
        } \
    }

typedef struct
{
    int port;
    string tag;
    DATA_TYPE type;

    uint16_t value_uint16;
    uint32_t value_uint32;
} PUBLISHER_PARAMS;

static PUBLISHER_PARAMS processArgs( int argc, char* argv[] )
{
    int opt = 0;
    PUBLISHER_PARAMS params = { INT32_MAX };
    params.tag = "";
    params.type = ( DATA_TYPE ) INT32_MAX;

    string typeString;

    do
    {
        opt = getopt( argc, argv, "p:t:" );

        switch ( opt )
        {
            case -1:
                break;
            case 'p':
                params.port = strtol( optarg, nullptr, 10 );
                if( params.port <= 0 )
                {
                    fprintf( stderr, "Invalid TCP port \"%s\"\n", optarg );
                    exit( EXIT_FAILURE );
                }
                break;
            case 't':
                params.tag = string( optarg );
                break;
            case 'y':
                params.type = ZMBQData::typeFromString( optarg );
                break;
            case 'v':
                typeString = string( optarg );
                break;
            default:
                fprintf( stderr, "Usage: %s [-p publishPort]\n", argv[ 0 ] );
                exit( EXIT_FAILURE );
                break;
        }
    } while( opt != -1 );

    CHECK_PARAMETER_SET( params.port, INT32_MAX, "TCP port", "p" );
    CHECK_PARAMETER_SET( params.tag.compare( "" ), 0, "ZeroMQ tag", "t" );
    CHECK_PARAMETER_SET( params.type, INT32_MAX, "data type", "y" );
    CHECK_PARAMETER_SET( typeString.compare( "" ), 0, "data value", "v" );

    switch( params.type )
    {
        case DATA_TYPE_UINT16:
            CHECK_VALUE_RANGE( typeString, UINT16_MAX, 0, uint16_t, "uint16", params.value_uint16 );
            break;
        case DATA_TYPE_UINT32:
            CHECK_VALUE_RANGE( typeString, UINT32_MAX, 0, uint32_t, "uint32", params.value_uint32 );
            break;
    }

    return params;
}



int main( int argc, char *argv[] )
{
    PUBLISHER_PARAMS pubParams = processArgs( argc, argv );

    return 0;
}