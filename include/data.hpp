#ifndef DATA_HPP__
#define DATA_HPP__

#include <string>
#include <map>

#include <stdint.h>

using namespace std;

#define DATA_TYPE_RAW_SIZE          ( sizeof( uint32_t ) )

#define DATATYPE_STRING_UINT16      "uint16"
#define DATATYPE_STRING_UINT32      "uint32"

typedef bool (*ConvertFromZMQFunc)( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
typedef bool (*ConvertToZMQFunc)( void* value, void* buffer, uint32_t bufferSize );

typedef enum
{
    DATA_TYPE_UINT16,
    DATA_TYPE_UINT32
} DATA_TYPE;

typedef struct
{
    DATA_TYPE type;
    uint16_t value;
} RAWDATA_UINT16;

typedef struct
{
    DATA_TYPE type;
    uint32_t value;
} RAWDATA_UINT32;

class ZMBQData
{
    private:
    public:
        static DATA_TYPE typeFromString( string typeString );

        static ConvertFromZMQFunc getConversionFunc( DATA_TYPE type, string order );

        static bool Convert_zmq_to_uint16_12( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_zmq_to_uint16_21( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_zmq_to_uint32_4321( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        static bool Convert_zmq_to_uint32_1234( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );

        static bool Convert_uint16_12_to_zmq( void* value, void* buffer, uint32_t bufferSize );
        static bool Convert_uint16_21_to_zmq( void* value, void* buffer, uint32_t bufferSize );
        
        static bool Convert_uint32_1234_to_zmq( void* value, void* buffer, uint32_t bufferSize );
        static bool Convert_uint32_4321_to_zmq( void* value, void* buffer, uint32_t bufferSize );
};

#endif