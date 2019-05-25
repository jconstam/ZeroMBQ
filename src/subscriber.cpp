#include <iostream>

#include "data.hpp"
#include "subscriber.hpp"

using namespace std;
using namespace zmq;

static bool socketHasMoreData( void* socket )
{
    int hasData = false;
    size_t hasDataSize = 0;
    zmq_getsockopt( socket, ZMQ_RCVMORE, &( hasData ), &( hasDataSize ) );

    return ( ( hasDataSize > 0 ) && ( hasData == true ) );
}

ZMQSubscriber::ZMQSubscriber( int tcpPort )
{
    m_tcpPort = tcpPort;
    m_stopRequested = false;

    m_context = zmq_ctx_new( );
    m_subSocket = nullptr;
}

void ZMQSubscriber::start( vector<string> subscriptions, ZMBQDataPointCollection dataPoints )
{
    m_stopRequested = false;
    m_subThread = thread( &ZMQSubscriber::subThreadFunction, this, subscriptions, dataPoints );
}

void ZMQSubscriber::stop( )
{
    m_stopRequested = true;
    if( m_subSocket != nullptr )
    {
        zmq_close( m_subSocket );
    }

    m_subThread.join( );
}

void ZMQSubscriber::subThreadFunction( vector<string> subscriptions, ZMBQDataPointCollection dataPoints )
{
    m_subSocket = zmq_socket( m_context, ZMQ_SUB );

    for( auto &subTopic : subscriptions )
    {
        zmq_setsockopt( m_subSocket, ZMQ_SUBSCRIBE, &( subTopic ), subTopic.size( ) );
    }

    while( m_stopRequested != true )
    {
        char topicBuffer[ ZMQ_MAX_TOPIC_LEN ] = { 0 };
        uint8_t dataBuffer[ ZMQ_BUFFER_SIZE_MAX ] = { 0 };

        int topicSize = zmq_recv( m_subSocket, topicBuffer, ZMQ_MAX_TOPIC_LEN, 0 );
        if( topicSize <= 0 )
        {
            break;
        }

        if( socketHasMoreData( m_subSocket ) )
        {
            int dataSize = zmq_recv( m_subSocket, dataBuffer, ZMQ_BUFFER_SIZE_MAX, 0 );
            if( dataSize <= 0 )
            {
                break;
            }

            dataPoints.publishNewData( string( topicBuffer ), dataBuffer );
        }
    }
}