#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
#include "figure.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->draw_view->setScene(scene);
}

MainWindow::~MainWindow()
{
    event_t event;
    event.task = QUIT;
    event_handler(event);
    delete ui;
}

void MainWindow::on_exit_btn_clicked()
{
    this->close();
}

void MainWindow::on_load_btn_clicked()
{
    filename_t name = ui->filename->text().toStdString().c_str();

    event_t event;
    event.task = LOAD;
    event.filename = name;


    rc_t return_code = event_handler(event);
    if (return_code)
    {
        handle_return_code(return_code);
    }
    else if ((return_code = draw()))
    {
        handle_return_code(return_code);
    }
}

rc_t MainWindow::draw()
{
    plane_t plane;

    plane.scene = ui->draw_view->scene();
    plane.width = ui->draw_view->width();
    plane.height = ui->draw_view->height();

    event_t event;
    event.task = DRAW;
    event.plane = plane;

    rc_t return_code = event_handler(event);
    return return_code;
}

void MainWindow::on_scale_btn_clicked()
{
    scale_t params;

    params.kx = ui->kx->text().toDouble();
    params.ky = ui->ky->text().toDouble();
    params.kz = ui->kz->text().toDouble();

    event_t event;
    event.task = SCALE;
    event.scale = params;

    rc_t return_code = event_handler(event);
    if (return_code)
    {
        handle_return_code(return_code);
    }
    else if ((return_code = draw()))
    {
        handle_return_code(return_code);
    }
}

void MainWindow::on_move_btn_clicked()
{
    move_t params;

    params.dx = ui->dx->text().toDouble();
    params.dy = ui->dy->text().toDouble();
    params.dz = ui->dz->text().toDouble();

    event_t event;
    event.task = MOVE;
    event.move = params;

    rc_t return_code = event_handler(event);
    if (return_code)
    {
        handle_return_code(return_code);
    }
    else if ((return_code = draw()))
    {
        handle_return_code(return_code);
    }
}

void MainWindow::on_rotate_btn_clicked()
{
    rotate_t params;

    params.rx = ui->rx->text().toDouble();
    params.ry = ui->ry->text().toDouble();
    params.rz = ui->rz->text().toDouble();

    event_t event;
    event.task = ROTATE;
    event.rotate = params;

    rc_t return_code = event_handler(event);
    if (return_code)
    {
        handle_return_code(return_code);
    }
    else if ((return_code = draw()))
    {
        handle_return_code(return_code);
    }
}
