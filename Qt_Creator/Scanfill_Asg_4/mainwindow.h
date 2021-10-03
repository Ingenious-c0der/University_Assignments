#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void DDA_line(float,float,float,float);
      void display(int,int);     
      void scanfill();
      int rgb[3];

private slots:
      void on_pushButton_clicked();

      void on_pushButton_2_clicked();

      void on_pushButton_3_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
