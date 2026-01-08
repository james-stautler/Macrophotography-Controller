cmake_minimum_required(VERSION 3.10)
project(MacroLab)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GPHOTO2 REQUIRED libgphoto2)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)
add_subdirectory(src)
