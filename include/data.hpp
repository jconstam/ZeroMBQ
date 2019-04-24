#ifndef DATA_HPP__
#define DATA_HPP__

#include <string>
#include <map>

#include <stdint.h>

using namespace std;

#define DATA_TYPE_RAW_SIZE          ( sizeof( uint32_t ) )

#define DATATYPE_STRING_UINT16      "uint16"
#define DATATYPE_STRING_UINT32      "uint32"

typedef bool (*ConvertFunc)( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
typedef void (*ParseRawDataFunc)( uint8_t* rawBuffer, uint32_t bufferSize, void* data );

typedef enum
{
    DATA_TYPE_UINT16,
    DATA_TYPE_UINT32
} DATA_TYPE;

class ZMBQData
{
    private:
    public:
        static DATA_TYPE typeFromString( string typeString );

        static ParseRawDataFunc getParseRawDataFunc( DATA_TYPE type );
        static void parseRawData_uint16( uint8_t* rawBuffer, uint32_t bufferSize, void* data );
        static void parseRawData_uint32( uint8_t* rawBuffer, uint32_t bufferSize, void* data );

        static ConvertFunc getConversionFunc( DATA_TYPE type, string order );
        static bool Convert_uint16_12( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_uint16_21( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_uint32_4321( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_uint32_1234( uint16_t* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
};

#endif