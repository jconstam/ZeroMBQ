#include "dataPoint.hpp"

ZMBQDataPoint::ZMBQDataPoint( ) : ZMBQDataPoint( "Unknown", "uint16" )
{
    
}

ZMBQDataPoint::ZMBQDataPoint( string name, string type )
{
    m_name = name;
    m_type = ZMBQData::typeFromString( type );
}
