#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init_signal_slots() ;
private slots:
    void on_newmsg_get() ;
    void on_switchbutton_toggled(bool open) ;
    void on_open_robot_required() ;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
