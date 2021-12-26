cmake_minimum_required(VERSION "3.16.3")
enable_language(CXX)

project("VideoStreamer")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(VideoStreamer main.cpp  utils/socket/makeSocket.cpp utils/image/sendImage.cpp)
target_link_libraries(VideoStreamer ${OpenCV_LIBS})
