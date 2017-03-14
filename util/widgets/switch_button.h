#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QObject>
#include <QWidget>

#include <QWidget>
#include <QTimer>

class SwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchButton(QWidget *parent = 0);

    bool isToggled() const;

    void setToggle(bool checked);


    void setBackgroundColor(QColor color);

    void setCheckedColor(QColor color);

    void setDisbaledColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void toggled(bool checked);

private slots:
    void onTimeout();

private:
    bool m_bChecked;         // 是否选中
    QColor m_background;     // 背景颜色
    QColor m_checkedColor;   // 选中颜色
    QColor m_disabledColor;  // 不可用颜色
    QColor m_thumbColor;     // 拇指颜色
    qreal m_radius;          // 圆角
    qreal m_nX;              // x点坐标
    qreal m_nY;              // y点坐标
    qint16 m_nHeight;        // 高度
    qint16 m_nMargin;        // 外边距
    QTimer m_timer;          // 定时器
};

#endif // SWITCHBUTTON_H
