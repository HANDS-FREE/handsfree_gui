cmake_minimum_required(VERSION 2.8.3)
project(qcustomplot)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5PrintSupport)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
	.
)

 
 add_library(qcustomplot qcustomplot.h qcustomplot.cpp)


 target_link_libraries(qcustomplot
    Qt5::PrintSupport
    Qt5::Core
    Qt5::Widgets
 )



