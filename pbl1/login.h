#ifndef LOGIN_H
#define LOGIN_H

#include "libs.h"
#include <QStandardPaths>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
public:
    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){
       //QString path = QCoreApplication::applicationDirPath() + "/TB1.db";
       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("C:/sqlite3/TB1.db");
//       mydb.setHostName("127.0.0.1");
//       mydb.setUserName("root");
//       mydb.setPassword("");
//       mydb.setDatabaseName("QLSV");
//       mydb.setPort(3306);

       if(!mydb.open()){
           qDebug()<<"Failed to open the Database!!!";
           return false;
       }
       else {
           qDebug()<<"Connected.......!";
           return true;
       }
    }
public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_6_clicked();

    void on_Show_Team_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
