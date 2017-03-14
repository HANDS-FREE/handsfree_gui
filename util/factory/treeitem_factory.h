#ifndef TREEITEMFACTORY_H
#define TREEITEMFACTORY_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QDebug>

class TreeItemFactory
{
public:
    static inline QTreeWidgetItem* makeNewItem(QTreeWidget *target_widget,
                                                                    const int col_1,
                                                                    const QString &text,
                                                                    QTreeWidgetItem *target_item = NULL)
    {
        if(NULL==target_widget)return NULL;
        QTreeWidgetItem *new_item = new QTreeWidgetItem() ;
        if(target_item!=NULL)target_item->addChild(new_item);
        else target_widget->addTopLevelItem(new_item);
        new_item->setText(col_1,text);
        return new_item ;
    }

    static inline QTreeWidgetItem* makeNewItem(QTreeWidget *target_widget,
                                                                    const int col_1,
                                                                    const QString& text,
                                                                    const int col_2,
                                                                    QWidget* widget,
                                                                    QTreeWidgetItem *target_item = NULL)
    {
        if(NULL==target_widget||NULL==widget)return NULL;
        QTreeWidgetItem *new_item = new QTreeWidgetItem() ;
        new_item->setText(col_1,text);
        if(target_item!=NULL)target_item->addChild(new_item);
        else target_widget->addTopLevelItem(new_item);
        target_widget->setItemWidget(new_item,col_2,widget);
        return new_item ;
    }

    static inline QTreeWidgetItem* makeNewItem(QTreeWidget *target_widget,
                                                                    const int col_1,
                                                                    const QString& text,
                                                                    const int col_2,
                                                                    const QString& text_2,
                                                                    QTreeWidgetItem *target_item = NULL)
    {
        if(NULL==target_widget)return NULL;
        QTreeWidgetItem *new_item = new QTreeWidgetItem() ;
        if(target_item!=NULL)target_item->addChild(new_item);
        else target_widget->addTopLevelItem(new_item);
        new_item->setText(col_1,text);
        new_item->setText(col_2,text_2);
        return new_item ;
    }

private:
  TreeItemFactory(){}
signals:

public slots:
};

#endif // TREEITEMFACTORY_H
