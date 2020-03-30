#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    void serial_start_init();

    QSerialPort serial_port;
    //QSerialPortInfo serial_port_info;
};
#endif // MAINWIDGET_H
