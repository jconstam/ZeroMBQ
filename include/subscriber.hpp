#ifndef SUBSCRIBER_HPP__
#define SUBSCRIBER_HPP__

#include <thread>
#include <vector>
#include <string>

#include <zmq.hpp>

#include "dataPoint.hpp"

class ZMQSubscriber
{
    public:
        ZMQSubscriber( int tcpPort );

        void start( std::vector<std::string> subscriptions, ZMBQDataPointCollection dataPoints );
        void stop( );

    private:
        int m_tcpPort;
        std::thread m_subThread;
        bool m_stopRequested;

        void* m_context;
        void* m_subSocket;

        void subThreadFunction( std::vector<std::string> subscriptions, ZMBQDataPointCollection dataPoints );
};

#endif