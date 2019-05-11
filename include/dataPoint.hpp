#ifndef DATAPOINT_HPP__
#define DATAPOINT_HPP__

using namespace std;

#include <string>

#include "data.hpp"

class ZMBQDataPoint
{
    public:
        ZMBQDataPoint( );
        ZMBQDataPoint( string, string );

    private:
        string m_name;
        DATA_TYPE m_type;
};

#endif