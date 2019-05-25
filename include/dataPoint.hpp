#ifndef DATAPOINT_HPP__
#define DATAPOINT_HPP__

using namespace std;

#include <string>
#include <vector>
#include <map>

#include "data.hpp"

class ZMBQDataPoint
{
    public:
        ZMBQDataPoint( );
        ZMBQDataPoint( std::string name, std::string type );

        std::string name( ){ return m_name; };
        int size_bytes( ){ return m_size; };
        int size_registers( ){ return m_size / sizeof( uint16_t ); };

        void addDataLocation( void* dataPointer );
        void publish( void* dataMessage );

    private:
        std::string m_name;
        DATA_TYPE m_type;
        int m_size;
        std::vector<void*> m_dataLocations;
};

class ZMBQDataPointCollection
{
    public:
        ZMBQDataPointCollection( );

        ZMBQDataPoint &operator[]( std::string name );

        void addDataPoint( ZMBQDataPoint newDataPoint );
        bool dataPointExists( std::string name );

        void publishNewData( std::string topic, uint8_t* buffer );
    
    private:
        std::map<std::string, ZMBQDataPoint> m_dataPoints;
};

#endif