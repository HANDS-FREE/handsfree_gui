#ifndef MEASUREGLOBALCOORDINATE_H
#define MEASUREGLOBALCOORDINATE_H
#include "robot/command.h"
#include "robot/command_factory.h"
class MeasureGlobalCoordinate : public CommandAvailable
{
    Q_OBJECT
public:
    MeasureGlobalCoordinate(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        CommandAvailable(command_name,target_widget,parent)
    {
        this->_label_coordinate_x = new QLabel(tr("0 m")) ;
        this->_label_coordinate_y = new QLabel(tr("0 m")) ;
        this->_label_coordinate_w = new QLabel(tr("0 r")) ;

        this->_item_top = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                       0,
                                                       tr("global_coordinate")) ;
        this->_item_coordinate_x = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("X"),
                                                                1,this->_label_coordinate_x,
                                                                this->_item_top) ;
        this->_item_coordinate_y = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("Y"),
                                                                1,this->_label_coordinate_y,
                                                                this->_item_top) ;
        this->_item_coordinate_w = TreeItemFactory::makeNewItem(this->_target_treewidget,
                                                                0,tr("W"),
                                                                1,this->_label_coordinate_w,
                                                                this->_item_top) ;
    }
    ~MeasureGlobalCoordinate(){
        delete _label_coordinate_w ;
        delete _label_coordinate_x ;
        delete _label_coordinate_y ;

        delete _item_top ;
        delete _item_coordinate_w ;
        delete _item_coordinate_x ;
        delete _item_coordinate_y ;
    }
public slots:
    virtual void update(){
        float x = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_global_coordinate.x ;
        float y = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_global_coordinate.y ;
        float z = RobotHardware::getRobotHardWare()->getRobotAbstract()->
                measure_global_coordinate.z ;

        this->_label_coordinate_x->setText(QString("%1 m").arg(x));
        this->_label_coordinate_y->setText(QString("%1 m").arg(y));
        this->_label_coordinate_w->setText(QString("%1 r").arg(z));
    }
private:
    QTreeWidgetItem* _item_top ;
    QTreeWidgetItem* _item_coordinate_x ;
    QTreeWidgetItem* _item_coordinate_y ;
    QTreeWidgetItem* _item_coordinate_w ;

    QLabel* _label_coordinate_x ;
    QLabel* _label_coordinate_y ;
    QLabel* _label_coordinate_w ;
};

class MeasureGlobalCoordinateFactory:public CommandFactory
{
public:
    CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget){
        return new MeasureGlobalCoordinate(command_name,target_widget) ;
    }
    MeasureGlobalCoordinateFactory(){}
};

#endif // MEASUREGLOBALCOORDINATE_H
