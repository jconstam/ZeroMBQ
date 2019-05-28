#include "dataPoint.hpp"

#include <cstring>

using namespace std;

ZMBQDataPoint::ZMBQDataPoint( string name, string typeString )
{
    m_name = name;
    m_type = ZMBQData::typeFromString( typeString );
    m_size = ZMBQData::typeSize( m_type );
}

void ZMBQDataPoint::addDataLocation( void* dataPointer )
{
    m_dataLocations.push_back( dataPointer );
}

void ZMBQDataPoint::publish( void* dataMessage )
{
    for( auto &dataLocation : m_dataLocations )
    {
        memcpy( dataLocation, ZMQ_DATA_MSG_DATA_PTR( dataMessage ), m_size );
    }
}

ZMBQDataPointCollection::ZMBQDataPointCollection( )
{

}

ZMBQDataPoint &ZMBQDataPointCollection::operator[ ]( std::string name )
{
    return m_dataPoints[ name ];
}

void ZMBQDataPointCollection::addDataPoint( ZMBQDataPoint newDataPoint )
{
    m_dataPoints[ newDataPoint.name( ) ] = newDataPoint;
}

bool ZMBQDataPointCollection::dataPointExists( std::string name )
{
    return ( m_dataPoints.find( name ) != m_dataPoints.end( ) );
}

void ZMBQDataPointCollection::publishNewData( string topic, uint8_t* buffer )
{
    if( m_dataPoints.find( topic ) != m_dataPoints.end( ) )
    {
        m_dataPoints[ topic ].publish( buffer );
    }
}
