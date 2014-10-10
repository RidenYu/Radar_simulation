// RadarView.cpp : implementation of the CRadarView class
//

#include "stdafx.h"
#include "Radar.h"
#include "Dlg2.h"
#include "Dlg3.h"


#include "RadarDoc.h"
#include "RadarView.h"

#include "math.h"

#define pi  3.1415f//////////�����״ﻷ����ʾ������
#define angle1 pi/6

#define f22_a 5/////////////����Ŀ��ɻ�����
#define f22_b 10
#define f22_c 10
#define f22_angle1 pi/6
#define f22_angle2 6*pi/7
#define f22_angle3 pi/3

////////////////////////////�������Ż�ģ�Ͳ���
#define g1_a 5/////////////����Ŀ��ɻ�����
#define g1_b 10
#define g1_c 10
#define g1_angle1 pi/6
#define g1_angle2 6*pi/7
#define g1_angle3 pi/3


////////////////////////////////////�״��Լ����Ż���һЩĬ�ϲ���


#define Kj  0.5   //////////////////����ѹ��ϵ��

#define D0  1     /////////////////�״￹���Ÿ�������

#define Kh  pow(10,0.3)   ////////////////���Ż�������ƥ�����ϵ��
				//////////////�״���Ż�ͨ������Բ������������Ӧ���ֲ�ͬ�����Լ������״�
				/////////////Բ�����ĸ��Ż����һ��Ϊ3DBת��Ϊʮ����������ʾ


#define Lj    1   ////////////////���Ż��������ϵ��

#define Ld    3   ////////////////�״﷢����������ϵ��



#define Kc  0.06   //////////////////////�����������йصĳ�����0.04-0.06,0.07-0.1֮��




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarView

IMPLEMENT_DYNCREATE(CRadarView, CView)

BEGIN_MESSAGE_MAP(CRadarView, CView)
	//{{AFX_MSG_MAP(CRadarView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_EXPOSE, OnExpose)
	ON_COMMAND(ID_ALERT, OnAlert)
	ON_COMMAND(ID_ATTACK, OnAttack)
	ON_COMMAND(ID_TURNON, OnTurnon)
	ON_COMMAND(ID_TURNOFF, OnTurnoff)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarView construction/destruction


struct point
{
	double x;
	double y;
};



CRadarView::CRadarView()
{
	// TODO: add construction code here
	end_fi=0;/////////////////////////////��ʼ��
	expose=0;////////////////////////////
	attack=0;
	turnon=0;
	wave_color=0.0f;
	wave_step=0.0f;
}

CRadarView::~CRadarView()
{
}

BOOL CRadarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	////////////////////////////////////////////////////////////////
//���ô�������
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRadarView drawing

void CRadarView::OnDraw(CDC* pDC)
{
	CRadarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CRadarView printing

BOOL CRadarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRadarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRadarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRadarView diagnostics

#ifdef _DEBUG
void CRadarView::AssertValid() const
{
	CView::AssertValid();
}

void CRadarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRadarDoc* CRadarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRadarDoc)));
	return (CRadarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRadarView message handlers

int CRadarView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/////////////////////////////////////////////////n/////////////////
//��ʼ��OpenGL�����ö�ʱ��
	m_pDC = new CClientDC(this);
	SetTimer(1, 50, NULL);
	SetTimer(2, 100, NULL);
	SetTimer(3, 400,NULL);
	SetTimer(4,500,NULL);///////////////////////////////�����״��Ų��Ķ�̬���䶨ʱ��
	/////////////////////////////////�����״��Ų��Ķ�̬���䶨ʱ��
	SetTimer(5,50,NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	return 0;
}
void CRadarView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	/////////////////////////////////////////////////////////////////
//ɾ����ɫ�����Ⱦ�����ġ���ʱ��
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);	
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	KillTimer(5);

/////////////////////////////////////////////////////////////////
}

void CRadarView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	/////////////////////////////////////////////////////////////////

//��Ӵ�������ʱ��ͼ�α任����
	if(cy==0) cy=1;
	glViewport(0,0,cx,cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(cx<=cy)
	{
		glOrtho(0.0f,250.0f,0.0f,250.0f*cy/cx,1.0f,-1.0f);
	}
	else
	{
		glOrtho(0.0f,250.0f*cx/cy,0.0f,250.0f,1.0f,-1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

/////////////////////////////////////////////////////////////////
}

double color_x=0.6f;
double color_y=0.5f;
double color_z=0.2f;
double t;

double fire_step=0;///////////////////��¼�����˶�����


void CRadarView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	/////////////////////////////////////////////////////////////////

	switch(nIDEvent)
	{
	case 1:
		end_fi+=0.1;
		break;
	case 2:
		fire_step+=0.15;
		break;
	case 3:
		t=color_x;
		color_x=color_y;
		color_y=color_z;
		color_z=t;
		break;
	case 4:
		if(wave_color==0.0f)
		{
			wave_color=1.0f;
		}
		else
		{
			wave_color=0.0f;
		}
		break;
	case 5:
		wave_step+=2.0f;
		if(wave_step>=dis-38)
		{
			wave_step=0;
		}
		break;

	default:break;
	}
//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void CRadarView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//						��ʼ��openGL����
//////////////////////////////////////////////////////////
BOOL CRadarView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//�õ�ǰ����������
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						�������ظ�ʽ
//////////////////////////////////////////////////////////
BOOL CRadarView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    24,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    32,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//�������ظ�ʽ
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}



//////////////////////////////////////////////////////////
//						������������Ⱦ
//////////////////////////////////////////////////////////
BOOL CRadarView::RenderScene() 
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	extern double num1;/////////////////////////////�״﷢������

	extern double num2;////////////////////////////��Ƶ

	extern double num3;/////////////////////////////��Ƶ

	extern double num4;/////////////////////////////////�״����

	extern double num5;/////////////////////////////////�״﷢�书��

	extern double num6;/////////////////////////////////�״���������

	extern double num7;/////////////////////////////////�״︱������

	extern double num8;//////////////////////////////////�״�������

	extern double num9;/////////////////////////////////�״�X����

	extern double num10;////////////////////////////////�״�Y����

	extern double num12;/////////////////////////////////Ŀ��ɻ�X����

	extern double num13;/////////////////////////////////Ŀ��ɻ�Y����

	extern double num15;/////////////////////////////////���Ż�X����

	extern double num16;/////////////////////////////////���Ż�Y����

	extern double num18;/////////////////////////////////Ŀ��ɻ���ЧRCS

	extern double num19;

	extern double num20;

	extern double num21;

	extern double num22;

	extern double num23;/////////////////////////////////���Ż�����

	extern double num24;/////////////////////////////////���Ż���������

	extern double num25;/////////////////////////////////���Ż����Ŵ���

	extern double num26;

	extern double num27;

	extern double num28;

	extern double num29;

	extern double num30;

	extern double num31;

	extern double num32;

	extern double num33;



	double angle;////////////////////////////////////////�洢�Ƕ�ѭ��
	double x;////////////////////////////////////////////�洢�״�Բ��X����
	double y;/////////////////////////////////////////////�洢�״�Բ��Y����
	double f22_x;/////////////////////////////////////////�洢Ŀ��ɻ�X����
	double f22_y;/////////////////////////////////////////�洢Ŀ��ɻ�Y����


	double g1_x,g2_x,g3_x,g4_x,g5_x;/////////////////////////////////////////�洢���Ż�X����
	double g1_y,g2_y,g3_y,g4_y,g5_y;/////////////////////////////////////////�洢���Ż�Y����



	double RCS=num18;///////////////////////////////////////////�洢Ŀ�����ЧRCS
	double Pt=pow(10,num5/10);////////////////////////////////////////////�洢�״﷢�书��,����λdBWת����W
	double Gt=pow(10,num6/10);////////////////////////////////////////////�洢�״��������棬����λdBת����ʮ����
	double Kf=num4/num25;////////////////////////////////////////////�״���ջ����������Ƶ�׿�ȱ�
	double Pj=pow(10,num23/10);////////////////////////////////////////////�洢���Ż����ʣ�����λ��dBWת����W
	double Gj=pow(10,num24/10);////////////////////////////////////////////�洢���Ż���������,����λdBת����ʮ����

	//�����״�ģ��
	glLineWidth(2.0f);//�����߿�1.5
	glColor3f(0.39f,0.54f,0.145f);//������ɫǳ��
	glBegin(GL_LINE_STRIP);
		for(angle=0.0f;angle<=2*pi;angle+=0.001f)
		{
			x=num9+15*cos(angle);
			y=num10+15*sin(angle);
			glVertex3f(x,y,1.0f);
		}
	glEnd();

	glBegin(GL_LINE_STRIP);
		for(angle=0.0f;angle<=2*pi;angle+=0.001f)
		{
			x=num9+7*cos(angle);
			y=num10+7*sin(angle);
			glVertex3f(x,y,1.0f);
		}
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x-15,y,0.0f);
		glVertex3f(x+15,y,0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x,y+15,0.0f);
		glVertex3f(x,y-15,0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x+7*cos(pi/4),y+7*sin(pi/4),0.0f);
		glVertex3f(x-7*cos(pi/4),y-7*sin(pi/4),0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x+7*cos(3*pi/4),y+7*sin(3*pi/4),0.0f);
		glVertex3f(x-7*cos(3*pi/4),y-7*sin(3*pi/4),0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x+15*cos(pi/4),y+15*sin(pi/4),0.0f);
		glVertex3f(x+12*cos(pi/4),y+12*sin(pi/4),0.0f);
	glEnd();
	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x-15*cos(pi/4),y-15*sin(pi/4),0.0f);
		glVertex3f(x-12*cos(pi/4),y-12*sin(pi/4),0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x+15*cos(3*pi/4),y+15*sin(3*pi/4),0.0f);
		glVertex3f(x+12*cos(3*pi/4),y+12*sin(3*pi/4),0.0f);
	glEnd();

	glBegin(GL_LINES);
		x=num9;
		y=num10;
		glVertex3f(x-15*cos(3*pi/4),y-15*sin(3*pi/4),0.0f);
		glVertex3f(x-12*cos(3*pi/4),y-12*sin(3*pi/4),0.0f);
	glEnd();

//////////////////////////////////////////////////////
	///////////////////////////////����Ŀ��ɻ�ģ��


		Gj0=Gj;
		Pj0=Pj;
		f22_x=num12;
		f22_y=num13;
		point point1;
		point point2;
		point point3;
		point point4;


		dis=sqrt((f22_x-x)*(f22_x-x)+(f22_y-y)*(f22_y-y));///////////////////////////�ɻ������״�ľ���
		point1.x=f22_x+f22_a*(((f22_x-x)/dis)*cos(f22_angle1/2)+((f22_y-y)/dis)*sin(f22_angle1/2));
		point1.y=f22_y+f22_a*(((f22_y-y)/dis)*cos(f22_angle1/2)-((f22_x-x)/dis)*sin(f22_angle1/2));

		point4.x=f22_x+f22_a*(((f22_x-x)/dis)*cos(f22_angle1/2)-((f22_y-y)/dis)*sin(f22_angle1/2));
		point4.y=f22_y+f22_a*(((f22_y-y)/dis)*cos(f22_angle1/2)+((f22_x-x)/dis)*sin(f22_angle1/2));

		point2.x=point1.x+f22_b*(((point1.x-f22_x)/f22_a)*cos(pi-f22_angle2)+((point1.y-f22_y)/f22_a)*sin(pi-f22_angle2));
		point2.y=point1.y+f22_b*(((point1.y-f22_y)/f22_a)*cos(pi-f22_angle2)-((point1.x-f22_x)/f22_a)*sin(pi-f22_angle2));

		point3.x=point4.x+f22_b*(((point4.x-f22_x)/f22_a)*cos(pi-f22_angle2)-((point4.y-f22_y)/f22_a)*sin(pi-f22_angle2));
		point3.y=point4.y+f22_b*(((point4.y-f22_y)/f22_a)*cos(pi-f22_angle2)+((point4.x-f22_x)/f22_a)*sin(pi-f22_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.0f);
		glVertex3f(f22_x,f22_y,0.0f);
		glVertex3f(point1.x,point1.y,0.0f);
		glVertex3f(point4.x,point4.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(color_x,color_y,0.3f);
		glVertex3f(point1.x,point1.y,0.0f);
		glVertex3f(point2.x,point2.y,0.0f);
		glVertex3f(point3.x,point3.y,0.0f);
		glVertex3f(point4.x,point4.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(f22_x,f22_y,0.0f);
		glVertex3f(point1.x,point1.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point1.x,point1.y,0.0f);
		glVertex3f(point2.x,point2.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point2.x,point2.y,0.0f);
		glVertex3f(point3.x,point3.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point3.x,point3.y,0.0f);
		glVertex3f(point4.x,point4.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point4.x,point4.y,0.0f);
		glVertex3f(f22_x,f22_y,0.0f);
	glEnd();
	
/////////////////////////////////////////////////////////////////////////////////////////////////ģ���Ų���̬����
	if(turnon==1)
	{
	double wave_x,wave_y;
	double plane_angle;
	plane_angle=acos((f22_x-x)/dis);
	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for(double wave=plane_angle-0.05;wave<=plane_angle+0.05;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+18*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+18*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();

	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.1;wave<=plane_angle+0.1;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+20*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+20*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();

	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.11;wave<=plane_angle+0.11;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+23*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+23*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();

	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.105;wave<=plane_angle+0.105;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+26*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+26*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();

	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.12;wave<=plane_angle+0.12;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+29*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+29*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();

	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.125;wave<=plane_angle+0.125;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+32*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+32*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();
	glColor3f(0.0f,wave_color,0.0f);
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.13;wave<=plane_angle+0.13;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+35*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+35*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();
	glBegin(GL_LINE_STRIP);
		for( wave=plane_angle-0.13;wave<=plane_angle+0.13;wave+=0.001f)
		{
			wave_x=num9+wave_step*cos(plane_angle)+38*cos(wave);
			wave_y=num10+wave_step*sin(plane_angle)+38*sin(wave);
			glVertex3f(wave_x,wave_y,1.0f);
		}
	glEnd();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////��ʼɨ��
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f,1.0f,0.0f);
		x=num9;
		y=num10;
		double end_x=x+15*cos(end_fi);
		double end_y=y+15*sin(end_fi);
		glVertex3f(x,y,0.0f);
		glVertex3f(x+15*cos(end_fi),y+15*sin(end_fi),1.0f);
		glVertex3f(x+15*cos(end_fi+pi/200),y+15*sin(end_fi+pi/200),0.0f);

		glColor3f(0.74f,0.98f,0.78f);
		glVertex3f(x+15*cos(end_fi+2*pi/200),y+15*sin(end_fi+2*pi/200),0.0f);		
		glVertex3f(x+15*cos(end_fi+3*pi/200),y+15*sin(end_fi+3*pi/200),0.0f);

		glColor3f(1.0f,0.87f,0.67f);
		glVertex3f(x+15*cos(end_fi+4*pi/200),y+15*sin(end_fi+4*pi/200),0.0f);
		glVertex3f(x+15*cos(end_fi+5*pi/200),y+15*sin(end_fi+5*pi/200),0.0f);
	glEnd();
	}
	/////////////////////////////////////////////////////////////////////////////////////////�������Ż�1ģ��
		g1_x=num15;
		g1_y=num16;
		point point5;
		point point6;
		point point7;
		point point8;


		dis1=sqrt((g1_x-x)*(g1_x-x)+(g1_y-y)*(g1_y-y));
		point5.x=g1_x+g1_a*(((g1_x-x)/dis1)*cos(g1_angle1/2)+((g1_y-y)/dis1)*sin(g1_angle1/2));
		point5.y=g1_y+g1_a*(((g1_y-y)/dis1)*cos(g1_angle1/2)-((g1_x-x)/dis1)*sin(g1_angle1/2));

		point8.x=g1_x+g1_a*(((g1_x-x)/dis1)*cos(g1_angle1/2)-((g1_y-y)/dis1)*sin(g1_angle1/2));
		point8.y=g1_y+g1_a*(((g1_y-y)/dis1)*cos(g1_angle1/2)+((g1_x-x)/dis1)*sin(g1_angle1/2));

		point6.x=point5.x+g1_b*(((point5.x-g1_x)/g1_a)*cos(pi-g1_angle2)+((point5.y-g1_y)/g1_a)*sin(pi-g1_angle2));
		point6.y=point5.y+g1_b*(((point5.y-g1_y)/g1_a)*cos(pi-g1_angle2)-((point5.x-g1_x)/g1_a)*sin(pi-g1_angle2));

		point7.x=point8.x+g1_b*(((point8.x-g1_x)/g1_a)*cos(pi-g1_angle2)-((point8.y-g1_y)/g1_a)*sin(pi-g1_angle2));
		point7.y=point8.y+g1_b*(((point8.y-g1_y)/g1_a)*cos(pi-g1_angle2)+((point8.x-g1_x)/g1_a)*sin(pi-g1_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(g1_x,g1_y,0.0f);
		glVertex3f(point5.x,point5.y,0.0f);
		glVertex3f(point8.x,point8.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(point5.x,point5.y,0.0f);
		glVertex3f(point6.x,point6.y,0.0f);
		glVertex3f(point7.x,point7.y,0.0f);
		glVertex3f(point8.x,point8.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(g1_x,g1_y,0.0f);
		glVertex3f(point5.x,point5.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point5.x,point5.y,0.0f);
		glVertex3f(point6.x,point6.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point6.x,point6.y,0.0f);
		glVertex3f(point7.x,point7.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point7.x,point7.y,0.0f);
		glVertex3f(point8.x,point8.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point8.x,point8.y,0.0f);
		glVertex3f(g1_x,g1_y,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////�������Ż�2ģ��
		g2_x=num19;
		g2_y=num20;
		point point9;
		point point10;
		point point11;
		point point12;


		dis2=sqrt((g2_x-x)*(g2_x-x)+(g2_y-y)*(g2_y-y));
		point9.x=g2_x+g1_a*(((g2_x-x)/dis2)*cos(g1_angle1/2)+((g2_y-y)/dis2)*sin(g1_angle1/2));
		point9.y=g2_y+g1_a*(((g2_y-y)/dis2)*cos(g1_angle1/2)-((g2_x-x)/dis2)*sin(g1_angle1/2));

		point12.x=g2_x+g1_a*(((g2_x-x)/dis2)*cos(g1_angle1/2)-((g2_y-y)/dis2)*sin(g1_angle1/2));
		point12.y=g2_y+g1_a*(((g2_y-y)/dis2)*cos(g1_angle1/2)+((g2_x-x)/dis2)*sin(g1_angle1/2));

		point10.x=point9.x+g1_b*(((point9.x-g2_x)/g1_a)*cos(pi-g1_angle2)+((point9.y-g2_y)/g1_a)*sin(pi-g1_angle2));
		point10.y=point9.y+g1_b*(((point9.y-g2_y)/g1_a)*cos(pi-g1_angle2)-((point9.x-g2_x)/g1_a)*sin(pi-g1_angle2));

		point11.x=point12.x+g1_b*(((point12.x-g2_x)/g1_a)*cos(pi-g1_angle2)-((point12.y-g2_y)/g1_a)*sin(pi-g1_angle2));
		point11.y=point12.y+g1_b*(((point12.y-g2_y)/g1_a)*cos(pi-g1_angle2)+((point12.x-g2_x)/g1_a)*sin(pi-g1_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(g2_x,g2_y,0.0f);
		glVertex3f(point9.x,point9.y,0.0f);
		glVertex3f(point12.x,point12.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(point9.x,point9.y,0.0f);
		glVertex3f(point10.x,point10.y,0.0f);
		glVertex3f(point11.x,point11.y,0.0f);
		glVertex3f(point12.x,point12.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(g2_x,g2_y,0.0f);
		glVertex3f(point9.x,point9.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point9.x,point9.y,0.0f);
		glVertex3f(point10.x,point10.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point10.x,point10.y,0.0f);
		glVertex3f(point11.x,point11.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point11.x,point11.y,0.0f);
		glVertex3f(point12.x,point12.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point12.x,point12.y,0.0f);
		glVertex3f(g2_x,g2_y,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////�������Ż�3ģ��
		g3_x=num22;
		g3_y=num26;
		point point13;
		point point14;
		point point15;
		point point16;


		dis3=sqrt((g3_x-x)*(g3_x-x)+(g3_y-y)*(g3_y-y));
		point13.x=g3_x+g1_a*(((g3_x-x)/dis3)*cos(g1_angle1/2)+((g3_y-y)/dis3)*sin(g1_angle1/2));
		point13.y=g3_y+g1_a*(((g3_y-y)/dis3)*cos(g1_angle1/2)-((g3_x-x)/dis3)*sin(g1_angle1/2));

		point16.x=g3_x+g1_a*(((g3_x-x)/dis3)*cos(g1_angle1/2)-((g3_y-y)/dis3)*sin(g1_angle1/2));
		point16.y=g3_y+g1_a*(((g3_y-y)/dis3)*cos(g1_angle1/2)+((g3_x-x)/dis3)*sin(g1_angle1/2));

		point14.x=point13.x+g1_b*(((point13.x-g3_x)/g1_a)*cos(pi-g1_angle2)+((point13.y-g3_y)/g1_a)*sin(pi-g1_angle2));
		point14.y=point13.y+g1_b*(((point13.y-g3_y)/g1_a)*cos(pi-g1_angle2)-((point13.x-g3_x)/g1_a)*sin(pi-g1_angle2));

		point15.x=point16.x+g1_b*(((point16.x-g3_x)/g1_a)*cos(pi-g1_angle2)-((point16.y-g3_y)/g1_a)*sin(pi-g1_angle2));
		point15.y=point16.y+g1_b*(((point16.y-g3_y)/g1_a)*cos(pi-g1_angle2)+((point16.x-g3_x)/g1_a)*sin(pi-g1_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(g3_x,g3_y,0.0f);
		glVertex3f(point13.x,point13.y,0.0f);
		glVertex3f(point16.x,point16.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(point13.x,point13.y,0.0f);
		glVertex3f(point14.x,point14.y,0.0f);
		glVertex3f(point15.x,point15.y,0.0f);
		glVertex3f(point16.x,point16.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(g3_x,g3_y,0.0f);
		glVertex3f(point13.x,point13.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point13.x,point13.y,0.0f);
		glVertex3f(point14.x,point14.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point14.x,point14.y,0.0f);
		glVertex3f(point15.x,point15.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point15.x,point15.y,0.0f);
		glVertex3f(point16.x,point16.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point16.x,point16.y,0.0f);
		glVertex3f(g3_x,g3_y,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////�������Ż�4ģ��
		g4_x=num28;
		g4_y=num29;
		point point17;
		point point18;
		point point19;
		point point20;


		dis4=sqrt((g4_x-x)*(g4_x-x)+(g4_y-y)*(g4_y-y));
		point17.x=g4_x+g1_a*(((g4_x-x)/dis4)*cos(g1_angle1/2)+((g4_y-y)/dis4)*sin(g1_angle1/2));
		point17.y=g4_y+g1_a*(((g4_y-y)/dis4)*cos(g1_angle1/2)-((g4_x-x)/dis4)*sin(g1_angle1/2));

		point20.x=g4_x+g1_a*(((g4_x-x)/dis4)*cos(g1_angle1/2)-((g4_y-y)/dis4)*sin(g1_angle1/2));
		point20.y=g4_y+g1_a*(((g4_y-y)/dis4)*cos(g1_angle1/2)+((g4_x-x)/dis4)*sin(g1_angle1/2));

		point18.x=point17.x+g1_b*(((point17.x-g4_x)/g1_a)*cos(pi-g1_angle2)+((point17.y-g4_y)/g1_a)*sin(pi-g1_angle2));
		point18.y=point17.y+g1_b*(((point17.y-g4_y)/g1_a)*cos(pi-g1_angle2)-((point17.x-g4_x)/g1_a)*sin(pi-g1_angle2));

		point19.x=point20.x+g1_b*(((point20.x-g4_x)/g1_a)*cos(pi-g1_angle2)-((point20.y-g4_y)/g1_a)*sin(pi-g1_angle2));
		point19.y=point20.y+g1_b*(((point20.y-g4_y)/g1_a)*cos(pi-g1_angle2)+((point20.x-g4_x)/g1_a)*sin(pi-g1_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(g4_x,g4_y,0.0f);
		glVertex3f(point17.x,point17.y,0.0f);
		glVertex3f(point20.x,point20.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(point17.x,point17.y,0.0f);
		glVertex3f(point18.x,point18.y,0.0f);
		glVertex3f(point19.x,point19.y,0.0f);
		glVertex3f(point20.x,point20.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(g4_x,g4_y,0.0f);
		glVertex3f(point17.x,point17.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point17.x,point17.y,0.0f);
		glVertex3f(point18.x,point18.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point18.x,point18.y,0.0f);
		glVertex3f(point19.x,point19.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point19.x,point19.y,0.0f);
		glVertex3f(point20.x,point20.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point20.x,point20.y,0.0f);
		glVertex3f(g4_x,g4_y,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////�������Ż�5ģ��
		g5_x=num31;
		g5_y=num32;
		point point21;
		point point22;
		point point23;
		point point24;


		dis5=sqrt((g5_x-x)*(g5_x-x)+(g5_y-y)*(g5_y-y));
		point21.x=g5_x+g1_a*(((g5_x-x)/dis5)*cos(g1_angle1/2)+((g5_y-y)/dis5)*sin(g1_angle1/2));
		point21.y=g5_y+g1_a*(((g5_y-y)/dis5)*cos(g1_angle1/2)-((g5_x-x)/dis5)*sin(g1_angle1/2));

		point24.x=g5_x+g1_a*(((g5_x-x)/dis5)*cos(g1_angle1/2)-((g5_y-y)/dis5)*sin(g1_angle1/2));
		point24.y=g5_y+g1_a*(((g5_y-y)/dis5)*cos(g1_angle1/2)+((g5_x-x)/dis5)*sin(g1_angle1/2));

		point22.x=point21.x+g1_b*(((point21.x-g5_x)/g1_a)*cos(pi-g1_angle2)+((point21.y-g5_y)/g1_a)*sin(pi-g1_angle2));
		point22.y=point21.y+g1_b*(((point21.y-g5_y)/g1_a)*cos(pi-g1_angle2)-((point21.x-g5_x)/g1_a)*sin(pi-g1_angle2));

		point23.x=point24.x+g1_b*(((point24.x-g5_x)/g1_a)*cos(pi-g1_angle2)-((point24.y-g5_y)/g1_a)*sin(pi-g1_angle2));
		point23.y=point24.y+g1_b*(((point24.y-g5_y)/g1_a)*cos(pi-g1_angle2)+((point24.x-g5_x)/g1_a)*sin(pi-g1_angle2));

		glColor3f(1.0f,0.0f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(g5_x,g5_y,0.0f);
		glVertex3f(point21.x,point21.y,0.0f);
		glVertex3f(point24.x,point24.y,0.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(point21.x,point21.y,0.0f);
		glVertex3f(point22.x,point22.y,0.0f);
		glVertex3f(point23.x,point23.y,0.0f);
		glVertex3f(point24.x,point24.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(g5_x,g5_y,0.0f);
		glVertex3f(point21.x,point21.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point21.x,point21.y,0.0f);
		glVertex3f(point22.x,point22.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point22.x,point22.y,0.0f);
		glVertex3f(point23.x,point23.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point23.x,point23.y,0.0f);
		glVertex3f(point24.x,point24.y,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(point24.x,point24.y,0.0f);
		glVertex3f(g5_x,g5_y,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////��¶��/ѹ�����Ļ���
/////////////////////////////////////////////////////////////////////��¶�����ؾ���
	double Rj0=sqrt(((Kj*RCS*D0*Pt*Gt*Kh*Lj*Kf)/(4*pi*Pj*Gj*Ld)));
	if(expose==1)
	{
		glColor3f(1.0f,1.0f,0.0f);
		glBegin(GL_LINE_STRIP);
			for(theta=0;theta<=pi;theta+=0.0001f)
			{
				theta0=theta;
				if(g1_y>=y)
				{
					theta1=acos((dis*dis+dis1*dis1-(f22_x-g1_x)*(f22_x-g1_x)-(f22_y-g1_y)*(f22_y-g1_y))/(2*dis*dis1))-theta;
				}
				if(g1_y<y)
				{
					theta1=acos((dis*dis+dis1*dis1-(f22_x-g1_x)*(f22_x-g1_x)-(f22_y-g1_y)*(f22_y-g1_y))/(2*dis*dis1))-theta;
				}
				if(g2_y-y>=0)
				{
					theta2=acos((dis*dis+dis2*dis2-(f22_x-g2_x)*(f22_x-g2_x)-(f22_y-g2_y)*(f22_y-g2_y))/(2*dis*dis2))-theta;
				}
				else
				{
					theta2=2*pi-acos((g2_x-x)/dis2)-theta;
				}
				if(g3_y-y>=0)
				{
					theta3=acos((dis*dis+dis3*dis3-(f22_x-g3_x)*(f22_x-g3_x)-(f22_y-g3_y)*(f22_y-g3_y))/(2*dis*dis3))-theta;
				}
				else
				{
					theta3=2*pi-acos((g3_x-x)/dis3)-theta;
				}
				if(g4_y-y>=0)
				{
					theta4=acos((dis*dis+dis4*dis4-(f22_x-g4_x)*(f22_x-g4_x)-(f22_y-g4_y)*(f22_y-g4_y))/(2*dis*dis4))-theta;
				}
				else
				{
					theta4=2*pi-acos((g4_x-x)/dis4)-theta;
				}
				if(g5_y-y>=0)
				{
					theta5=acos((dis*dis+dis5*dis5-(f22_x-g5_x)*(f22_x-g5_x)-(f22_y-g5_y)*(f22_y-g5_y))/(2*dis*dis5))-theta;
				}
				else
				{
					theta5=2*pi-acos((g5_x-x)/dis5)-theta;
				}

				
				double a0=(Pj0*Gj0)/(dis*dis*theta0*theta0);
				double a1,a2,a3,a4,a5;

				if((g1_x==0)&&(g1_y==0))
				{a1=0;}
				else
				{
					a1=(Pj*Gj)/(dis1*dis1*theta1*theta1);
				}
				if((g2_x==0)&&(g2_y==0))
				{a2=0;}
				else
				{
					a2=(Pj*Gj)/(dis2*dis2*theta2*theta2);
				}
				if((g3_x==0)&&(g3_y==0))
				{a3=0;}
				else
				{
					a3=(Pj*Gj)/(dis3*dis3*theta3*theta3);
				}
				if((g4_x==0)&&(g4_y==0))
				{a4=0;}
				else
				{
					a4=(Pj*Gj)/(dis4*dis4*theta4*theta4);
				}
				if((g5_x==0)&&(g5_y==0))
				{a5=0;}
				else
				{
					a5=(Pj*Gj)/(dis5*dis5*theta5*theta5);
				}
	
	

				Rt=sqrt(sqrt(((Kj*RCS*D0*Pt*Gt*Ld)/(4*pi*Kh*Lj*Kf*Kc*num8*num8*(a0+a1+a2+a3+a4+a5)))));

				x=num9+(Rt+Rj0+15)*(((f22_x-x)/dis)*cos(theta)-((f22_y-y)/dis)*sin(theta));
				y=num10+(Rt+Rj0+15)*(((f22_y-y)/dis)*cos(theta)+((f22_x-x)/dis)*sin(theta));
				glVertex3f(x,y,0.0f);
		}
		glEnd();
		glColor3f(1.0f,1.0f,0.0f);
		glBegin(GL_LINE_STRIP);
			for(theta=0;theta<pi;theta+=0.0001f)
			{
				theta0=theta;
				double a0=(Pj0*Gj0)/(dis*dis*theta0*theta0);
				double a1,a2,a3,a4,a5;
				if((g1_x==0)&&(g1_y==0))
				{a1=0;}
				else
				{
					a1=(Pj*Gj)/(dis1*dis1*theta1*theta1);
				}
				if((g2_x==0)&&(g2_y==0))
				{a2=0;}
				else
				{
					a2=(Pj*Gj)/(dis2*dis2*theta2*theta2);
				}
				if((g3_x==0)&&(g3_y==0))
				{a3=0;}
				else
				{
					a3=(Pj*Gj)/(dis3*dis3*theta3*theta3);
				}
				if((g4_x==0)&&(g4_y==0))
				{a4=0;}
				else
				{
					a4=(Pj*Gj)/(dis4*dis4*theta4*theta4);
				}
				if((g5_x==0)&&(g5_y==0))
				{a5=0;}
				else
				{
					a5=(Pj*Gj)/(dis5*dis5*theta5*theta5);
				}
				Rt=sqrt(sqrt(((Kj*RCS*D0*Pt*Gt*Ld)/(4*pi*Kh*Lj*Kf*Kc*num8*num8*(a0+a1+a2+a3+a4+a5)))));

				x=num9+(Rt+Rj0+15)*(((f22_x-x)/dis)*cos(theta)+((f22_y-y)/dis)*sin(theta));
				y=num10+(Rt+Rj0+15)*(((f22_y-y)/dis)*cos(theta)-((f22_x-x)/dis)*sin(theta));

				glVertex3f(x,y,0.0f);
		}
		glEnd();

	}
	static double linjie=22.0;
	CDlg3 dlg3;
	if(attack==1)
	{
		glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_LINE_STRIP);
			for(angle=0.0f;angle<=2*pi;angle+=0.001f)
			{
				double Vx=35;
				double Vy=35*(num13-num10)/(num12-num9);
				x=num12-Vx*fire_step+1*cos(angle);
				y=num13-Vy*fire_step+1*sin(angle);
				glVertex3f(x,y,1.0f);
			}
		glEnd();
		if(sqrt((x-num9)*(x-num9)+(y-num10)*(y-num10))<linjie)
		{
			KillTimer(2);
			linjie=0;
			dlg3.DoModal();
			//MessageBox(" Alert!!!Alert     Enemy Found!!!",NULL,MB_OK);
		}

	}
	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

/////////////////////////////////////////////////////////��Ӧ��¶����ʾ
void CRadarView::OnExpose() 
{
	// TODO: Add your command handler code here
	expose=1;	
}
void CRadarView::OnAlert() 
{
	// TODO: Add your command handler code here
	if(dis<=Rt)
	{
		MessageBox("     Alert!!!Alert!!!",NULL,MB_OK);
	}
	else 
	{
		MessageBox("     No Enemy Found!",NULL,MB_OK);
		
	}	
}

void CRadarView::OnAttack() 
{
	// TODO: Add your command handler code here
	attack=1;
	fire_step=0;	
}

void CRadarView::OnTurnon() 
{
	// TODO: Add your command handler code here
	turnon=1;
	
}

void CRadarView::OnTurnoff() 
{
	// TODO: Add your command handler code here
	turnon=0;
	
}
