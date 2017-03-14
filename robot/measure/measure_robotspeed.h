#ifndef MEASUREROBOTSPEED_H
#define MEASUREROBOTSPEED_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class MeasureRobotSpeed : public CommandAvailable
{
    Q_OBJECT
public:
    MeasureRobotSpeed(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_label_speed_x = new QLabel(tr("0 m/s")) ;
        this->_label_speed_y = new QLabel(tr("0 m/s")) ;
        this->_label_speed_z = new QLabel(tr("0 r/s")) ;

        this->_item_top = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                       0,
                                                       tr("robot_speed")) ;

        this->_item_speed_x = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("X"),
                                                           1,this->_label_speed_x,
                                                           this->_item_top) ;
        this->_item_speed_y = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("Y"),
                                                           1,this->_label_speed_y,
                                                           this->_item_top) ;
        this->_item_speed_z = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                           0,tr("W"),
                                                           1,this->_label_speed_z,
                                                           this->_item_top)  ;
    }
    ~MeasureRobotSpeed(){
        delete _label_speed_z ;
        delete _label_speed_x ;
        delete _label_speed_y ;

        delete _item_top ;
        delete _item_speed_z ;
        delete _item_speed_x ;
        delete _item_speed_y ;
    }
public slots:
    virtual void update(){
        float speed_x = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->measure_robot_speed.x ;
        float speed_y = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->measure_robot_speed.y ;
        float speed_z = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->measure_robot_speed.z ;

        this->_label_speed_x->setText(QString("%1 m/s").arg(speed_x));
        this->_label_speed_y->setText(QString("%1 m/s").arg(speed_y));
        this->_label_speed_z->setText(QString("%1 r/s").arg(speed_z));
    }
private:
    QTreeWidgetItem* _item_top ;
    QTreeWidgetItem* _item_speed_x;
    QTreeWidgetItem* _item_speed_y ;
    QTreeWidgetItem* _item_speed_z ;


    QLabel* _label_speed_x ;
    QLabel* _label_speed_y ;
    QLabel* _label_speed_z ;
};
class MeasureRobotSpeedFactory:public CommandFactory
{
public :
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget){
        return new MeasureRobotSpeed(command_name,target_widget) ;
    }
    MeasureRobotSpeedFactory(){}
};

#endif // MEASUREROBOTSPEED_H
