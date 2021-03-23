#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "return_codes.h"
#include <QPainter>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QTextStream>
#include <fstream>
#include <QMessageBox>

QGraphicsScene *scene;

parr_t dots;
larr_t links;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene();
    dots.arr = NULL;
    dots.size = 0;
    links.arr = NULL;
    links.size = 0;
}

MainWindow::~MainWindow() {
    free(dots.arr);
    free(links.arr);
    delete scene;
    delete ui;
}

void MainWindow::on_MainWindow_destroyed() {}

int MainWindow::load_data(FILE *f, parr_t& dots, larr_t& links)
{
    size_t n;
    if (fscanf(f, "%ld", &n) != 1)
        return ERR_FSCANF;

    point_t *data = (point_t *) malloc(n * sizeof(point_t));
    if (!data)
        return ERR_ALLOCATION;
    for (size_t i = 0; i < n; i++)
        if (fscanf(f, "%lf%lf%lf", &data[i].x, &data[i].y, &data[i].z) != 3)
            return ERR_FSCANF;

    size_t m;
    if (fscanf(f, "%ld", &m) != 1)
        return ERR_FSCANF;

    link_t *data_links = (link_t *) malloc(sizeof(link_t) * m);
    if (!data_links)
        return ERR_ALLOCATION;
    for (size_t i = 0; i < m; i++)
        if (fscanf(f, "%d%d", &data_links[i].src, &data_links[i].dst) != 2)
            return ERR_FSCANF;

    point_t center;
    if (fscanf(f, "%lf%lf%lf", &center.x, &center.y, &center.z) != 3)
        return ERR_FSCANF;

    dots.arr = data;
    dots.size = n;
    dots.center = center;

    update_center();

    links.arr = data_links;
    links.size = m;

    return OK;
}

void MainWindow::update_center()
{
    point_t center = dots.center;

    ui->lineEdit_2->setText(QString::number(center.x, 'f', 2));
    ui->lineEdit_3->setText(QString::number(center.y, 'f', 2));
    ui->lineEdit_4->setText(QString::number(center.z, 'f', 2));

    ui->lineEdit_8->setText(QString::number(center.x, 'f', 2));
    ui->lineEdit_9->setText(QString::number(center.y, 'f', 2));
    ui->lineEdit_10->setText(QString::number(center.z, 'f', 2));
}

void MainWindow::draw_figure()
{
    update_center();
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
    for (size_t i = 0; i < links.size; i++)
    {
        src = links.arr[i].src - 1;
        dst = links.arr[i].dst - 1;

        x_src = dots.arr[src].x;
        y_src = dots.arr[src].y;
        x_dst = dots.arr[dst].x;
        y_dst = dots.arr[dst].y;

        p.drawLine(x_src, y_src, x_dst, y_dst);
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addPixmap(pixmap);
}

void MainWindow::on_pushButton_5_pressed()
{
    int rc;
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
        if ((rc = load_data(f, dots, links)))
        {
            QMessageBox msg;
            msg.setWindowTitle("Ошибка");
            if (rc == ERR_ALLOCATION)
                msg.setText("Произошла ошибка во время выделения памяти.");
            if (rc == ERR_FSCANF)
                msg.setText("Произошла ошибка во время считывания данных из файла.");
            msg.setIcon(QMessageBox::Critical);
            msg.exec();
        }
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
    for(size_t i = 0; i < dots.size; i++)
    {
        dots.arr[i].x += dx;
        dots.arr[i].y += dy;
        dots.arr[i].z += dz;
    }

    dots.center.x += dx;
    dots.center.y += dy;
    dots.center.z += dz;

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
        for (size_t i = 0; i < dots.size; i++)
        {
            temp_y = (dots.arr[i].y - center.y) * cos(angle) - (dots.arr[i].z - center.z) * sin(angle) + center.y;
            temp_z = (dots.arr[i].y - center.y) * sin(angle) + (dots.arr[i].z - center.z) * cos(angle) + center.z;
            dots.arr[i].y = temp_y;
            dots.arr[i].z = temp_z;
        }
    }
    else if (ui->radioButton_2->isChecked())
    {
        for (size_t i = 0; i < dots.size; i++)
        {
            temp_x = (dots.arr[i].x - center.x) * cos(angle) + (dots.arr[i].z - center.z) * sin(angle) + center.x;
            temp_z = -(dots.arr[i].x - center.x) * sin(angle) + (dots.arr[i].z - center.z) * cos(angle) + center.z;
            dots.arr[i].x = temp_x;
            dots.arr[i].z = temp_z;
        }
    }
    else if (ui->radioButton_3->isChecked())
    {
        for (size_t i = 0; i < dots.size; i++)
        {
            temp_x = (dots.arr[i].x - center.x) * cos(angle) - (dots.arr[i].y - center.y) * sin(angle) + center.x;
            temp_y = (dots.arr[i].x - center.x) * sin(angle) + (dots.arr[i].y - center.y) * cos(angle) + center.y;
            dots.arr[i].x = temp_x;
            dots.arr[i].y = temp_y;
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

    for (size_t i = 0; i < dots.size; i++)
    {
        dots.arr[i].x = (dots.arr[i].x - center.x) * kx + center.x;
        dots.arr[i].y = (dots.arr[i].y - center.y) * ky + center.y;
        dots.arr[i].z = (dots.arr[i].z - center.z) * kz + center.z;
    }

    dots.center.x = (dots.center.x - center.x) * kx + center.x;
    dots.center.y = (dots.center.y - center.y) * ky + center.y;
    dots.center.z = (dots.center.z - center.z) * kz + center.z;

    draw_figure();
}
