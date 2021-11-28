#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCore>
#include<QtGui>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void multiply(float matrice[2][2]);
    void operator*(float matrice[2][2]);
    void operator = (float matrix[4][2]);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();


    void on_pushButton_5_clicked();

private:
    float Rx=0 ,Ry = 0 ;
    float Sx=1,Sy=1;
    float Rs,Rc = 0 ;
    Ui::MainWindow *ui;
    void display(int x, int y);
    void DDA_line(float,float,float,float);
    int x1,y1,l,b;
    void drawrect(float,float,float,float);
    float scaling_matrix[2][2] = {{Sx,0},{0,Sy}};
    float rotation_matrix[2][2] = {{Rc,-Rs},{Rs,Rc}};
    void rotateRect(float,float,float,float);
    float points_matrix[4][2] = {{0,0},{0,0},{0,0},{0,0}};
    void scaleRect();
    void drawrect_2(MainWindow&);

};
#endif // MAINWINDOW_H
