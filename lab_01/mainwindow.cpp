#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QVector3D>
#include <chrono>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <QTextStream>
#include <fstream>
#include <QMessageBox>

QGraphicsScene *scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  scene = new QGraphicsScene();
}

MainWindow::~MainWindow() {

  delete scene;

  delete ui;
}

void MainWindow::on_pushButton_clicked() {

    scene->clear();
    ui->graphicsView->items().clear();
    QImage image = QImage(1061, 941, QImage::Format_RGB32);
    QPainter p(&image);
    p.setBrush(QColor(0, 0, 0));
    p.setPen(QPen(QColor(0, 0, 0), 3));

    QPolygon back = QPolygon();
    QPoint buf(0, 0);
    back << buf;
    buf = QPoint(1061, 941);
    back << buf;
    buf = QPoint(1061, 0);
    back << buf;
    p.drawPolygon(back);

    p.setPen(QPen(QColor(173, 237, 190), 3));

    QPolygon polygon = QPolygon();
    buf = QPoint(1, 1);
    polygon << buf;
    buf = QPoint(20, 20);
    polygon << buf;
    buf = QPoint(20, 1);
    polygon << buf;
    p.drawPolygon(polygon);

    for (int i = 0; i < 300; i++) {
      QPoint a(i, i);
      p.drawPoint(a);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_MainWindow_destroyed() {}

void MainWindow::add_point(int x, int y)
{
    QImage image = QImage(1000, 900, QImage::Format_RGB32);
    QPainter p(&image);
    p.setBrush(QColor(0, 100, 0));
    p.setPen(QPen(QColor(255, 0, 0), 10));
    QPoint a(x, y);
    p.drawLine(1000, 900, x, y);
    ui->graphicsView->scene()->update();

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    ui->graphicsView->items().clear();
    QImage image = QImage(1000, 900, QImage::Format_RGB32);
    QPainter p(&image);

    p.setBrush(QColor(0, 100, 0));
    p.setPen(QPen(QColor(173, 237, 190), 3));

    add_point(300, 100);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

struct point
{
    double x, y, z;
};
using point_t = struct point;

void MainWindow::load_data(std::ifstream& f)
{

    QImage image = QImage(1000, 900, QImage::Format_RGB32);
    QPainter p(&image);
    p.setBrush(QColor(0, 100, 0));
    p.setPen(QPen(QColor(173, 237, 190), 5));

    int n;
    f >> n;
    point_t data[n];
    for (int i = 0; i < n; i++)
        f >> data[i].x >> data[i].y >> data[i].z;
    int x_screen, y_screen, k = 1000;
    for (int i = 0; i < n; i++)
    {
        x_screen = k * data[i].x / (data[i].z + k);
        y_screen = k * data[i].y / (data[i].z + k);
        p.drawPoint(x_screen, y_screen);
        std::cout << data[i].x << " " << data[i].y << " " << data[i].z << "\n";
    }

    int m;
    f >> m;
    int src, dst, x1_screen, y1_screen, x2_screen, y2_screen;
    for (int i = 0; i < m; i++)
    {
        f >> src >> dst;
        src--;
        dst--;
        x1_screen = k * data[src].x / (data[src].z + k);
        y1_screen = k * data[src].y / (data[src].z + k);
        x2_screen = k * data[dst].x / (data[dst].z + k);
        y2_screen = k * data[dst].y / (data[dst].z + k);

        p.drawLine(x1_screen, y1_screen, x2_screen, y2_screen);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

void MainWindow::on_pushButton_5_pressed()
{
    std::ifstream f(ui->lineEdit->text().toStdString().c_str(), std::ios_base::in);
    if (!f)
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка");
        msg.setText("Невозможно открыть файл с заданным названием.");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
    else
    {
        load_data(f);
        f.close();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    this->close();
}
