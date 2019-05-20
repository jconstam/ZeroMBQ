#ifndef CONFIG_HPP__
#define CONFIG_HPP__

using namespace std;

#include <string>
#include <vector>
#include <map>

#include "jsoncpp/json/json.h"

#include "dataPoint.hpp"

class ZMBQConfig
{
    public:
        ZMBQConfig( );
        bool parseConfig( string filePath );

    private:
        void parseDataPoints( const Json::Value dataPoints );
        void parseMaps( const Json::Value maps );

        map<string, ZMBQDataPoint> m_dataPoints;
};

#endif