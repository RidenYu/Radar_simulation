// Dlg1.cpp : implementation file
//

#include "stdafx.h"
#include "Radar.h"
#include "Dlg1.h"
#include "Dlg2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg1 dialog


CDlg1::CDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg1, CDialog)
	//{{AFX_MSG_MAP(CDlg1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg1 message handlers

void CDlg1::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CDlg2 dlg2;
	dlg2.DoModal();


	
}

void CDlg1::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg1::OnCancel() 
{
	// TODO: Add extra cleanup here
	//MessageBox("Exit",NULL,MB_YESNO);
	
	CDialog::OnCancel();
}
