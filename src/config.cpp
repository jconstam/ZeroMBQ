    #include <fstream>
#include <iostream>

#include "config.hpp"
#include "dataPoint.hpp"

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

    return true;
}

void ZMBQConfig::parseDataPoints( const Json::Value dataPoints )
{
    m_dataPoints.clear( );

    for ( unsigned int dataPointIndex = 0; dataPointIndex < dataPoints.size(); dataPointIndex++ )
    {
        string name = dataPoints[ dataPointIndex ][ "name" ].asString( );
        string type = dataPoints[ dataPointIndex ][ "type" ].asString( );

        m_dataPoints[ name ] = ZMBQDataPoint( name, type );
    }
}