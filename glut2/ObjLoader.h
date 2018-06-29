#pragma once

#include <windows.h>
#include <sstream>
#include <fstream>
#include <glew.h>
#include <gl/GL.h>
// MainWnd.h: interface for the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(MAINWND_H_INCLUDED)
#define MAINWND_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMainWnd
// Encapsulates the main window
//
struct POINT3 {
	double X;
	double Y;
	double Z;
};
struct WenLi {
	double TU;
	double TV;
};
struct FaXiangLiang {
	double NX;
	double NY;
	double NZ;
};
struct Mian {
	unsigned int V[3];
    unsigned int T[3];
    unsigned int N[3];
};
class PIC
{
public:
	vector<POINT3> V;//V�������㡣��ʽΪV X Y Z��V�����X Y Z��ʾ�����������ꡣ������
	vector<WenLi>  VT;//��ʾ�������ꡣ��ʽΪVT TU TV��������
	vector<FaXiangLiang> VN;//VN����������ÿ�������ε��������㶼Ҫָ��һ������������ʽΪVN NX NY NZ��������
	vector<Mian> F;//F���档�������ŵ�����ֵ�ֱ������������Ķ��㡢�������ꡢ��������������
				   //��ĸ�ʽΪ��f Vertex1/Texture1/Normal1 Vertex2/Texture2/Normal2 Vertex3/Texture3/Normal3
};

class CMainWnd
{
public:
	CMainWnd(string path);
	virtual ~CMainWnd();

	HWND m_hWnd;
	HGLRC m_hRC;			// Handle to RC
	GLfloat m_fAngle;		// Rotation angle of the cube
	PIC m_pic;
	string m_path;
    GLfloat* vertices;
    GLuint* indices;

	void ReadPIC();
    void PICToVertex();
	void DrawScene();
	void KillScene();
	void InitScene();
	void Tick(BOOL &bRedrawScene);
	void GLCube();
    void SetupRC();
};

#endif // !defined(MAINWND_H_INCLUDED)