#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setbuf(stdout, NULL);

    QObject::connect(this, SIGNAL(floor_selected(int)), &_elevator, SLOT(button_pressed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_1_clicked()
{
    emit floor_selected(1);
}

void MainWindow::on_button_2_clicked()
{
    emit floor_selected(2);
}

void MainWindow::on_button_3_clicked()
{
    emit floor_selected(3);
}

void MainWindow::on_button_4_clicked()
{
    emit floor_selected(4);
}

void MainWindow::on_button_5_clicked()
{
    emit floor_selected(5);
}

void MainWindow::on_button_6_clicked()
{
    emit floor_selected(6);
}

void MainWindow::on_button_7_clicked()
{
    emit floor_selected(7);
}

void MainWindow::on_button_8_clicked()
{
    emit floor_selected(8);
}
