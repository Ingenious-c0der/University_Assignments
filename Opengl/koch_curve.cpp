#include<iostream>
#include<GL/glut.h>
#include<stdio.h>
//#include<math.h>
using namespace std;
float x1 = 1, x2= 600 , y_one= 1, y2 = 600, n = 3;


void koch(float x1, float y_one, float x2, float y2, float n)
{
	float ang = 60; ang = ang * 3.14 / 180; //converting to radians
	float x3 = (2 * x1 + x2) / 3;
	float y3 = (2 * y_one + y2) / 3;
	float x4 = (x1 + 2 * x2) / 3;
	float y4 = (y_one + 2 * y2) / 3;
	float x = x3 + (x4 - x3) * 0.5 + (y4 - y3) * 0.8660;
	float y = y3 - (x4 - x3) * 0.8660 + (y4 - y3) * 0.5;
	if (n > 0)
	{
		koch(x1, y_one, x3, y3, n - 1);
		koch(x3, y3, x, y, n - 1);
		koch(x, y, x4, y4, n - 1);
		koch(x4, y4, x2, y2, n - 1);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		glVertex2f(x1, y_one);
		glColor3f(0.0, 1.0, 1.0);
		glVertex2f(x3, y3);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(x, y);
		glColor3f(1.0, 0.0, 1.0);
		glVertex2f(x4, y4);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(x2, y2);
		glEnd();

	}
}
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 640.0, 480.0, 0.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	koch(x1, y_one, x2, y2, n);
	glFlush();
}
int main(int argv, char** argc)
{

	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("koch fractal");
	Init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
