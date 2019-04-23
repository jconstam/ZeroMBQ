#include <iostream>
#include <climits>

#include <string.h>

#include "data.hpp"

using namespace std;

#define VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, dataSize )   \
    if( ( bufferIndex ) + ( dataSize ) > ( bufferSize ) ) { return false; }
#define SET_BUFFER( outBuffer, bufferIndex, rawData, rawDataIndex, mask, shift )    \
    ( outBuffer )[ bufferIndex ] = ( ( ( rawData )[ rawDataIndex ] & ( mask ) ) >> ( shift ) )

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
            if( order.compare( "4321" ) == 0 )
            {
                return &( Convert_uint32_4321 );
            }
            else
            {
                return &( Convert_uint32_1234 );
            }
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
    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( uint16_t ) );

    SET_BUFFER( outBuffer, bufferIndex + 0U, rawData, 0, 0xFF00, 8 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, rawData, 0, 0x00FF, 0 );

    return true;
}

bool ZMBQData::Convert_uint16_21( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( uint16_t ) );
    
    SET_BUFFER( outBuffer, bufferIndex + 0U, rawData, 0, 0x00FF, 0 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, rawData, 0, 0xFF00, 8 );

    return true;
}

bool ZMBQData::Convert_uint32_4321( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( uint32_t ) );
    
    SET_BUFFER( outBuffer, bufferIndex, rawData, 1, 0x00FF, 0 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, rawData, 1, 0xFF00, 8 );
    SET_BUFFER( outBuffer, bufferIndex + 2U, rawData, 0, 0x00FF, 0 );
    SET_BUFFER( outBuffer, bufferIndex + 3U, rawData, 0, 0xFF00, 8 );

    return true;
}

bool ZMBQData::Convert_uint32_1234( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( uint32_t ) );
    
    SET_BUFFER( outBuffer, bufferIndex, rawData, 0, 0xFF00, 8 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, rawData, 0, 0x00FF, 0 );
    SET_BUFFER( outBuffer, bufferIndex + 2U, rawData, 1, 0xFF00, 8 );
    SET_BUFFER( outBuffer, bufferIndex + 3U, rawData, 1, 0x00FF, 0 );

    return true;
}