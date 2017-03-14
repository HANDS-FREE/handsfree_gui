#include "util/sliding/sliding_moudle.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QDebug>
#include <QMutex>

SlidingMoudle::SlidingMoudle(QObject *parent) :
    QObject(parent),
    _has_size(false),
    _need_shake(false),
    _duration(0),
    _m_active(false),
    _container_size(NULL)
{
}

SlidingMoudle::~SlidingMoudle(){
    delete this->_container_size ;
}

void SlidingMoudle::slideComponent(QWidget *now, QWidget *next, Direct t_direction)
{
    if(this->_m_active)return ;//this means there are some animation
                               //unfishing
    this->_m_active = true ;
    if(!now||!next)return ;
    this->_now_widget = now ;
    this->_next_widget = next ;
    this->moveComponent(t_direction);
}

void SlidingMoudle::slideComponent(QWidget *now, const QPoint &target_point)
{
    if(this->_m_active)return ;//this means there are some animation
                               //unfishing
    this->_m_active = true ;
    this->_now_widget = now ;
    this->_next_widget = NULL ;
    QPropertyAnimation *animation = new QPropertyAnimation(this->_now_widget,"pos") ;
    animation->setDuration(500);
    animation->setStartValue(this->_now_widget->pos());
    animation->setEndValue(target_point);
    animation->start();
    connect(animation,SIGNAL(finished()),this,SLOT(on_animation_over())) ;
}

void SlidingMoudle::on_animation_over()
{
    //set the prev widget to original position
    if(this->_next_widget!=NULL){
    this->_now_widget->hide();
    this->_now_widget->move(this->_next_widget->pos());
    }
    emit this->moveFinished();
    this->_m_active = false ;

}

void SlidingMoudle::moveComponent(Direct t_direction)
{
    if(!this->_container_size)return ;
    QPoint p_now = this->_now_widget->pos() ;
    QPoint p_next = this->_next_widget->pos() ;

    //make sure that next widget is hiden before animation starting.
    this->_next_widget->show();
    this->_next_widget->raise();

    int offset_x = this->_container_size->width() ;
    int offset_y = this->_container_size->height() ;
    if(t_direction==BOTTOM2TOP){
        offset_x = 0 ;
        offset_y = -offset_y ;
    }
    else if(t_direction==TOP2BOTTOM){
        offset_x = 0  ;
        offset_y = offset_y ;
    }
    else if(t_direction==LEFT2RIGHT){
        offset_x = offset_x ;
        offset_y = 0 ;
    }
    else if(t_direction==RIGHT2LEFT){
        offset_x = -offset_x ;
        offset_y = 0 ;
    }
    QPropertyAnimation *animation_now = new QPropertyAnimation(this->_now_widget,"pos") ;
    animation_now->setDuration(this->_duration);
    animation_now->setStartValue(p_now);
    animation_now->setEndValue(QPoint(p_now.x()+offset_x,p_now.y()+offset_y));

    QPropertyAnimation *animation_next = new QPropertyAnimation(this->_next_widget,"pos") ;
    animation_next->setDuration(this->_duration);
    animation_next->setStartValue(QPoint(p_next.x()-offset_x,p_next.y()-offset_y));
    animation_next->setEndValue(p_now);

    if(this->_need_shake){
        animation_now->setEasingCurve(QEasingCurve::OutBounce);
        animation_next->setEasingCurve(QEasingCurve::OutBounce);
    }
    QParallelAnimationGroup *animation_group = new QParallelAnimationGroup() ;
    animation_group->addAnimation(animation_now);
    animation_group->addAnimation(animation_next);

    connect(animation_group,SIGNAL(finished()),this,SLOT(on_animation_over())) ;
    animation_group->start();
}

