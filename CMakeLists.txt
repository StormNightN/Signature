cmake_minimum_required(VERSION 3.13)
project(Signature)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O2 -Werror")

add_executable(Signature main.cpp
        DataChank.cpp
        DataChank.h
        Helpers.h
        Helpers.cpp
        FileReader.h
        FileReader.cpp
        WorkQueue.h)

#target_include_directories(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} ssl crypto)