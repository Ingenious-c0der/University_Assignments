#include "windowclip.h"
#include "ui_windowclip.h"
#include<iostream>
#include<QMouseEvent>
QImage surface(551,531,QImage::Format_RGB888);

int WindowClip::ymin =50 ; int WindowClip::ymax = 300; int WindowClip::xmin = 50; int WindowClip::xmax =300;
WindowClip::WindowClip(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WindowClip)
{
    ui->setupUi(this);
    dda_line(xmin,ymin,xmin,ymax);
    dda_line(xmin,ymax,xmax,ymax);
    dda_line(xmax,ymax,xmax,ymin);
    dda_line(xmax,ymin,xmin,ymin);
}
void WindowClip :: mousePressEvent(QMouseEvent *ev){

        int p = ev->pos().x();
        int q = ev->pos().y();
        points[ver][0] = p;
        points[ver][1] = q;
        if(ver>0){
            dda_line(points[ver][0],points[ver][1],points[ver-1][0],points[ver-1][1]);
        }
        ver++;
}
int* Clip(int code1,int code2, float x1,float y1,float x2,float y2){
    int C;
    int *intersection_points = new int[3];
    float x,y;
    const int TOP = 1;
    const int BOTTOM = 2;
    const int RIGHT = 4;
    const int LEFT = 8;
    if( (code1!= 0) and (code2!=0)){

    }
    C = code1?code1:code2;

    if(C & LEFT){
            x = WindowClip::xmin ;
            y = y1+(y2-y1)*((WindowClip::xmin-x1)/(x2-x1));
            std::cout<<"LEFT"<<std::endl;
    }
    if (C & BOTTOM){
        y = WindowClip::ymax ;
        x = x1+(x2-x1)*((WindowClip::ymax-y1)/(y2-y1));
        std::cout<<"bottom"<<std::endl;
    }

    if (C & RIGHT){

        x = WindowClip::xmax;
        y = y1+(y2-y1)*((WindowClip::xmax-x1)/(x2-x1));
        std::cout<<"RIGHT"<<std::endl;
    }
    if(C & TOP){
            y = WindowClip::ymin ;
            x = x1+(x2-x1)*(( WindowClip::ymin -y1)/(y2-y1));
            std::cout<<"top"<<std::endl;
    }



    intersection_points[0] = x ;
    intersection_points[1] = y ;
    intersection_points[2] = C;
    std::cout<<x<<"  "<<y<<" "<<x1<< "  "<<y1<<"  "<<x2<< "  "<<y2<<"  "<<std::endl;
    return intersection_points;

}

int ComputeOutCode(float x,float y){
    int code = 0 ;
    const int TOP = 1;
    const int BOTTOM = 2;
    const int RIGHT = 4;
    const int LEFT = 8;
    if (x>300)
        code|= RIGHT;
    else if(x<50)
        code|= LEFT;
    if (y<50)
        code|=TOP;
    else if(y>300)
        code|= BOTTOM;

    return code;
}

void WindowClip::cohensutherland()
{
    for (int i = 0 ;i<ver-1;i++){
        float x1 = points[i][0];
        float y1 = points[i][1];
        float x2 = points [i+1][0];
        float y2 = points[i+1][1];
        auto code1 = ComputeOutCode(x1,y1);
        auto code2 = ComputeOutCode(x2,y2);

        if ((code1 | code2) == 0 ){}

        else if ((code1 & code2) !=0){
            dda_line(x1,y1,x2,y2,false);

        }
        else{
           int * res = Clip(code1,code2,x1,y1,x2,y2);
           float x,y;
           x = res[0];
           y = res[1];
           int C = res[2];
           if (C == code1){
               if (code1!=0 and code2!=0){
                   dda_line(x,y,x1,y1,false);
                   delete [] res;
                   res = Clip(0,code2,x,y,x2,y2);
                   x = res[0];
                   y = res[1];
                   dda_line(x,y,x2,y2,false);
                   delete [] res;

               }else{
               dda_line(x,y,x1,y1,false);
               delete[] res;
               }

           }
           else{
               if (code1!=0 and code2!=0){
                   dda_line(x,y,x2,y2,false);
                   delete[] res;
                   res = Clip(code1,0,x,y,x1,y1);
                   x = res[0];
                   y = res[1];
                   delete[] res;
                   dda_line(x,y,x1,y1,false);

               }else{
               dda_line(x,y,x2,y2,false);
               delete[] res;
               }
           }

        }

}



}



WindowClip::~WindowClip()
{
    delete ui;
}
void display(float x, float y,bool w = true){

    w?surface.setPixel(x,y,qRgb(255,255,255)):surface.setPixel(x,y,qRgb(0,0,0));
    if(not w){
        surface.setPixel(x+1,y+1,qRgb(0,0,0));
        surface.setPixel(x-1,y,qRgb(0,0,0));
        surface.setPixel(x,y+1,qRgb(0,0,0));
        surface.setPixel(x-1,y-1,qRgb(0,0,0));

}
}

void WindowClip::dda_line(float x, float y,float x1,float y1,bool w ){

    float dx = x1 - x ;
    float dy = y1 - y;
    float step = abs(dy)>abs(dx)?abs(dy):abs(dx);
    float x_inc = dx/step;
    float y_inc = dy/step;

    display(x,y,w);
    for(int i= 0 ; i<step;i++){
        x = x + x_inc ;
        y = y + y_inc ;
        display(x,y,w);

    }

    ui->label->setPixmap(QPixmap::fromImage(surface));
    k=0;


}

void WindowClip::on_pushButton_clicked()
{

    cohensutherland();
    dda_line(xmin,ymin,xmin,ymax);
    dda_line(xmin,ymax,xmax,ymax);
    dda_line(xmax,ymax,xmax,ymin);
    dda_line(xmax,ymin,xmin,ymin);
}
