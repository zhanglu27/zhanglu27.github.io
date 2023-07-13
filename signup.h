#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QtSql>
#include <QMessageBox>
namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_registerButton_clicked();

    void on_calcelButto_clicked();

private:
    Ui::signup *ui;
    QLabel *userlabel,*passwordlabel,*repeadlabel;
    QLineEdit *userlineEdit,*passwordlineEdit,*repeatlineEdit;
    QPushButton *registerButton,*cancelButton;
    QSqlDatabase db;
};

#endif // SIGNUP_H
