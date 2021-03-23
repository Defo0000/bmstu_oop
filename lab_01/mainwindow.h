#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
  void add_point(int x, int y);
  void load_data(std::ifstream& f);

private slots:

  void on_pushButton_clicked();

  void on_MainWindow_destroyed();

  void on_pushButton_2_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_5_pressed();


private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
