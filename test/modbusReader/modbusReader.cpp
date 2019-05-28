#include <iostream>
#include <cfloat>

#include <unistd.h>
#include <errno.h>

#include <modbus.h>
#include <data.hpp>

using namespace std;

#define CHECK_PARAMETER_SET( param, badValue, name, flag )      \
    if( ( param ) == ( badValue ) ) \
    { \
        cerr << "Error: " << name << " not specified." << endl << "Use \"-" << flag << "\"." << endl; \
        exit( EXIT_FAILURE ); \
    }

#define CHECK_VALUE_RANGE( typeString, maxValue, minValue, type, typeName, value ) \
    { \
        char* endPtr; \
        long int testValue = strtol( ( typeString ).c_str( ), &( endPtr ), 0 ); \
        if( endPtr == ( typeString ).c_str( ) ) \
        { \
            cerr << "Error: " << typeString << " is not a valid " << typeName << endl; \
            exit( EXIT_FAILURE ); \
        } \
        if( testValue > ( long int )( maxValue ) || testValue < ( long int )( minValue ) ) \
        { \
            cerr << "Error: Failed to parse value " << typeString << " as a " << typeName << endl; \
            exit( EXIT_FAILURE ); \
        } \
        else \
        { \
            ( value ) = ( type )( testValue ); \
        } \
    }

typedef struct
{
    int         port;
    uint16_t    baseRegister;
    DATA_TYPE   type;

    uint16_t value_uint16;
    uint32_t value_uint32;
    float value_float;
} MODBUS_READER_PARAMS;

static MODBUS_READER_PARAMS processArgs( int argc, char* argv[] )
{
    int temp;
    int opt = 0;
    string typeString;
    MODBUS_READER_PARAMS params;

    params.port = INT32_MAX;
    params.baseRegister = UINT16_MAX;
    params.type = ( DATA_TYPE ) INT32_MAX;

    do
    {
        opt = getopt( argc, argv, "p:r:t:" );

        switch ( opt )
        {
            case -1:
                break;
            case 'p':
                params.port = strtol( optarg, nullptr, 10 );
                if( params.port <= 0 )
                {
                    cerr << "Invalid TCP port \"" << optarg << "\"" << endl;
                    exit( EXIT_FAILURE );
                }
                break;
            case 'r':
                temp = strtol( optarg, nullptr, 10 );
                params.baseRegister = ( uint16_t ) temp;
                if( ( temp > UINT16_MAX ) || ( params.baseRegister <= 0 ) )
                {
                    cerr << "Invalid base register \"" << optarg << "\"" << endl;
                    exit( EXIT_FAILURE );
                }
                break;
            case 't':
                params.type = ZMBQData::typeFromString( optarg );
                break;
            case 'v':
                typeString = string( optarg );
                break;
            default:
                cerr << "Usage: " << argv[ 0 ] << " [-p modbusPort] [-r baseRegister]" << endl;
                exit( EXIT_FAILURE );
                break;
        }
    } while( opt != -1 );

    CHECK_PARAMETER_SET( params.port, INT32_MAX, "Modbus port", "p" );
    CHECK_PARAMETER_SET( params.baseRegister, UINT16_MAX, "base register", "r" );
    CHECK_PARAMETER_SET( params.type, INT32_MAX, "data type", "y" );

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

static int analyzeResults( MODBUS_READER_PARAMS* params, uint16_t* registers )
{
    int result = EXIT_SUCCESS;
    float float_result;
    uint32_t uint32_result;

    switch( params->type )
    {
        case DATA_TYPE_UINT16:
            if( registers[ 0 ] != params->value_uint16 )
            {
                cerr << "Expected uint16 value " << params->value_uint16 << ". Got " << registers[ 0 ] << "." << endl;
                result = EXIT_FAILURE;
            }
            break;
        case DATA_TYPE_UINT32:
            uint32_result = ( registers[ 0 ] << 16 ) + registers[ 1 ];
            if( uint32_result != params->value_uint32 )
            {
                cerr << "Expected uint32 value " << params->value_uint32 << ". Got " << uint32_result << "." << endl;
                result = EXIT_FAILURE;
            }
            break;
        case DATA_TYPE_FLOAT:
            float_result = modbus_get_float( registers );
            if( ( float_result < params->value_float - 0.001 ) || ( float_result > params->value_float + 0.001 ) )
            {
                cerr << "Expected float value " << params->value_float << ". Got " << float_result << "." << endl;
                result = EXIT_FAILURE;
            }
            break;
    }

    return result;
}

int main( int argc, char *argv[] )
{
    modbus_t* context;
    int result = EXIT_SUCCESS;
    uint16_t registers[ 8 ] = { 0 };
    MODBUS_READER_PARAMS params = processArgs( argc, argv );

    context = modbus_new_tcp( "127.0.0.1", params.port );
    if( context == nullptr )
    {
        cerr << "Could not create libmodbus context on port " << params.port << endl;
        result = EXIT_FAILURE;
    }
    else 
    {
        if( modbus_connect( context ) == -1 ) 
        {
            cerr << "Could not connect with libmodbus on port " << params.port << endl;
            result = EXIT_FAILURE;
        }
        else 
        {
            if( modbus_read_registers( context, params.baseRegister, ZMBQData::typeSize( params.type ) / sizeof( uint16_t ), registers ) == -1 )
            {
                cerr << "Could not read " << ZMBQData::typeSize( params.type ) / sizeof( uint16_t ) << " registers from address " << params.baseRegister << "." << endl;
                result = EXIT_FAILURE;
            }
            else
            {
                result = analyzeResults( &( params ), registers );
            }

            modbus_close( context );
        }
        
        modbus_free( context );
    }

    return result;
}
