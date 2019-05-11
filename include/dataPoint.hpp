#ifndef DATAPOINT_HPP__
#define DATAPOINT_HPP__

using namespace std;

#include <string>

#include "data.hpp"

template <typename T>
class ZMBQDataPoint
{
    public:
        ZMBQDataPoint( );
        ZMBQDataPoint( string name, T value );

    private:
        string m_name;
        DATA_TYPE m_type;
        T m_value;
};

#endif