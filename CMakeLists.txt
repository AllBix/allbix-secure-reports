cmake_minimum_required(VERSION 3.28)
project(SecureIncidentReporter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SecureIncidentReporter
        incident_reporter.cpp
        incident_reporter.h
        main.cpp)
