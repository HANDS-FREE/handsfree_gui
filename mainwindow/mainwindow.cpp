#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init_signal_slots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_signal_slots()
{
    connect(ui->switch_button,SIGNAL(toggled(bool)),
            this,SLOT(on_switchbutton_toggled(bool))) ;
    connect(RobotHardware::getReadThread(),SIGNAL(newMsgGet()),
            this, SLOT(on_newmsg_get())) ;
    connect(ui->widget_control,SIGNAL(openRobotRequired()) ,
            this, SLOT(on_open_robot_required()))  ;
}

void MainWindow::on_newmsg_get()
{
    float x = RobotHardware::getRobotHardWare()->getRobotAbstract()->
            measure_global_coordinate.x ;
    float y = RobotHardware::getRobotHardWare()->getRobotAbstract()->
            measure_global_coordinate.y ;
    ui->widget_radar->setPoint(x,y);
}

void MainWindow::on_switchbutton_toggled(bool open)
{
    if(open){
        QString usb_name = ui->comboBox_port_name->currentText() ;
        if(usb_name.isEmpty()){
            QMessageBox::critical(NULL,tr("WRONG"),tr("no serial found"),QMessageBox::Yes,QMessageBox::Yes) ;
            ui->switch_button->setToggle(false);
            return ;
        }
        QRegExp linux_reg("^ttyUSB\\d\\d?$") ; //for linux usb
        QRegExp windows_reg("^com\\d\\d?$") ; //for windows usb
        QString target_serial_name = "serial://";
        if(linux_reg.exactMatch(usb_name)){
            target_serial_name += "/dev/"+usb_name ;
        }
        else if(windows_reg.exactMatch(usb_name)){
            target_serial_name += usb_name ;
        }
        RobotHardware::launchRobot(target_serial_name.toStdString()) ;
        RobotHardware::getReadThread()->start();
    }
    else{
        RobotHardware::getReadThread()->stop();
        RobotHardware::closeRobot() ;
    }
}

void MainWindow::on_open_robot_required()
{
    ui->switch_button->setToggle(true);
    this->on_switchbutton_toggled(true);
}

