#include "button_listwidgetitem.h"
#include "ui_button_listwidgetitem.h"
#include <QDebug>
#include <QInputDialog>
ButtonListWidgetItem::ButtonListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonListWidgetItem),
    _enable_add_button(false),
    _enable_del_button(false),
    _enable_edit_button(false)
{
    ui->setupUi(this);
    ui->label_item->adjustSize();
    this->init_SignalSlot();
    this->hideAllButton();
}

ButtonListWidgetItem::ButtonListWidgetItem(const QString &text,const QString &icon, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ButtonListWidgetItem),
    _enable_checkbox(true),
    _enable_add_button(false),
    _enable_del_button(false),
    _enable_edit_button(false)
{
    ui->setupUi(this);
    ui->label_item->adjustSize();
    this->init_SignalSlot();
    this->set_LabelText(text);
    this->hideAllButton();
}

ButtonListWidgetItem::~ButtonListWidgetItem()
{
    delete ui;
}


void ButtonListWidgetItem::set_LabelText(const QString &text)
{
    ui->label_item->setText(text);
}

void ButtonListWidgetItem::enable_checkbox(bool need)
{
    this->_enable_checkbox = need;
    ui->checkBox_pub->setEnabled(need);
}

void ButtonListWidgetItem::enable_AddButton(bool need)
{
    this->_enable_add_button = need ;
    if(need)ui->pushButton_add->show() ;
    else ui->pushButton_add->hide();
}

void ButtonListWidgetItem::enable_DelButton(bool need)
{
    this->_enable_del_button = need ;
    if(need)ui->pushButton_delete->show();
    else ui->pushButton_delete->hide();
}

void ButtonListWidgetItem::enable_EditButton(bool need)
{
    this->_enable_edit_button = need ;
    if(need)ui->pushButton_edit->show() ;
    else ui->pushButton_edit->hide();
}

void ButtonListWidgetItem::setCheckboxState(bool checked)
{
    ui->checkBox_pub->setChecked(checked);
}

void ButtonListWidgetItem::enterEvent(QEvent *e)
{
    Q_UNUSED(e) ;
    if(this->_enable_add_button)
    {
        ui->pushButton_add->show() ;
    }
    if(this->_enable_del_button)ui->pushButton_delete->show();
    if(this->_enable_edit_button)ui->pushButton_edit->show();
}

void ButtonListWidgetItem::leaveEvent(QEvent *e)
{
    Q_UNUSED(e) ;
    this->hideAllButton();
}

void ButtonListWidgetItem::on_pushbutton_edit_clicked()
{
    bool has_changed = false ;
    QString new_name = QInputDialog::getText(this,tr("change name"),tr("New Name"),QLineEdit::Normal,ui->label_item->text(),&has_changed);
    if(has_changed)ui->label_item->setText(new_name);
    emit editButtonClicked();

}


void ButtonListWidgetItem::init_SignalSlot()
{
    connect(ui->pushButton_add,SIGNAL(clicked(bool)),
            this,SLOT(on_pushbutton_add_clicked())) ;
    connect(ui->pushButton_delete,SIGNAL(clicked(bool)),
            this,SLOT(on_pushbutton_del_clicked())) ;
    connect(ui->pushButton_edit,SIGNAL(clicked(bool)),
            this,SLOT(on_pushbutton_edit_clicked()));
    connect(ui->checkBox_pub,SIGNAL(clicked(bool)),
            this , SLOT(on_checkbox_pub_clicked(bool)))  ;

}

void ButtonListWidgetItem::hideAllButton()
{
    ui->pushButton_add->hide();
    ui->pushButton_delete->hide();
    ui->pushButton_edit->hide();
}
