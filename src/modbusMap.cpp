#include "modbusMap.hpp"

#include <climits>

using namespace std;

ZMBQMap::ZMBQMap( string name )
{
    m_name = name;
    m_baseAddress = UINT_MAX;
    m_size = 0U;
}

string ZMBQMap::GetName( )
{
    return m_name;
}

void ZMBQMap::InitMap_ExpandMap( uint32_t address, uint32_t count )
{
    m_baseAddress = min( m_baseAddress, address );
    m_size = max( m_size, address + count );
}

void ZMBQMap::InitMap_Generate( )
{
    m_dataMap = modbus_mapping_new( 0, 0, m_size, m_size );
}

void* ZMBQMap::GetDataPointer_InputRegs( uint32_t address )
{
    if( address < m_baseAddress + m_size )
    {
        return &( m_dataMap->tab_input_registers[ address - m_baseAddress ] );
    }
    else
    {
        return nullptr;
    }
}

void* ZMBQMap::GetDataPointer_HoldingRegs( uint32_t address )
{
    if( address < m_baseAddress + m_size )
    {
        return &( m_dataMap->tab_registers[ address - m_baseAddress ] );
    }
    else
    {
        return nullptr;
    }
}