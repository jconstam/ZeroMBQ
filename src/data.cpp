#include <iostream>
#include <climits>

#include <string.h>

#include "data.hpp"

using namespace std;

DATA_TYPE ZMBQData::typeFromString( string typeString )
{
    DATA_TYPE type;

    if( typeString.compare( DATATYPE_STRING_FLOAT ) == 0 )
    {
        type = DATA_TYPE_FLOAT;
    }
    else if( typeString.compare( DATATYPE_STRING_UINT32 ) == 0 )
    {
        type = DATA_TYPE_UINT32;
    }
    else
    {
        type = DATA_TYPE_UINT16;
    }

    return type;
}

int ZMBQData::typeSize( DATA_TYPE type )
{
    switch( type )
    {
        case( DATA_TYPE_UINT32 ):
            return sizeof( uint32_t );
        case( DATA_TYPE_FLOAT ):
            return sizeof( float );
        case( DATA_TYPE_UINT16 ):
            return sizeof( uint16_t );
    }

    return 0;
}
