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
        cerr << "Error: " << name << " not specified." << endl << "Use \"-" << flag << "\"." << endl; \
        exit( EXIT_FAILURE ); \
    }

typedef struct
{
    int         port;
    uint16_t    baseRegister;
} MODBUS_READER_PARAMS;

static MODBUS_READER_PARAMS processArgs( int argc, char* argv[] )
{
    int temp;
    int opt = 0;
    MODBUS_READER_PARAMS params;
    params.port = INT32_MAX;
    params.baseRegister = UINT16_MAX;

    do
    {
        opt = getopt( argc, argv, "p:r:" );

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
            default:
                cerr << "Usage: " << argv[ 0 ] << " [-p modbusPort] [-r baseRegister]" << endl;
                exit( EXIT_FAILURE );
                break;
        }
    } while( opt != -1 );

    CHECK_PARAMETER_SET( params.port, INT32_MAX, "Modbus port", "p" );
    CHECK_PARAMETER_SET( params.baseRegister, UINT16_MAX, "base register", "r" );

    return params;
}

int main( int argc, char *argv[] )
{
    int result = EXIT_SUCCESS;
    MODBUS_READER_PARAMS pubParams = processArgs( argc, argv );

    pubParams.port++;

    return result;
}