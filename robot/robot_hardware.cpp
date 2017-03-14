#include "robot_hardware.h"
#include <QMutex>
#include <QDebug>
handsfree_hw::HF_HW* RobotHardware::_robot_hardware = NULL ;
std::string RobotHardware::_default_port="serial:///dev/ttyUSB0" ;
std::string RobotHardware::_default_filename = "/home/liao/Documents/handsfree/gui/config.txt" ;
ThreadRead* RobotHardware::_thread_read = NULL ;

RobotHardware::~RobotHardware()
{

}

//single
handsfree_hw::HF_HW *RobotHardware::getRobotHardWare()
{
    if(_robot_hardware==NULL){
        QMutex mutex ;
        mutex.lock();
        if(_robot_hardware==NULL){
            _robot_hardware = new handsfree_hw::HF_HW(_default_port,
                                                      _default_filename) ;
        }
        mutex.unlock();
    }
    return _robot_hardware ;
}

ThreadRead *RobotHardware::getReadThread()
{
    if(_thread_read==NULL){
        QMutex mutex ;
        mutex.lock();
        if(_thread_read==NULL){
            _thread_read = new ThreadRead() ;
        }
        mutex.unlock();
    }
    return _thread_read ;
}

bool RobotHardware::isRobotOpened()
{
    if(NULL==_robot_hardware)return false ;
    return true ;
}

void RobotHardware::launchRobot()
{
    RobotHardware::launchRobot(RobotHardware::_default_port,RobotHardware::_default_filename);
}

void RobotHardware::launchRobot(std::string port_name){
    RobotHardware::launchRobot(port_name,RobotHardware::_default_filename);
}

void RobotHardware::launchRobot(std::string port_name, std::string filename){
    if(!RobotHardware::isRobotOpened()){
    _robot_hardware = new handsfree_hw::HF_HW(port_name,
                                              filename) ;
    }
    else{
        RobotHardware::closeRobot();
        _robot_hardware = new handsfree_hw::HF_HW(port_name,
                                                  filename) ;
    }
}

void RobotHardware::closeRobot()
{
    if(_robot_hardware!=NULL)delete _robot_hardware ;
    _robot_hardware = NULL ;
}



