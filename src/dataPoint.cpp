#include "dataPoint.hpp"

#include <cstring>

ZMBQDataPoint::ZMBQDataPoint( ) : ZMBQDataPoint( "Unknown", "uint16" )
{
    
}

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
