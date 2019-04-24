#include "slave.hpp"

ZeroMBQSlave::ZeroMBQSlave( ) : ZeroMBQSlave( 0 ){ };
ZeroMBQSlave::ZeroMBQSlave( uint16_t deviceID )
{
    m_deviceID = deviceID;
}

void ZeroMBQSlave::AddDataItem( string itemName, ZeroMBQDataItem* newItem )
{
    m_dataLookup[ itemName ] = newItem;

    m_modbusData.resize( newItem->getAddress( ) + 1U, 0U );
}

uint16_t ZeroMBQSlave::GetDeviceID( ) const
{
    return m_deviceID;
}

