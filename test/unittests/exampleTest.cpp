#include "gtest/gtest.h"

class ExampleTest : public ::testing::Test
{
    protected:
        void SetUp( ) override
        {

        }

        void TearDown( ) override
        {

        }
};

TEST_F( ExampleTest, PassTest )
{
    EXPECT_EQ( 0, 0 );
}