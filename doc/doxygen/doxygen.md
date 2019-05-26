# ZeroMBQ {#mainpage}
[TOC]

## Introduction
A [ZeroMQ](https://github.com/zeromq) Modbus server.  This library provides a system for bridging a ZeroMQ publish-subscribe network to a Modbus server/client network.

## Dependencies
### Build
* [CMake](https://cmake.org/) 3.5 or later

### Library
* [ZeroMQ](http://zeromq.org/) 4.1 or later
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp) 1.7 or later 
* [libModbus](https://libmodbus.org/) 3.0.6 or later

### Other
* [Doxygen](http://www.doxygen.nl/index.html) 1.8 or later
* [GCovr](https://www.gcovr.com/en/stable/) 4.1 or later

## Code
|Code File|Header File|
|:-------:|:---------:|
|[config.cpp](@ref config.cpp)|[config.hpp](@ref config.hpp)|
|[data.cpp](@ref data.cpp)|[data.hpp](@ref data.hpp)|
|[dataPoint.cpp](@ref dataPoint.cpp)|[dataPoint.hpp](@ref dataPoint.hpp)|
|[modbusMap.cpp](@ref modbusMap.cpp)|[modbusMap.hpp](@ref modbusMap.hpp)|
|[subscriber.cpp](@ref subscriber.cpp)|[subscriber.hpp](@ref subscriber.hpp)|

## Code Metrics
* [Unit Test Coverage](@ref test_coverage)