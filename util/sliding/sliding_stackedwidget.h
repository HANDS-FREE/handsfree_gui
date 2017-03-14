#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>

class SlidingMoudle ;
class QMutex ;


class SlidingStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    SlidingStackedWidget(QWidget *parent=0);
    ~SlidingStackedWidget() ;
    void setEnableShake(bool need_shake) ;
public slots:
    void setCurrentIndex(int id) ;
    void onAnimationDone() ;
private slots:
    void slidingFromBottom(int next_id) ;
    void slidingFromTop(int next_id) ;
    void onCurrentIndexChanged(int id){
        Q_UNUSED(id) ;
        this->_w_active = false;
    }
private:
    int _prev_id ;
    int _now_id ;
    int _next_id ;


    bool _w_active ; //same to _m_active
    SlidingMoudle *_sliding_moudle ;
};

#endif // SLIDINGSTACKEDWIDGET_H
