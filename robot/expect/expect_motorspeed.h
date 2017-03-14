#ifndef EXPECTMOTORSPEED_H
#define EXPECTMOTORSPEED_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectMotorSpeed : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectMotorSpeed(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_spinbox_servo1 = new QDoubleSpinBox() ;
        this->_spinbox_servo2 = new QDoubleSpinBox() ;
        this->_spinbox_servo3 = new QDoubleSpinBox() ;
        this->_spinbox_servo4 = new QDoubleSpinBox() ;

        this->_spinbox_servo1->setMinimum(-65536);
        this->_spinbox_servo2->setMinimum(-65536);
        this->_spinbox_servo3->setMinimum(-65536);
        this->_spinbox_servo4->setMinimum(-65536);

        this->_item_servo1 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo1"),
                                                           1,this->_spinbox_servo1
                                                           ) ;
        this->_item_servo2 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo2"),
                                                           1,this->_spinbox_servo2
                                                           ) ;
        this->_item_servo3 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo3"),
                                                           1,this->_spinbox_servo3
                                                           ) ;
        this->_item_servo4 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo4"),
                                                           1,this->_spinbox_servo4
                                                           ) ;
    }
    ~ExpectMotorSpeed(){
        delete _spinbox_servo1 ;
        delete _spinbox_servo2 ;
        delete _spinbox_servo3 ;
        delete _spinbox_servo4 ;

        delete _item_servo1 ;
        delete _item_servo2 ;
        delete _item_servo3 ;
        delete _item_servo4 ;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_motor_speed.servo1=this->_spinbox_servo1->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_motor_speed.servo2=this->_spinbox_servo2->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_motor_speed.servo3=this->_spinbox_servo3->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_motor_speed.servo4=this->_spinbox_servo4->value() ;

        RobotHardware::getRobotHardWare()->sendCommand(SET_MOTOR_SPEED);
    }
private:
    QTreeWidgetItem*  _item_servo1;
    QTreeWidgetItem*  _item_servo2;
    QTreeWidgetItem*  _item_servo3;
    QTreeWidgetItem*  _item_servo4;

    QDoubleSpinBox *_spinbox_servo1 ;
    QDoubleSpinBox *_spinbox_servo2 ;
    QDoubleSpinBox *_spinbox_servo3 ;
    QDoubleSpinBox *_spinbox_servo4 ;
};

class ExpectMotorSpeedFactory:public CommandFactory{
public:
    ExpectMotorSpeedFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectMotorSpeed(command_name,target_widget) ;
    }
} ;

#endif // EXPECTMOTORSPEED_H
