#ifndef FORWARDER_HPP__
#define FORWARDER_HPP__

#include <string>
#include <thread>

using namespace std;

class ZMQForwarder
{
    public:
        ZMQForwarder( );

        void start( int subPort, int pubPort, string protocol );
    
    private:
        thread forwarderThread;

        static void forwarderTask( int subPort, int pubPort, string protocol );
};

#endif