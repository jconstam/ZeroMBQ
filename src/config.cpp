#include <fstream>
#include <iostream>

#include "config.hpp"
#include "dataItem.hpp"

ZeroMBQConfig::ZeroMBQConfig( )
{

}

bool ZeroMBQConfig::parseConfig( string path )
{
    Json::Value root;
    Json::Reader reader;

    ifstream file( path );
    file >> root;

    parseSlaveConfig( root[ "slaves" ] );
}

void ZeroMBQConfig::parseSlaveConfig( const Json::Value slaves )
{
    for ( int slaveIndex = 0; slaveIndex < slaves.size(); slaveIndex++ )
    {
        ZeroMBQSlave currSlave( slaves[ slaveIndex ][ "deviceID" ].asUInt( ) );
        Json::Value currSlaveData = slaves[ slaveIndex ];
        for ( int dataIndex = 0; dataIndex < currSlaveData[ "data" ].size(); dataIndex++ )
        {
            Json::Value currData = currSlaveData[ "data" ][ dataIndex ];

            currSlave.AddDataItem( currData[ "tag" ].asString( ), 
                new ZeroMBQDataItem( currData[ "address" ].asUInt( ), currData[ "order" ].asString( ), currData[ "tag" ].asString( ), currData[ "type" ].asString( ) ) );
        }

        m_slaveList[ currSlave.GetDeviceID( ) ] = currSlave;
    }
}