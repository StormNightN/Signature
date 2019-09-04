cmake_minimum_required(VERSION 3.13)
project(Signature)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenSSL REQUIRED)

add_executable(Signature main.cpp DataChank.cpp DataChank.h Helpers.h Helpers.cpp FileReader.h FileReader.cpp WorkQueue.h WorkQueue.cpp)
#target_include_directories(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} ssl crypto)