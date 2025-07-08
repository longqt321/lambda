cmake_minimum_required(VERSION 3.10)
project(lambda)

# Đặt chuẩn C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Thêm thư mục chưa header (.h)
include_directories(include)

# Thêm source files
file(GLOB SOURCES "src/*.cpp")


# Thêm executable và source files
add_executable(lambda main.cpp ${SOURCES})
