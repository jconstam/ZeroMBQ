#ifndef SLAVE_HPP__
#define SLAVE_HPP__

using namespace std;

#include <string>
#include <map>
#include <vector>

#include "data.hpp"
#include "dataItem.hpp"

class ZeroMBQSlave
{
    public:
        ZeroMBQSlave( );
        ZeroMBQSlave( uint16_t deviceID );

        void AddDataItem( string itemName, ZeroMBQDataItem* newItem );
        uint16_t GetDeviceID( ) const;

        void ProcessNewData( string tag, void* data, uint32_t dataSize );

    private:
        uint16_t m_deviceID;
        map< string, ZeroMBQDataItem* > m_dataLookup;
        vector< uint8_t > m_modbusData;
};

#endif