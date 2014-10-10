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
	double dis;///////////�״����Ŀ��ɻ��ľ���
	double dis1,dis2,dis3,dis4,dis5;///////////�״������Ż��ľ���
	double Gj0,Gj1,Gj2,Gj3,Gj4,Gj5;
	double Pj0,Pj1,Pj2,Pj3,Pj4,Pj5;
	double Rt;///////////��ʾ��¶��,���ڻ��Ʊ�¶��Rt-theta����
	double theta;////////��¼�״�-Ŀ������״�-���Ż���ļнǣ����״�����͸���ļн�
	double theta0,theta1,theta2,theta3,theta4,theta5;
	double expose;///////��¶����ʾ��־
	double turnon;///////////////////////�״￪����ʾ
	double attack;//////////////�ɻ����״���й�����־
	double end_fi;
	double wave_color;
	double wave_step;
	virtual ~CRadarView();
	/////////////////////////////////////////////
	////////////////////////////////////////////
	//��ӳ�Ա�������Ա����
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL����������
	HPALETTE	m_hPalette;		//OpenGL��ɫ��
	CDC*	    m_pDC;			//OpenGL�豸������
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
