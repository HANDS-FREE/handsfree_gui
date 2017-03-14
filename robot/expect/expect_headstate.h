#ifndef EXPECTHEADSTATE_H
#define EXPECTHEADSTATE_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class ExpectHeadState : public CommandAvailable
{
    Q_OBJECT
public:
    ExpectHeadState(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_spinbox_pitch = new QDoubleSpinBox() ;
        this->_spinbox_roll = new QDoubleSpinBox() ;
        this->_spinbox_yaw = new QDoubleSpinBox() ;

        this->_spinbox_pitch->setMinimum(-65536);
        this->_spinbox_roll->setMinimum(-65536);
        this->_spinbox_yaw->setMinimum(-65536);

        this->_item_yaw = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("yaw"),
                                                           1,this->_spinbox_yaw
                                                           ) ;
        this->_item_pitch = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("pitch"),
                                                           1,this->_spinbox_pitch
                                                           ) ;
        this->_item_roll = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("roll"),
                                                           1,this->_spinbox_roll
                                                           ) ;
    }
    ~ExpectHeadState(){
        delete this->_spinbox_pitch ;
        delete this->_spinbox_roll ;
        delete this->_spinbox_yaw ;

        delete  _item_yaw;
        delete  _item_roll;
        delete  _item_pitch;
    }
public slots:
    virtual void update(){
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_head_state.yaw = this->_spinbox_yaw->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_head_state.roll = this->_spinbox_roll->value() ;
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_head_state.pitch = this->_spinbox_pitch->value() ;

        RobotHardware::getRobotHardWare()->sendCommand(SET_HEAD_STATE);
    }
private:
    QTreeWidgetItem*  _item_yaw;
    QTreeWidgetItem*  _item_roll;
    QTreeWidgetItem*  _item_pitch;

    QDoubleSpinBox *_spinbox_yaw ;
    QDoubleSpinBox *_spinbox_roll ;
    QDoubleSpinBox *_spinbox_pitch ;
};

class ExpectHeadStateFactory:public CommandFactory{
public:
    ExpectHeadStateFactory(){}
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget)
    {
        return new ExpectHeadState(command_name,target_widget) ;
    }
} ;

#endif // EXPECTHEADSTATE_H
