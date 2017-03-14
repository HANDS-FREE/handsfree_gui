#include "combobox_serial.h"
#include <QtSerialPort/QSerialPortInfo>
ComboBoxSerialName::ComboBoxSerialName(QWidget *parent):
    QComboBox(parent)
{

    this->refresh_usb_list();
}

void ComboBoxSerialName::showPopup()
{
    this->refresh_usb_list();
    QComboBox::showPopup();
}

void ComboBoxSerialName::refresh_usb_list()
{
    this->clear();
    QStringList list_port_name ;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        list_port_name.append(info.portName());
    }
    this->addItems(list_port_name);

}

