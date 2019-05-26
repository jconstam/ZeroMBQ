#ifndef MODBUS_SLAVE_HPP__
#define MODBUS_SLAVE_HPP__

#include <thread>
#include <vector>
#include <string>

#include <modbus.h>

#include "dataPoint.hpp"

class ModbusSlave
{
    public:
        ModbusSlave( int tcpPort );

        void start( modbus_mapping_t* mapping );
        void stop( );

    private:
        int m_tcpPort;

        void slaveThreadFunction( modbus_mapping_t* mapping );
};

#endif