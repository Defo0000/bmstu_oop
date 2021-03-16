#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QTextStream>
#include <fstream>
#include <QMessageBox>

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
    this->close();
}

void MainWindow::on_pushButton_5_pressed()
{
    QTextStream out(stdout);
    QString val = ui->lineEdit->text();
    std::string a = (val).toStdString(), b = (val).toStdString();
    std::ifstream f(a.c_str(), std::ios_base::in);
    if (f.is_open())
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка");
        msg.setText("Невозможно открыть файл с заданным названием.");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
    else
    {
        int a;
        f >> a;
        std::cout << "First num in file: " << a;
        f.close();
    }
}
