cmake_minimum_required(VERSION 2.6)
   PROJECT (main)


find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


#file(GLOB_RECURSE main_SOURCES "*.cpp")
#file(GLOB_RECURSE main_HEADERS "*.h")

#add_library(source "Volume.cpp")


add_executable(main "super_voxels.cpp")


target_link_libraries(main ${ITK_LIBRARIES})
#target_link_libraries (main source)

