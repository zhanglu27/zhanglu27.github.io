#include "login.h"
#include "ui_login.h"
#include "widget.h"
#include "signup.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QMessageBox>


login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
//连接数据库

    this->setWindowTitle("用户登录");
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    ui->passwordlineEdit->setMaxLength(6);
    ui->passwordlineEdit->setPlaceholderText("请输入6位字符");

    QSqlDatabase db = QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    bool ok = db.open();
    if(!ok)
    {
        QMessageBox::about(this,"错误","数据库创建失败");
        return;
    }
    QSqlQuery query;

    QString sql="select * from userInfo";
    if(!query.exec(sql))
    {
        qDebug()<<"userinfo 不存在";
        query.exec("create table userInfo(username varchar(20),password varchar(20))");
        //query.exec(sql);
        sql ="INSERT INTO userInfo (username,password) VALUES('zhangsan','123456')";
        query.exec(sql);
    }else
    {
        qDebug()<<"userInfo 存在";
    }

    //ui设计
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint);//无边框
    //this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体背景全透明

    QPixmap pixmap = QPixmap(":/xiche.png").scaled(this->size());
    QPalette palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

login::~login()
{
    db.close();
    delete ui;
}


//登录
void login::on_loginButton_clicked()
{

    QString str =ui->passwordlineEdit->text();
    if(str.length()!=6)
    {
        QMessageBox::about(this,"错误","密码少于6个字符");
        return;
    }
      bool ok = db.open();
      int open_flag=1;
    if(1)
    {
        QSqlQuery query("select username,password from userInfo",db);
        while(query.next())
        {
            QString account=query.value(0).toString();
            QString password=query.value(1).toString();
            if(ui->userlineEdit->text()==account&&ui->passwordlineEdit->text()==password)
            {
                this->hide();
                Widget *w=new Widget();
                w->show();
                db.close();
                open_flag=0;
                break;
            }
        }
        if(open_flag)QMessageBox::about(this,"提示","账号或密码错误");
    }
    else
    {
        qDebug()<<"数据库创建失败！"<< db.lastError().text();
    }
}


//注册
void login::on_registerButton_clicked()
{
    this->hide();
    signup *w=new signup();
    w->show();
}

//退出
void login::on_cancelButton_clicked()
{
    this->close();
}

//显示密码
void login::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked()) {
        ui->passwordlineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    }
}

