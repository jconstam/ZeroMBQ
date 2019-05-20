#ifndef MODBUSMAP_HPP__
#define MODBUSMAP_HPP__

using namespace std;

#include <string>

#include "modbus.h"

class ZMBQMap
{
    public:
        ZMBQMap( );
        ZMBQMap( string name );

        void InitMap_ExpandMap( uint32_t address, uint32_t count );
        void InitMap_Generate( );
        void* GetDataPointer_InputRegs( uint32_t address );
        void* GetDataPointer_HoldingRegs( uint32_t address );

    private:
        string m_name;

        uint32_t m_baseAddress;
        uint32_t m_size;

        modbus_mapping_t* m_dataMap;
};

#endif