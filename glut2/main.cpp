#pragma comment(lib,"glew32.lib")
#include "ObjLoader.h"

#include <glew.h>

#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <time.h>


using namespace std;

//models path
string filePath = "ChargerBar.obj";

CMainWnd obj = CMainWnd(filePath);

//实现移动鼠标观察模型所需变量
float c = 3.1415926 / 180.0f;
float r = 2.0f;
float degreeX = 90;
float degreeY = 90;
float ratio = 0.1;
int h = 0.0;

static int oldPosX = -1;
static int oldPosY = -1;
// settings
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;
//安置光源
void setLightRes() {
	GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHTING); //启用光源
	glEnable(GL_LIGHT0);   //使用指定灯光
}

//初始化
void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutInitWindowPosition(500, 250);
	glutCreateWindow("ObjLoader");
    glewInit();

	glClearDepth(1.0f);				//  深度缓存设置
	glEnable(GL_DEPTH_TEST);		//  打开深度测试
	glDepthFunc(GL_LEQUAL);         //  设置深度测试类型
	glShadeModel(GL_SMOOTH);
}

void display()
{
    cout << "enter display " << endl;
    clock_t time0 = clock();
	obj.DrawScene();//绘制obj模型
	//glutSwapBuffers();
    clock_t time1 = clock();
    cout << static_cast<double>(time1 - time0) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "out display " << endl;

}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

//移动鼠标360观察模型
void moseMove(int button, int state, int x, int y)
{
	if (button != GLUT_LEFT_BUTTON) {
		return;
	}
	if (state == GLUT_DOWN) {
		oldPosX = x;
		oldPosY = y;
		return;
	}
	
	//cout << x << endl;
	//cout << y << endl;

	GLint viewport[4];
	
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//视图矩阵
	glGetDoublev(GL_PROJECTION_MATRIX, projection);//投影矩阵
	glGetIntegerv(GL_VIEWPORT, viewport);//视口
	winX = (float)x;//OGL中的窗口x坐标
	winY = (float)viewport[3] - (float)y;//OGL中的窗口y坐标

	glReadPixels(x, //x坐标
		int(winY), //y坐标
		1, 1,//读取一个像素
		GL_DEPTH_COMPONENT,//获得深度信息
		GL_FLOAT,//数据类型为浮点型
		&winZ);//获得的深度值保存在winZ中
	//cout << winZ << endl;
	
	GLfloat* pDepth = new GLfloat[SCR_HEIGHT*SCR_WIDTH];
	clock_t start_time = clock();
	glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, pDepth);
	
	ofstream fileMat("C:\\Users\\wangquan\\Documents\\Visual Studio 2015\\Projects\\glut2\\glut2\\2.txt");
	for (int i = SCR_HEIGHT; i > 0; i--) {
		for (int j = 0; j < SCR_WIDTH; j++) {
			if (pDepth[j+ SCR_WIDTH*i] == 1) {
				fileMat << 0 << " ";
			}
			else {
				fileMat << 255 << " ";
			}
		}
	}
	fileMat.close();
	
}
void changeViewPoint(int x, int y)
{
	degreeX += ratio*(x - oldPosX);
	degreeY -= ratio*(y - oldPosY);
}

void myIdle()
{
	glutPostRedisplay();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(moseMove);
	glutMotionFunc(changeViewPoint);
	glutIdleFunc(myIdle);
	
    glewInit();
    obj.SetupRC();

    glutMainLoop();
	return 0;
}