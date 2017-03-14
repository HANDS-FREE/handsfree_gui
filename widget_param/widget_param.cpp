#include "widget_param.h"
#include "ui_widget_param.h"

#include "robot/robot_commands.h"
#include "robot/robot_hardware.h"
#include "QDebug"

WidgetParam::WidgetParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetParam)
{
    ui->setupUi(this);
    this->_available_measure_list = RobotCommands::getRobotCommands()->getAvailableMeasureDate() ;
    this->init_param_widget();
    this->init_signal_slot();
}

WidgetParam::~WidgetParam()
{
    delete ui;
    //to delete the _vc
}

void WidgetParam::on_new_msg_get()
{
    qDebug()<<"in" ;
    size_t size = this->_vc_measure_commands.size() ;
    //update msg
    for(size_t i = 0 ; i < size ; i++)this->_vc_measure_commands[i]->update() ;
}

void WidgetParam::init_signal_slot()
{
    connect(RobotHardware::getReadThread(),SIGNAL(newMsgGet()),
            this, SLOT(on_new_msg_get()));
}

void WidgetParam::init_param_widget()
{
    size_t list_size = this->_available_measure_list.size() ;
    for(size_t i = 0 ; i < list_size ; i++){
        this->_vc_measure_commands.push_back(
                    RobotCommands::getRobotCommands()->getMeasureFactory(this->_available_measure_list[i])
                    ->createNewCommand(this->_available_measure_list[i],ui->treeWidget)
                    );
    }
}
