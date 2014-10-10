// RadarView.h : interface of the CRadarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARVIEW_H__459443D0_004F_435A_B451_BB23B6BE2970__INCLUDED_)
#define AFX_RADARVIEW_H__459443D0_004F_435A_B451_BB23B6BE2970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRadarView : public CView
{
protected: // create from serialization only
	CRadarView();
	DECLARE_DYNCREATE(CRadarView)

// Attributes
public:
	CRadarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	double dis;///////////雷达距离目标飞机的距离
	double dis1,dis2,dis3,dis4,dis5;///////////雷达距离干扰机的距离
	double Gj0,Gj1,Gj2,Gj3,Gj4,Gj5;
	double Pj0,Pj1,Pj2,Pj3,Pj4,Pj5;
	double Rt;///////////表示暴露区,用于绘制暴露区Rt-theta曲线
	double theta;////////记录雷达-目标机与雷达-干扰机间的夹角，即雷达主瓣和副瓣的夹角
	double theta0,theta1,theta2,theta3,theta4,theta5;
	double expose;///////暴露区显示标志
	double turnon;///////////////////////雷达开关显示
	double attack;//////////////飞机对雷达进行攻击标志
	double end_fi;
	double wave_color;
	double wave_step;
	virtual ~CRadarView();
	/////////////////////////////////////////////
	////////////////////////////////////////////
	//添加成员函数与成员变量
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL绘制描述表
	HPALETTE	m_hPalette;		//OpenGL调色板
	CDC*	    m_pDC;			//OpenGL设备描述表
/////////////////////////////////////////////////////////////////



#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRadarView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnExpose();
	afx_msg void OnAlert();
	afx_msg void OnAttack();
	afx_msg void OnTurnon();
	afx_msg void OnTurnoff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RadarView.cpp
inline CRadarDoc* CRadarView::GetDocument()
   { return (CRadarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARVIEW_H__459443D0_004F_435A_B451_BB23B6BE2970__INCLUDED_)
