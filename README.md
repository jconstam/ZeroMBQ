# ZeroMBQ
A [ZeroMQ](https://github.com/zeromq) Modbus server.  This library provides a system for bridging a ZeroMQ publish-subscribe network to a Modbus server/client network.

[![Build Status](https://travis-ci.org/jconstam/ZeroMBQ.svg?branch=master)](https://travis-ci.org/jconstam/ZeroMBQ)

# Dependencies
* [CMake](https://cmake.org/) 3.5 or later
* [ZeroMQ](http://zeromq.org/) 4.1 or later
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp) 1.7 or later 
* [libModbus](https://libmodbus.org/) 3.0.6 or later

# Goals
* Support user defined mapping of tag values to registers
* Good performance in an embedded (Linux) environment for the most used operations (ZeroMQ publish, Modbus Read)
* Scalable to >10k registers/tags
* Support multiple modbus maps simultaneously
* Support Modbus TCP and RTU

# Documentation
See [Doxygen documentation](https://jconstam.github.io/ZeroMBQDocs/)
