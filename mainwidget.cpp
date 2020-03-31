#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QList>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

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
    QSqlDatabase datebase_serial_parameter=QSqlDatabase::addDatabase("QSQLITE");
    datebase_serial_parameter.setDatabaseName(QApplication::applicationDirPath()+"/datebase.db");
    if (!datebase_serial_parameter.open()) {
           QMessageBox::warning(0, QObject::tr("Database Error"),datebase_serial_parameter.lastError().text());
    }

    QSqlQuery query;
    //创建表
    query.exec("CREATE TABLE seria_parameter("
               "name VARCHAR(20) NOT NULL,"
               "data INTEGER NOT NULL)");
    //导入数据
    query.exec("INSERT INTO serial_parameter (name,data)"
               "VALUES ('port','3')");
    query.exec("INSERT INTO serial_parameter (name,data)"
               "VALUES ('baudrate','9600')");
    query.exec("INSERT INTO serial_parameter (name,data)"
               "VALUES ('StopBit','1')");
    query.exec("INSERT INTO serial_parameter (name,data)"
               "VALUES ('DataBit','8')");
    query.exec("INSERT INTO serial_parameter (name,data)"
               "VALUES ('check','0')");

    query.exec("CREATE TABLE students ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "name VARCHAR(40) NOT NULL, "
                       " score INTEGER NOT NULL, "
                       "class VARCHAR(40) NOT NULL)");
    query.exec("INSERT INTO students (name, score,class) "
                   "VALUES ('小张', 85, '初2-1班')");
                  //向students表里的(name, score,class)标题下插入一项数据'小张', 85, '初2-1班'





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
