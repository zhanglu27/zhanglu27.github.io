#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_cancelButton_clicked();

    void on_radioButton_clicked();

private:
    Ui::login *ui;
    QLineEdit *passwordlineEdit,*userlineEdit;
    QPushButton *loginButton,*registerButton,*cancelButton;
    QLabel *userlabel,*passwordlabel;
    QLabel *backgroundlabel;
    QSqlDatabase db;

    bool openDatabase();
    void closeDatabase();
};

#endif // LOGIN_H
