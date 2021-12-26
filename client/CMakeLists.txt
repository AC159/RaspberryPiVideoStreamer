cmake_minimum_required(VERSION 3.18.4)
project(VideoStreamerClient)

set(CMAKE_CXX_STANDARD 20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(VideoStreamerClient main.cpp utils/socketBuffer.cpp)
target_link_libraries( VideoStreamerClient ${OpenCV_LIBS} )
