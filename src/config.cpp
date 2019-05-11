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

        switch( ZMBQData::typeFromString( dataPoints[ dataPointIndex ][ "type" ].asString( ) ) )
        {
            case( DATA_TYPE_FLOAT ):
                m_dataPoints[ name ] = new ZMBQDataPoint<float>( name, 0.0f );
                break;
            case( DATA_TYPE_UINT32 ):
                m_dataPoints[ name ] = new ZMBQDataPoint<uint32_t>( name, 0U );
                break;
            case( DATA_TYPE_UINT16 ):
            default:
                m_dataPoints[ name ] = new ZMBQDataPoint<uint16_t>( name, 0U );
                break;
        }
    }
}