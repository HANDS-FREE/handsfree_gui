#ifndef SLIDINGMOUDLE_H
#define SLIDINGMOUDLE_H

/*
    author : liao-zhihan
    date : 2017-01-07
    version : v1.0
    description : this is a library for exchange two widgets by sliding
    warn :
        1.duration must be set!
        2.container size must be set!
*/

#include <QObject>
#include <QWidget>

typedef enum{
    BOTTOM2TOP,
    TOP2BOTTOM,
    LEFT2RIGHT,
    RIGHT2LEFT
}Direct ;


class SlidingMoudle : public QObject
{
    Q_OBJECT
public:
    explicit SlidingMoudle(QObject *parent = 0);
    ~SlidingMoudle() ;
    void setContainerSize(const int width ,const int height){
        this->_container_size = new QSize(width,height);
    }
    void setContainerSize(const QSize &size){
        this->_container_size = new QSize(size);
    }

    void setDuration(const int ms){
        this->_duration = ms;
    }


    void setEndWithShake(bool need_shake){
        this->_need_shake = need_shake ;
    }

    bool canRequest()const{return this->_m_active;}

    void slideComponent(QWidget *now , QWidget *next , Direct t_direction) ;
    void slideComponent(QWidget *now , const QPoint &target_point) ;
signals:
    // emit this after animation is over
    void moveFinished() ;
public slots:
    //reset the _m_active false
    void on_animation_over() ;
private:
    void moveComponent(Direct t_direction) ;
private:
    QSize *_container_size ;
    bool _has_size ;
    bool _need_shake ;
    int _duration ;
    QWidget *_now_widget , *_next_widget ;

    /*
        _m_active is a very important  value,
        when we start the animation we set the _m_active true
        which means we would not accept next request.
        After the current animation is over , we would reset the
        _m_active false,which means we could accept next request.
    */
    bool _m_active ;

};

#endif // SLIDINGMOUDLE_H
