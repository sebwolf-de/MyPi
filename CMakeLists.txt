cmake_minimum_required(VERSION 3.10)

project(MyPi)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(mypi src/main.cpp)

find_package(MPI REQUIRED)
target_link_libraries(mypi PUBLIC MPI::MPI_CXX)
#build and link libraries and executable
#add_library(lib src/lib.cpp)
#target_link_libraries(main PUBLIC lib)

#target_include_directories(main PUBLIC include_path)


