#include "read_thread.h"
#include "robot/robot_hardware.h"
#include <QDebug>
ThreadRead::ThreadRead(QObject *parent) :
    QThread(parent),
    _stop_read(false)
{
    this->_mutex_stop = new QMutex() ;
}

ThreadRead::~ThreadRead()
{
    delete this->_mutex_stop ;
}

void ThreadRead::run()
{
    this->_mutex_stop->lock();
    this->_stop_read = false ;
    this->_mutex_stop->unlock();
    for(;;){
        msleep(200);
        this->_mutex_stop->lock();
        if(this->_stop_read){
            this->_mutex_stop->unlock();
            emit stopRead()  ;
            break ;
        }
        this->_mutex_stop->unlock();
        if(!RobotHardware::getRobotHardWare()->initialize_ok())continue;
        RobotHardware::getRobotHardWare()->updateRobot();
        qDebug()<<RobotHardware::getRobotHardWare()->getRobotAbstract()->measure_global_coordinate.x
               <<"  "<<RobotHardware::getRobotHardWare()->getRobotAbstract()->measure_global_coordinate.y
              <<"  "<<RobotHardware::getRobotHardWare()->getRobotAbstract()->measure_global_coordinate.z ;
        emit newMsgGet();
    }
}

void ThreadRead::stop()
{
    this->_mutex_stop->lock();
    this->_stop_read = true ;
    this->_mutex_stop->unlock();
}

