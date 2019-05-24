#ifndef CONFIG_HPP__
#define CONFIG_HPP__

using namespace std;

#include <string>
#include <vector>
#include <map>

#include "jsoncpp/json/json.h"

#include "dataPoint.hpp"
#include "modbusMap.hpp"

class ZMBQConfig
{
    public:
        ZMBQConfig( );
        bool parseConfig( string filePath );

    private:
        void parseDataPoints( const Json::Value dataPoints );
        void parseMaps( const Json::Value maps );

        ZMBQDataPointCollection m_dataPoints;
        map<string, ZMBQMap> m_maps;
};

#endif