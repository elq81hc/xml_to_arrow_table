cmake_minimum_required(VERSION 3.13)        # CMake version check

project(xml_to_arrow_table)                 # Create project "xml_to_arrow_table"
set(CMAKE_CXX_STANDARD 11)                  # Enable c++11 standard

if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
# arrow apache
find_package(Arrow REQUIRED)
# tinyxml2
find_package(tinyxml2 CONFIG REQUIRED)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(xml2arrowtable ${SOURCE_FILES})
target_link_libraries(xml2arrowtable PRIVATE 
    arrow_shared
    tinyxml2::tinyxml2
)