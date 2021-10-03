#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utility>
#include <QColorDialog>
#include<QPainter>
#include<iostream>

QImage surface(400,400,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

struct Cood{
    int x;
    int y;
    bool operator<(const Cood& other)
    { if (y==other.y){
            if (x>other.x){
                return false;
            }else{
                return true;
            }
        }else{
      return y < other.y;
        }
    }
};

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDA_line(float x1, float y1, float x2, float y2)
{

    float step;
       float dx = (x2-x1);
       float dy = (y2-y1);
       if (dx==0 && dy==0){
           display(x1,y1);
       }
       else{
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
}

void MainWindow::display(int x, int y)
{
    surface.setPixel(x,y,qRgb(rgb[0],rgb[1],rgb[2]));
}




void MainWindow::on_pushButton_clicked()

{
    DDA_line(100,100,200,60);
    DDA_line(200,60,300,150);
    DDA_line(300,150,240,250);
    DDA_line(240,250,80,200);
    DDA_line(80,200,120,150);
    DDA_line(120,150,100,100);
    ui->label->setPixmap(QPixmap::fromImage(surface));
}


void MainWindow::on_pushButton_2_clicked()
{
    QColor color;
    color = QColorDialog::getColor();
    rgb[0]=color.red();
    rgb[1]=color.green();
    rgb[2]=color.blue();

}


void MainWindow::on_pushButton_3_clicked()
{
    scanfill();
}


void MainWindow::scanfill(){
   int x1[]={100, 200, 120,300, 80,  240 };
   int y1[]={100, 60, 150,150, 200,  250 };
    int x_at_ymin;
    int x_l_points[100];
    int x_r_points[100];
    int y_l_points[100];
    int y_r_points[100];
    int n = sizeof(y1) / sizeof(y1[0]);
    Cood store[100] ;
    for(int i=0;i<n;i++){

        store[i].x = x1[i];
        store[i].y = y1[i];

    }
    std::sort(&store[0], &store[n]);
    x_at_ymin = store[0].x;

    for(int i =0;i<n-1;i++){
        x1[i] = store[i].x;

        y1[i] = store[i].y;
    }


    x_r_points[0] =store[0].x;
    x_l_points[0] =store[0].x;
    y_r_points[0]= store[0].y;
    y_l_points[0]= store[0].y;
    int r = 1; int l = 1;

    for (int j=1;j<n;j++){
        if (x1[j]>x_at_ymin or y1[j]==store[n-1].y ){
            x_r_points[r] = x1[j];
            y_r_points[r]= y1[j];
            r+=1;
        }
        if(x1[j]<x_at_ymin or y1[j]==store[n-1].y) {
            x_l_points[l]=x1[j];
            y_l_points[l]= y1[j];
            l+=1;
        }


        }
    r+=1;
    float x_l[1000];
    x_l[0] = x_at_ymin;
    float x_r[1000];
    x_r[0] = x_at_ymin;
    int b = 0;
    int t = 0  ;
    int offset_l = 0;
    int offset_r = 0;


    while (b<l){
        float dx = x_l_points[b+1]-x_l_points[b];
        float dy = y_l_points[b+1]-y_l_points[b];

        for(int i=1;i<=abs(dy);i++){

            x_l[i+offset_l] = x_l[i-1+offset_l]+(dx/dy);


            }
        offset_l+=dy;
        b+=1;
        }


    while (t<r-2){
        float dx = x_r_points[t+1]-x_r_points[t];
        float dy = y_r_points[t+1]-y_r_points[t];

        for(int i=1;i<=abs(dy);i++){

            x_r[i+offset_r] = x_r[i-1+offset_r]+(dx/dy);
//            std::cout<<"Travel "<<x_r_points[t+1]<<"<-"<<x_r_points[t]<<std::endl;
//            std::cout<<"dx/dy "<<dx/dy<<"dx :"<<dx<<"dy :"<<dy<<std::endl;
//            std::cout<<"Point "<<x_r[i+offset_r]<<std::endl;
            }
        offset_r+=dy;
        t+=1;



    }
    int ymin = y1[0];
    int ymax = y1[n-1];
    int c = 0 ;
    while (ymin<ymax){
        float x_l_value = x_l[c];
        float x_r_value = x_r[c];
        float y_value = ymin;
//        std::cout<<"Left value : "<<x_l_value<<"Right value : "<<x_r_value<<std::endl;
//        std::cout<<"Y value : "<<y_value<<std::endl;
        c+=1;
        ymin+=1;
        DDA_line(x_r_value,y_value,x_l_value,y_value);

    }

}

