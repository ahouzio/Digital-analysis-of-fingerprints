cmake_minimum_required(VERSION 3.0.0)
project(starter VERSION 0.1.0)

include(CTest)
enable_testing()

set(OpenCV_DIR "C:/Users/Ahouz/OneDrive/Bureau/opencv/build/x64/vc15/lib")
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

set(SRCS
    ./src/img.cpp
    ./src/main.cpp)

set(HEADER
    ./include/img.h)

add_executable(starter ${SRCS} ${HEADER})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXXçSTANDARD_REQUIRED ON)

include_directories(./include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(starter ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
