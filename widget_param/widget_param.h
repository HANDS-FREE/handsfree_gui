#ifndef WIDGET_PARAM_H
#define WIDGET_PARAM_H

#include <QWidget>

class  CommandAvailable ;
namespace Ui {
class WidgetParam;
}

class WidgetParam : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetParam(QWidget *parent = 0);
    ~WidgetParam();
public slots:
    void on_new_msg_get() ;
private:
    void init_signal_slot() ;
    void init_param_widget() ;
private:
    Ui::WidgetParam *ui;
    QStringList _available_measure_list ;
    std::vector<CommandAvailable *> _vc_measure_commands ;
};

#endif // WIDGET_PARAM_H
