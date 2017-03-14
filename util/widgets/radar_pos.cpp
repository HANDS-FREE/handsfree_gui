#include "radar_pos.h"
#include <QPainter>
#include <QThread>
#include <QConicalGradient>
#include <QtMath>
#include <QDebug>

WidgetRadar::WidgetRadar(QWidget *parent) :
    QWidget(parent),
    _start_angle(0.0),
    _angle_delt(2.6),
    _scale(0.01)
{
    this->_mid_point = new QPointF() ;
    this->_target_point = new QPointF() ;
    this->_rader_rect = new QRect() ;
    this->_scanning_region = new QPolygonF() ;
    this->_color_last = QColor("#FFFFFF") ;
}


WidgetRadar::~WidgetRadar()
{
    delete _mid_point ;
    delete _rader_rect ;
    //   delete _target_point ;
    delete _scanning_region ;
}
void WidgetRadar::setPoint(double x, double y)
{
    float coordinate_x , coordinate_y ;
    //bigger axis decide the scale
    if(fabs(x)>fabs(y)){
        coordinate_x = getTargetPositionPoint(x) ;
        coordinate_y = -getTargetPositionPoint(y) ;
    }
    else{
        coordinate_y = -getTargetPositionPoint(y) ;
        coordinate_x = getTargetPositionPoint(x) ;
    }
    this->_target_point->setX(this->_mid_point->x()+coordinate_x);
    this->_target_point->setY(this->_mid_point->y()+coordinate_y);
    update();
}

void WidgetRadar::setPoint(const QPointF &point)
{
    this->setPoint(point.x() , point.y());
}

float WidgetRadar::getTargetPositionPoint(float x)
{
    float target_x = fabs(x) ;

    while((target_x/this->_scale)>=4){
        //has out the coordinate)
        this->_scale = this->_scale*10 ;
    }
    //get the position on the coordinate
    float position = (target_x/this->_scale)*5*this->_scale_delt ;
    if(x>0)return position ;
    else return -position ;
}

void WidgetRadar::changeScanerRegion(double start_angle)
{
    this->_scanning_region->clear();
    double end_angle = start_angle - 60.0 ;
    double mid_angle = start_angle - 30.0 ;
    //point 1 //start point
    this->_scanning_region->push_back(*(this->_mid_point));

    //point 2
    double point_1_x = this->_mid_point->x()+this->_max_radius*cos(this->_start_angle*M_PI/180) ;
    double point_1_y = this->_mid_point->y()-this->_max_radius*sin(this->_start_angle*M_PI/180) ;
    this->_scanning_region->push_back(QPointF(point_1_x,point_1_y));

    //point 3
    double point_2_x = this->_mid_point->x()+this->_max_radius*cos(mid_angle*M_PI/180) ;
    double point_2_y = this->_mid_point->y()-this->_max_radius*sin(mid_angle*M_PI/180) ;
    this->_scanning_region->push_back(QPointF(point_2_x,point_2_y));

    //point 4
    double point_3_x = this->_mid_point->x()+this->_max_radius*cos(end_angle*M_PI/180) ;
    double point_3_y = this->_mid_point->y()-this->_max_radius*sin(end_angle*M_PI/180) ;
    this->_scanning_region->push_back(QPointF(point_3_x,point_3_y));

    //point 5 (end point)
    this->_scanning_region->push_back(*(this->_mid_point));

}

void WidgetRadar::drawBackground()
{
    QPalette pal(this->palette()) ;
    pal.setColor(QPalette::Background,QColor("#0A0A0A"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->_mid_point->setX(this->size().width()/2) ;
    this->_mid_point->setY(this->size().height()/2);

    QPainter painter(this) ;
    this->_max_radius = (this->size().height()>this->size().width()?this->size().width():this->size().height()-4)/2 ;


    QPen ellipse_pen ;
    ellipse_pen.setBrush(QBrush(QColor("#698B22")));
    ellipse_pen.setWidth(3);
    painter.setPen(ellipse_pen);
    //draw 4 ellipses
    int radius_delt = (this->_max_radius-0)/4 ;
    for(int radius = 0 ;  radius<=this->_max_radius ; radius+=radius_delt)painter.drawEllipse(*(this->_mid_point),radius,radius);

    //draw cross_line
    QPen line_pen ;
    line_pen.setBrush(QBrush(QColor("#698B22")));
    line_pen.setWidth(1);
    painter.setPen(line_pen);
    QPoint horizental_start_point = QPoint(this->_mid_point->rx()-this->_max_radius,this->_mid_point->ry()) ;
    QPoint horizental_end_point = QPoint(this->_mid_point->rx()+this->_max_radius,this->_mid_point->ry()) ;

    QPoint vertical_start_point = QPoint(this->_mid_point->rx(),this->_mid_point->ry()-this->_max_radius) ;
    QPoint vertical_end_point = QPoint(this->_mid_point->rx(),this->_mid_point->ry()+this->_max_radius) ;

    painter.drawLine(horizental_start_point,horizental_end_point);
    painter.drawLine(vertical_start_point,vertical_end_point);
    this->_scale_delt = (this->_max_radius-0)/4/5 ; //have 5 scale between two circle
    //draw horizental scale
    for(float i = 0 ; i <= this->_max_radius ; i+=this->_scale_delt){
        painter.drawLine(this->_mid_point->x()+i,this->_mid_point->y(),this->_mid_point->x()+i,this->_mid_point->y()-5);
    }

    //draw the mid point
    QPen point_pen ;
    point_pen.setBrush((QBrush(QColor("#EEC900"))));
    point_pen.setWidth(8) ;
    painter.setPen(point_pen);
    painter.drawPoint(*(this->_mid_point));

    this->_rader_rect->setRect(this->_mid_point->x()-this->_max_radius,this->_mid_point->y()-this->_max_radius
                               ,this->_max_radius*2,this->_max_radius*2);
}

void WidgetRadar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e) ;
    this->drawBackground();
    QPainter arc_painter(this) ;
    if(this->_start_angle>=360)this->_start_angle = this->_start_angle-360.0 ;
    QConicalGradient arc_brush(*(this->_mid_point),this->_start_angle) ;
    arc_brush.setColorAt(0.8,QColor("#FFFFFF"));
    arc_brush.setColorAt(0.9,QColor("#CAFF70"));
    arc_brush.setColorAt(1.0,QColor("#698B22"));
    arc_painter.setBrush(QBrush(arc_brush));
    arc_painter.setOpacity(0.2);
    arc_painter.drawPie(*(this->_rader_rect),this->_start_angle*16,360*16) ;
    this->changeScanerRegion(this->_start_angle);
    if(this->_scanning_region->containsPoint(*(this->_target_point),Qt::OddEvenFill)){
        this->_color_current.setRgb(255,0,0);
    }
    else{
        this->_color_current = this->_color_last.lighter(101) ;
    }
    this->_color_last = this->_color_current ;
    arc_painter.setPen(QColor(this->_color_current));
    arc_painter.setBrush(QBrush(QColor(this->_color_current)));
    arc_painter.setOpacity(1.0);
    //could draw the point
    if(this->_color_current.blue()!=255&&this->_color_current.green()!=255)arc_painter.drawEllipse(this->_target_point->x(),this->_target_point->y(),11,11);
    this->_start_angle+=this->_angle_delt ;
    this->_scale = 0.01 ;
    QThread::msleep(15) ;
    update() ;
}

