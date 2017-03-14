#include "widget_control.h"
#include "ui_widget_control.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
WidgetControl::WidgetControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetControl),
    _current_speed(0.1),
    _speed_scale(1.0)
{
    ui->setupUi(this);
}

WidgetControl::~WidgetControl()
{
    delete ui;
}

void WidgetControl::keyPressEvent(QKeyEvent *e)
{
    if(!RobotHardware::isRobotOpened()){
        QMessageBox::StandardButton rb =
                QMessageBox::question(NULL, tr("error"),tr("serial not open , do you want to open it?"),
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb==QMessageBox::Yes){
            emit openRobotRequired();
        }
        else{
            QMessageBox::critical(NULL,"WRONG","can not send command",QMessageBox::Yes,QMessageBox::Yes) ;
            return ;
        }
    }
    //check agin
    if(!RobotHardware::isRobotOpened())return ;
    brake();
    switch (e->key()) {
    case Qt::Key_Up:
        ui->pushButton_up->animateClick(100); //+1s
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x =
                this->_current_speed*this->_speed_scale ;
        break;
    case Qt::Key_Down:
        ui->pushButton_down->animateClick(100); //+1s
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x =
                -this->_current_speed*this->_speed_scale ;
        break;
    case Qt::Key_Left:
        ui->pushButton_left->animateClick(100); //+1s
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z =
                this->_current_speed*this->_speed_scale ;
        break;
    case Qt::Key_Right:
        ui->pushButton_right->animateClick(100); //+1s
        RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z =
                -this->_current_speed*this->_speed_scale ;
        break;
    case Qt::Key_Q:
        ui->pushButton_add->animateClick(100);
        this->_speed_scale *= 1.2 ; //add 20%
        break;
    case Qt::Key_Z:
        ui->pushButton_reduce->animateClick(100); //+1s
        this->_speed_scale *= 0.8 ; //del 20%
        break;
    case Qt::Key_S:
        ui->pushButton_stop->animateClick(100); //+1s
        //do nothing
        break;
    default:
        QWidget::keyPressEvent(e) ;//return and do nothing
        return ;
        break;
    }
    this->changeCurrentLabel();
    RobotHardware::getRobotHardWare()->sendCommand(SET_ROBOT_SPEED);
}

void WidgetControl::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Q||e->key()==Qt::Key_Z)return ;
    this->brake();
    RobotHardware::getRobotHardWare()->sendCommand(SET_ROBOT_SPEED);
    this->changeCurrentLabel();
    QWidget::keyReleaseEvent(e) ;
}

void WidgetControl::brake()
{
    RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x = 0.0 ;
    RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.y = 0.0 ;
    RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z = 0.0  ;
}

void WidgetControl::changeCurrentLabel()
{
    ui->label_speed_x->setText(QString::number(RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x,
                                               'g',3));
    ui->label_speed_y->setText(QString::number(RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.y,
                                               'g',3));
    ui->label_speed_z->setText(QString::number(RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z,
                                               'g',3));
    ui->label_scale_num->setText(QString::number(this->_speed_scale,'g',4));
    ui->control_scale->setValue(this->_speed_scale);
}

