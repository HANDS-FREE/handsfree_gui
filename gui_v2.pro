#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T15:03:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_v2
TEMPLATE = app
LIBS += -lboost
            -L $$PWD/ -lhandsfree_hw -lqcustomplot

INCLUDEPATH += sdk/ \
                               sdk/handsfree_sdk

SOURCES += main.cpp\
        mainwindow.cpp\
        util/widget/switch_button.cpp\
        util/widget/radar_pos.cpp\
        util/sliding/sliding_moudle.cpp\
        util/sliding/sliding_stackedwidget.cpp\
        robot/robot_hardware.cpp\
        robot/robot_commands.cpp\
        robot/read_thread.cpp

HEADERS  += mainwindow.h\
        util/widget/switch_button.h\
        util/widget/radar_pos.h\
        util/sliding/sliding_moudle.h\
        util/sliding/sliding_stackedwidget.h\
        util/factory/linefactory.h\
        util/factory/treeitem_factory.h\
        robot/robot_hardware.h\
        robot/expect_list.h\
        robot/measure_list.h\
        robot/command.h\
        robot/robot_commands.h\
        robot/command_factory.h\
        robot/read_thread.h\

        robot/measure/measure_moterspeed.h
#        robot/measure/measure_robotspeed.h\
#        robot/measure/measure_systeminfo.h\
#        robot/measure/measure_globalspeed.h\
#        robot/measure/measure_robotcoordinate.h\
#        robot/measure/measure_globalcoordinate.h

#        robot/expect/expect_motorparameter.h\
#        robot/expect/expect_motorspeed.h\
#        robot/expect/expect_robotspeed.h\
#        robot/expect/expect_globalspeed.h\
#        robot/expect/expect_headstate.h\
#        robot/expect/expect_armstate.h

FORMS    += mainwindow.ui
RESOURCES += \
    image/image.qrc
