#include "availablecommand_list.h"
#include <QDebug>
#include "ui_availablecommand_list.h"
AvailableCommandList::AvailableCommandList(const QStringList &item_list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailableCommandList)
{
    ui->setupUi(this);
    ui->listWidget->addItems(item_list);
    this->init_SigSlot();
}

AvailableCommandList::AvailableCommandList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailableCommandList)
{
    ui->setupUi(this);
    this->init_SigSlot();
}

AvailableCommandList::~AvailableCommandList()
{
    delete ui;
}

void AvailableCommandList::setWidgetItems(const QStringList &items)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(items);
}

void AvailableCommandList::setItemSelectMode(QAbstractItemView::SelectionMode mode)
{
    ui->listWidget->setSelectionMode(mode);
}

void AvailableCommandList::on_pushbutton_confirm_clicked()
{
    QStringList item_selected ;
    size_t size = ui->listWidget->selectedItems().size() ;
    for(size_t i = 0 ; i < size ; i++){
        item_selected<<ui->listWidget->selectedItems().at(i)->text() ;
    }
    emit itemsConfirm(item_selected);
    ui->listWidget->clearSelection();
    this->close();
}

void AvailableCommandList::on_pushbutton_close_clicked()
{
    this->close() ;
}

void AvailableCommandList::init_SigSlot()
{
    connect(ui->pushButton_confirm,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_confirm_clicked())) ;
    connect(ui->pushButton_close,SIGNAL(clicked(bool)) ,this, SLOT(on_pushbutton_close_clicked())) ;
}
