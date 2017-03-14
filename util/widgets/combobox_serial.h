#ifndef COMBOBOXSERIALNAME_H
#define COMBOBOXSERIALNAME_H

#include <QObject>
#include <QComboBox>
#include <QGroupBox>
class ComboBoxSerialName : public QComboBox
{
public:
    ComboBoxSerialName(QWidget *parent);
    void showPopup();
public slots:
    void refresh_usb_list() ;
};

#endif // COMBOBOXSERIALNAME_H
