#include <iostream>
#include <zmq.hpp>

#include <unistd.h>

using namespace std;

typedef struct
{
    int port;
} PUBLISHER_PARAMS;


static PUBLISHER_PARAMS processArgs( int argc, char* argv[] )
{
    int opt = 0;
    PUBLISHER_PARAMS params = { 54321 };

    do
    {
        opt = getopt( argc, argv, "p:" );

        switch ( opt )
        {
            case -1:
                break;
            case 'p':
                params.port = strtol( optarg, nullptr, 10 );
                if( params.port <= 0 )
                {
                    fprintf( stderr, "Invalid TCP port %s\n", optarg );
                    exit( EXIT_FAILURE );
                }
                break;
            default:
                fprintf( stderr, "Usage: %s [-p publishPort]\n", argv[ 0 ] );
                exit( EXIT_FAILURE );
                break;
        }
    } while( opt != -1 );

    return params;
}

int main( int argc, char *argv[] )
{
    processArgs( argc, argv );

    return 0;
}