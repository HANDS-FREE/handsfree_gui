#include "widget_plot.h"
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QInputDialog>
WidgetPlot::WidgetPlot(QWidget *widget):
    QCustomPlot(0),
    _legend_visable(false)
{
    this->init_menu();
    this->init_plot();
    this->init_SignalSlot();
}

WidgetPlot::~WidgetPlot()
{
    delete _action_return_to_origin ;
    delete _action_remove_all ;
    delete _action_add_line ;

    delete _menu_legend ;
    delete _action_group_legend ;
    delete _action_legend_pos_topleft ;
    delete _action_legend_pos_topright ;
    delete _action_legend_pos_bottomleft ;
    delete _action_legend_pos_bottomright ;
    delete _action_legend_set ;

    delete _menu_axis ;
    delete _action_group_select_axis ;
    delete _action_axis_x_select ;
    delete _action_axis_y_select ;
    delete _action_axis_all_select ;

    delete _action_plot_control ;
    delete _action_setting ;

    delete _menu_change_text ;
    delete _action_change_title ;
    delete _action_change_xlabel ;
    delete _action_change_ylabel ;

    delete _menu_main ;
    delete _title ;
}

int WidgetPlot::addNewGraph(const QString &name, const QColor &line_color, const QColor &dot_color)
{
    //set line info
    int line_id = this->graphCount() ;
    this->addGraph() ;
    this->graph(line_id)->setPen(QPen(line_color));
    this->graph(line_id)->setName(name);

    //set dot information
    int dot_id = line_id+1 ;
    this->graph(dot_id)->setPen(QPen(dot_color));
    this->graph(dot_id)->setLineStyle(QCPGraph::lsNone) ;
    this->graph(dot_id)->setScatterStyle(QCPScatterStyle::ssDisc);

    return line_id ;

}

void WidgetPlot::removeSelectedGraph()
{
    if(this->selectedGraphs().size() > 0){
        this->removeGraph(this->selectedGraphs().first()) ;
        this->replot();
    }
}

void WidgetPlot::removeAllGraph()
{
    this->clearGraphs();
    this->replot();
}

void WidgetPlot::setData(const int line_id, double x, double y)
{
    int dot_id = line_id+1 ;
    this->graph(line_id)->addData(x,y);
    //to draw dot
    this->graph(dot_id)->clearData();
    this->graph(dot_id)->addData(x,y);
    this->graph(line_id)->rescaleAxes();
    this->xAxis->setRange(x,this->xAxis->range().size(),Qt::AlignRight);
}

void WidgetPlot::titleDoubleClick()
{
    bool ok;
    QString newTitle = QInputDialog::getText(this, "change title", "New plot title:", QLineEdit::Normal, this->_title->text(), &ok);
    if (ok)
    {
        this->_title->setText(newTitle);
        this->replot();
    }
}

void WidgetPlot::on_axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    if (part == QCPAxis::spAxisLabel)
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, tr("QCustomPlot example"),tr("New axis label:"), QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            this->replot();
        }
    }
}

void WidgetPlot::on_legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    Q_UNUSED(legend)
    if (item)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, tr("change legend name"), tr("New graph name:"), QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            this->replot();
        }
    }
}

void WidgetPlot::on_selectionChanged()
{
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    for (int i=0; i<this->graphCount(); ++i)
    {
        QCPGraph *graph = this->graph(i);
        QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelected(true);
        }
    }
}

void WidgetPlot::on_actionGroupTriggered(QAction *target_action)
{
    target_action->setCheckable(true);
    target_action->setChecked(true);
}

void WidgetPlot::on_action_control_triggered()
{

}

void WidgetPlot::on_action_remove_triggered()
{

}

void WidgetPlot::on_action_addLine_triggered()
{

}

void WidgetPlot::on_action_legend_move()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            if(-1==dataInt)this->changeLegendState(!this->_legend_visable);
            else{
                this->legend->setVisible(true);
                this->_legend_visable = true ;
                this->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
                this->replot();
            }
        }
    }
}


void WidgetPlot::contextMenuRequest(QPoint pos)
{
    if(!this->rect().contains(pos))return ;
    this->_menu_main->popup(this->mapToGlobal(pos));
}

void WidgetPlot::mousePress()
{
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->yAxis->orientation());
    else
        this->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void WidgetPlot::mouseWheel()
{
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->yAxis->orientation());
    else
        this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void WidgetPlot::init_SignalSlot()
{
    connect(this,SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
            this,SLOT(on_axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart))) ;
    connect(this,SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this,SLOT(on_legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*))) ;
    connect(this,SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)),
            this,SLOT(titleDoubleClick())) ;

    connect(this,SIGNAL(mousePress(QMouseEvent*)),
            this,SLOT(mousePress())) ;
    connect(this , SIGNAL(mouseWheel(QWheelEvent*)),
            this,SLOT(mouseWheel())) ;

    connect(this->xAxis,SIGNAL(rangeChanged(QCPRange)),
            this->xAxis2,SLOT(setRange(QCPRange))) ;
    connect(this->yAxis,SIGNAL(rangeChanged(QCPRange)),
            this->yAxis2,SLOT(setRange(QCPRange))) ;

    connect(this,SIGNAL(selectionChangedByUser()),
            this,SLOT(on_selectionChanged())) ;
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(contextMenuRequest(QPoint)));

    connect(this->_action_group_legend,SIGNAL(triggered(QAction*)),
            this , SLOT(on_actionGroupTriggered(QAction*))) ;
    connect(this->_action_group_select_axis,SIGNAL(triggered(QAction*)),
            this,SLOT(on_actionGroupTriggered(QAction*))) ;

    connect(this->_action_legend_pos_bottomleft,SIGNAL(triggered(bool)),
            this,SLOT(on_action_legend_move()));
    connect(this->_action_legend_pos_bottomright,SIGNAL(triggered(bool)),
            this,SLOT(on_action_legend_move()));
    connect(this->_action_legend_pos_topleft,SIGNAL(triggered(bool)),
            this,SLOT(on_action_legend_move()));
    connect(this->_action_legend_pos_topright,SIGNAL(triggered(bool)),
            this,SLOT(on_action_legend_move()));
    connect(this->_action_legend_set,SIGNAL(triggered(bool)),
            this,SLOT(on_action_legend_move()));

    connect(this->_action_change_title,SIGNAL(triggered(bool)),
            this,SLOT(titleDoubleClick())) ;

    connect(this->_action_axis_x_select,SIGNAL(triggered(bool)),
            this,SLOT(on_action_select_axisX())) ;
    connect(this->_action_axis_y_select,SIGNAL(triggered(bool)),
            this,SLOT(on_action_select_axisY())) ;
    connect(this->_action_axis_all_select,SIGNAL(triggered(bool)),
            this,SLOT(on_action_select_none())) ;

    connect(this->_action_change_xlabel,SIGNAL(triggered(bool)),
            this,SLOT(on_action_xlabel_changed())) ;
    connect(this->_action_change_ylabel,SIGNAL(triggered(bool)),
            this,SLOT(on_action_ylabel_changed())) ;
    connect(this->_action_return_to_origin,SIGNAL(triggered(bool)),
            this,SLOT(on_action_return_origin())) ;

}

void WidgetPlot::init_menu()
{
    this->_menu_main = new QMenu() ;

    this->_action_return_to_origin = new QAction(tr("return to the origin"),this) ;
    this->_action_remove_all = new QAction(tr("remove all line"),this) ;
    this->_action_add_line = new QAction(tr("add new line"),this) ;

    this->_action_group_legend = new QActionGroup(this) ;
    this->_action_legend_pos_topleft = new QAction(tr("show the legend on top_left"),this) ;
    this->_action_legend_pos_topleft->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    this->_action_legend_pos_topright = new QAction(tr("show legend on top_right"),this) ;
    this->_action_legend_pos_topright->setData((int)(Qt::AlignTop|Qt::AlignRight));
    this->_action_legend_pos_bottomleft = new QAction(tr("show legend on bottom_left"),this) ;
    this->_action_legend_pos_bottomleft->setData((int)(Qt::AlignBottom|Qt::AlignLeft)) ;
    this->_action_legend_pos_bottomright = new QAction(tr("show legend on bottom_right"),this) ;
    this->_action_legend_pos_bottomright->setData((int)(Qt::AlignBottom|Qt::AlignRight)) ;
    this->_action_legend_set = new QAction(tr("hide/show the legend"),this) ;
    this->_action_legend_set->setData((int)-1);

    this->_action_group_select_axis = new QActionGroup(this) ;
    this->_action_axis_x_select = new QAction(tr("select the x axis"),this) ;
    this->_action_axis_y_select = new QAction(tr("select the y axis"),this) ;
    this->_action_axis_all_select = new QAction(tr("select the x and y axis"),this) ;

    this->_action_plot_control = new QAction(tr("run/stop the plot"),this) ;
    this->_action_setting = new QAction(tr("setting"),this) ;

    this->_action_change_title = new QAction(tr("change the text of title"),this) ;
    this->_action_change_xlabel = new QAction(tr("change the text of x-label"),this) ;
    this->_action_change_ylabel = new QAction(tr("change the text of y-label"),this) ;

    /*--------------------------------plot control and setting--------------------------------------------------------*/
    this->_menu_main->addAction(this->_action_plot_control) ;
    this->_menu_main->addAction(this->_action_setting) ;
    this->_menu_main->addAction(this->_action_return_to_origin) ;
    this->_menu_main->addSeparator() ;
    /*------------------------------------remove and add----------------------------------------------------*/
    this->_menu_main->addAction(this->_action_remove_all) ;
    this->_menu_main->addAction(this->_action_add_line) ;
    this->_menu_main->addSeparator() ;
    /*--------------------------------select axis--------------------------------------------------------*/
    this->_menu_axis = this->_menu_main->addMenu(tr("focus axis")) ;
    this->_action_group_select_axis->addAction(this->_action_axis_x_select) ;
    this->_action_group_select_axis->addAction(this->_action_axis_y_select) ;
    this->_action_group_select_axis->addAction(this->_action_axis_all_select) ;
    this->_action_group_select_axis->setExclusive(true);
    this->_action_axis_all_select->setCheckable(true);
    this->_action_axis_all_select->setChecked(true);

    this->_menu_axis->addAction(this->_action_axis_x_select) ;
    this->_menu_axis->addAction(this->_action_axis_y_select) ;
    this->_menu_axis->addAction(this->_action_axis_all_select) ;

    /*----------------------------------text------------------------------------------------------*/
    this->_menu_change_text = this->_menu_main->addMenu(tr("text")) ;
    this->_menu_change_text->addAction(this->_action_change_title) ;
    this->_menu_change_text->addAction(this->_action_change_xlabel) ;
    this->_menu_change_text->addAction(this->_action_change_ylabel) ;

    /*--------------------------------------legend--------------------------------------------------*/
    this->_menu_legend = this->_menu_main->addMenu(tr("legend pos")) ;
    this->_action_group_legend->addAction(this->_action_legend_pos_topleft) ;
    this->_action_group_legend->addAction(this->_action_legend_pos_topright) ;
    this->_action_group_legend->addAction(this->_action_legend_pos_bottomleft) ;
    this->_action_group_legend->addAction(this->_action_legend_pos_bottomright) ;
    this->_action_group_legend->addAction(this->_action_legend_set) ;
    this->_action_group_legend->setExclusive(true);
    this->_action_legend_set->setCheckable(true);
    this->_action_legend_set->setChecked(true);

    this->_menu_legend->addAction(this->_action_legend_pos_topleft) ;
    this->_menu_legend->addAction(this->_action_legend_pos_topright) ;
    this->_menu_legend->addAction(this->_action_legend_pos_bottomleft) ;
    this->_menu_legend->addAction(this->_action_legend_pos_bottomright) ;
    this->_menu_legend->addAction(this->_action_legend_set) ;
    this->_menu_main->addSeparator() ;
    /*---------------------------------end for action set---------------------------------------*/

    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void WidgetPlot::init_plot()
{
    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                          QCP::iSelectLegend | QCP::iSelectPlottables);
    this->xAxis->setLabel("x Axis");
    this->yAxis->setLabel("y Axis");
    this->axisRect()->setupFullAxesBox();
    this->plotLayout()->insertRow(0);
    this->_title = new QCPPlotTitle(this, "Click To Change");
    this->legend->setFont( QFont("sans", 10, QFont::Bold));
    this->plotLayout()->addElement(0,0,this->_title) ;
}


