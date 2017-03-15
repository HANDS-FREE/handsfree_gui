cmake_minimum_required(VERSION 2.8.3)
project(handsfree_hw)
find_package(Boost COMPONENTS REQUIRED system thread)
find_package(Qt5Core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
  include
  include/sdk/hf_link/
  include/sdk/robot_abstract/
  ${Boost_INCLUDE_DIRS}
)

 
 add_library(handsfree_qt_sdk src/transport_serial.cpp
                    include/sdk/hf_link/hf_link.cpp
                    include/handsfree_hw/hf_hw.h
                    include/sdk/hf_link/hf_link_state_machine.cpp src/hf_hw.cpp)


 target_link_libraries(handsfree_qt_sdk
   ${Boost_LIBRARIES}
    Qt5::Core
 )


