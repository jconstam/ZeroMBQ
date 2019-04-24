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

    private:
        uint16_t m_deviceID;
        map< string, ZeroMBQDataItem* > m_dataLookup;
        vector< uint16_t > m_modbusData;
};

#endif