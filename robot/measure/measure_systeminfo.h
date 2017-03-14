#ifndef MEASURESYSTEMlabel_H
#define MEASURESYSTEMlabel_H

#include <QObject>
#include "robot/command.h"
#include "robot/command_factory.h"
class MeasureSystemInfo : public CommandAvailable
{
    Q_OBJECT
public:
    MeasureSystemInfo(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_label_cpu_temperature = new QLabel(tr("no temperature")) ;
        this->_label_cpu_usage = new QProgressBar() ;
        this->_label_cpu_usage->setTextVisible(true);
        this->_label_cpu_usage->setValue(0);
        this->_label_power_label = new QProgressBar() ;
        this->_label_power_label->setTextVisible(true);
        this->_label_power_label->setValue(0);

        this->_item_top = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                       0,
                                                       tr("system_info")) ;

        this->_item_cpu_temperature = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                   0,tr("temperature"),
                                                                   1,this->_label_cpu_temperature,
                                                                   this->_item_top) ;
        this->_item_cpu_usage = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                             0,tr("usage"),
                                                             1,this->_label_cpu_usage,
                                                             this->_item_top) ;
        this->_item_power_info = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                              0,tr("power"),
                                                              1,this->_label_power_label,
                                                              this->_item_top) ;


    }
    ~MeasureSystemInfo(){
        delete _label_cpu_temperature ;
        delete _label_power_label ;
        delete _label_cpu_usage ;


        delete _item_top ;
        delete _item_cpu_temperature ;
        delete _item_power_info ;
        delete _item_cpu_usage ;
    }
public slots:
    virtual void update(){
        float cpu_usage = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->system_info.cpu_usage ;
        float power_remain = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->system_info.power_remain ;
        float cpu_temperature = RobotHardware::getRobotHardWare()->
                getRobotAbstract()->system_info.cpu_temperature ;

        this->_label_cpu_usage->setValue(cpu_usage);
        this->_label_power_label->setValue(power_remain);
        QString temperature_text = QString("%1 C").arg(cpu_temperature);
        this->_label_cpu_temperature->setText(temperature_text);
    }
private:
    QTreeWidgetItem* _item_top ;
    QTreeWidgetItem* _item_cpu_temperature ;
    QTreeWidgetItem* _item_power_info ;
    QTreeWidgetItem* _item_cpu_usage ;

    QLabel* _label_cpu_temperature ;
    QProgressBar* _label_power_label ;
    QProgressBar* _label_cpu_usage ;
};

class MeasureSystemInfoFactory:public CommandFactory
{
public:
     CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget){
        return new MeasureSystemInfo(command_name,target_widget) ;
    }
    MeasureSystemInfoFactory(){}
};

#endif // MEASURESYSTEMlabel_H
