#ifndef EXPECTARMSTATE_H
#define EXPECTARMSTATE_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectArmState : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectArmState(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_spinbox_servo1 = new QDoubleSpinBox() ;
        this->_spinbox_servo2 = new QDoubleSpinBox() ;
        this->_spinbox_servo3 = new QDoubleSpinBox() ;
        this->_spinbox_servo4 = new QDoubleSpinBox() ;
        this->_spinbox_servo5 = new QDoubleSpinBox() ;
        this->_spinbox_servo6 = new QDoubleSpinBox() ;
        this->_spinbox_servo7 = new QDoubleSpinBox() ;
        this->_spinbox_servo8 = new QDoubleSpinBox() ;

        this->_spinbox_servo1->setMinimum(-65536);
        this->_spinbox_servo2->setMinimum(-65536);
        this->_spinbox_servo3->setMinimum(-65536);
        this->_spinbox_servo4->setMinimum(-65536);
        this->_spinbox_servo5->setMinimum(-65536);
        this->_spinbox_servo6->setMinimum(-65536);
        this->_spinbox_servo7->setMinimum(-65536);
        this->_spinbox_servo8->setMinimum(-65536);

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
        this->_item_servo5 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo5"),
                                                           1,this->_spinbox_servo5
                                                           ) ;
        this->_item_servo6 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo6"),
                                                           1,this->_spinbox_servo6
                                                           ) ;
        this->_item_servo7 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo7"),
                                                           1,this->_spinbox_servo7
                                                           ) ;
        this->_item_servo8 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("servo8"),
                                                           1,this->_spinbox_servo8
                                                           ) ;
    }
    ~ExpectArmState(){
        delete _spinbox_servo1 ;
        delete _spinbox_servo2 ;
        delete _spinbox_servo3 ;
        delete _spinbox_servo4 ;
        delete _spinbox_servo5 ;
        delete _spinbox_servo6 ;
        delete _spinbox_servo7 ;
        delete _spinbox_servo8 ;

        delete  _item_servo1;
        delete  _item_servo2;
        delete  _item_servo3;
        delete  _item_servo4;
        delete  _item_servo5;
        delete  _item_servo6;
        delete  _item_servo7;
        delete  _item_servo8;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo1 = this->_spinbox_servo1->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo2 = this->_spinbox_servo2->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo3 = this->_spinbox_servo3->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo4 = this->_spinbox_servo4->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo5 = this->_spinbox_servo5->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo6 = this->_spinbox_servo6->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo7 = this->_spinbox_servo7->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_arm_state.servo8 = this->_spinbox_servo8->value() ;

        RobotHardware::getRobotHardWare()->sendCommand(SET_ARM_STATE);
    }
private:
    QTreeWidgetItem*  _item_servo1;
    QTreeWidgetItem*  _item_servo2;
    QTreeWidgetItem*  _item_servo3;
    QTreeWidgetItem*  _item_servo4;
    QTreeWidgetItem*  _item_servo5;
    QTreeWidgetItem*  _item_servo6;
    QTreeWidgetItem*  _item_servo7;
    QTreeWidgetItem*  _item_servo8;


    QDoubleSpinBox *_spinbox_servo1 ;
    QDoubleSpinBox *_spinbox_servo2 ;
    QDoubleSpinBox *_spinbox_servo3 ;
    QDoubleSpinBox *_spinbox_servo4 ;
    QDoubleSpinBox *_spinbox_servo5 ;
    QDoubleSpinBox *_spinbox_servo6 ;
    QDoubleSpinBox *_spinbox_servo7 ;
    QDoubleSpinBox *_spinbox_servo8 ;
};

class ExpectArmStateFactory:public CommandFactory{
public:
    ExpectArmStateFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectArmState(command_name,target_widget) ;
    }
} ;

#endif // EXPECTARMSTATE_H
