#ifndef EXPECTGLOBALSPEED_H
#define EXPECTGLOBALSPEED_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectGlobalSpeed : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectGlobalSpeed(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
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
    ~ExpectGlobalSpeed(){
        delete _spinbox_x ;
        delete _spinbox_y ;
        delete _spinbox_z ;

        delete  _item_speed_x ;
        delete  _item_speed_y ;
        delete  _item_speed_z ;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_global_speed.x = this->_spinbox_x->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_global_speed.y = this->_spinbox_y->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_global_speed.z = this->_spinbox_z->value() ;

        qDebug()<<"in1";
        RobotHardware::getRobotHardWare()->sendCommand(SET_GLOBAL_SPEED);
    }
private:
    QTreeWidgetItem*  _item_speed_x ;
    QTreeWidgetItem*  _item_speed_y ;
    QTreeWidgetItem*  _item_speed_z ;

    QDoubleSpinBox *_spinbox_x ;
    QDoubleSpinBox *_spinbox_y ;
    QDoubleSpinBox *_spinbox_z ;
};
class ExpectGlobalSpeedFactory:public CommandFactory{
public:
    ExpectGlobalSpeedFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectGlobalSpeed(command_name,target_widget) ;
    }
} ;

#endif // EXPECTGLOBALSPEED_H
