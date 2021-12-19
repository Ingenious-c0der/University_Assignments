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

private slots:
    void on_pushButton_clicked();
    void B_line(int ,int , int , int );
    int sign(float );
    void mousePressEvent(QMouseEvent *ev);
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int ver=0,temp,i,j,a[20],b[20];
    float slope[20],dx,dy,x[20];
    bool start;
};
#endif // MAINWINDOW_H
