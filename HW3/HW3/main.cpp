#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
using namespace std;

static int cubeBody = 0, head = 0,tail=0;
static int lf1 = 0, lf2 = 0, rf1 = 0, rf2 = 0, lb1 = 0, lb2 = 0, rb1 = 0, rb2 = 0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		//body
		glRotatef((GLfloat)cubeBody, 0.0, 0.0, 1.0);
		glPushMatrix();
			glScalef(2.0,2.0,2.0);
			glutWireCube(1.0);
		glPopMatrix();
		//head
		glPushMatrix();
			glTranslatef(-1.075, 0.3, 0.0);
			glRotatef((GLfloat)head, 0.0, 0.0, 1.0);
			glTranslatef(-0.375, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.75, 0.75, 0.75);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		//tail
		glPushMatrix();
			glTranslatef(1.05, 0.5, 0.0);
			glRotatef((GLfloat)tail, 0.0, 0.0, 1.0);
			glTranslatef(0.15, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.3, 0.3, 0.3);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
		//left-front legs
		glPushMatrix();
			glTranslatef(-0.4, -1.0, 0.5);
			glRotatef((GLfloat)lf1, 0.0, 0.0, 1.0);
			glTranslatef(0.0, -0.15, 0.0);
			glPushMatrix();
				glScalef(0.3, 0.3, 0.3);
				glutWireCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.15, 0.0);
				glRotatef((GLfloat)lf2, 0.0, 0.0, 1.0);
				glTranslatef(0.0, -0.15, 0.0);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//left-back legs
		glPushMatrix();
			glTranslatef(0.4, -1.0, 0.5);
			glRotatef((GLfloat)lb1, 0.0, 0.0, 1.0);
			glTranslatef(0.0, -0.15, 0.0);
			glPushMatrix();
				glScalef(0.3, 0.3, 0.3);
				glutWireCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.15, 0.0);
				glRotatef((GLfloat)lb2, 0.0, 0.0, 1.0);
				glTranslatef(0.0, -0.15, 0.0);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//right-front legs
		glPushMatrix();
			glTranslatef(-0.4, -1.0, -0.5);
			glRotatef((GLfloat)rf1, 0.0, 0.0, 1.0);
			glTranslatef(0.0, -0.15, 0.0);
			glPushMatrix();
				glScalef(0.3, 0.3, 0.3);
				glutWireCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.15, 0.0);
				glRotatef((GLfloat)rf2, 0.0, 0.0, 1.0);
				glTranslatef(0.0, -0.15, 0.0);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//right-back legs
		glPushMatrix();
			glTranslatef(0.4, -1.0, -0.5);
			glRotatef((GLfloat)rb1, 0.0, 0.0, 1.0);
			glTranslatef(0.0, -0.15, 0.0);
			glPushMatrix();
				glScalef(0.3, 0.3, 0.3);
				glutWireCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.15, 0.0);
				glRotatef((GLfloat)rb2, 0.0, 0.0, 1.0);
				glTranslatef(0.0, -0.15, 0.0);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					glutWireCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();			
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void special(int key, int x, int y) {
	cout << key << endl;
}

//ARGSUSED1
bool isDraggingL = false; // 標記是否正在拖曳
bool isDraggingR = false;
int startX, startY; // 拖曳開始的滑鼠座標
void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDraggingL = true; // 按下滑鼠左鍵開始拖曳
			startX = x;
			startY = y;
		}
		else {
			isDraggingL = false; // 放開滑鼠左鍵停止拖曳
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDraggingR = true; // 按下滑鼠右鍵開始拖曳
			startX = x;
			startY = y;
		}
		else {
			isDraggingR = false; // 放開滑鼠右鍵停止拖曳
		}
	}
}
void mouseMotion(int x, int y) {
	if (isDraggingL) {
		// 計算滑鼠移動的距離
		int deltaX = x - startX;
		int deltaY = y - startY;

		// 在這裡可以對物件位置進行更新，例如使用OpenGL的平移函數glTranslate()等
		// 假設對物件進行平移
		glTranslatef(deltaX * 0.01, -deltaY * 0.01, 0.0);

		// 更新起始位置
		startX = x;
		startY = y;

		glutPostRedisplay(); // 重新繪製畫面
	}
	if (isDraggingR) {
		// 計算滑鼠移動的距離
		int deltaX = x - startX;
		int deltaY = y - startY;

		// 在這裡可以對物件位置進行更新，例如使用OpenGL的平移函數glTranslate()等
		// 假設對物件進行平移
		glRotatef(deltaX,0.0,1.0,0.0);
		glRotatef(deltaY, 1.0, 0.0, 0.0);

		// 更新起始位置
		startX = x;
		startY = y;

		glutPostRedisplay(); // 重新繪製畫面
	}
}

void keyboard(unsigned char key, int x, int y) {
	cout << key << endl;
	switch (key)
	{
		case 'b':
			cubeBody = (cubeBody + 355) % 360;
			glutPostRedisplay();
			break;
		case 'B':
			cubeBody = (cubeBody + 5) % 360;
			glutPostRedisplay();
			break;
		case 'h':
			if(head>315 || head<=45)
				head = (head + 355) % 360;
			glutPostRedisplay();
			break;
		case 'H':
			if(head<45 || head>=315)
				head = (head + 5) % 360;
			glutPostRedisplay();
			break;
		case 't':
			if(tail>315 || tail<=45)
			tail = (tail + 355) % 360;
			glutPostRedisplay();
			break;
		case 'T':
			if(tail>=315 || tail<45)
			tail = (tail + 5) % 360;
			glutPostRedisplay();
			break;
		case 'q':
			if(lf1>270 || lf1<=90)
			lf1 = (lf1 + 355) % 360;
			glutPostRedisplay();
			break;
		case 'Q':
			if (lf1 >= 270 || lf1 < 90)
			lf1 = (lf1 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'w':
			if (rf1 > 270 || rf1 <= 90)
			rf1 = (rf1 + 355) % 360;
			glutPostRedisplay();
			break;
		case 'W':
			if (rf1 >= 270 || rf1 < 90)
			rf1 = (rf1 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'a':
			if (lb1 > 270 || lb1 <= 90)
			lb1 = (lb1 + 355) % 360;
			glutPostRedisplay();
			break;
		case 'A':
			if (lb1 >= 270 || lb1 < 90)
			lb1 = (lb1 + 5) % 360;
			glutPostRedisplay();
			break;
		case 's':
			if (rb1 > 270 || rb1 <= 90)
			rb1 = (rb1 + 355) % 360;
			glutPostRedisplay();
			break;
		case 'S':
			if (rb1 >= 270 || rb1 < 90)
			rb1 = (rb1 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'e':
			if(lf2<=90 && lf2>0)
			lf2 = (lf2 - 5) % 360;
			glutPostRedisplay();
			break;
		case 'E':
			if (lf2 < 90 && lf2>=0)
			lf2 = (lf2 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'r':
			if (rf2 <= 90 && rf2>0)
			rf2 = (rf2 - 5) % 360;
			glutPostRedisplay();
			break;
		case 'R':
			if (rf2 < 90 && rf2 >= 0)
			rf2 = (rf2 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'd':
			if (lb2 <= 90 && lb2>0)
			lb2 = (lb2 - 5) % 360;
			glutPostRedisplay();
			break;
		case 'D':
			if (lb2 < 90 && lb2 >= 0)
			lb2 = (lb2 + 5) % 360;
			glutPostRedisplay();
			break;
		case 'f':
			if (rb2 <= 90 && rb2>0)
			rb2 = (rb2 - 5) % 360;
			glutPostRedisplay();
			break;
		case 'F':
			if (rb2 < 90 && rb2 >= 0)
			rb2 = (rb2 + 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void timer(int value) {

	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube View");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutKeyboardUpFunc(keyboard);
	glutTimerFunc(0,timer,0);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}