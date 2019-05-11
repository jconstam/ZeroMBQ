#include "dataPoint.hpp"

// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
template class ZMBQDataPoint<uint16_t>;
template class ZMBQDataPoint<uint32_t>;
template class ZMBQDataPoint<float>;

template <typename T>
ZMBQDataPoint<T>::ZMBQDataPoint( ) : ZMBQDataPoint( "Unknown", 0 )
{
    
}

template <typename T>
ZMBQDataPoint<T>::ZMBQDataPoint( string name, T value )
{
    m_name = name;
    m_value = value;
}
