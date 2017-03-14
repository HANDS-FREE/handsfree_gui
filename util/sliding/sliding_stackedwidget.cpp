#include <util/sliding/sliding_moudle.h>
#include <util/sliding/sliding_stackedwidget.h>
#include <QDebug>
#include <QMutex>
SlidingStackedWidget::SlidingStackedWidget(QWidget *parent)
    :QStackedWidget(parent),
      _prev_id(-1),
      _now_id(0),
      _next_id(-1),
      _w_active(false)
{
    this->_sliding_moudle = new SlidingMoudle() ;
    this->_sliding_moudle->setDuration(200);
    this->_sliding_moudle->setContainerSize(this->size());

    connect(this->_sliding_moudle,SIGNAL(moveFinished()),
            this,SLOT(onAnimationDone()));
}

SlidingStackedWidget::~SlidingStackedWidget()
{
    delete this->_sliding_moudle ;
}

void SlidingStackedWidget::setEnableShake(bool need_shake)
{
    this->_sliding_moudle->setEndWithShake(need_shake);
}

void SlidingStackedWidget::setCurrentIndex(int id)
{
    if(this->_w_active)return ;
    this->_now_id = this->currentIndex() ;
    this->_next_id = id ;
    if(this->_now_id==this->_next_id)return ;
    this->_w_active = true ;

    if(this->_now_id<this->_next_id){
        this->slidingFromBottom(this->_next_id);
    }
    else if(this->_now_id>this->_next_id){
        this->slidingFromTop(this->_next_id);
    }
    QStackedWidget::setCurrentIndex(id) ;
}

void SlidingStackedWidget::slidingFromBottom(int next_id)
{
    this->_sliding_moudle->slideComponent(widget(this->_now_id),
                                          widget(next_id),
                                          BOTTOM2TOP);
}

void SlidingStackedWidget::slidingFromTop(int next_id)
{
    this->_sliding_moudle->slideComponent(widget(this->_now_id),
                                          widget(next_id),
                                          TOP2BOTTOM);
}



void SlidingStackedWidget::onAnimationDone()
{
    this->setCurrentIndex(this->_next_id);
    this->_w_active = false ;
}
