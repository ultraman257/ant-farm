cmake_minimum_required(VERSION 3.23)
project(simulite)

set(CMAKE_CXX_STANDARD 14)

set(FLTK_DIR /mingw64/share/fltk)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

find_package(FLTK REQUIRED NO_MODULE)

add_executable(simulite WIN32 MACOSX_BUNDLE main.cpp Person.cpp)


target_link_libraries(simulite fltk)

#add_executable(simulite main.cpp)

#target_include_directories(${FLTK_INCLUDE_DIRS} public)

