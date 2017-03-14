#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QString>
#include <QTreeWidget>
#include <QVector>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "robot_hardware.h"
#include "util/factory/treeitem_factory.h"

class CommandAvailable : public QObject
{
    Q_OBJECT
public:
    explicit CommandAvailable(const QString &command_name,QTreeWidget *target_widget,QObject *parent = 0):
        QObject(parent),
        _target_treewidget(target_widget),
        _command_name(command_name)
    {
        QStringList header_name ;
        header_name<<tr("param")<<tr("value") ;
        this->_target_treewidget->setHeaderLabels(header_name);
        this->_target_treewidget->setColumnCount(2);
        this->_target_treewidget->setColumnWidth(0,this->_target_treewidget->width()/2);
        this->_target_treewidget->setColumnWidth(1,(this->_target_treewidget->width()-2)/2);
    }
    virtual QString getName(){
        return this->_command_name ;
    }
    virtual QTreeWidget* getTargetTreeWidget(){return this->_target_treewidget;}

    virtual ~CommandAvailable(){}
public slots:
    //to send or read data from hardware
    virtual void update() = 0 ;
signals:
    //emit this when new msg get
    void newMsgGet(const QString &name) ;
    //emit this when new msg send to robot
    void newMsgSend(const QString &name) ;
    //send this with source widget
    void newMsgSend(const QString &name,QWidget *widget_send) ;
    //when user edit some widget such as qcheckbox,change this
    void newValueSet(const QString &name,QWidget *widget_changed) ;
protected:
    QTreeWidget *_target_treewidget ;
    QString _command_name ;
};

#endif // COMMAND_H
