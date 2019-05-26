#include <iostream>

#include "modbusSlave.hpp"

using namespace std;

ModbusSlave::ModbusSlave( int tcpPort )
{
    m_tcpPort = tcpPort;
}

void ModbusSlave::start( modbus_mapping_t* mapping )
{
    
}

void ModbusSlave::stop( )
{

}

void ModbusSlave::slaveThreadFunction( modbus_mapping_t* mapping )
{
    
}