#ifndef ROBOTHARDWARE_H
#define ROBOTHARDWARE_H

#include <handsfree_hw/hf_hw.h>
#include "read_thread.h"
class RobotHardware
{
public:
    ~RobotHardware() ;
    static handsfree_hw::HF_HW *getRobotHardWare() ;
    static ThreadRead *getReadThread() ;

    static bool isRobotOpened() ;
    static void closeRobot() ;
    static void launchRobot() ;
    static void launchRobot(std::string port_name,std::string filename) ;
    static void launchRobot(std::string port_name) ;

private:
    RobotHardware(){}
    RobotHardware operator =(const RobotHardware &){}
private:
    static handsfree_hw::HF_HW *_robot_hardware ;
    static ThreadRead* _thread_read ;
    static std::string _default_port ;
    static std::string _default_filename ;

};


#endif // ROBOTHARDWARE_H
