#include "studentinfo.h"
#include "ui_studentinfo.h"
Login *t;
StudentInfo::StudentInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Danh sách sinh viên");
    if(!conn.connOpen())
        ui->label->setText("Failed to open the Database!!!");
    else ui->label->setText("Connected.......!");
    QString arr[] = {"Hiển Thị Tất Cả","Lọc theo lớp","Lọc theo đội","Lọc theo khoá","Lọc theo Tiến độ(lớn hơn tiến độ hiện tại)","Lọc theo Tiến độ(nhỏ hơn hoặc bằng tiến độ hiện tại)"};
    //ui->comboBox->addItem(QIcon(":/logo.png"),"Hiển Thị Tất Cả");
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;++i) ui->comboBox->addItem(QIcon(":/logo.png"),arr[i]);
}

StudentInfo::~StudentInfo()
{
    delete ui;
}

void StudentInfo::on_pushButton_clicked()
{
    Login conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    QString Team,Class,Achivement,Grade;
    Team=ui->team_2->text();
    Class=ui->lop->text();
    Achivement=ui->achivem->text();
    Grade=ui->khoa->text();
    QString str;
    str+=Achivement[0].toUpper();
    for(int i=1;i<Achivement.length();++i){
        str+=Achivement[i];
        if(Achivement[i]==' '&&Achivement[i+1]!=' ') str+=Achivement[i+1].toUpper();
    }
    for(int i=0;i<str.length();++i) {
        if(str[i]==' ') str.remove(str[i+2]);
    }
    ui->label->setText(str);
    //STT,Name,Class,Grade,Achivement,Team
    //qry->prepare("select * from TB3");
    if(ui->all->isChecked()) qry->prepare("select top 3 from TB3");
    else if(ui->Lop->isChecked()) qry->prepare("select * from TB3 where Class='"+Class+"'");
    else if(ui->grade->isChecked()) qry->prepare("select * from TB3 where Grade='"+Grade+"'");
    else if(ui->team->isChecked()) qry->prepare("select * from TB3 where Team='"+Team+"'");
    else if(ui->achive->isChecked()) qry->prepare("select * from TB3 where Achivement='"+str+"'");
    QString text=ui->comboBox->currentText();
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void StudentInfo::on_comboBox_currentIndexChanged(int index)
{
    QString name = ui->comboBox->currentText();
    Login conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    QString text=ui->lineEdit->text();
    QString arr[] = {"Hiển Thị Tất Cả","Lọc theo lớp","Lọc theo đội","Lọc theo khoá","Lọc theo Tiến độ(lớn hơn tiến độ hiện tại)","Lọc theo Tiến độ(nhỏ hơn hoặc bằng tiến độ hiện tại)"};
    if(name==arr[0]) qry->prepare("select (STT,Name,ID,Class,Grade,Project,Progress) from TB3");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void StudentInfo::on_pushButton_2_clicked()
{
    hide();
    t=new Login();
    t->show();
}


