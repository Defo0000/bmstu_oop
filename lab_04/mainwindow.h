#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include <stdio.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void floor_selected(int floor);

private slots:
    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

private:
    Ui::MainWindow *ui;

    elevator _elevator;
};
#endif // MAINWINDOW_H
