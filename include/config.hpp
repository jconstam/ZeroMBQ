#ifndef CONFIG_HPP__
#define CONFIG_HPP__

/// @file config.hpp
/// @brief Contains a class for parsing the system config file and apply it to the system.

#include <string>
#include <vector>
#include <map>

#include "jsoncpp/json/json.h"

#include "dataPoint.hpp"
#include "modbusMap.hpp"

/// @brief Manages the system configuration.
class ZMBQConfig
{
    public:
	/// @brief Basic constructor.  Currently does nothing.
        ZMBQConfig( );
	/// @brief Parses the configuration file at the given path.  Sets internal members based on the contents of the file.
	/// @param filePath The absolute path of the configuration file.
	/// @return true - The configuration is valid and loaded.
	/// @return false - An error occurred loading the configuration file.
        bool parseConfig( std::string filePath );

    private:
	/// @brief Parses all of the data points at the given JSON node.
	/// @param dataPoints A JSON node containing a list of data points.
        void parseDataPoints( const Json::Value dataPoints );
	/// @brief Parses all of the maps at the given JSON node.
	/// @param maps a JSON node containing a list of data points.
        void parseMaps( const Json::Value maps );

	/// @brief @ref ZMBQDataPointCOllection containing all of the data points in the configuration.
        ZMBQDataPointCollection m_dataPoints;
	/// @brief std::map containing all of the maps in the configuration.
        std::map<std::string, ZMBQMap> m_maps;
};

#endif
