#include <climits>

#include <string.h>

#include "data.hpp"

DATA_TYPE ZMBQData::typeFromString( string typeString )
{
    DATA_TYPE type;

    if( typeString.compare( DATATYPE_STRING_UINT32 ) == 0 )
    {
        type = DATA_TYPE_UINT32;
    }
    else
    {
        type = DATA_TYPE_UINT16;
    }

    return type;
}

ConvertFunc ZMBQData::getConversionFunc( DATA_TYPE type, string order )
{
    switch( type )
    {
        case( DATA_TYPE_UINT32 ):
            break;
        case( DATA_TYPE_UINT16 ):
        default:
            if( order.compare( "21" ) == 0 )
            {
                return &( Convert_uint16_21 );
            }
            else
            {
                return &( Convert_uint16_12 );
            }
            break;
    }
}

bool ZMBQData::Convert_uint16_12( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    if( bufferIndex + sizeof( uint16_t ) > bufferSize )
    {
        return false;
    }
    else
    {
        outBuffer[ bufferIndex ] = ( ( rawData[ 0 ] & 0xFF00 ) >> 8 );
        outBuffer[ bufferIndex + 1U ] = ( ( rawData[ 0 ] & 0x00FF ) >> 0 );

        return true;
    }
}

bool ZMBQData::Convert_uint16_21( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    if( bufferIndex + sizeof( uint16_t ) > bufferSize )
    {
        return false;
    }
    else
    {
        outBuffer[ bufferIndex ] = ( ( rawData[ 0 ] & 0x00FF ) >> 0 );
        outBuffer[ bufferIndex + 1U ] = ( ( rawData[ 0 ] & 0xFF00 ) >> 8 );

        return true;
    }
}