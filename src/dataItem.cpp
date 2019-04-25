#include "dataItem.hpp"

ZeroMBQDataItem::ZeroMBQDataItem( int address, string order, string tag, string type )
{
    m_address = address;
    m_tag = tag;
    m_type = ZMBQData::typeFromString( type );
    m_convertFunc = ZMBQData::getConversionFunc( m_type, order );
}

uint16_t ZeroMBQDataItem::getAddress( ) const
{
    return m_address;
}
string ZeroMBQDataItem::getTag( ) const
{
    return m_tag;
}
DATA_TYPE ZeroMBQDataItem::getType( ) const
{
    return m_type;
}
ConvertFunc ZeroMBQDataItem::getConvertFunc( ) const
{
    return m_convertFunc;
}