#ifndef WIDGET_COMMAND_H
#define WIDGET_COMMAND_H

#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QTreeWidget>
#include <QResizeEvent>
#include <util/factory/linefactory.h>
#include <QTimer>
#include <QDebug>
namespace Ui {
class WidgetCommand;
}
class QTreeWidgetItem ;
class CommandAvailable ;
class AvailableCommandList ;
class QListWidgetItem ;
class ButtonListWidgetItem ;
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
    QLabel* _default_item_label ;

    QVector<ButtonListWidgetItem *> _vc_item_widget ;
    QMap<ButtonListWidgetItem *,QListWidgetItem *> _map_item_listwidgetItem ;
    QMap<ButtonListWidgetItem *,QTreeWidget *> _map_item_treewidget ;
    QMap<ButtonListWidgetItem *,CommandAvailable *> _map_item_command ;
    QVector<ButtonListWidgetItem *> _vc_item_checked ;

    QTimer *_timer_update_commands;
};



#endif // WIDGET_COMMAND_H
