#ifndef SHOW_H
#define SHOW_H

#include <QDialog>
#include "login.h"
#include "libs.h"
namespace Ui {
class Show;
}

class Show : public QDialog
{
    Q_OBJECT

public:
    Login conn;
    explicit Show(QWidget *parent = nullptr);
    ~Show();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::Show *ui;
};

#endif // SHOW_H
