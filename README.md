# ZeroMBQ
A [ZeroMQ](https://github.com/zeromq) Modbus server.  This library provides a system for bridging a ZeroMQ publish-subscribe network to a Modbus server/client network.

[![Build Status](https://travis-ci.org/jconstam/ZeroMBQ.svg?branch=master)](https://travis-ci.org/jconstam/ZeroMBQ)

# Dependencies
* CMake 3.5 or later
* ZeroMQ 4.1 or later
* JsonCpp 1.7 or later 

# Goals
* Support user defined mapping of tag values to registers
* Good performance in an embedded (Linux) environment for the most used operations (ZeroMQ publish, Modbus Read)
* Scalable to >10k registers/tags
* Support multiple modbus maps simultaneously
* Support Modbus TCP and RTU

# Documentation
See the doc folder
