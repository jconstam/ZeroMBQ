#include "dataPoint.hpp"

ZMBQDataPoint::ZMBQDataPoint( ) : ZMBQDataPoint( "Unknown", "uint16" )
{
    
}

ZMBQDataPoint::ZMBQDataPoint( string name, string typeString )
{
    m_name = name;
    m_type = ZMBQData::typeFromString( typeString );
    m_size = ZMBQData::typeSize( m_type );
    m_valueArray = ( uint8_t* ) calloc( m_size, sizeof( uint8_t ) );
}

void ZMBQDataPoint::addDataLocation( void* dataPointer )
{
    m_dataLocations.push_back( dataPointer );
}
