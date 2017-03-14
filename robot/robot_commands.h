#ifndef ROBOTCOMMANDS_H
#define ROBOTCOMMANDS_H
#include "expect_list.h"
#include "measure_list.h"

class RobotCommands{
public:
    static RobotCommands* getRobotCommands() ;
    ~RobotCommands() ;
    //param name only from listwidget's item
    //so need not to check whether the param_name is contains in available list
    inline CommandFactory* getMeasureFactory(const QString& param_name){
        if(!this->_available_measure_data.contains(param_name))return NULL ;
        else return this->_measure_data_factory[param_name] ;
    }
    inline CommandFactory* getExpectFactory(const QString& param_name){
        if(!this->_available_expect_data.contains(param_name))return NULL ;
        else return this->_expect_data_factory[param_name] ;
    }


    inline QStringList getAvailableExpectData(){
        return this->_available_expect_data ;
    }
    inline QStringList getAvailableMeasureDate(){
        return this->_available_measure_data ;
    }
protected:
     RobotCommands() ;
private:
     static RobotCommands* _available_commands;
    //store names of available expect data type
    QStringList _available_expect_data ;
    QMap<QString,CommandFactory *> _expect_data_factory  ;

    //store names of available measure data type
    QStringList _available_measure_data ;
    QMap<QString,CommandFactory *> _measure_data_factory ;
};

#endif // ROBOTCOMMANDS_H
