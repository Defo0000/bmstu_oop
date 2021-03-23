#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "items.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int load_data(FILE *f, parr_t& dots, larr_t& links);
    void draw_figure();
    void update_center();

private slots:

  void on_MainWindow_destroyed();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_pressed();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
