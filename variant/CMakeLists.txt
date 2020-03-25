cmake_minimum_required(VERSION 3.13)
project(fc_variant)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(fc_variant main.cpp variant.cpp hex.cpp base64.cpp string.cpp export_c.h export_c.cpp)