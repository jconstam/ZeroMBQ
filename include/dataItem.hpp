#ifndef DATAITEM_HPP__
#define DATAITEM_HPP__

using namespace std;

#include <string>

#include "data.hpp"

class ZeroMBQDataItem
{
    public:
        ZeroMBQDataItem( int, string, string, string );

        uint16_t getAddress( ) const;
        string getTag( ) const;
        DATA_TYPE getType( ) const;
        ConvertFromZMQFunc getConvertFromZMQFunc( ) const;
        ConvertToZMQFunc getConvertToZMQFunc( ) const;

        bool convertFromZMQ( void* rawData, uint8_t* outBuffer, uint32_t bufferIndex, uint32_t bufferSize );
        bool convertToZMQ( void* value, void* buffer, uint32_t bufferSize );

    private:
        uint16_t m_address;
        string m_tag;
        DATA_TYPE m_type;
        ConvertFromZMQFunc m_convertFromZMQFunc;
        ConvertToZMQFunc m_convertToZMQFunc;
};

#endif