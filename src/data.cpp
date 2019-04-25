#include <iostream>
#include <climits>

#include <string.h>

#include "data.hpp"

using namespace std;

#define VALIDATE_RAWDATA_BUFFER_SIZE( bufferSize, typeSize )    \
    if( ( bufferSize ) < DATA_TYPE_RAW_SIZE + ( typeSize ) ) { return false; }
#define VALIDATE_RAWDATA_TYPE( actualType, expectedType )    \
    if( ( actualType ) != ( expectedType ) ) { return false; }
#define VALIDATE_OUTBUFFER( data )    \
    if( data == nullptr ) { return false; }

#define VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, dataSize )   \
    if( ( bufferIndex ) + ( dataSize ) > ( bufferSize ) ) { return false; }
#define SET_BUFFER( outBuffer, bufferIndex, rawData, rawDataByteIndex )    \
    ( outBuffer )[ bufferIndex ] = ( ( uint8_t* ) ( rawData ) )[ rawDataByteIndex ]

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

bool ZMBQData::Convert_uint16_12( void* rawBuffer, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    RAWDATA_UINT16* rawData = ( RAWDATA_UINT16* ) rawBuffer;
    
    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( RAWDATA_UINT16 ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT16 );
    VALIDATE_OUTBUFFER( outBuffer );

    SET_BUFFER( outBuffer, bufferIndex + 0U, &( rawData->value ), 1 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, &( rawData->value ), 0 );

    return true;
}

bool ZMBQData::Convert_uint16_21( void* rawBuffer, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    RAWDATA_UINT16* rawData = ( RAWDATA_UINT16* ) rawBuffer;

    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( RAWDATA_UINT16 ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT16 );
    VALIDATE_OUTBUFFER( outBuffer );
    
    SET_BUFFER( outBuffer, bufferIndex + 0U, &( rawData->value ), 0 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, &( rawData->value ), 1 );

    return true;
}

bool ZMBQData::Convert_uint32_4321( void* rawBuffer, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    RAWDATA_UINT32* rawData = ( RAWDATA_UINT32* ) rawBuffer;

    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( RAWDATA_UINT32 ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT32 );
    VALIDATE_OUTBUFFER( outBuffer );
    
    SET_BUFFER( outBuffer, bufferIndex, &( rawData->value ), 0 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, &( rawData->value ), 1 );
    SET_BUFFER( outBuffer, bufferIndex + 2U, &( rawData->value ), 2 );
    SET_BUFFER( outBuffer, bufferIndex + 3U, &( rawData->value ), 3 );

    return true;
}

bool ZMBQData::Convert_uint32_1234( void* rawBuffer, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    RAWDATA_UINT32* rawData = ( RAWDATA_UINT32* ) rawBuffer;

    VALIDATE_BUFFER_PARAMS( bufferIndex, bufferSize, sizeof( RAWDATA_UINT32 ) );
    VALIDATE_RAWDATA_TYPE( rawData->type, DATA_TYPE_UINT32 );
    VALIDATE_OUTBUFFER( outBuffer );
    
    SET_BUFFER( outBuffer, bufferIndex, &( rawData->value ), 3 );
    SET_BUFFER( outBuffer, bufferIndex + 1U, &( rawData->value ), 2 );
    SET_BUFFER( outBuffer, bufferIndex + 2U, &( rawData->value ), 1 );
    SET_BUFFER( outBuffer, bufferIndex + 3U, &( rawData->value ), 0 );

    return true;
}