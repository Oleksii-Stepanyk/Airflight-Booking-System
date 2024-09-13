cmake_minimum_required(VERSION 3.29)
project(Airflight_Booking_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Airflight_Booking_System main.cpp
        Classes/Ticket.cpp
        Classes/Ticket.h
        Classes/Airplane.cpp
        Classes/Airplane.h
        Classes/AirlineSystemManager.cpp
        Classes/AirlineSystemManager.h
        Classes/FileHandler.cpp
        Classes/FileHandler.h
        Classes/Text.cpp
        Classes/Text.h
        Classes/FileReader.cpp
        Classes/FileReader.h)
