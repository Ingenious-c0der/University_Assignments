#ifndef WINDOWCLIP_H
#define WINDOWCLIP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowClip; }
QT_END_NAMESPACE

class WindowClip : public QMainWindow
{
    Q_OBJECT

public:
    WindowClip(QWidget *parent = nullptr);
    ~WindowClip();
    void dda_line(float,float,float,float,bool w = true);
    float points[100][2];
    int ver = 0 ;
    void mousePressEvent(QMouseEvent *ev);
    void cohensutherland();
    int k = 0 ;
    static int xmin,ymin,xmax,ymax;


private slots:
    void on_pushButton_clicked();

private:
    Ui::WindowClip *ui;
};
#endif // WINDOWCLIP_H
