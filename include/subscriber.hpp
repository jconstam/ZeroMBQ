#ifndef SUBSCRIBER_HPP__
#define SUBSCRIBER_HPP__

/// @file subscriber.hpp
/// @brief Contains a class which manages a set of ZeroMQ subscriptions.

#include <thread>
#include <vector>
#include <string>

#include <zmq.hpp>

#include "dataPoint.hpp"

/// @brief A class which manages receiving ZeroMQ subscriptions and translating them to Modbus registers.
class ZMQSubscriber
{
    public:
	/// @brief Constructor.  Initializes @ref m_tcpPort to the specified port.  Gets the ZeroMQ context in @ref m_context. 
	/// @param tcpPort The TCP port that the ZeroMQ socket should be bound to.
        ZMQSubscriber( int tcpPort );

	/// @brief Starts the subscriber task.
	/// @param subscriptions std::vector containing subscriptions (which are std::string)
	/// @param dataPoints @ref ZMBQDataPointCollection containing data points to publish data to.
        void start( std::vector<std::string> subscriptions, ZMBQDataPointCollection dataPoints );
	/// @brief Stops the subscriber task.
        void stop( );

    private:
	/// @brief The TCP port to bind the ZeroMQ subscriber socket to.
        int m_tcpPort;
	/// @brief std::thread which runs to collect subscription data.
        std::thread m_subThread;
	/// @brief Set in @ref ZMQSubscriber::stop to indicate the thread is requested to stop.
        bool m_stopRequested;

	/// @brief Contains the ZeroMQ context.  Set in @ref ZMQSubscriber::ZMQSubscriber.
        void* m_context;
	/// @brief The subscriber's ZeroMQ socket.
        void* m_subSocket;

	/// @brief The function to be run in the subscriber thread.
	/// @param subscriptions std::vector containing subscriptions (which are std::string)
	/// @param dataPoints @ref ZMBQDataPointCollection containing data points to publish data to.
        void subThreadFunction( std::vector<std::string> subscriptions, ZMBQDataPointCollection dataPoints );

	/// @brief Indicates whether the ZeroMQ socket has more data available.
	/// @param socket The ZeroMQ subscriber socket.
	/// @return true The ZeroMQ subscriber socket has more data.
	/// @return false The ZeroMQ subscriber socket does not have more data.
	static bool socketHasMoreData( void* socket );
};

#endif
