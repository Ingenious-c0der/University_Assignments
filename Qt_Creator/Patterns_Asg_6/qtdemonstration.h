#ifndef QTDEMONSTRATION_H
#define QTDEMONSTRATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QtDemonstration; }
QT_END_NAMESPACE

class QtDemonstration : public QMainWindow
{
    Q_OBJECT

public: //add the created functions here
    QtDemonstration(QWidget *parent = nullptr);
    ~QtDemonstration();
    void bresenham_line(int,int,int,int);
    void display(int,int);
    void drawCircle(float,float,float,float);
    void DDA_line(float,float,float,float);
    void B_circle(float,float,float);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::QtDemonstration *ui;
};
#endif // QTDEMONSTRATION_H
