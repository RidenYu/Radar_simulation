#if !defined(AFX_DLG1_H__B5B14F62_F150_4D31_9735_08FB7F49DD88__INCLUDED_)
#define AFX_DLG1_H__B5B14F62_F150_4D31_9735_08FB7F49DD88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg1 dialog

class CDlg1 : public CDialog
{
// Construction
public:
	CDlg1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg1)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg1)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG1_H__B5B14F62_F150_4D31_9735_08FB7F49DD88__INCLUDED_)
