#ifndef EXPECTMOTORPARAMETER_H
#define EXPECTMOTORPARAMETER_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectMotorParameter : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectMotorParameter(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_spinbox_id = new QSpinBox();
        this->_spinbox_encode_num = new QDoubleSpinBox();
        this->_spinbox_pwm_max = new QDoubleSpinBox();
        this->_spinbox_pwm_dead_zone = new QDoubleSpinBox();
        this->_spinbox_speed_low_filter = new QDoubleSpinBox();
        this->_spinbox_protect_current = new QDoubleSpinBox();
        this->_spinbox_pid_p1 = new QDoubleSpinBox();
        this->_spinbox_pid_i1 = new QDoubleSpinBox();
        this->_spinbox_pid_d1 = new QDoubleSpinBox();
        this->_spinbox_pid_p2 = new QDoubleSpinBox();
        this->_spinbox_pid_i2 = new QDoubleSpinBox();
        this->_spinbox_pid_d2 = new QDoubleSpinBox();


        this->_item_moter_id = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("moter_id"),
                                                           1,this->_spinbox_id
                                                           ) ;
        this->_item_encode_num = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("encode_num"),
                                                           1,this->_spinbox_encode_num
                                                           ) ;
        this->_item_pwm_max = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pwm_max"),
                                                           1,this->_spinbox_pwm_max
                                                           ) ;
        this->_item_pwm_dead_zone = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pwm_dead_zone"),
                                                           1,this->_spinbox_pwm_dead_zone
                                                           ) ;
        this->_item_speed_low_filter = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("speed_low_filter"),
                                                           1,this->_spinbox_speed_low_filter
                                                           ) ;
        this->_item_protect_current = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("protect_current"),
                                                           1,this->_spinbox_protect_current
                                                           ) ;
        this->_item_pid_p1 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_p1"),
                                                           1,this->_spinbox_pid_p1
                                                           ) ;
        this->_item_pid_i1 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_i1"),
                                                           1,this->_spinbox_pid_i1
                                                           ) ;
        this->_item_pid_d1 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_d1"),
                                                           1,this->_spinbox_pid_d1
                                                           ) ;
        this->_item_pid_p2 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_p2"),
                                                           1,this->_spinbox_pid_p2
                                                           ) ;
        this->_item_pid_i2 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_i2"),
                                                           1,this->_spinbox_pid_i2
                                                           ) ;
        this->_item_pid_d2 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pid_d2"),
                                                           1,this->_spinbox_pid_d2
                                                           ) ;
    }
    ~ExpectMotorParameter(){
        delete _spinbox_id ;
        delete _spinbox_encode_num ;
        delete _spinbox_pwm_max ;
        delete _spinbox_pwm_dead_zone ;
        delete _spinbox_speed_low_filter ;
        delete _spinbox_protect_current ;
        delete _spinbox_pid_p1 ;
        delete _spinbox_pid_i1 ;
        delete _spinbox_pid_d1 ;
        delete _spinbox_pid_p2 ;
        delete _spinbox_pid_i2 ;
        delete _spinbox_pid_d2 ;

        delete  _item_moter_id ;
        delete  _item_encode_num ;
        delete  _item_pwm_max ;
        delete  _item_pwm_dead_zone ;
        delete  _item_speed_low_filter ;
        delete  _item_protect_current ;
        delete  _item_pid_p1 ;
        delete  _item_pid_i1 ;
        delete  _item_pid_d1 ;
        delete  _item_pid_p2 ;
        delete  _item_pid_i2 ;
        delete  _item_pid_d2 ;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.motor_id = this->_spinbox_id->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.encoder_num = this->_spinbox_encode_num->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.protect_current = this->_spinbox_protect_current->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pwm_dead_zone = this->_spinbox_pwm_dead_zone->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pwm_max = this->_spinbox_pwm_max->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.speed_low_filter = this->_spinbox_speed_low_filter->value() ;

        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.p1 = this->_spinbox_pid_p1->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.i1 = this->_spinbox_pid_i1->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.d1 = this->_spinbox_pid_d1->value() ;

        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.p2 = this->_spinbox_pid_p2->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.i2 = this->_spinbox_pid_i2->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->para.motor_para.pid.d2 = this->_spinbox_pid_d2->value() ;

        RobotHardware::getRobotHardWare()->sendCommand(SET_MOTOR_PARAMETERS);
    }
private:
    QTreeWidgetItem*  _item_moter_id ;
    QTreeWidgetItem*  _item_encode_num ;
    QTreeWidgetItem*  _item_pwm_max ;
    QTreeWidgetItem*  _item_pwm_dead_zone ;
    QTreeWidgetItem*  _item_speed_low_filter ;
    QTreeWidgetItem*  _item_protect_current ;
    QTreeWidgetItem*  _item_pid_p1 ;
    QTreeWidgetItem*  _item_pid_i1 ;
    QTreeWidgetItem*  _item_pid_d1 ;
    QTreeWidgetItem*  _item_pid_p2 ;
    QTreeWidgetItem*  _item_pid_i2 ;
    QTreeWidgetItem*  _item_pid_d2 ;


    QSpinBox *_spinbox_id ;
    QDoubleSpinBox *_spinbox_encode_num ;
    QDoubleSpinBox *_spinbox_pwm_max ;
    QDoubleSpinBox *_spinbox_pwm_dead_zone ;
    QDoubleSpinBox *_spinbox_speed_low_filter ;
    QDoubleSpinBox *_spinbox_protect_current ;
    QDoubleSpinBox *_spinbox_pid_p1 ;
    QDoubleSpinBox *_spinbox_pid_i1 ;
    QDoubleSpinBox *_spinbox_pid_d1 ;
    QDoubleSpinBox *_spinbox_pid_p2 ;
    QDoubleSpinBox *_spinbox_pid_i2 ;
    QDoubleSpinBox *_spinbox_pid_d2 ;
};

class ExpectMotorParameterFactory:public CommandFactory{
public:
    ExpectMotorParameterFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectMotorParameter(command_name,target_widget) ;
    }
} ;

#endif // EXPECTMOTORPARAMETER_H
