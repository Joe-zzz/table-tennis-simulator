#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets\qmainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();


    void on_leftSpeed_textEdited(const QString &arg1);

    void on_rightSpeed_textEdited(const QString &arg1);

    void on_downSpeed_textEdited(const QString &arg1);

    void on_upSpeed_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
