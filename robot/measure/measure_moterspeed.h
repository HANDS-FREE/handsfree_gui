#ifndef MEASUREMOTERSPEED_H
#define MEASUREMOTERSPEED_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class MeasureMoterSpeed : public CommandAvailable
{
    Q_OBJECT
public:
    MeasureMoterSpeed(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_label_speed_servo1 = new QLabel(tr("0 r/s")) ;
        this->_label_speed_servo2 = new QLabel(tr("0 r/s")) ;
        this->_label_speed_servo3 = new QLabel(tr("0 r/s")) ;
        this->_label_speed_servo4 = new QLabel(tr("0 r/s")) ;

        this->_item_top = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                       0,
                                                       tr("motor_speed")) ;
        this->_item_speed_servo1 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("servo1"),
                                                                1,this->_label_speed_servo1,
                                                                this->_item_top) ;
        this->_item_speed_servo2 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("servo2"),
                                                                1,this->_label_speed_servo2,
                                                                this->_item_top) ;
        this->_item_speed_servo3 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("servo3"),
                                                                1,this->_label_speed_servo3,
                                                                this->_item_top) ;
        this->_item_speed_servo4 = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("servo4"),
                                                                1,this->_label_speed_servo4,
                                                                this->_item_top) ;

    }
    ~MeasureMoterSpeed(){
        delete _label_speed_servo1 ;
        delete _label_speed_servo2 ;
        delete _label_speed_servo3 ;
        delete _label_speed_servo4 ;

        delete _item_top ;
        delete _item_speed_servo1 ;
        delete _item_speed_servo2 ;
        delete _item_speed_servo3 ;
        delete _item_speed_servo4 ;
    }
public slots:
    virtual void update(){
        float servo1 = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_motor_speed.servo1 ;
        float servo2 = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_motor_speed.servo2 ;
        float servo3 = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_motor_speed.servo3 ;
        float servo4 = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_motor_speed.servo4 ;

        this->_label_speed_servo1->setText(QString("%1 r/s").arg(servo1));
        this->_label_speed_servo2->setText(QString("%1 r/s").arg(servo2));
        this->_label_speed_servo3->setText(QString("%1 r/s").arg(servo3));
        this->_label_speed_servo4->setText(QString("%1 r/s").arg(servo4));
    }
private:
    QTreeWidgetItem* _item_top ;
    QTreeWidgetItem* _item_speed_servo1;
    QTreeWidgetItem* _item_speed_servo2 ;
    QTreeWidgetItem* _item_speed_servo3 ;
    QTreeWidgetItem* _item_speed_servo4 ;

    QLabel* _label_speed_servo1 ;
    QLabel* _label_speed_servo2 ;
    QLabel* _label_speed_servo3 ;
    QLabel* _label_speed_servo4 ;
};

class MeasureMoterSpeedFactory:public CommandFactory
{
public :
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget){
        return new MeasureMoterSpeed(command_name,target_widget) ;
    }
    MeasureMoterSpeedFactory() {}
};
#endif // MEASUREMOTERSPEED_H
