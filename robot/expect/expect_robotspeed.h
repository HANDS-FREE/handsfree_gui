#ifndef EXPECTROBOTSPEED_H
#define EXPECTROBOTSPEED_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectRobotSpeed : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectRobotSpeed(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_spinbox_x = new QDoubleSpinBox() ;
        this->_spinbox_y = new QDoubleSpinBox() ;
        this->_spinbox_z = new QDoubleSpinBox() ;

        this->_spinbox_x->setMinimum(-65536);
        this->_spinbox_y->setMinimum(-65536);
        this->_spinbox_z->setMinimum(-65536);

        this->_item_speed_x = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("speed_x"),
                                                           1,this->_spinbox_x
                                                           ) ;
        this->_item_speed_y = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("speed_y"),
                                                           1,this->_spinbox_y
                                                           ) ;
        this->_item_speed_z = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("speed_z"),
                                                           1,this->_spinbox_z
                                                           ) ;


    }
    ~ExpectRobotSpeed(){
        delete _spinbox_x ;
        delete _spinbox_y ;
        delete _spinbox_z ;

        delete  _item_speed_x ;
        delete  _item_speed_y ;
        delete  _item_speed_z ;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x = this->_spinbox_x->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.y = this->_spinbox_y->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z = this->_spinbox_z->value() ;
        RobotHardware::getRobotHardWare()->sendCommand(SET_ROBOT_SPEED);
    }
private:
    QTreeWidgetItem*  _item_speed_x ;
    QTreeWidgetItem*  _item_speed_y ;
    QTreeWidgetItem*  _item_speed_z ;

    QDoubleSpinBox *_spinbox_x ;
    QDoubleSpinBox *_spinbox_y ;
    QDoubleSpinBox *_spinbox_z ;
};

class ExpectRobotSpeedFactory:public CommandFactory{
public:
    ExpectRobotSpeedFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectRobotSpeed(command_name,target_widget) ;
    }
} ;

#endif // EXPECTROBOTSPEED_H
