#include "robot_commands.h"
#include <QMutex>
RobotCommands* RobotCommands::_available_commands = NULL ;

RobotCommands::RobotCommands()
{
    this->_available_expect_data<<"arm state"<<"global speed"
                               <<"head state"<<"motor parameter"
                              <<"motor speed"<<"robot speed" ;

    this->_expect_data_factory["arm state"] = new ExpectArmStateFactory() ;
    this->_expect_data_factory["global speed"] = new ExpectGlobalSpeedFactory() ;
    this->_expect_data_factory["head state"] = new ExpectHeadStateFactory() ;
    this->_expect_data_factory["motor parameter"] = new ExpectMotorParameterFactory() ;
    this->_expect_data_factory["motor speed"] = new ExpectMotorSpeedFactory() ;
    this->_expect_data_factory["robot speed"]= new ExpectRobotSpeedFactory() ;

    this->_available_measure_data<<"global coordinate"<<"robot coordinate"
                                <<"global speed"<<"moter speed"
                                <<"robot speed"<<"system information" ;

    this->_measure_data_factory["global coordinate"] = new MeasureGlobalCoordinateFactory() ;
    this->_measure_data_factory["robot coordinate"] = new MeasureRobotCoordinateFactory() ;
    this->_measure_data_factory["global speed"] = new MeasureGlobalspeedFactory() ;
    this->_measure_data_factory["moter speed"] = new MeasureMoterSpeedFactory() ;
    this->_measure_data_factory["robot speed"] = new MeasureRobotSpeedFactory() ;
    this->_measure_data_factory["system information"] = new MeasureSystemInfoFactory() ;
}

RobotCommands *RobotCommands::getRobotCommands()
{
    if(_available_commands==NULL){
        QMutex mutex ;
        mutex.lock();
        if(_available_commands==NULL){
            _available_commands = new RobotCommands() ;
        }
        mutex.unlock();
    }
    return _available_commands ;
}

RobotCommands::~RobotCommands()
{
    QMap<QString,CommandFactory*>::iterator it_commands ;
    for(it_commands = this->_expect_data_factory.begin();it_commands!=this->_expect_data_factory.end();it_commands++){
        delete it_commands.value() ;
    }
    for(it_commands = this->_measure_data_factory.begin();it_commands!=this->_measure_data_factory.end();it_commands++){
        delete it_commands.value() ;
    }
}
