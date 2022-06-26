#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include "login.h"
#include "libs.h"
namespace Ui {
class StudentInfo;
}

class StudentInfo : public QDialog
{
    Q_OBJECT

public:
    Login conn;
    explicit StudentInfo(QWidget *parent = nullptr);
    ~StudentInfo();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::StudentInfo *ui;
};

#endif // STUDENTINFO_H
