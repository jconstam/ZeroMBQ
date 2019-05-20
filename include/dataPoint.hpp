#ifndef DATAPOINT_HPP__
#define DATAPOINT_HPP__

using namespace std;

#include <string>
#include <vector>

#include "data.hpp"

using namespace std;

class ZMBQDataPoint
{
    public:
        ZMBQDataPoint( );
        ZMBQDataPoint( string name, string type );

        int size_bytes( ){ return m_size; };
        int size_registers( ){ return m_size / sizeof( uint16_t ); };

        void addDataLocation( void* dataPointer );

    private:
        string m_name;
        DATA_TYPE m_type;
        int m_size;
        uint8_t* m_valueArray;
        vector<void*> m_dataLocations;
};

#endif