#ifndef RADAR_POS_H
#define RADAR_POS_H

#include <QWidget>


class WidgetRadar : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRadar(QWidget *parent = 0);
    ~WidgetRadar();
    void setPoint(double x , double y) ;
    void setPoint(const QPointF &point) ;
private:
    float getTargetPositionPoint(float x) ;
    void changeScanerRegion(double start_angle) ;
    void drawBackground() ;
    void paintEvent(QPaintEvent *e) ;
private:
    QPointF *_mid_point ;
    QRect *_rader_rect ;
    QPolygonF *_scanning_region ;
    float _scale ;
    float _scale_delt ;
    int _max_radius ;
    double _start_angle ;
    double _angle_delt ;
    QPointF *_target_point ;
    QColor _color_current ;
    QColor _color_last ;
};

#endif // RADAR_POS_H


