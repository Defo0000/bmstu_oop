#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"

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
        return;
    }

}
