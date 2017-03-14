#include "widget_visualization.h"
#include "ui_widget_visualization.h"

WidgetVisualization::WidgetVisualization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVisualization)
{
    ui->setupUi(this);
}

WidgetVisualization::~WidgetVisualization()
{
    delete ui;
}
