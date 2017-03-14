#ifndef WIDGET_VISUALIZATION_H
#define WIDGET_VISUALIZATION_H

#include <QWidget>

namespace Ui {
class WidgetVisualization;
}

class WidgetVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVisualization(QWidget *parent = 0);
    ~WidgetVisualization();

private:
    Ui::WidgetVisualization *ui;
};

#endif // WIDGET_VISUALIZATION_H
