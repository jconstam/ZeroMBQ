#include "slave.hpp"

ZeroMBQSlave::ZeroMBQSlave( ) : ZeroMBQSlave( 0 ){ };
ZeroMBQSlave::ZeroMBQSlave( uint16_t deviceID )
{
    m_deviceID = deviceID;
}

void ZeroMBQSlave::AddDataItem( string itemName, ZeroMBQDataItem* newItem )
{
    m_dataLookup[ itemName ] = newItem;

    m_modbusData.resize( ( newItem->getAddress( ) + 1U ) * sizeof( uint16_t ), 0U );
}

uint16_t ZeroMBQSlave::GetDeviceID( ) const
{
    return m_deviceID;
}

void ZeroMBQSlave::ProcessNewData( string tag, void* data, uint32_t dataSize )
{
    if( m_dataLookup.find( tag ) != m_dataLookup.end( ) )
    {
        ZeroMBQDataItem* dataItem = m_dataLookup[ tag ];

        if( ! dataItem->getConvertFunc( )( data, m_modbusData.data( ), dataItem->getAddress( ), dataSize ) )
        {
            
        }
    }
}
