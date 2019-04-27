#include "gtest/gtest.h"

#include "data.hpp"
#include "dataItem.hpp"

class DataItemTest : public ::testing::Test
{
    protected:
        void SetUp( ) override
        {

        }

        void TearDown( ) override
        {

        }
};

TEST_F( DataItemTest, ConstructorAndGetters )
{
    ZeroMBQDataItem item( 10, "12", "taggyTag", "uint16" );

    EXPECT_EQ( 10, item.getAddress( ) );
    EXPECT_EQ( item.getTag( ).compare( "taggyTag" ), 0 );
    EXPECT_EQ( DATA_TYPE_UINT16, item.getType( ) );
    EXPECT_EQ( &( ZMBQData::Convert_zmq_to_uint16_12 ), item.getConvertFromZMQFunc( ) );
    EXPECT_EQ( &( ZMBQData::Convert_uint16_12_to_zmq ), item.getConvertToZMQFunc( ) );
}
