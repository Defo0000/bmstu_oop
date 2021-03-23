#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "return_codes.h"
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

parr_t dots_arr;
larr_t links_arr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene();
    dots_arr.arr = NULL;
    links_arr.arr = NULL;
}

MainWindow::~MainWindow() {
    free(dots_arr.arr);
    free(links_arr.arr);

    delete scene;

    delete ui;
}

void MainWindow::on_MainWindow_destroyed() {}

int MainWindow::load_data(FILE *f, parr_t& dots_arr, larr_t& links_arr)
{
    size_t dots;
    if (fscanf(f, "%ld", &dots) != 1)
        return ERR_FSCANF;
    if (dots <= 0)
        return ERR_DIM;

    point_t *data = (point_t *) malloc(dots * sizeof(point_t));
    if (!data)
        return ERR_ALLOCATION;

    for (size_t i = 0; i < dots; i++)
        if (fscanf(f, "%lf%lf%lf", &data[i].x, &data[i].y, &data[i].z) != 3)
            return ERR_FSCANF;

    size_t links;
    if (fscanf(f, "%ld", &links) != 1)
        return ERR_FSCANF;
    if (links <= 0)
        return ERR_DIM;

    link_t *data_links = (link_t *) malloc(sizeof(link_t) * links);
    if (!data_links)
        return ERR_ALLOCATION;

    for (size_t i = 0; i < links; i++)
        if (fscanf(f, "%d%d", &data_links[i].src, &data_links[i].dst) != 2)
            return ERR_FSCANF;

    point_t center;
    if (fscanf(f, "%lf%lf%lf", &center.x, &center.y, &center.z) != 3)
        return ERR_FSCANF;

    dots_arr.arr = data;
    dots_arr.size = dots;
    dots_arr.center = center;

    ui->lineEdit_2->setText(QString::number(center.x, 'f', 2));
    ui->lineEdit_3->setText(QString::number(center.y, 'f', 2));
    ui->lineEdit_4->setText(QString::number(center.z, 'f', 2));

    ui->lineEdit_8->setText(QString::number(center.x, 'f', 2));
    ui->lineEdit_9->setText(QString::number(center.y, 'f', 2));
    ui->lineEdit_10->setText(QString::number(center.z, 'f', 2));

    links_arr.arr = data_links;
    links_arr.size = links;
    return OK;
}

void MainWindow::draw_figure()
{
    QImage image = QImage(1000, 900, QImage::Format_RGB32);
    QPainter p(&image);
    p.setBrush(QColor(0, 0, 0));
    p.setPen(QPen(QColor(0, 0, 0), 5));

    QPolygon polygon = QPolygon();
    QPoint buf = QPoint(0, 0);
    polygon << buf;
    buf = QPoint(1000, 0);
    polygon << buf;
    buf = QPoint(1000, 900);
    polygon << buf;
    buf = QPoint(0, 900);
    polygon << buf;
    p.drawPolygon(polygon);

    p.setPen(QPen(QColor(173, 237, 190), 5));

    double x_src, y_src, x_dst, y_dst;
    int src, dst;
    for (int i = 0; i < links_arr.size; i++)
    {
        src = links_arr.arr[i].src - 1;
        dst = links_arr.arr[i].dst - 1;
        x_src = dots_arr.arr[src].x;
        y_src = dots_arr.arr[src].y;
        x_dst = dots_arr.arr[dst].x;
        y_dst = dots_arr.arr[dst].y;

        p.drawLine(x_src, y_src, x_dst, y_dst);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

void MainWindow::on_pushButton_5_pressed()
{
    FILE *f = fopen(ui->lineEdit->text().toStdString().c_str(), "r");
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
        load_data(f, dots_arr, links_arr);
        fclose(f);
        draw_figure();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    double dx = ui->lineEdit_12->text().toDouble();
    double dy = ui->lineEdit_14->text().toDouble();
    double dz = ui->lineEdit_15->text().toDouble();
    for(size_t i = 0; i < dots_arr.size; i++)
    {
        dots_arr.arr[i].x += dx;
        dots_arr.arr[i].y += dy;
        dots_arr.arr[i].z += dz;
    }
    draw_figure();
}

void MainWindow::on_pushButton_3_clicked()
{
    double angle = ui->lineEdit_11->text().toDouble() * (3.1416 / 180);
    point_t center;
    center.x = ui->lineEdit_8->text().toDouble();
    center.y = ui->lineEdit_9->text().toDouble();
    center.z = ui->lineEdit_10->text().toDouble();

    double temp_x, temp_y, temp_z;

    if (ui->radioButton->isChecked())
    {
        for (size_t i = 0; i < dots_arr.size; i++)
        {
            temp_y = (dots_arr.arr[i].y - center.y) * cos(angle) - (dots_arr.arr[i].z - center.z) * sin(angle) + center.y;
            temp_z = (dots_arr.arr[i].y - center.y) * sin(angle) + (dots_arr.arr[i].z - center.z) * cos(angle) + center.z;
            dots_arr.arr[i].y = temp_y;
            dots_arr.arr[i].z = temp_z;
        }
    }
    else if (ui->radioButton_2->isChecked())
    {
        for (size_t i = 0; i < dots_arr.size; i++)
        {
            temp_x = (dots_arr.arr[i].x - center.x) * cos(angle) + (dots_arr.arr[i].z - center.z) * sin(angle) + center.x;
            temp_z = -(dots_arr.arr[i].x - center.x) * sin(angle) + (dots_arr.arr[i].z - center.z) * cos(angle) + center.z;
            dots_arr.arr[i].x = temp_x;
            dots_arr.arr[i].z = temp_z;
        }
    }
    else if (ui->radioButton_3->isChecked())
    {
        for (size_t i = 0; i < dots_arr.size; i++)
        {
            temp_x = (dots_arr.arr[i].x - center.x) * cos(angle) - (dots_arr.arr[i].y - center.y) * sin(angle) + center.x;
            temp_y = (dots_arr.arr[i].x - center.x) * sin(angle) + (dots_arr.arr[i].y - center.y) * cos(angle) + center.y;
            dots_arr.arr[i].x = temp_x;
            dots_arr.arr[i].y = temp_y;
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle("Ошибка");
        msg.setText("Необходимо выбрать ось, относительно которой будет происходить поворот изображения.");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }

    draw_figure();
}

void MainWindow::on_pushButton_7_clicked()
{
    double kx = ui->lineEdit_5->text().toDouble();
    double ky = ui->lineEdit_6->text().toDouble();
    double kz = ui->lineEdit_7->text().toDouble();

    point_t center;
    center.x = ui->lineEdit_2->text().toDouble();
    center.y = ui->lineEdit_3->text().toDouble();
    center.z = ui->lineEdit_4->text().toDouble();

    for (size_t i = 0; i < dots_arr.size; i++)
    {
        dots_arr.arr[i].x = (dots_arr.arr[i].x - center.x) * kx + center.x;
        dots_arr.arr[i].y = (dots_arr.arr[i].y - center.y) * ky + center.y;
        dots_arr.arr[i].z = (dots_arr.arr[i].z - center.z) * kz + center.z;
    }

    draw_figure();
}
