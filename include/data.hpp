#ifndef DATA_HPP__
#define DATA_HPP__

#include <string>
#include <map>

#include <stdint.h>

using namespace std;

#define DATATYPE_STRING_UINT16      "uint16"
#define DATATYPE_STRING_UINT32      "uint32"

typedef bool (*ConvertFunc)( uint16_t*, uint8_t*, uint32_t, uint32_t );

typedef enum
{
    DATA_TYPE_UINT16,
    DATA_TYPE_UINT32
} DATA_TYPE;

class ZMBQData
{
    private:
    public:
        static DATA_TYPE typeFromString( string );

        static ConvertFunc getConversionFunc( DATA_TYPE, string );
        static bool Convert_uint16_12( uint16_t*, uint8_t*, uint32_t, uint32_t );
        static bool Convert_uint16_21( uint16_t*, uint8_t*, uint32_t, uint32_t );
};

#endif