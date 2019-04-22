#include "slave.hpp"

ZeroMBQSlave::ZeroMBQSlave( ) : ZeroMBQSlave( 0 ){ };
ZeroMBQSlave::ZeroMBQSlave( uint16_t deviceID )
{
    m_deviceID = deviceID;
}

void ZeroMBQSlave::AddDataItem( string itemName, ZeroMBQDataItem* newItem )
{
    m_data[ itemName ] = newItem;
}
uint16_t ZeroMBQSlave::GetDeviceID( )
{
    return m_deviceID;
}