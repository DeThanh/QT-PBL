#include "show.h"
#include "ui_show.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
Login *h;
using namespace std;
Show::Show(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show)
{
    ui->setupUi(this);
    this->setWindowTitle("Danh sách sinh viên");
    if(!conn.connOpen())
        ui->label->setText("Failed to open the Database!!!");
    else ui->label->setText("Connected.......!");
    QString arr[] = {"Hiển Thị Tất Cả","Lọc theo lớp","Lọc theo đội","Lọc theo khoá","Lọc theo dự án","Lọc theo Tiến độ(lớn hơn hoặc bằng tiến độ hiện tại)","Lọc theo Tiến độ(nhỏ hơn hoặc bằng tiến độ hiện tại)"};
    //ui->comboBox->addItem(QIcon(":/logo.png"),"Hiển Thị Tất Cả");
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;++i) ui->comboBox->addItem(QIcon(":/logo.png"),arr[i]);
}

Show::~Show()
{
    delete ui;
}

void Show::on_comboBox_currentIndexChanged(int index)
{
    QString name = ui->comboBox->currentText();
    Login conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    QString text=ui->lineEdit->text();
    QString temp="";
    for(int i=0;i<text.size();++i) if(text[i]!='%') temp+=text[i];

    qry->prepare("insert into TB3 temp='"+temp+"'");
    QString arr[] = {"Hiển Thị Tất Cả","Lọc theo lớp","Lọc theo đội","Lọc theo khoá","Lọc theo dự án","Lọc theo Tiến độ(lớn hơn hoặc bằng tiến độ hiện tại)","Lọc theo Tiến độ(nhỏ hơn hoặc bằng tiến độ hiện tại)"};
    if(name==arr[0]) qry->prepare("select length(Name) from TB3 ");
    else if(name==arr[1]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where Class='"+text+"'");
    else if(name==arr[2]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where Team='"+text+"'");
    else if(name==arr[3]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where Grade='"+text+"'");
    else if(name==arr[4]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where Project='"+text+"'");
    else if(name==arr[5]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where pc between '"+temp+"'and 100");
    else if(name==arr[6]) qry->prepare("Select STT,Name,Class,Grade,ID,Team,Project,Progress from TB3 where pc between 0 and '"+temp+"'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}


void Show::on_pushButton_2_clicked()
{
    hide();
    h=new Login();
    h->show();
}


void Show::on_pushButton_3_clicked()
{
    QFile file("D:\\project qt\\pbl1\\readme1.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
}



