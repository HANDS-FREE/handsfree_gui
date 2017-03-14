#ifndef LINEFACTORY_H
#define LINEFACTORY_H

#include <QObject>
#include <QFrame>
typedef enum{HLINE,VLINE} LTYPE ;

class LineFactory
{
public:
    LineFactory();
    //get a new line
    static QFrame* getNewLine(QFrame::Shape target_shape, const QSize &target_size){
        QFrame *line = new QFrame();
        line->setMaximumSize(target_size);
       line->resize(target_size);
        line->setStyleSheet("QFrame{background-color:#ABABAB}");
        line->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        line->setFrameShape(target_shape);
        line->setFrameShadow(QFrame::Sunken);
        return line ;
    }
};

#endif // LINEFACTORY_H
