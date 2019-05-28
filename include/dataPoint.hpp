#ifndef DATAPOINT_HPP__
#define DATAPOINT_HPP__

/// @file dataPoint.hpp
/// @brief Contains classes for managing individual data points and collections of them.

#include <string>
#include <vector>
#include <map>

#include "data.hpp"

/// @brief Holds and manages a single data point.
class ZMBQDataPoint
{
    public:
	/// @brief Basic constructor.  Initializes a data point with the name "Unknown" and the type uint16_t.
        ZMBQDataPoint( );
	/// @brief Normal constructor.  Sets up @ref m_name, @ref m_type, @ref m_size, and initializes @ref m_dataLocations.
        ZMBQDataPoint( std::string name, std::string type );

	/// @brief Gets the data point's name.
	/// @return The value of @ref m_name.
        std::string name( ){ return m_name; };
	/// @brief Gets the size of the data point's value in bytes.
	/// @return The value of @ref m_size;
        int size_bytes( ){ return m_size; };
	/// @brief Gets the size of the data point's value in registers (uint16_t).
	/// @return The value of @ref m_size divided by the size of uint16_t.
        int size_registers( ){ return m_size / sizeof( uint16_t ); };

	/// @brief Adds a data location to the data point's list of destination pointers.
	/// @param dataPointer Pointer to the data location.
        void addDataLocation( void* dataPointer );
	/// @brief Publishes new data to all of the destination pointers.
	/// @param dataMessage Pointer to the new data received from ZeroMQ.
        void publish( void* dataMessage );

    private:
	/// @brief Contains the name of the data point.
        std::string m_name;
	/// @brief Contains the @ref DATA_TYPE type of the data point.
        DATA_TYPE m_type;
	/// @brief Contains the size of the data point value in bytes.
        int m_size;
	/// @brief std::vector containing the list of destination pointers.
        std::vector<void*> m_dataLocations;
};

/// @brief A collection of @ref ZMBQDataPoint objects.
class ZMBQDataPointCollection
{
    public:
	/// @brief Generic constructor.  Currently does nothing.
        ZMBQDataPointCollection( );

	/// @brief Operator overload for the indexing operator.
	/// @param name The name of the data point to retrieve.
	/// @return The @ref ZMBQDataPoint object with the given name.
        ZMBQDataPoint &operator[]( std::string name );

	/// @brief Adds a new @ref ZMBQDataPoint object to the collection.
	/// @param newDataPoint The @ref ZMBQDataPoint object to be added.
        void addDataPoint( ZMBQDataPoint newDataPoint );
	/// @brief Checks if the collection contains an @ref ZMBQDataPoint object with the given name.
	/// @param name The name of the @ref ZMBQDataPoint object to look for.
	/// @return true - The data point exists in the collection.
	/// @return false - The data point does not exist in the collection.
        bool dataPointExists( std::string name );

	/// @brief Calls the @ref ZMBQDataPoint::publish function for the @ref ZMBQDataPoint object with the given name.
	/// @param topic The ZeroMQ topic that was received.  Corresponds to the name of the data point.
	/// @param buffer The ZeroMQ data buffer that was received.
        void publishNewData( std::string topic, uint8_t* buffer );
    
    private:
	/// @brief std::map containing the data points.
        std::map<std::string, ZMBQDataPoint> m_dataPoints;
};

#endif
