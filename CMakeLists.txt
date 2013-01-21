cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)

# This is not used yet, but it will be soon ;-)
include_directories(.)
include_directories(clcc)
add_library( clew SHARED clcc/clew.c )
target_link_libraries( clew dl )

add_library( OpenCLHelper SHARED OpenCLHelper.cpp )
target_link_libraries( OpenCLHelper clew )

add_executable( gpuinfo gpuinfo.cpp )
target_link_libraries( gpuinfo clew )

add_executable( testopenclhelper test/testopenclhelper.cpp )
target_link_libraries( testopenclhelper clew OpenCLHelper )
