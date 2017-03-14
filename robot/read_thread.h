#ifndef TRANSPORTSERIAL_H
#define TRANSPORTSERIAL_H

#include <QThread>
#include <QMutex>

class ThreadRead : public QThread
{
    Q_OBJECT
public:
    explicit ThreadRead(QObject *parent = 0);
    ~ThreadRead() ;
signals:
    void newMsgGet() ;
    void stopRead() ;
private:
    void run();
public slots:
    void stop();
private:
    QMutex *_mutex_stop ;
    bool _stop_read ;
};

#endif // TRANSPORTSERIAL_H
