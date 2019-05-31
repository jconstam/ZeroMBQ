#include "gtest/gtest.h"

#include "data.hpp"

#include <climits>

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
    EXPECT_EQ( DATA_TYPE_FLOAT, ZMBQData::typeFromString( "float" ) );
    EXPECT_EQ( DATA_TYPE_UINT32, ZMBQData::typeFromString( "uint32" ) );
    EXPECT_EQ( DATA_TYPE_UINT16, ZMBQData::typeFromString( "uint16" ) );
    EXPECT_EQ( DATA_TYPE_UINT16, ZMBQData::typeFromString( "dummy" ) );
}

TEST_F( DataTest, TypeSize )
{
    EXPECT_EQ( sizeof( uint32_t ), ZMBQData::typeSize( DATA_TYPE_UINT32 ) );
    EXPECT_EQ( sizeof( float ), ZMBQData::typeSize( DATA_TYPE_FLOAT ) );
    EXPECT_EQ( sizeof( uint16_t ), ZMBQData::typeSize( DATA_TYPE_UINT16 ) );
    EXPECT_EQ( 0U, ZMBQData::typeSize( ( DATA_TYPE ) INT_MAX ) );
}
