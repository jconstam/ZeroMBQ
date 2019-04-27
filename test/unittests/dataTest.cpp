#include "gtest/gtest.h"

#include "data.hpp"

class DataTest : public ::testing::Test
{
    protected:
        void SetUp( ) override
        {

        }

        void TearDown( ) override
        {

        }
};

TEST_F( DataTest, TypeFromString )
{
    EXPECT_EQ( DATA_TYPE_UINT32, ZMBQData::typeFromString( "uint32" ) );
    EXPECT_EQ( DATA_TYPE_UINT16, ZMBQData::typeFromString( "uint16" ) );
    EXPECT_EQ( DATA_TYPE_UINT16, ZMBQData::typeFromString( "dummy" ) );
}

TEST_F( DataTest, GetConversionFunc )
{
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint32_4321 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "4321" ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint32_1234 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "1234" ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint32_1234 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "dummy" ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint16_21 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "21" ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint16_12 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "12" ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint16_12 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "dummy" ) );
}

TEST_F( DataTest, ConvertZMQToUInt16Order12InvalidBuffer )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT16, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_12( &raw, buffer, 1U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order12WrongType )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT32, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_12( &raw, buffer, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order12NullOutBuffer )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT32, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_12( &raw, nullptr, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order12 )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT16, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_zmq_to_uint16_12( &raw, buffer, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0x12U, buffer[ 0 ] );
    EXPECT_EQ( 0x34U, buffer[ 1 ] );
}

TEST_F( DataTest, ConvertZMQToUInt16Order21InvalidBuffer )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT16, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_21( &raw, buffer, 1U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order21WrongType )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT32, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_21( &raw, buffer, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order21NullOutBuffer )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT32, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint16_21( &raw, nullptr, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertZMQToUInt16Order21 )
{
    RAWDATA_UINT16 raw = { DATA_TYPE_UINT16, 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_zmq_to_uint16_21( &raw, buffer, 0U, sizeof( RAWDATA_UINT16 ) ) );
    
    EXPECT_EQ( 0x34U, buffer[ 0 ] );
    EXPECT_EQ( 0x12U, buffer[ 1 ] );
}

TEST_F( DataTest, ConvertZMQToUInt32Order1234InvalidBuffer )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT32, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_1234( &raw, buffer, 1U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertZMQToUInt32Order1234WrongType )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT16, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_1234( &raw, buffer, 0U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertZMQToUInt32Order1234NullOutBuffer )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT32, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_1234( &raw, nullptr, 0U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertZMQToUInt32Order1234 )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT32, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_zmq_to_uint32_1234( &raw, buffer, 0U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0x12U, buffer[ 0 ] );
    EXPECT_EQ( 0x34U, buffer[ 1 ] );
    EXPECT_EQ( 0x56U, buffer[ 2 ] );
    EXPECT_EQ( 0x78U, buffer[ 3 ] );
}

TEST_F( DataTest, ConvertZMQToUInt32Order4321InvalidBuffer )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT32, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_4321( &raw, buffer, 1U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertZMQToUInt32Order4321WrongType )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT16, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_4321( &raw, buffer, 0U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertZMQToUInt32Order4321NullOutBuffer )
{
    RAWDATA_UINT32 raw = { DATA_TYPE_UINT32, 0x12345678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_zmq_to_uint32_4321( &raw, nullptr, 0U, sizeof( RAWDATA_UINT32 ) ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}

TEST_F( DataTest, ConvertUInt16Order12ToZMQNullValue )
{
    //uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_12_to_zmq( nullptr, buffer, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order12ToZMQNullBuffer )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_12_to_zmq( &( value ), nullptr, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order12ToZMQBadBufferSize )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_12_to_zmq( &( value ), buffer, 2U ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order12ToZMQ )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint16_12_to_zmq( &( value ), buffer, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( ( uint8_t ) DATA_TYPE_UINT16, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0x12U, buffer[ 4 ] );
    EXPECT_EQ( 0x34U, buffer[ 5 ] );
}

TEST_F( DataTest, ConvertUInt16Order21ToZMQNullValue )
{
    //uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_21_to_zmq( nullptr, buffer, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order21ToZMQNullBuffer )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_21_to_zmq( &( value ), nullptr, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order21ToZMQBadBufferSize )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_21_to_zmq( &( value ), buffer, 2U ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
}
TEST_F( DataTest, ConvertUInt16Order21ToZMQ )
{
    uint16_t value = 0x1234;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint16_21_to_zmq( &( value ), buffer, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ) );

    EXPECT_EQ( ( uint8_t ) DATA_TYPE_UINT16, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0x34U, buffer[ 4 ] );
    EXPECT_EQ( 0x12U, buffer[ 5 ] );
}

TEST_F( DataTest, ConvertUInt32Order1234ToZMQNullValue )
{
    //uint32_t value = 0x12345678;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint32_1234_to_zmq( nullptr, buffer, DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
    EXPECT_EQ( 0U, buffer[ 6 ] );
    EXPECT_EQ( 0U, buffer[ 7 ] );
}
TEST_F( DataTest, ConvertUInt32Order1234ToZMQNullBuffer )
{
    uint32_t value = 0x12345678;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint32_1234_to_zmq( &( value ), nullptr, DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
    EXPECT_EQ( 0U, buffer[ 6 ] );
    EXPECT_EQ( 0U, buffer[ 7 ] );
}
TEST_F( DataTest, ConvertUInt32Order1234ToZMQBadBufferSize )
{
    uint32_t value = 0x12345678;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint32_1234_to_zmq( &( value ), buffer, 2U ) );

    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0U, buffer[ 4 ] );
    EXPECT_EQ( 0U, buffer[ 5 ] );
    EXPECT_EQ( 0U, buffer[ 6 ] );
    EXPECT_EQ( 0U, buffer[ 7 ] );
}
TEST_F( DataTest, ConvertUInt32Order1234ToZMQ )
{
    uint32_t value = 0x12345678;
    uint8_t buffer[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint32_1234_to_zmq( &( value ), buffer, DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ) );

    EXPECT_EQ( ( uint8_t ) DATA_TYPE_UINT32, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
    EXPECT_EQ( 0x12U, buffer[ 4 ] );
    EXPECT_EQ( 0x34U, buffer[ 5 ] );
    EXPECT_EQ( 0x56U, buffer[ 6 ] );
    EXPECT_EQ( 0x78U, buffer[ 7 ] );
}
