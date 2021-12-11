#include <iostream>
#include <stdlib.h>
#include< GL/glut.h>
using namespace std;


class Ball {
	float radius;
	float translation_level;
	friend void keyPress(int,int,int);
public:
	float Ballx;
	float Bally;

	Ball(float radius,float x, float y,float translation_level) {
		this->Ballx = x;
		this->Bally = y; 
		this->radius = radius; 
		this->translation_level = translation_level; 
		
	}
	void translate_left() {
		Ballx = Ballx - translation_level;
	}
	void translate_right() {
		Ballx = Ballx + translation_level;

	}
	void translate_up() {
		Bally = Bally + translation_level;

	}
	void translate_down() {
		Bally = Bally - translation_level;
	
	}
	void drawBall() {
		glColor3f(0.7, 0.6, 0.8);
		glTranslatef(Ballx, Bally, 0);
		glutSolidSphere(this->radius, 40, 40);
	}
	

};

Ball ball(0.1, 0.5, 0.5, 0.1);

void keyPress(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT){
		ball.translate_right();
	cout << "right";
	}

	if (key == GLUT_KEY_LEFT) {
		ball.translate_left();
		cout << "left";
	}
	

	if (key == GLUT_KEY_UP) {
		ball.translate_up();
		cout << "up";
	}
		

	if (key == GLUT_KEY_DOWN) {
		ball.translate_down();
		cout << "down";
	}

	glutPostRedisplay();
}

void draw_ball() {
	glClear(GL_COLOR_BUFFER_BIT );
	glClearColor(0, 0, 0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	ball.drawBall();
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	
	cout << ball.Ballx;
	cout << ball.Bally; 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );

	glutInitWindowSize(800, 800);

	glutCreateWindow("Ball movement");
	glutDisplayFunc(draw_ball);
	glutSpecialFunc(keyPress);

	glutMainLoop();

}
