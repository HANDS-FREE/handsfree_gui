#include "widget_command.h"
#include "ui_widget_command.h"
#include "util/widgets/button_listwidgetitem.h"
#include "robot/robot_commands.h"
#include "util/widgets/availablecommand_list.h"
#include <QMessageBox>
#include <QListWidgetItem>

WidgetCommand::WidgetCommand(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCommand)
{
    ui->setupUi(this);
    this->_available_expect_list = new AvailableCommandList(RobotCommands::getRobotCommands()->getAvailableExpectData()) ;
    //ui->stackedWidget->setEnableShake(true);
    this->_timer_update_commands = new QTimer() ;
    this->init_view();
    this->init_signal_slots();
}

WidgetCommand::~WidgetCommand()
{
    delete ui;
    delete this->_available_expect_list ;
}

void WidgetCommand::init_signal_slots()
{
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),
            ui->stackedWidget, SLOT(setCurrentIndex(int))) ;

    connect(this->_default_item_widget,SIGNAL(addButtonClicked()),
            this, SLOT(on_item_widget_add_clicked())) ;

    connect(this->_available_expect_list,SIGNAL(itemsConfirm(QStringList)),
            this, SLOT(on_commands_list_confirm(QStringList))) ;

    connect(this->_timer_update_commands,SIGNAL(timeout()),
            this, SLOT(on_timer_timeout())) ;

}

void WidgetCommand::init_view()
{
    this->_default_item_widget = new ButtonListWidgetItem(tr("add some command")) ;
    this->_default_item_widget->enable_AddButton(true);//could use this item to add new command item
    this->_default_item_widget->enable_checkbox(false);

    this->_default_listwidget_item = new QListWidgetItem() ;
    this->_default_listwidget_item->setSizeHint(QSize(ui->listWidget->width(),50));
    ui->listWidget->addItem(_default_listwidget_item);
    ui->listWidget->setItemWidget(this->_default_listwidget_item,this->_default_item_widget);

//    this->_default_item_treewidget = new TreeWidgetCommandDefault() ;
    this->_default_item_label = new QLabel(tr("please add some command , and make sure you have open your robot before using")) ;
    this->_default_item_label->setFont(QFont("Georgia",12));
    this->_default_item_label->adjustSize();
    this->_default_item_label->setWordWrap(true);
    ui->stackedWidget->addWidget(this->_default_item_label) ;

}

void WidgetCommand::on_item_checkbox_clicked(bool checked, ButtonListWidgetItem *source_item)
{
    if(!RobotHardware::isRobotOpened()){
        //to do
        //add some code to deal with this and remove return
        QMessageBox::critical(NULL,tr("WRONG"),tr("please open robot first"),QMessageBox::Yes,QMessageBox::Yes) ;
        source_item->setCheckboxState(false);
        return ;
    }
    if(checked){
         this->_vc_item_checked.push_back(source_item);
         //timer not start
         if(1==this->_vc_item_checked.size())this->_timer_update_commands->start(500);
    }
    else{
        //this->_vc_item_checked.removeOne(source_item) ;
	int index_target = this->_vc_item_checked.indexOf(source_item) ; 
	this->_vc_item_checked.removeAt(index_target) ;         
	if(this->_map_item_command[source_item]->getName()=="robot speed"){
            //to brake robot
            RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.x =0 ;
            RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.y =0 ;
            RobotHardware::getRobotHardWare()->getRobotAbstract()->expect_robot_speed.z =0 ;
            RobotHardware::getRobotHardWare()->sendCommand(SET_ROBOT_SPEED);
        }
        if(0==this->_vc_item_checked.size())this->_timer_update_commands->stop();
    }
}

void WidgetCommand::on_item_widget_add_clicked()
{
    int pos_mid_x = this->pos().x() + this->width()/2 ;
    int pos_mid_y = this->pos().y() + this->height()/2 ;

    //ExtendedSelection means that user could change multi item at one time
    this->_available_expect_list->setItemSelectMode(QAbstractItemView::ExtendedSelection);
    this->_available_expect_list->show();
    this->_available_expect_list->move(pos_mid_x,pos_mid_y);
}

void WidgetCommand::on_item_widget_delete_clicked(ButtonListWidgetItem *delete_target)
{
    //to get all delete target
    CommandAvailable *delete_target_command = this->_map_item_command[delete_target] ;
    QTreeWidget *delete_target_treewidget = this->_map_item_treewidget[delete_target] ;
    QListWidgetItem *delete_target_listwidgetitem = this->_map_item_listwidgetItem[delete_target] ;

    disconnect(delete_target,SIGNAL(delButtonClicked(ButtonListWidgetItem*)),
               this,SLOT(on_item_widget_delete_clicked(ButtonListWidgetItem*))) ;
    disconnect(delete_target,SIGNAL(checkboxClicked(bool,ButtonListWidgetItem*)),
               this, SLOT(on_item_checkbox_clicked(bool,ButtonListWidgetItem*))) ;

   //s this->_vc_item_widget.removeOne(delete_target) ;
    int index_target = this->_vc_item_widget.indexOf(delete_target) ;
    this->_vc_item_widget.removeAt(index_target) ; 
    this->_map_item_command.remove(delete_target) ;
    this->_map_item_listwidgetItem.remove(delete_target) ;
    this->_map_item_treewidget.remove(delete_target) ;

    ui->listWidget->removeItemWidget(delete_target_listwidgetitem) ;
    ui->stackedWidget->removeWidget(delete_target_treewidget);

    delete delete_target ;
    delete delete_target_command ;
    delete delete_target_listwidgetitem ;
    delete delete_target_treewidget ;
}

void WidgetCommand::on_commands_list_confirm(QStringList confirm_list)
{
    CommandAvailable *command ;
    size_t list_size = confirm_list.size() ;
    //to add new command
    for(size_t i = 0 ; i < list_size ; i++){
        QListWidgetItem *listwidget_item = new QListWidgetItem() ;
        QTreeWidget *command_treewidget = new QTreeWidget() ;
        command_treewidget->resize(ui->stackedWidget->size());
        ButtonListWidgetItem *item_widget = new ButtonListWidgetItem(confirm_list[i]) ;
        command = RobotCommands::getRobotCommands()->getExpectFactory(confirm_list[i])
                ->createNewCommand(confirm_list[i],command_treewidget) ;

        item_widget->enable_DelButton(true);
        item_widget->enable_EditButton(true);
        item_widget->enable_checkbox(true);

        //to insert new widget to listwidget and stackwidget
        listwidget_item->setSizeHint(QSize(ui->listWidget->width(),50));
        ui->listWidget->addItem(listwidget_item);
        ui->listWidget->setItemWidget(listwidget_item,item_widget);
        ui->stackedWidget->addWidget(command_treewidget) ;

        connect(item_widget,SIGNAL(delButtonClicked(ButtonListWidgetItem*)),
                this,SLOT(on_item_widget_delete_clicked(ButtonListWidgetItem*))) ;

        connect(item_widget,SIGNAL(checkboxClicked(bool,ButtonListWidgetItem*)),
                this, SLOT(on_item_checkbox_clicked(bool,ButtonListWidgetItem*))) ;


        this->_vc_item_widget.push_back(item_widget) ;
        this->_map_item_command.insert(item_widget,command) ;
        this->_map_item_listwidgetItem.insert(item_widget,listwidget_item) ;
        this->_map_item_treewidget.insert(item_widget,command_treewidget) ;
    }
}

void WidgetCommand::on_timer_timeout()
{
    size_t updater_num = this->_vc_item_checked.size()  ;
    for(size_t i = 0 ; i < updater_num ; i++)this->_map_item_command[this->_vc_item_checked[i]]->update();
}
