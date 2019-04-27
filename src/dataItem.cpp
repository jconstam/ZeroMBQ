#include "dataItem.hpp"

ZeroMBQDataItem::ZeroMBQDataItem( int address, string order, string tag, string type )
{
    m_address = address;
    m_tag = tag;
    m_type = ZMBQData::typeFromString( type );
    m_convertFromZMQFunc = ZMBQData::getConvertFromZMQFunc( m_type, order );
    m_convertToZMQFunc = ZMBQData::getConvertToZMQFunc( m_type, order );
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
ConvertFromZMQFunc ZeroMBQDataItem::getConvertFromZMQFunc( ) const
{
    return m_convertFromZMQFunc;
}
ConvertToZMQFunc ZeroMBQDataItem::getConvertToZMQFunc( ) const
{
    return m_convertToZMQFunc;
}

bool ZeroMBQDataItem::convertFromZMQ( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize )
{
    return getConvertFromZMQFunc( )( rawData, outBuffer, bufferIndex, bufferSize );
}
bool ZeroMBQDataItem::convertToZMQ( void* value, void* buffer, uint32_t bufferSize )
{
    return getConvertToZMQFunc( )( value, buffer, bufferSize );
}
