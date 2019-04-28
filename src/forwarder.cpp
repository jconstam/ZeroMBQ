#include <iostream>

#include "forwarder.hpp"

#include "zmq.hpp"

ZMQForwarder::ZMQForwarder( )
{

}

void ZMQForwarder::start( int subPort, int pubPort, string protocol = "tcp" )
{
    forwarderThread = thread( ZMQForwarder::forwarderTask, subPort, pubPort, protocol );
}

void ZMQForwarder::forwarderTask( int subPort, int pubPort, string protocol )
{
    string subEndpoint = protocol + "://*" + to_string( subPort );
    string pubEndpoint = protocol + "://*" + to_string( pubPort );

    try
    {
        void* context = zmq_ctx_new( );
        if( context == nullptr )
        {
            throw "Could not create ZMQ context";
        }

        void* subSocket = zmq_socket( context, ZMQ_XSUB );
        if( subSocket == nullptr )
        {
            throw "Could not create subscriber socket";
        }

        if( zmq_bind( subSocket, subEndpoint.c_str( ) ) != 0 )
        {
            throw "Could not bind subscriber to endpoint " + subEndpoint;
        }
        
        if( zmq_setsockopt( subSocket, ZMQ_SUBSCRIBE, "", 0 ) != 0 )
        {
            throw "Could not subscribe";
        }

        void* pubSocket = zmq_socket( context, ZMQ_XPUB );
        if( pubSocket == nullptr )
        {
            throw "Could not create subscriber socket";
        }

        if( zmq_bind( pubSocket, pubEndpoint.c_str( ) ) != 0 )
        {
            throw "Could not bind publisher to endpoint " + pubEndpoint;
        }

        zmq_proxy( subSocket, pubSocket, NULL );
    }
    catch( exception e )
    {
        cerr << "Exception in Forwarder: " << e.what( ) << endl;
    }
}