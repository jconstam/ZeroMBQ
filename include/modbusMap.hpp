#ifndef MODBUSMAP_HPP__
#define MODBUSMAP_HPP__

using namespace std;

#include <string>

class ZMBQMap
{
    public:
        ZMBQMap( );
        ZMBQMap( string );

    private:
        string m_name;
};

#endif