    #include <fstream>
#include <iostream>

#include "config.hpp"
#include "dataPoint.hpp"
#include "modbusMap.hpp"

ZMBQConfig::ZMBQConfig( )
{

}

bool ZMBQConfig::parseConfig( string filePath )
{
    Json::Value root;
    Json::Reader reader;

    ifstream file( filePath );
    file >> root;

    parseDataPoints( root[ "dataPoints" ] );
    parseMaps( root[ "maps" ] );

    return true;
}

void ZMBQConfig::parseDataPoints( const Json::Value dataPoints )
{
    m_dataPoints.clear( );

    for ( unsigned int dataPointIndex = 0; dataPointIndex < dataPoints.size(); dataPointIndex++ )
    {
        string name = dataPoints[ dataPointIndex ][ "name" ].asString( );

        m_dataPoints[ name ] = ZMBQDataPoint( name, dataPoints[ dataPointIndex ][ "type" ].asString( ) );
    }
}

void ZMBQConfig::parseMaps( const Json::Value maps )
{
    for ( unsigned int mapIndex = 0; mapIndex < maps.size(); mapIndex++ )
    {
        Json::Value currMapData = maps[ mapIndex ];

        ZMBQMap currMap = ZMBQMap( currMapData[ "name" ].asString( ) );

        Json::Value dataList = currMapData[ "dataList" ];
        for ( unsigned int dataPointIndex = 0; dataPointIndex < dataList.size(); dataPointIndex++ )
        {
            Json::Value currData = dataList[ dataPointIndex ];
            if( m_dataPoints.find( currData[ "dataPoint" ].asString( ) ) != m_dataPoints.end( ) )
            {
                currMap.InitMap_ExpandMap( currData[ "baseAddr" ].asUInt( ), m_dataPoints[ currData[ "dataPoint" ].asString( ) ].size_bytes( ) );
            }
        }

        currMap.InitMap_Generate( );
        
        for ( unsigned int dataPointIndex = 0; dataPointIndex < dataList.size(); dataPointIndex++ )
        {
            Json::Value currData = dataList[ dataPointIndex ];
            if( m_dataPoints.find( currData[ "dataPoint" ].asString( ) ) != m_dataPoints.end( ) )
            {
                m_dataPoints[ currData[ "dataPoint" ].asString( ) ].addDataLocation( currMap.GetDataPointer_InputRegs( currData[ "baseAddr" ].asUInt( ) ) );
                m_dataPoints[ currData[ "dataPoint" ].asString( ) ].addDataLocation( currMap.GetDataPointer_HoldingRegs( currData[ "baseAddr" ].asUInt( ) ) );
            }
        }
    }
}