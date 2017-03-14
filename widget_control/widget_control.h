#ifndef WIDGET_CONTROL_H
#define WIDGET_CONTROL_H

#include <QWidget>
#include <robot/robot_commands.h>
namespace Ui {
class WidgetControl;
}
class CommandAvailable ;
class WidgetControl : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetControl(QWidget *parent = 0);
    ~WidgetControl();
    void keyPressEvent(QKeyEvent *e) ;
    void keyReleaseEvent(QKeyEvent *e) ;
    void brake() ;
    void changeCurrentLabel() ;
signals:
    void openRobotRequired() ;
private:
    Ui::WidgetControl *ui;


    //this is only for handsfree_gui v0.1
    //and one day we may change our command framework
    //how about the decorate partten?
    float _current_speed ;
    float _speed_scale ;
};


#endif // WIDGET_CONTROL_H
