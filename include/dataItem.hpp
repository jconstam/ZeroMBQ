#ifndef DATAITEM_HPP__
#define DATAITEM_HPP__

using namespace std;

#include <string>

#include "data.hpp"

class ZeroMBQDataItem
{
    public:
        ZeroMBQDataItem( int, string, string, string );

    private:
        uint16_t m_address;
        string m_tag;
        DATA_TYPE m_type;
        ConvertFunc m_convertFunc;
};

#endif