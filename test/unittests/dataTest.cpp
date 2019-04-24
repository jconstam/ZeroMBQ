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
    EXPECT_EQ( &( ZMBQData::Convert_uint32_4321 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "4321" ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint32_1234 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "1234" ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint32_1234 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT32, "dummy" ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint16_21 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "21" ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint16_12 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "12" ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint16_12 ), ZMBQData::getConversionFunc( DATA_TYPE_UINT16, "dummy" ) );
}

TEST_F( DataTest, ConvertUInt16Order12Fail )
{
    uint16_t raw = 0x1234;
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_12( &raw, buffer, 1U, 2U ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertUInt16Order12 )
{
    uint16_t raw = 0x1234;
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint16_12( &raw, buffer, 0U, 2U ) );
    
    EXPECT_EQ( 0x12U, buffer[ 0 ] );
    EXPECT_EQ( 0x34U, buffer[ 1 ] );
}

TEST_F( DataTest, ConvertUInt16Order21Fail )
{
    uint16_t raw[ 1 ] = { 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint16_21( raw, buffer, 1U, 2U ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
}
TEST_F( DataTest, ConvertUInt16Order21 )
{
    uint16_t raw[ 1 ] = { 0x1234 };
    uint8_t buffer[ sizeof( uint16_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint16_21( raw, buffer, 0U, 2U ) );
    
    EXPECT_EQ( 0x34U, buffer[ 0 ] );
    EXPECT_EQ( 0x12U, buffer[ 1 ] );
}

TEST_F( DataTest, ConvertUInt32Order1234Fail )
{
    uint16_t raw[ 2 ] = { 0x1234, 0x5678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint32_1234( raw, buffer, 1U, 4U ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertUInt32Order1234 )
{
    uint16_t raw[ 2 ] = { 0x1234, 0x5678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint32_1234( raw, buffer, 0U, 4U ) );
    
    EXPECT_EQ( 0x12U, buffer[ 0 ] );
    EXPECT_EQ( 0x34U, buffer[ 1 ] );
    EXPECT_EQ( 0x56U, buffer[ 2 ] );
    EXPECT_EQ( 0x78U, buffer[ 3 ] );
}

TEST_F( DataTest, ConvertUInt32Order4321Fail )
{
    uint16_t raw[ 2 ] = { 0x1234, 0x5678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( false, ZMBQData::Convert_uint32_4321( raw, buffer, 1U, 4U ) );
    
    EXPECT_EQ( 0U, buffer[ 0 ] );
    EXPECT_EQ( 0U, buffer[ 1 ] );
    EXPECT_EQ( 0U, buffer[ 2 ] );
    EXPECT_EQ( 0U, buffer[ 3 ] );
}
TEST_F( DataTest, ConvertUInt32Order4321 )
{
    uint16_t raw[ 2 ] = { 0x1234, 0x5678 };
    uint8_t buffer[ sizeof( uint32_t ) ] = { 0 };

    EXPECT_EQ( true, ZMBQData::Convert_uint32_4321( raw, buffer, 0U, 4U ) );
    
    EXPECT_EQ( 0x78U, buffer[ 0 ] );
    EXPECT_EQ( 0x56U, buffer[ 1 ] );
    EXPECT_EQ( 0x34U, buffer[ 2 ] );
    EXPECT_EQ( 0x12U, buffer[ 3 ] );
}

TEST_F( DataTest, ParseRawDataUInt16BufferFail )
{
    uint16_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT16;
    *( ( uint16_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x1234U;

    ZMBQData::parseRawData_uint16( rawData, 3U, &( value ) );

    EXPECT_EQ( 0U, value );
}
TEST_F( DataTest, ParseRawDataUInt16WrongType )
{
    uint16_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT32;
    *( ( uint16_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x1234U;

    ZMBQData::parseRawData_uint16( rawData, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ), &( value ) );

    EXPECT_EQ( 0U, value );
}
TEST_F( DataTest, ParseRawDataUInt16 )
{
    uint16_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint16_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT16;
    *( ( uint16_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x1234U;

    ZMBQData::parseRawData_uint16( rawData, DATA_TYPE_RAW_SIZE + sizeof( uint16_t ), &( value ) );

    EXPECT_EQ( 0x1234U, value );
}

TEST_F( DataTest, ParseRawDataUInt32BufferFail )
{
    uint32_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT32;
    *( ( uint32_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x12345678U;

    ZMBQData::parseRawData_uint32( rawData, 3U, &( value ) );

    EXPECT_EQ( 0U, value );
}
TEST_F( DataTest, ParseRawDataUInt32WrongType )
{
    uint32_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT16;
    *( ( uint32_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x12345678U;

    ZMBQData::parseRawData_uint32( rawData, DATA_TYPE_RAW_SIZE + sizeof( uint32_t ), &( value ) );

    EXPECT_EQ( 0U, value );
}
TEST_F( DataTest, ParseRawDataUInt32 )
{
    uint32_t value = 0U;
    uint8_t rawData[ DATA_TYPE_RAW_SIZE + sizeof( uint32_t ) ];
    *( ( uint32_t* ) &( rawData[ 0U ] ) ) = DATA_TYPE_UINT32;
    *( ( uint32_t* ) &( rawData[ DATA_TYPE_RAW_SIZE ] ) ) = 0x12345678U;

    ZMBQData::parseRawData_uint32( rawData, DATA_TYPE_RAW_SIZE + sizeof( uint32_t ), &( value ) );

    EXPECT_EQ( 0x12345678U, value );
}
