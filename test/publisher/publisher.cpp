#include <iostream>
#include <cfloat>

#include <unistd.h>
#include <errno.h>

#include <zmq.hpp>
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
        char* endPtr; \
        long int testValue = strtol( ( typeString ).c_str( ), &( endPtr ), 0 ); \
        if( endPtr == ( typeString ).c_str( ) ) \
        { \
            fprintf( stderr, "Error: \"%s\" is not a valid %s\n", typeString.c_str( ), typeName ); \
            exit( EXIT_FAILURE ); \
        } \
        if( testValue > ( maxValue ) || testValue < ( minValue ) ) \
        { \
            fprintf( stderr, "Error: Failed to parse value \"%s\" as a %s\n", typeString.c_str( ), typeName ); \
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
    float value_float;
} PUBLISHER_PARAMS;

typedef struct
{
    void* context;
    void* socket;
    bool connected;
} ZMQ_CONNECTION;

static PUBLISHER_PARAMS processArgs( int argc, char* argv[] )
{
    int opt = 0;
    PUBLISHER_PARAMS params;
    params.port = INT32_MAX;
    params.tag = "";
    params.type = ( DATA_TYPE ) INT32_MAX;
    params.value_uint16 = UINT16_MAX;
    params.value_uint32 = UINT32_MAX;

    string typeString;

    do
    {
        opt = getopt( argc, argv, "p:t:y:v:o:" );

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
        case DATA_TYPE_FLOAT:
            CHECK_VALUE_RANGE( typeString, FLT_MAX, FLT_MIN, float, "float", params.value_float );
            break;
    }

    return params;
}

static size_t buildPacket( PUBLISHER_PARAMS* pubParams, uint8_t* buffer )
{
    switch( pubParams->type )
    {
        case( DATA_TYPE_FLOAT ):
            return ZMBQData::Convert_float_4321_to_zmq( &( pubParams->value_float ), buffer, ZMQ_BUFFER_SIZE_FLOAT );
        case( DATA_TYPE_UINT32 ):
            return ZMBQData::Convert_uint32_4321_to_zmq( &( pubParams->value_uint32 ), buffer, ZMQ_BUFFER_SIZE_UINT32 );
        case( DATA_TYPE_UINT16 ):
            return ZMBQData::Convert_uint16_21_to_zmq( &( pubParams->value_uint16 ), buffer, ZMQ_BUFFER_SIZE_UINT16 );
        default:
            return 0;
    }
}

static ZMQ_CONNECTION connectToZeroMQ( string endPoint )
{
    ZMQ_CONNECTION connection;
    connection.connected = false;
    
    connection.context = zmq_ctx_new( );
    if( connection.context == NULL )
    {
        fprintf( stderr, "Failed to create ZeroMQ context.\n" );
    }
    else
    {
        connection.socket = zmq_socket( connection.context, ZMQ_PUB );
        if( connection.socket == NULL )
        {
            fprintf( stderr, "Failed to create ZeroMQ publish socket.\n" );
        }
        else if( zmq_connect( connection.socket, endPoint.c_str( ) ) != 0 )
        {
            fprintf( stderr, "Failed to connect to ZeroMQ endpoint %s.\n", endPoint.c_str( ) );
        }
        else
        {
            connection.connected = true;
        }
    }

    return connection;
}

static void disconnectFromZeroMQ( ZMQ_CONNECTION connection )
{
    if( zmq_close( connection.socket ) != 0 )
    {
        fprintf( stderr, "Failed to destroy ZeroMQ publish socket.\n" );
    }
    if( zmq_ctx_destroy( connection.context ) != 0 )
    {
        fprintf( stderr, "Failed to destroy ZeroMQ context.\n" );
    }
}

static void publishData( ZMQ_CONNECTION connection, string tag, void* buffer, size_t bufferSize )
{
    zmq_msg_t tagMsg;
    zmq_msg_t dataMsg;

    if( zmq_msg_init_data( &( tagMsg ), ( void* ) tag.c_str( ), tag.size( ), NULL, NULL ) != 0 )
    {
        fprintf( stderr, "Failed to initialize ZeroMQ message for tag %s.\n", tag.c_str( ) );
    }
    else if( zmq_msg_send( &( tagMsg ), connection.socket, ZMQ_SNDMORE ) != ( int ) tag.size( ) )
    {
        fprintf( stderr, "Failed to send ZeroMQ message for tag %s.\n", tag.c_str( ) );
    }
    else if( zmq_msg_init_data( &( dataMsg ), buffer, bufferSize, NULL, NULL ) != 0 )
    {
        fprintf( stderr, "Failed to initialize ZeroMQ message with %d data bytes.\n", ( int ) bufferSize );
    }
    else if( zmq_msg_send( &( dataMsg ), connection.socket, 0 ) != ( int ) bufferSize )
    {
        fprintf( stderr, "Failed to send ZeroMQ message with %d data bytes.\n", ( int ) bufferSize );
    }
    else
    {
        fprintf( stdout, "Send ZeroMQ message with tag %s and %d data bytes.\n", tag.c_str( ), ( int ) bufferSize );
    }
}

int main( int argc, char *argv[] )
{
    int result = EXIT_SUCCESS;
    PUBLISHER_PARAMS pubParams = processArgs( argc, argv );

    uint8_t buffer[ ZMQ_BUFFER_SIZE_MAX ];
    size_t bufferSize = buildPacket( &( pubParams ), buffer );
    if( bufferSize == 0 )
    {
        fprintf( stderr, "Error building ZeroMQ packet for tag %s.\n", pubParams.tag.c_str( ) );
        exit( EXIT_FAILURE );
    }

    ZMQ_CONNECTION connection = connectToZeroMQ( string( "tcp://localhost:" ) + to_string( pubParams.port ) );
    if( connection.connected )
    {
        publishData( connection, pubParams.tag, buffer, bufferSize );
    }
    else
    {
        result = EXIT_FAILURE;
    }

    disconnectFromZeroMQ( connection );

    return result;
}