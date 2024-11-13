cmake_minimum_required(VERSION 3.29)
project(PlanificationCPP)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_DEBUG "$ {CMAKE_CXX_FLAGS_DEBUG} -g -oo")
add_executable(PlanificationCPP main.cpp
        FCFS.h
        SJF.h
        RR.h
        RRP.h
        SRTF.h
        Processus.h)
