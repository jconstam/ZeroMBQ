#include <iostream>

#include "config.hpp"

using namespace std;

int main( int argc, char *argv[] )
{ 
    ZeroMBQConfig config;

    config.parseConfig( "/mnt/c/Users/Juventas/Documents/Development/ZeroMBQ/test/test.json" );

    return 0;
}