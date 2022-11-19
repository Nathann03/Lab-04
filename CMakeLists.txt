cmake_minimum_required(VERSION 3.5)

project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()


set( PROJECT_CPP_SOURCES
  Source.cpp
  )


add_executable(${PROJECT_NAME} ${PROJECT_CPP_SOURCES})
target_link_libraries(
 ${PROJECT_NAME}
)

