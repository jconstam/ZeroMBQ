#ifndef SLAVE_HPP__
#define SLAVE_HPP__

using namespace std;

#include <string>
#include <map>

#include "data.hpp"
#include "dataItem.hpp"

class ZeroMBQSlave
{
    public:
        ZeroMBQSlave( );
        ZeroMBQSlave( uint16_t );

        void AddDataItem( string, ZeroMBQDataItem* );
        uint16_t GetDeviceID( );

    private:
        uint16_t m_deviceID;
        map<string,ZeroMBQDataItem*> m_data;
};

#endif