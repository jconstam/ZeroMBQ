#include <iostream>

#include "config.hpp"

using namespace std;

int main( int argc, char *argv[] )
{ 
    ZeroMBQConfig config;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " <configFile>.\n" << endl;
        exit( EXIT_FAILURE );
    }
    else if( !config.parseConfig( argv[ 1 ] ) )
    {
        cerr << "Could not parse config file." << endl;
        exit( EXIT_FAILURE );
    }

    exit( EXIT_SUCCESS );
}