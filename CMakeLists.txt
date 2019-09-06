cmake_minimum_required(VERSION 3.13)
project(Signature)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic -O2 -Werror")

add_executable(Signature main.cpp
        DataChank.cpp
        DataChank.h
        Helpers.h
        Helpers.cpp
        FileReader.h
        FileReader.cpp
        WorkQueue.h
        HashProcess.h
        HashProcess.cpp
        FileWriter.h
        FileWriter.cpp
        )

target_link_libraries(${PROJECT_NAME} ssl crypto)