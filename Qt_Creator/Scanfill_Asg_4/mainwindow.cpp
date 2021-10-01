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


MainWindow::~MainWindow()
{
    delete ui;
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
    myfunct();
}

void MainWindow::myfunct()
{
        int x1[]={100,200,300,240,80,120};
        int y1[]={100,60,150,250,200,150};
        int i=0;
        int n=5;
        int ymin = 250, ymax=60;
        int c,j,y;
        float m[50],a[50],dx,dy,t;

        for(i=0;i<n-1;i++)
        {
            DDA_line(x1[i],y1[i],x1[i+1],y1[i+1]);
        }



        for(i=0;i<n;i++)
        {
            if(y1[i]>=ymax)
                ymax=y1[i];
            if(y1[i]<=ymin)
                ymin=y1[i];
            dx=x1[i+1]-x1[i];
            dy=y1[i+1]-y1[i];
            if(dx==0)
                m[i]=0;
            if(dy==0)
                m[i]=1;
            if(dx!=0 && dy!=0)
                m[i]=dx/dy;
        }
        for(y=ymax;y>=ymin;y--)
        {
            c=0;
            for(i=0;i<n;i++)
            {
                if((y1[i]>y && y1[i+1] <=y) || (y1[i]<=y && y1[i+1]>y))
    {
                    a[c]=x1[i]+(m[i]*(y-y1[i]));
                    c++;
            }
        }
    for(i=0;i<c-1;i++)
    {
        for(j=0;j<c-1;j++)
        {
            if(a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
        for(i=0;i<c-1;i=i+3)
        {

            DDA_line(a[i],y,a[i+1],y);

        }
    }
    }


