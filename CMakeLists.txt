cmake_minimum_required(VERSION 3.5)
project(Exe)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fexceptions -g -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}")


set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS regex system)

include_directories(
    include    
    )

if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_library(${PROJECT_NAME} 
            SHARED
            src/firstCode.cpp)
link_libraries()

target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES} boost_program_options)

# target_link_libraries(${PROJECT_NAME} "/usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.65.1" ${Boost_LIBRARIES})


add_executable(firstCode src/firstCode.cpp)
target_link_libraries(firstCode  ${PROJECT_NAME})



