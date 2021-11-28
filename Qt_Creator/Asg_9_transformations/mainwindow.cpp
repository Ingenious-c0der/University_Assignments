#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
QImage surface(400,400,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::operator =(float matrix[4][2]){
    for(int i = 0 ;i<4;i++){
        this->points_matrix[i][0] = matrix[i][0];
        this->points_matrix[i][1] = matrix[i][1];

    }

}


void MainWindow::multiply(float matrice[2][2])
{
    for(int i = 0 ;i<4;i++){
        points_matrix[i][0] = points_matrix[i][0]*matrice[0][0]+points_matrix[i][1]*matrice[0][1];
        points_matrix[i][1] = points_matrix[i][1]*matrice[1][0]+points_matrix[i][1]*matrice[1][1];

    }

}
void MainWindow::operator * (float matrice[2][2]){

    float x , y ;
        for(int i = 0 ;i<4;i++){
                std::cout<<points_matrix[i][0]<<"  "<<points_matrix[i][1]<<"  "<<std::endl;

        }
        std::cout<<float(matrice[1][1])<<"  "<<float(matrice[0][0])<<"  "<<float(matrice[0][1])<<"  "<<matrice[1][0]<<"  "<<std::endl;
    for(int i = 0 ;i<4;i++){
        x = points_matrix[i][0];y = points_matrix[i][1];
        points_matrix[i][0] = x*matrice[0][0]+y*matrice[0][1] +Rx - matrice[0][0]*Rx-matrice[0][1]*Ry;
        points_matrix[i][1] = x*matrice[1][0]+y*matrice[1][1] +Ry - matrice[1][0]*Rx-matrice[1][1]*Ry;

    }



}
void MainWindow::display(int x, int y){
    surface.setPixel(x,y,qRgb(255,255,255));
}

void MainWindow::DDA_line(float x1, float y1, float x2, float y2)
{
    float step;
       float dx = (x2-x1);
       float dy = (y2-y1);
       if (abs(dx)>=abs(dy))
       {
           step = abs(dx);
       }
       else
       {
           step = abs(dy);
       }
       float x_inc = dx/step;
       float y_inc = dy/step;
       display(x1,y1);

       for (int i=0; i<step;i++){
           x1 = x1 + x_inc;
           y1 = y1 + y_inc;
           display(x1,y1);

       }
       ui->label->setPixmap(QPixmap::fromImage(surface));
}

void MainWindow::on_pushButton_clicked()
{
        int dx , dy ;
        dx = ui->textEdit_7->toPlainText().toInt();
        dy = ui->textEdit_8->toPlainText().toInt();
        drawrect(x1+dx,y1+dy,l,b);


}


void MainWindow::on_pushButton_2_clicked()
{       float t;
       t =  qDegreesToRadians( ui->textEdit_3->toPlainText().toFloat());
       Rc = qCos(t);
       Rs = qSin(t);
       MainWindow Object;
           Object.Rx = (points_matrix[0][0]+points_matrix[1][0]+points_matrix[2][0]+points_matrix[3][0])/4;
           Object.Ry = (points_matrix[0][1]+points_matrix[1][1]+points_matrix[2][1]+points_matrix[3][1])/4;
           Object = this->points_matrix;


       rotation_matrix[0][0] = Rc;
       rotation_matrix[0][1] = -Rs;
       rotation_matrix[1][0] = Rs;
       rotation_matrix[1][1] = Rc;
        Object * rotation_matrix;
       drawrect_2(Object);
}


void MainWindow::on_pushButton_3_clicked()
{
        Sx = ui->textEdit_4->toPlainText().toFloat();
        Sy = ui->textEdit_9->toPlainText().toFloat();

        MainWindow Object;
        Object.Sx = Sx;
        Object.Sy = Sy;
        Object = this->points_matrix;
        Object.scaling_matrix[0][0] = Sx;
        Object.scaling_matrix[1][1] = Sy ;

        Object * Object.scaling_matrix;
        drawrect_2(Object);


}


void MainWindow::on_pushButton_4_clicked()
{

}


void MainWindow::on_pushButton_5_clicked()
{
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    l = ui->textEdit_5->toPlainText().toInt();
    b = ui->textEdit_6->toPlainText().toInt();
    drawrect(x1,y1,l,b);
}

void MainWindow::drawrect(float x,float y,float l, float b){
    points_matrix[0][0] = x;
    points_matrix[1][0] = x+b ;
    points_matrix[2][0] =  x+b;
    points_matrix[3][0] =  x;
    points_matrix[0][1] = y;
    points_matrix[1][1] =  y;
    points_matrix[2][1] =  y+l;
    points_matrix[3][1] =  y+l;


    DDA_line(x,y,x+b,y);
    DDA_line(x+b,y,x+b,y+l);
    DDA_line(x+b,y+l,x,y+l);
    DDA_line(x,y+l,x,y);
}


void MainWindow::drawrect_2(MainWindow &Object){

    DDA_line(Object.points_matrix[0][0],Object.points_matrix[0][1],Object.points_matrix[1][0],Object.points_matrix[1][1]);
    DDA_line(Object.points_matrix[1][0],Object.points_matrix[1][1],Object.points_matrix[2][0],Object.points_matrix[2][1]);
    DDA_line(Object.points_matrix[2][0],Object.points_matrix[2][1],Object.points_matrix[3][0],Object.points_matrix[3][1]);
    DDA_line(Object.points_matrix[3][0],Object.points_matrix[3][1],Object.points_matrix[0][0],Object.points_matrix[0][1]);

}
