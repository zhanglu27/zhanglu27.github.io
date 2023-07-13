#include "signup.h"
#include "ui_signup.h"
#include <login.h>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    ui->repeatlineEdit->setEchoMode(QLineEdit::Password);
    ui->passwordlineEdit->setMaxLength(6);
    ui->repeatlineEdit->setMaxLength(6);
}

signup::~signup()
{
    db.close();
    delete ui;
}

void signup::on_registerButton_clicked()
{
    QString str1=ui->passwordlineEdit->text();
      QString str2=ui->passwordlineEdit->text();
      int y=QString::compare(str1,str2,Qt::CaseSensitive);
      if(y){
          QMessageBox::about(this,"错误","两次输入不同");
          return;
      }
      if((str1.length()!=6)&&(str2!=6))
      {
          QMessageBox::about(this,"错误","密码需要6个字符");
          return;
      }

      db=QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName("user.db");

      int flag=1;
      bool ok= db.open();
      if(ok)
      {
          QSqlQuery query("select username from userInfo",db);
          while(query.next())
          {
              if(ui->userlineEdit->text()==query.value(0).toString())
              {
                  flag=0;
                  break;
              }
          }
          if(flag){
              QSqlQuery query;
              query.prepare("INSERT INTO userInfo (username, password) VALUES (:username,:password)");
              query.bindValue(":username",ui->userlineEdit->text());
              query.bindValue(":password",ui->passwordlineEdit->text());

              query.exec();
              QMessageBox::about(this,"提示","注册用户成功!");
              this->hide();
              login *w = new login;
              w->show();
          }
          else QMessageBox::about(this,"错误","用户已存在");
      }
      else
      {
          qDebug()<<"数据库创建失败！";
          exit(-1);
      }
}

void signup::on_calcelButto_clicked()
{
        this->close();
}
