#ifndef WIDGET_COMMAND_H
#define WIDGET_COMMAND_H

#include <QWidget>
#include <QFrame>
#include <QTreeWidget>
#include <QResizeEvent>
#include <util/factory/linefactory.h>
#include <QTimer>
namespace Ui {
class WidgetCommand;
}
class QTreeWidgetItem ;
class CommandAvailable ;
class AvailableCommandList ;
class QListWidgetItem ;
class ButtonListWidgetItem ;
class TreeWidgetCommandDefault ;
class WidgetCommand : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetCommand(QWidget *parent = 0);
    ~WidgetCommand();
private:
    void init_signal_slots() ;
    void init_view() ;
private slots:
    //only signal from default button item
    void on_item_checkbox_clicked(bool checked,ButtonListWidgetItem* source_item) ;
    void on_item_widget_add_clicked() ;
    void on_item_widget_delete_clicked(ButtonListWidgetItem* delete_target)  ;
    void on_commands_list_confirm(QStringList confirm_list) ;
    void on_timer_timeout() ;
private:
    Ui::WidgetCommand *ui;

    QListWidgetItem *_default_listwidget_item ;
    ButtonListWidgetItem *_default_item_widget ;
    AvailableCommandList *_available_expect_list ;
    TreeWidgetCommandDefault* _default_item_treewidget ;

    QVector<ButtonListWidgetItem *> _vc_item_widget ;
    QMap<ButtonListWidgetItem *,QListWidgetItem *> _map_item_listwidgetItem ;
    QMap<ButtonListWidgetItem *,QTreeWidget *> _map_item_treewidget ;
    QMap<ButtonListWidgetItem *,CommandAvailable *> _map_item_command ;
    QVector<ButtonListWidgetItem *> _vc_item_checked ;

    QTimer *_timer_update_commands;
};


/*-------------------default treewidget---------------------*/
class TreeWidgetCommandDefault: public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidgetCommandDefault(QWidget *parent=0):
        QTreeWidget(parent),
        _item_height(20),
        _item_num(0)
    {

    }
    ~TreeWidgetCommandDefault(){
        this->deleteAllitem();
    }
    void resizeEvent(QResizeEvent *event){
        this->init_view();
    }
protected:
    void deleteAllitem(){
        this->clear();
       // for(int i = 0 ; i < mid_line_num ; i++)delete this->_vc_mid_line[i] ;
        this->_vc_mid_line.clear();
    }
    void init_view(){
        this->deleteAllitem();
        QStringList head_string ;
        head_string<<tr("param")<<tr("value") ;
        this->setHeaderLabels(head_string);
        this->setColumnCount(2);
        this->setIndentation(0);
        this->setColumnWidth(0,this->width()*2/5);
        this->setColumnWidth(1,(this->width()*3-3)/5);
        this->_item_num = this->height()/this->_item_height ;
        for(int i = 0 ; i < this->_item_num ; i++){
            QTreeWidgetItem *item = new QTreeWidgetItem() ;
            item->setDisabled(true);
            item->setTextAlignment(0,Qt::AlignCenter);
            if(0==i%2){
                item->setBackgroundColor(0,QColor("#F0F0F0"));
                item->setBackgroundColor(1,QColor("#F0F0F0"));
            }
            else{
                item->setBackgroundColor(0,QColor("#FFFFF0"));
                item->setBackgroundColor(1,QColor("#FFFFF0"));
            }
            this->addTopLevelItem(item);
            QFrame *mid_line = LineFactory::getNewLine(QFrame::VLine,QSize(1,this->columnWidth(0))) ;
            this->setItemWidget(item,1,mid_line) ;
            this->_vc_mid_line.push_back(mid_line);
        }
    }
private:
    int _item_height ;
    int _item_num ;
    QVector<QFrame *> _vc_mid_line ;
} ;

#endif // WIDGET_COMMAND_H
