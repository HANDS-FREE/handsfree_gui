#ifndef WIDGETPLOT_H
#define WIDGETPLOT_H

#include <QObject>
#include "qcustomplot.h"

class QMenu ;
class QAction ;
class QActionGroup ;
class WidgetPlot : public QCustomPlot
{
    Q_OBJECT
public:
    WidgetPlot(QWidget *widget=NULL);
    ~WidgetPlot() ;
public slots:
    inline void changeLegendState(bool open){
        this->legend->setVisible(open);
        this->_legend_visable = open ;
        this->replot();
    }
    int addNewGraph(const QString &name , const QColor &line_color , const QColor &dot_color) ;
    void removeSelectedGraph() ;
    void removeAllGraph() ;
    void setData(const int line_id , double x , double y) ;
protected:
private slots:
    void titleDoubleClick( );
    void on_axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part) ;
    void on_legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item) ;
    void on_selectionChanged() ;

    void on_actionGroupTriggered(QAction *target_action) ;
    void on_action_control_triggered() ;
    void on_action_remove_triggered() ;
    void on_action_addLine_triggered() ;
    void on_action_legend_move() ;
    void on_action_return_origin(){
     //   qDebug()<<"rescale" ;
        this->rescaleAxes();
        this->replot();
    }
    inline void on_action_xlabel_changed() {
        this->on_axisLabelDoubleClick(this->xAxis,QCPAxis::spAxisLabel);
    }
    inline void on_action_ylabel_changed(){
        this->on_axisLabelDoubleClick(this->yAxis,QCPAxis::spAxisLabel);
    }
    void on_action_select_axisX(){
       this->yAxis2->setSelectedParts(QCPAxis::spNone);
       this->yAxis->setSelectedParts(QCPAxis::spNone);
        this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
     void on_action_select_axisY(){
        this->xAxis->setSelectedParts(QCPAxis::spNone);
        this->xAxis2->setSelectedParts(QCPAxis::spNone);
        this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
     void on_action_select_none(){
        this->yAxis2->setSelectedParts(QCPAxis::spNone);
        this->yAxis->setSelectedParts(QCPAxis::spNone);
        this->xAxis->setSelectedParts(QCPAxis::spNone);
        this->xAxis2->setSelectedParts(QCPAxis::spNone);
    }

    void contextMenuRequest(QPoint pos);
    void mousePress();
    void mouseWheel();

private:
    void init_SignalSlot() ;
    void init_menu() ;
    void init_plot() ;
private:
    bool _legend_visable ;
    QCPPlotTitle *_title;

    QAction *_action_remove_all ;
    QAction *_action_add_line ;
    QAction *_action_return_to_origin ;


    QMenu *_menu_legend ;
    QActionGroup *_action_group_legend ;
    QAction *_action_legend_pos_topleft ;
    QAction *_action_legend_pos_topright ;
    QAction *_action_legend_pos_bottomleft ;
    QAction *_action_legend_pos_bottomright ;
    QAction *_action_legend_set ;

    QMenu *_menu_axis ;
    QActionGroup *_action_group_select_axis ;
    QAction *_action_axis_x_select ;
    QAction *_action_axis_y_select ;
    QAction *_action_axis_all_select ;

    QAction *_action_plot_control ;
    QAction *_action_setting ;

   QMenu *_menu_change_text ;
    QAction *_action_change_title ;
    QAction *_action_change_xlabel ;
    QAction *_action_change_ylabel ;

    QMenu *_menu_main ;

};

#endif // WIDGETPLOT_H
