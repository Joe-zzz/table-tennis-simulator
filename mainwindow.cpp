#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool success=true;
    bool success2;
    float z=ui->height->text().toFloat(&success2);
    success=success&&success2;
    float y=ui->InitialY->text().toFloat(&success2);
    success=success&&success2;
    float topSpinning=ui->topSpinning->text().toFloat(&success2)*(ui->comboBox->currentIndex()==0?1:-1);
    success=success&&success2;
    float leftSpinning=ui->rightSpeed->text().toFloat(&success2)*(ui->comboBox_2->currentIndex()==0?1:-1);
    success=success&&success2;
    float leftsideSpinning=ui->sideSpinning->text().toFloat(&success2)*(ui->comboBox_3->currentIndex()==0?1:-1);
    success=success&&success2;
    float x_vel=ui->forwardSpeed->text().toFloat(&success2);
    success=success&&success2;
    float y_vel=ui->leftSpeed->text().toFloat(&success2);
    success=success&&success2;
    float z_vel=ui->downSpeed->text().toFloat(&success2);
    success=success&&success2;
    if(success){
        QMessageBox::information(this,"","true");
    }
    else{
        QMessageBox::information(this,"","failed");
    }


}

void MainWindow::on_leftSpeed_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty()) ui->rightSpeed->setText("-"+arg1);
    else ui->rightSpeed->setText("");
}

void MainWindow::on_rightSpeed_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())ui->leftSpeed->setText("-"+arg1);
    else ui->leftSpeed->setText("");
}

void MainWindow::on_upSpeed_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())ui->downSpeed->setText("-"+arg1);
    else ui->downSpeed->setText("");
}



void MainWindow::on_downSpeed_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())ui->upSpeed->setText("-"+arg1);
    else ui->upSpeed->setText("");
}


