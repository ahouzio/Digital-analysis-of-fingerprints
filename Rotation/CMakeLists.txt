cmake_minimum_required(VERSION 3.5)
project(starter-main2)

set(CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package( OpenCV REQUIRED)
include_directories( ./include ${OpenCV_INCLUDE_DIRS} )

set(SRCS
	./src/rotation.cpp
	./src/warp.cpp
	./src/main.cpp
	)
set(SRCS_ROT
	./src/rotation.cpp
	./src/main_starter.cpp
	)

set(HEADERS
	./include/rotation.hpp
	./include/warp.hpp
	)
set(HEADERS_ROT
	./include/rotation.hpp
	)

add_executable(bin ${SRCS} ${HEADERS} )
add_executable(rotation ${SRCS_ROT} ${HEADERS_ROT} )
target_link_libraries( bin ${OpenCV_LIBS} )
target_link_libraries( rotation ${OpenCV_LIBS} )

