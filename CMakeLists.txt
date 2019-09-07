cmake_minimum_required(VERSION 3.13)
project(Signature)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic -O2 -Werror")

add_executable(Signature main.cpp
        DataChank.cpp
        includes/DataChank.h
        includes/Helpers.h
        Helpers.cpp
        includes/FileReader.h
        FileReader.cpp
        includes/WorkQueue.h
        includes/HashProcess.h
        HashProcess.cpp
        includes/FileWriter.h
        FileWriter.cpp
        includes/EmptyQueueException.h EmptyQueueException.cpp)

target_link_libraries(${PROJECT_NAME} ssl crypto)