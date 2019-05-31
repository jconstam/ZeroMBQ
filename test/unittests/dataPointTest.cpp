#include "gtest/gtest.h"

#include "data.hpp"
#include "dataPoint.hpp"

class DataPointTest : public ::testing::Test
{
    protected:
        void SetUp( ) override
        {

        }

        void TearDown( ) override
        {

        }
};

TEST_F( DataPointTest, DefaultConstructor )
{
	ZMBQDataPoint dataPoint = ZMBQDataPoint( );
	
	EXPECT_STREQ( "Unknown", dataPoint.name( ).c_str( ) );
}

TEST_F( DataPointTest, AddAndWriteDataUInt16 )
{
	uint16_t data_A = 0U;
	uint16_t data_B = 0U;
	uint16_t data_In = 0x1234U;
	uint8_t message[ 6U ] = { 0 };

	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data_In ), sizeof( uint16_t ) );

	ZMBQDataPoint dataPoint = ZMBQDataPoint( "Test Point", "uint16" );
	
	dataPoint.addDataLocation( &( data_A ) );
	dataPoint.addDataLocation( &( data_B ) );

	dataPoint.writeToModbus( message );

	EXPECT_EQ( 0x1234U, data_A );
	EXPECT_EQ( 0x1234U, data_B );
}

TEST_F( DataPointTest, AddAndWriteDataUInt32 )
{
	uint32_t data_A = 0U;
	uint32_t data_B = 0U;
	uint32_t data_In = 0x12345678U;
	uint8_t message[ 8U ] = { 0 };

	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data_In ), sizeof( uint32_t ) );

	ZMBQDataPoint dataPoint = ZMBQDataPoint( "Test Point", "uint32" );
	
	dataPoint.addDataLocation( &( data_A ) );
	dataPoint.addDataLocation( &( data_B ) );

	dataPoint.writeToModbus( message );

	EXPECT_EQ( 0x12345678U, data_A );
	EXPECT_EQ( 0x12345678U, data_B );
}

TEST_F( DataPointTest, AddAndWriteDataFloat )
{
	float data_A = 0.0f;
	float data_B = 0.0f;
	float data_In = 1234.5678f;
	uint8_t message[ 8U ] = { 0 };

	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data_In ), sizeof( float ) );

	ZMBQDataPoint dataPoint = ZMBQDataPoint( "Test Point", "float" );
	
	dataPoint.addDataLocation( &( data_A ) );
	dataPoint.addDataLocation( &( data_B ) );

	dataPoint.writeToModbus( message );

	EXPECT_FLOAT_EQ( 1234.5678f, data_A );
	EXPECT_FLOAT_EQ( 1234.5678f, data_B );
}

TEST_F( DataPointTest, DataPointCollection )
{
	uint16_t data1 = 0U;
	uint32_t data2 = 0U;
	float data3 = 0.0f;

	uint16_t data1_In = 0x1234U;
	uint32_t data2_In = 0x87654321U;
	float data3_In = 123.456f;

	ZMBQDataPoint dataPoint1 = ZMBQDataPoint( "Test Point uint16", "uint16" );
	dataPoint1.addDataLocation( &( data1 ) );
	ZMBQDataPoint dataPoint2 = ZMBQDataPoint( "Test Point uint32", "uint32" );
	dataPoint2.addDataLocation( &( data2 ) );
	ZMBQDataPoint dataPoint3 = ZMBQDataPoint( "Test Point float", "float" );
	dataPoint3.addDataLocation( &( data3 ) );
	
	ZMBQDataPointCollection collection = ZMBQDataPointCollection( );
	collection.addDataPoint( dataPoint1 );
	collection.addDataPoint( dataPoint2 );
	collection.addDataPoint( dataPoint3 );

	EXPECT_STREQ( "Test Point uint16", collection[ "Test Point uint16" ].name( ).c_str( ) );
	EXPECT_STREQ( "Test Point uint32", collection[ "Test Point uint32" ].name( ).c_str( ) );
	EXPECT_STREQ( "Test Point float", collection[ "Test Point float" ].name( ).c_str( ) );

	EXPECT_EQ( true, collection.dataPointExists( "Test Point uint16" ) );
	EXPECT_EQ( true, collection.dataPointExists( "Test Point uint32" ) );
	EXPECT_EQ( true, collection.dataPointExists( "Test Point float" ) );
	EXPECT_EQ( false, collection.dataPointExists( "Test Point A" ) );

	uint8_t message[ 8U ];
	memset( message, 0U, 8U );
	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data1_In ), sizeof( uint16_t ) );

	collection.writeAllDataToModbus( "Test Point", message );
	EXPECT_EQ( 0U, data1 );
	EXPECT_EQ( 0U, data2 );
	EXPECT_FLOAT_EQ( 0.0f, data3 );

	collection.writeAllDataToModbus( "Test Point uint16", message );
	EXPECT_EQ( 0x1234U, data1 );
	EXPECT_EQ( 0U, data2 );
	EXPECT_FLOAT_EQ( 0.0f, data3 );

	memset( message, 0U, 8U );
	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data2_In ), sizeof( uint32_t ) );

	collection.writeAllDataToModbus( "Test Point uint32", message );
	EXPECT_EQ( 0x1234U, data1 );
	EXPECT_EQ( 0x87654321U, data2 );
	EXPECT_FLOAT_EQ( 0.0f, data3 );

	memset( message, 0U, 8U );
	memcpy( ZMQ_DATA_MSG_DATA_PTR( message ), &( data3_In ), sizeof( float ) );

	collection.writeAllDataToModbus( "Test Point float", message );
	EXPECT_EQ( 0x1234U, data1 );
	EXPECT_EQ( 0x87654321U, data2 );
	EXPECT_FLOAT_EQ( 123.456f, data3 );
}
