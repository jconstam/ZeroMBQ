#ifndef DATA_HPP__
#define DATA_HPP__

/// @file data.hpp
/// @brief Contains generic data handling structs, enums, and classes.

#include <string>
#include <map>

#include <stdint.h>

/// @brief Size of the data type field in a raw ZeroMQ packet
#define DATA_TYPE_RAW_SIZE              ( sizeof( uint32_t ) )
/// @brief Size of a raw ZeroMQ packet with a uint16_t payload
#define ZMQ_BUFFER_SIZE_UINT16          ( DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) )
/// @brief Size of a raw ZeroMQ packet with a uint32_t payload
#define ZMQ_BUFFER_SIZE_UINT32          ( DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) )
/// @brief Size of a raw ZeroMQ packet with a float payload
#define ZMQ_BUFFER_SIZE_FLOAT           ( DATA_TYPE_RAW_SIZE + sizeof( float ) )
/// @brief Maximum size of a raw ZeroMQ packet
#define ZMQ_BUFFER_SIZE_MAX             ( max( ZMQ_BUFFER_SIZE_UINT32, ZMQ_BUFFER_SIZE_UINT16 ) )

/// @brief Maximum size of a ZeroMQ topic
#define ZMQ_MAX_TOPIC_LEN               ( 1024U )

/// @brief String value corresponding to data type uint16_t / @ref DATA_TYPE_UINT16
#define DATATYPE_STRING_UINT16          "uint16"
/// @brief String value corresponding to data type uint32_t / @ref DATA_TYPE_UINT32
#define DATATYPE_STRING_UINT32          "uint32"
/// @brief String value corresponding to data type float / @ref DATA_TYPE_FLOAT
#define DATATYPE_STRING_FLOAT           "float"

/// @brief Provides a pointer to the data section of a raw ZeroMQ packet
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

/// @brief Contains static methods for handling data
class ZMBQData
{
    private:
    public:
	/// @brief Converts a type string to a @ref DATA_TYPE value.
	/// @param typeString The type string to convert.
	/// @return A valid @ref DATA_TYPE value.  Defaults to @ref DATA_TYPE_UINT16.
        static DATA_TYPE typeFromString( std::string typeString );
	/// @brief Gets the size (in bytes) of a @ref DATA_TYPE value.
	/// @param type The data type to get the size of.
	/// @return The size of a value of the given type in bytes. If the given type is invalid, 0.
        static int typeSize( DATA_TYPE type );
};

#endif
