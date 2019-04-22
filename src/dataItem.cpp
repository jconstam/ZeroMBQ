#include "dataItem.hpp"

ZeroMBQDataItem::ZeroMBQDataItem( int address, string order, string tag, string type )
{
    m_address = address;
    m_tag = tag;
    m_type = ZMBQData::typeFromString( type );
    m_convertFunc = ZMBQData::getConversionFunc( m_type, order );
}