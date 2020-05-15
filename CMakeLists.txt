cmake_minimum_required(VERSION 3.15)
set ( PROJECT_VERSION 0.0.1)
set ( PROJECT_DESCRIPTION  "Read & write INI-Files")
# Set the variable PROJ_NAME to whatever your library's name is, PROJECT_VERSION should be a version string like "0.1"
project(INIParser VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION})

set(CMAKE_CXX_STANDARD 17)

add_library(ini SHARED ini.cpp ini.h)
set_target_properties(ini PROPERTIES PREFIX "")