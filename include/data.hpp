#ifndef DATA_HPP__
#define DATA_HPP__

#include <string>
#include <map>

#include <stdint.h>

#define DATA_TYPE_RAW_SIZE              ( sizeof( uint32_t ) )
#define ZMQ_BUFFER_SIZE_UINT16          ( DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) )
#define ZMQ_BUFFER_SIZE_UINT32          ( DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) )
#define ZMQ_BUFFER_SIZE_FLOAT           ( DATA_TYPE_RAW_SIZE + sizeof( float ) )
#define ZMQ_BUFFER_SIZE_MAX             ( max( ZMQ_BUFFER_SIZE_UINT32, ZMQ_BUFFER_SIZE_UINT16 ) )

#define ZMQ_MAX_TOPIC_LEN               ( 1024U )

#define DATATYPE_STRING_UINT16          "uint16"
#define DATATYPE_STRING_UINT32          "uint32"
#define DATATYPE_STRING_FLOAT           "float"

#define ZMQ_DATA_MSG_DATA_PTR( msg )    ( &( ( ( uint8_t* ) msg )[ DATA_TYPE_RAW_SIZE ] ) )

/// @brief Internal data type
typedef enum
{
    /// @brief uint16_t
    DATA_TYPE_UINT16,
    /// @brief uint16_t
    DATA_TYPE_UINT32,
    /// @brief float
    DATA_TYPE_FLOAT
} DATA_TYPE;

/// @brief Raw ZeroMQ data for a uint16_t data point
typedef struct
{
    /// @brief Data type value
    DATA_TYPE type;
    /// @brief Raw uint16_t value
    uint16_t value;
} RAWDATA_UINT16;

/// @brief Raw ZeroMQ data for a uint32_t data point
typedef struct
{
    /// @brief Data type value
    DATA_TYPE type;
    /// @brief Raw uint32_t value
    uint32_t value;
} RAWDATA_UINT32;

/// @brief Raw ZeroMQ data for a float data point
typedef struct
{
    /// @brief Data type value
    DATA_TYPE type;
    /// @brief Raw float value
    float value;
} RAWDATA_FLOAT;

class ZMBQData
{
    private:
    public:
        static DATA_TYPE typeFromString( std::string typeString );
        static int typeSize( DATA_TYPE type );
};

#endif
