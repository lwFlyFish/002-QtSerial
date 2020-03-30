#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QList>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MainWidget::MainWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    serial_start_init();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::serial_start_init()
{
    this->setWindowTitle(QString("Serial"));

    // 判断是否创建数据库
    QSqlQuery query;
    bool isTableExist =query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg("CANexcel"));
    if(false==isTableExist)
    {
        qDebug() << "table does not exist";
    }
    else
    {
        //QMessageBox::critical(new QWidget,QString("创建数据库"),QString("数据库已经存在"));
        qDebug() << "table exists";
    }
        //return QSqlError();



    //获取电脑的所有串口并添加到ComboBox中，然后读取本地默认配置的数据
    ui->comboBox_param_interface->clear();
    QList < QString > list;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);

        if( serial.open( QIODevice::ReadWrite) )//如果串口是可以读写方式打开的
        {
            list.append(info.portName());
            serial.close();//然后自动关闭等待人为开启（通过那个打开串口的PushButton）
        }
    }
    std::sort(list.begin(),list.end());

    if(true==list.isEmpty())
    {
        ui->comboBox_param_interface->addItem(QString("无有效串口"));
    }
    else
    {
        ui->comboBox_param_interface->addItems(list);
    }

    //初始化串口参数

    //建立对应的信号槽

}
