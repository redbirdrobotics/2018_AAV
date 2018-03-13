cmake_minimum_required(VERSION 3.5.1)
project(stereo)

#___COMPILER_OPTIONS_____________________

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -lX11 -g")

#___DEPENDENCIES_________________________

SET("OpenCV_DIR" "/usr/home/opencv")
SET(CMAKE_MODULE_PATH "/usr/home/opencv/modules")


#find_package(X11 REQUIRED)
find_package(OpenCV 3.3 REQUIRED)
#find_package(Boost COMPONENTS system filesystem thread REQUIRED)
find_package(OpenMP)
#find_package(Chrono REQUIRED)

#find_library(LIB_boost_system NAMES boost_system)
#find_library(LIB_boost_program_options NAMES boost_program_options)
#___FILE_GLOBBING________________________

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers inc/*.h)
file(GLOB_RECURSE headers inc/*.hpp)
#set(OpenCV_LIBS "opencv_core")

include_directories(inc)
#include_directories(${X11_INCLUDE_DIR})
include_directories($(OpenCV_INCLUDE_DIRS))
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_features2d opencv_ml opencv_highgui opencv_objdetect)
#if(NOT LIB_boost_system)
  #message(FATAL_ERROR "LIB_boost_system not found")
#else()
  #message(STATUS "===================")
  #message(STATUS ${LIB_boost_system})
  #message(STATUS ${LIB_boost_program_options})
  #message(STATUS "===================")
#endif()

#___EXECUTABLES__________________________

add_executable(stereo ${sources} ${headers})

#___TARGET_DEFINITIONS___________________

#set_target_properties(stereo PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(stereo ${OpenCV_LIBS} )
        #${LIB_boost_program_options}
        #${Boost_LIBRARIES}
        #${Boost_SYSTEM_LIBRARY}
        #${X11_LIBRARIES})
