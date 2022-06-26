#include "login.h"
#include "ui_login.h"
#include "studentinfo.h"
#include "show.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QString title[]={"Quản Lý Sinh Viên NCKH","Xem Danh Sách Thành Viên \n            Nhóm Tại Đây"};
    ui->label_8->setText(title[1]);
    this->setWindowTitle(title[0]);
    if(!connOpen())
        ui->status->setText("Failed to open the Database!!!");
    else ui->status->setText("Connected.......!");

}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    this->hide();
    Show stdinfo;
    stdinfo.setModal(true);
    stdinfo.exec();
}


void Login::on_pushButton_2_clicked()
{
    QString STT,Name,Grade,Class,Progress,Team,Project_Name,ID;
    STT=ui->lineEdit_6->text();
    Name=ui->lineEdit->text();
    Class=ui->lineEdit_2->text();
    Grade=ui->lineEdit_3->text();
    Progress=ui->lineEdit_4->text();
    Team=ui->lineEdit_5->text();
    Project_Name=ui->lineEdit_7->text();
    ID=ui->lineEdit_8->text();
    QString temp;
    temp=temp+Progress[0]+Progress[1];
//    Name=Name.toLower();
//    Class=Class.toUpper();
//    Name[0]=Name[0].toUpper();
//    Achivement=Achivement.toLower();
//    Achivement[0]=Achivement[0].toUpper();
//    for(int i=1;i<Name.length();++i) if(Name[i]==' ') Name[i+1]=Name[i+1].toUpper();
//    for(int i=1;i<Achivement.length();++i) if(Achivement[i]==' ') Achivement[i+1]=Achivement[i+1].toUpper();
    if(!connOpen()){
        qDebug()<<"Failed to open the Database!!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    //qry.exec("PRAGMA locking_mode = EXCLUSIVE");
    qry.prepare("insert into TB3 (STT,Name,Class,Grade,Progress,Team,Project,ID,pc) values('"+STT+"','"+Name+"','"+Class+"','"+Grade+"','"+Progress+"','"+Team+"','"+Project_Name+"','"+ID+"','"+temp+"')");
    qry.exec();
    if(qry.exec()){
        QMessageBox::critical(this,tr("Save"),tr("Saved!"));
        connClose();
    }else{
        QMessageBox::critical(this,tr("Error!"),qry.lastError().text());
    }
}


void Login::on_pushButton_3_clicked()
{
    QString STT,Name,Grade,Class,Achivement,Team,Project_Name,ID;
    Name=ui->lineEdit->text();
    Class=ui->lineEdit_2->text();
    Grade=ui->lineEdit_3->text();
    Achivement=ui->lineEdit_4->text();
    Team=ui->lineEdit_5->text();
    STT=ui->lineEdit_6->text();
    Project_Name=ui->lineEdit_7->text();
    ID=ui->lineEdit_8->text();
    QString temp;
    temp=temp+Achivement[0]+Achivement[1];
//    Name=Name.toLower();
//    Class=Class.toUpper();
//    Name[0]=Name[0].toUpper();
//    Achivement=Achivement.toLower();
//    Achivement[0]=Achivement[0].toUpper();
//    for(int i=1;i<Name.length();++i) if(Name[i]==' ') Name[i+1]=Name[i+1].toUpper();
//    for(int i=1;i<Achivement.length();++i) if(Achivement[i]==' ') Achivement[i+1]=Achivement[i+1].toUpper();
    if(!connOpen()){
        qDebug()<<"Failed to open the Database!!";
        return;
    }
    connOpen();
    QSqlQuery qry;
    qry.prepare("update TB3 set Name='"+Name+"', Class='"+Class+"',Grade='"+Grade+"',Progress='"+Achivement+"',Team='"+Team+"',Project='"+Project_Name+"',ID='"+ID+"',pc='"+temp+"' where STT='"+STT+"'");
    if(qry.exec()){
        QMessageBox::critical(this,tr("Edit"),tr("Updated!"));
        connClose();
    }else{
        QMessageBox::critical(this,tr("Error!"),qry.lastError().text());
    }
}


void Login::on_pushButton_4_clicked()
{
    QString STT,Name,Grade,Class,Achivement,Team;
    Name=ui->lineEdit->text();
    Class=ui->lineEdit_2->text();
    Grade=ui->lineEdit_3->text();
    Achivement=ui->lineEdit_4->text();
    Team=ui->lineEdit_5->text();
    STT=ui->lineEdit_6->text();
    if(!connOpen()){
        qDebug()<<"Failed to open the Database!!";
        return;
    }
    int t = STT.toInt();
    t++;
    STT=QString::number(t);
    connOpen();
    QSqlQuery qry;
    qry.prepare("delete from TB3 where STT='"+STT+"'");
    if(qry.exec()){
        QMessageBox::critical(this,tr("Delete"),tr("Deteled!"));
        connClose();
    }else{
        QMessageBox::critical(this,tr("Error!"),qry.lastError().text());
    }
}

void Login::on_pushButton_6_clicked()
{
    QFile file("D:\\project qt\\pbl1\\readme1.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
}


void Login::on_Show_Team_clicked()
{
    QString link="https://dethanh.github.io/Web/index.html";
    QDesktopServices::openUrl(QUrl(link));
}

