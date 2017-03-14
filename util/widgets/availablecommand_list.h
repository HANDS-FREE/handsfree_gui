#ifndef AVAILABLECOMMAND_LIST_H
#define AVAILABLECOMMAND_LIST_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class AvailableCommandList;
}

class AvailableCommandList : public QWidget
{
    Q_OBJECT

public:
    explicit AvailableCommandList(const QStringList &item_list,QWidget *parent = 0);
    explicit AvailableCommandList(QWidget *parent = 0);
    ~AvailableCommandList();
    void setWidgetItems(const QStringList& items) ;


    //the default mode is single
    void setItemSelectMode(QAbstractItemView::SelectionMode mode);
signals:
    //emit this when user click confirm
    void itemsConfirm(QStringList item_choiced) ;
public slots:
    void on_pushbutton_confirm_clicked() ;
    void on_pushbutton_close_clicked() ;
private:
    void init_SigSlot() ;
private:
    Ui::AvailableCommandList *ui;
};

#endif // AVAILABLECOMMAND_LIST_H
