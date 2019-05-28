#ifndef MODBUSMAP_HPP__
#define MODBUSMAP_HPP__

/// @file modbusMap.hpp
/// @brief Manages the creation and control of a Modbus map.

#include <string>

#include "modbus.h"

/// @brief Class containing a Modbus map.
class ZMBQMap
{
    public:
	/// @brief Basic constructor. Initializes a Modbus map with the name "Unknown".
        ZMBQMap( ) : ZMBQMap( "Unknown" ){};
	/// @brief Common constructor.  Initializes a Modbus map with the given name.  Sets @ref m_name.  Initializes @ref m_size to 0.
        ZMBQMap( std::string name );

	/// @brief Gets the map's name.
	/// @return The name of the map (contained in @ref m_name).
        std::string GetName( );

	/// @brief Adds a new section to the map of the given size at the given address.
	/// @param address The base address of the new section.
	/// @param count The number of registers in the new section.
        void InitMap_ExpandMap( uint32_t address, uint32_t count );
	/// @brief Generates the map based on the sections that have been added with @ref ZMBQMap::InitMap_ExpandMap.
        void InitMap_Generate( );
	/// @brief Gets the pointer to the input registers at the given address.
	/// @param address The address to get a pointer to.
	/// @return A pointer to the desired input registers.  Can be null if the address is outside the bounds of the map.
        void* GetDataPointer_InputRegs( uint32_t address );
	/// @brief Gets the pointer to the holding registers at the given address.
	/// @param address The address to get a pointer to.
	/// @return A pointer to the desired holding registers.  Can be null if the address is outside the bounds of the map.
        void* GetDataPointer_HoldingRegs( uint32_t address );

    private:
	/// @brief The name of the map.
        std::string m_name;

	/// @brief The base address of the map.
        uint32_t m_baseAddress;
	/// @brief The size of the map in number of registers.
        uint32_t m_size;

	/// @brief The actual map data. Type is from libModbus.
        modbus_mapping_t* m_dataMap;
};

#endif
