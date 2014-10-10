#if !defined(AFX_DLG2_H__AC8A4EC3_9C0F_49C6_B7B9_78F1FB266C34__INCLUDED_)
#define AFX_DLG2_H__AC8A4EC3_9C0F_49C6_B7B9_78F1FB266C34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog

class CDlg2 : public CDialog
{
// Construction
public:
	CDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg2)
	enum { IDD = IDD_DIALOG2 };
	double	m_num9;
	double	m_num1;
	double	m_num10;
	double	m_num11;
	double	m_num12;
	double	m_num13;
	double	m_num14;
	double	m_num15;
	double	m_num16;
	double	m_num17;
	double	m_num18;
	double	m_num19;
	double	m_num2;
	double	m_num20;
	double	m_num21;
	double	m_num22;
	double	m_num23;
	double	m_num24;
	double	m_num25;
	double	m_num3;
	double	m_num4;
	double	m_num5;
	double	m_num6;
	double	m_num7;
	double	m_num8;
	double	m_num26;
	double	m_num27;
	double	m_num28;
	double	m_num29;
	double	m_num30;
	double	m_num31;
	double	m_num32;
	double	m_num33;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg2)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2_H__AC8A4EC3_9C0F_49C6_B7B9_78F1FB266C34__INCLUDED_)
