#pragma comment(lib,"glew32.lib")

#include "ObjLoader.h"
#include <windows.h>
#include <sstream>
#include <fstream>

#include <gl/glut.h>
#include <gl/GLU.h>

#include <stdio.h>
#include <iostream>
#include <time.h>


using namespace std;
//实现移动鼠标观察模型所需变量
extern float c;
extern float r;
extern float degreeX;
extern float degreeY;
extern int h;

GLuint VBO, VAO, EBO;

#define NORM 135
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMainWnd::CMainWnd(string path) :
	m_hWnd(NULL),
	m_fAngle(0.0f),
	m_hRC(NULL),
	m_path(path)
{
	InitScene();
}

CMainWnd::~CMainWnd()
{
}

//
// GLCube()
// Renders a cube.
//
#define YU 1
void CMainWnd::GLCube()
{
    clock_t time0 = clock();
    glBegin(GL_TRIANGLES);							// 绘制三角形

	for (int i = 0; i<m_pic.F.size(); i++)
	{

        /*
		if (m_pic.VT.size() != 0)
            glTexCoord2f(m_pic.VT[m_pic.F[i].T[0]].TU, m_pic.VT[m_pic.F[i].T[0]].TV);  //纹理	
		if (m_pic.VN.size() != 0)
            glNormal3f(m_pic.VN[m_pic.F[i].N[0]].NX, m_pic.VN[m_pic.F[i].N[0]].NY, m_pic.VN[m_pic.F[i].N[0]].NZ);//法向量
        */
		glVertex3f(m_pic.V[m_pic.F[i].V[0]].X, m_pic.V[m_pic.F[i].V[0]].Y, m_pic.V[m_pic.F[i].V[0]].Z);		// 上顶点
        /*
		if (m_pic.VT.size() != 0)
            glTexCoord2f(m_pic.VT[m_pic.F[i].T[2]].TU, m_pic.VT[m_pic.F[i].T[2]].TV);  //纹理
		if (m_pic.VN.size() != 0)
            glNormal3f(m_pic.VN[m_pic.F[i].N[2]].NX, m_pic.VN[m_pic.F[i].N[2]].NY, m_pic.VN[m_pic.F[i].N[2]].NZ);//法向量
		*/
        glVertex3f(m_pic.V[m_pic.F[i].V[2]].X, m_pic.V[m_pic.F[i].V[2]].Y, m_pic.V[m_pic.F[i].V[2]].Z);		// 右下
        /*
		if (m_pic.VT.size() != 0)
            glTexCoord2f(m_pic.VT[m_pic.F[i].T[1]].TU, m_pic.VT[m_pic.F[i].T[1]].TV);  //纹理
		if (m_pic.VN.size() != 0)
            glNormal3f(m_pic.VN[m_pic.F[i].N[1]].NX, m_pic.VN[m_pic.F[i].N[1]].NY, m_pic.VN[m_pic.F[i].N[1]].NZ);//法向量
        */
		glVertex3f(m_pic.V[m_pic.F[i].V[1]].X, m_pic.V[m_pic.F[i].V[1]].Y, m_pic.V[m_pic.F[i].V[1]].Z);		// 左下
	}
    glEnd();										// 三角形绘制结束	

    glutSwapBuffers();
    clock_t time1 = clock();
    cout << static_cast<double>(time1 - time0) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

//
// InitScene()
// Called when the OpenGL RC has been created. Sets the initial state for
// the OpenGL scene.
//
void CMainWnd::InitScene()
{
	ReadPIC();
    PICToVertex();
	glClearColor(0.000f, 0.000f, 0.000f, 1.0f); //Background color
}

//
// KillScene()
// Called when the OpenGL RC is about to be destroyed. 
//
void CMainWnd::KillScene()
{
	// TODO: Use KillScene to free resources.
}

//
// DrawScene()
// Called each time the OpenGL scene has to be drawn.
//
void CMainWnd::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers  // 清除屏幕及深度缓存
    glColor3f(0.0, 1.0, 0.0);												//绿色

	glLoadIdentity(); // Load identity matrix	// 重置模型观察矩阵
	//glEnable(GL_LIGHT0);//启用0号灯到7号灯(光源)　　光源要求由函数glLight函数来完成
	//glEnable(GL_LIGHTING);//启用灯源
	glEnable(GL_DEPTH_TEST);//启用深度测试。　　根据坐标的远近自动隐藏被遮住的图形（材料）

	
	gluLookAt(r*sin(c*degreeY)*cos(c*degreeX), r*cos(c*degreeY), r*sin(c*degreeY)*sin(c*degreeX), 
				0.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f);		//移动相机
    
    /*
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pic.F.size() * 3*sizeof(GLuint), indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawElements(GL_TRIANGLES, m_pic.F.size() * 3, GL_UNSIGNED_INT, indices);
    
	glFlush();
    */

  
    //开启VA状态  
    glEnableClientState(GL_VERTEX_ARRAY);

    //绑定数据  
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    //绘制

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, m_pic.F.size() * 3, GL_UNSIGNED_INT, 0);

    //关闭VA状态  
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

//
// Tick()
// The applications "heartbeat" function. Called before another frame needs
// to be drawn. Use this function to calculate new positions for objects in 
// the scene, for instance. Set bRedrawScene = FALSE if the scene should not be 
// redrawn.
//
void CMainWnd::Tick(BOOL &bRedrawScene)
{
	m_fAngle += 0.1; // Add some rotation to the cube
}

void CMainWnd::ReadPIC()
{
	ifstream ifs(m_path);//cube bunny Eight
	string s;
	Mian *f;
	POINT3 *v;
	FaXiangLiang *vn;
	WenLi	*vt;
	while (getline(ifs, s))
	{
		if (s.length()<2)continue;
		if (s[0] == 'v') {
			if (s[1] == 't') {//vt 0.581151 0.979929 纹理
				istringstream in(s);
				vt = new WenLi();
				string head;
				in >> head >> vt->TU >> vt->TV;
				m_pic.VT.push_back(*vt);
			}
			else if (s[1] == 'n') {//vn 0.637005 -0.0421857 0.769705 法向量
				istringstream in(s);
				vn = new FaXiangLiang();
				string head;
				in >> head >> vn->NX >> vn->NY >> vn->NZ;
				m_pic.VN.push_back(*vn);
			}
			else {//v -53.0413 158.84 -135.806 点
				istringstream in(s);
				v = new POINT3();
				string head;
				in >> head >> v->X >> v->Y >> v->Z;
                
                v->X = v->X / NORM;
                v->Y = v->Y / NORM;
                v->Z = v->Z / NORM;
				m_pic.V.push_back(*v);
			}
		}
		else if (s[0] == 'f') {//f 2443//2656 2442//2656 2444//2656 面
			for (int k = s.size() - 1; k >= 0; k--) {
				if (s[k] == '/')s[k] = ' ';
			}
			istringstream in(s);
			f = new Mian();
			string head;
			in >> head;
			int i = 0;
			while (i<3)
			{
				if (m_pic.V.size() != 0)
				{
					in >> f->V[i];
					f->V[i] -= 1;
				}
				if (m_pic.VT.size() != 0)
				{
					in >> f->T[i];
					f->T[i] -= 1;
				}
				if (m_pic.VN.size() != 0)
				{
					in >> f->N[i];
					f->N[i] -= 1;
				}
				i++;
			}
			m_pic.F.push_back(*f);
		}
	}
}

void CMainWnd::PICToVertex() 
{
    vertices = new GLfloat[m_pic.V.size()*3];
    indices = new GLuint[m_pic.F.size()*3];

    int i = 0;
    vector<POINT3>::iterator iter;
    for (iter = m_pic.V.begin(); iter != m_pic.V.end(); iter++) {
        if (i < m_pic.V.size()*3) {
            vertices[i] = iter->X;
            vertices[i+1] = iter->Y;
            vertices[i+2] = iter->Z;
            i += 3;
        }
    }

    i = 0;
    vector<Mian>::iterator iter_triangle;
    for (iter_triangle = m_pic.F.begin(); iter_triangle != m_pic.F.end(); iter_triangle++) {
        if (i < m_pic.F.size() * 3) {
            indices[i] = iter_triangle->V[0];
            indices[i+1] = iter_triangle->V[1];
            indices[i+2] = iter_triangle->V[2];
            i += 3;
        }
    }
}

void CMainWnd::SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pic.F.size() * 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}