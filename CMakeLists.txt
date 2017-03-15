cmake_minimum_required(VERSION 2.8.3)
project(handsfree_gui_v2)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5PrintSupport)
find_package(Qt5SerialPort)
find_package(Boost COMPONENTS REQUIRED system thread)

add_subdirectory(./lib/handsfree_hw)
add_subdirectory(./lib/qcustomplot)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(EXECUTABLE_OUTPUT_PATH  "${PROJECT_SOURCE_DIR}/bin")


set(handsfree_gui_SRCS
    mainwindow/main.cpp
    mainwindow/mainwindow.cpp

    widget_control/widget_control.cpp

    widget_param/widget_param.cpp

    widget_visualization/widget_visualization.cpp
    widget_visualization/widget_plot.cpp

    widget_command/widget_command.cpp

    util/widgets/combobox_serial.cpp
    util/widgets/availablecommand_list.cpp
    util/widgets/switch_button.cpp
    util/widgets/radar_pos.cpp
    util/widgets/button_listwidgetitem.cpp
    util/sliding/sliding_moudle.cpp
    util/sliding/sliding_stackedwidget.cpp

    robot/robot_hardware.cpp
    robot/robot_commands.cpp
    robot/read_thread.cpp
)

set(handsfree_gui_moc_HDRS

)

set(handsfree_gui_HDRS
    mainwindow/mainwindow.h

    widget_control/widget_control.h

    widget_param/widget_param.h
    widget_visualization/widget_visualization.h
    widget_visualization/widget_plot.h

    widget_command/widget_command.h

    util/sliding/sliding_moudle.h
    util/sliding/sliding_stackedwidget.h
    util/widgets/combobox_serial.h
    util/widgets/availablecommand_list.h
    util/widgets/switch_button.h
    util/widgets/radar_pos.h
    util/widgets/button_listwidgetitem.h
    util/factory/linefactory.h
    util/factory/treeitem_factory.h

    robot/robot_hardware.h
    robot/expect_list.h
    robot/measure_list.h
    robot/command.h
    robot/robot_commands.h
    robot/command_factory.h
    robot/read_thread.h

    robot/measure/measure_moterspeed.h
    robot/measure/measure_robotspeed.h
    robot/measure/measure_systeminfo.h
    robot/measure/measure_globalspeed.h
    robot/measure/measure_robotcoordinate.h
    robot/measure/measure_globalcoordinate.h

    robot/expect/expect_motorparameter.h
    robot/expect/expect_motorspeed.h
    robot/expect/expect_robotspeed.h
    robot/expect/expect_globalspeed.h
    robot/expect/expect_headstate.h
    robot/expect/expect_armstate.h
)

set(handsfree_gui_UIS
    mainwindow/ui/mainwindow.ui
    widget_control/ui/widget_control.ui
    widget_param/ui/widget_param.ui
    widget_visualization/ui/widget_visualization.ui
    widget_command/ui/widget_command.ui

    util/ui/button_listwidgetitem.ui
    util/ui/availablecommand_list.ui
)

set(handsfree_gui_RCC
    image/image.qrc
)
link_directories(.)
INCLUDE_DIRECTORIES(
	sdk/
        sdk/handsfree_sdk/
        ${QT_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
)


QT5_ADD_RESOURCES(handsfree_RESOURCES_CPP ${handsfree_gui_RCC})
QT5_WRAP_CPP(handsfree_MOCS ${handsfree_gui_moc_HDRS})
QT5_WRAP_UI(handsfree_UIS_H ${handsfree_gui_UIS})

ADD_EXECUTABLE(handsfree_gui_v2 ${handsfree_gui_SRCS} ${handsfree_UIS_H} ${handsfree_MOCS}
                                                ${handsfree_RESOURCES_CPP} ${handsfree_gui_HDRS})
target_link_libraries(handsfree_gui_v2 handsfree_qt_sdk qcustomplot Qt5::SerialPort Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport
                                                        ${Boost_LIBRARIES})


