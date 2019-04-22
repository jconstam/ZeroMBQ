#ifndef CONFIG_HPP__
#define CONFIG_HPP__

using namespace std;

#include <string>
#include <vector>

#include "jsoncpp/json/json.h"

#include "slave.hpp"

class ZeroMBQConfig
{
    public:
        ZeroMBQConfig( );
        bool parseConfig( string );

    private:
        map<uint16_t, ZeroMBQSlave> m_slaveList;

        void parseSlaveConfig( const Json::Value );
};

#endif