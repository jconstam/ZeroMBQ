#include <iostream>
#include <climits>

#include <string.h>

#include "data.hpp"

using namespace std;

#define VALIDATE_RAWDATA_BUFFER_SIZE( bufferSize, typeSize )    \
    if( ( bufferSize ) < DATA_TYPE_RAW_SIZE + ( typeSize ) ) { return; }
#define VALIDATE_RAWDATA_TYPE( actualType, expectedType )    \
    if( ( actualType ) != ( expectedType ) ) { return; }
#define VALIDATE_RAWDATA_VALUE( data )    \
    if( data == nullptr ) { return; }

#define VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, dataSize )   \
    if( ( bufferIndex ) + ( dataSize ) > ( bufferSize ) ) { return false; }
#define SET_BUFFER( outBuffer, bufferIndex, rawData, rawDataIndex, mask, shift )    \
    ( outBuffer )[ bufferIndex ] = ( ( ( rawData )[ rawDataIndex ] & ( mask ) ) >> ( shift ) )

typedef struct
{
    uint32_t type;
    uint16_t value;
} RAWDATA_UINT16;

typedef struct
{
    uint32_t type;
    uint32_t value;
} RAWDATA_UINT32;

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

ParseRawDataFunc ZMBQData::getParseRawDataFunc( DATA_TYPE type )
{
    if( type == DATA_TYPE_UINT32 )
    {
        return &( parseRawData_uint32 );
    }
    else
    {
        return &( parseRawData_uint16 );
    }
}

void ZMBQData::parseRawData_uint16( uint8_t* rawBuffer, uint32_t bufferSize, void* data )
{
    RAWDATA_UINT16* rawData = ( RAWDATA_UINT16* ) rawBuffer;

    VALIDATE_RAWDATA_BUFFER_SIZE( bufferSize, sizeof( uint16_t ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT16 );
    VALIDATE_RAWDATA_VALUE( data );

    *( ( uint16_t* ) data ) = rawData->value;
    
}
void ZMBQData::parseRawData_uint32( uint8_t* rawBuffer, uint32_t bufferSize, void* data )
{
    RAWDATA_UINT32* rawData = ( RAWDATA_UINT32* ) rawBuffer;

    VALIDATE_RAWDATA_BUFFER_SIZE( bufferSize, sizeof( uint32_t ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT32 );
    VALIDATE_RAWDATA_VALUE( data );
    
    *( ( uint32_t* ) data ) = rawData->value;
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