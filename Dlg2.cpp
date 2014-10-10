// Dlg2.cpp : implementation file
//

#include "stdafx.h"
#include "Radar.h"
#include "Dlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog
double num1;
double num2;
double num3;
double num4;
double num5;
double num6;
double num7;
double num8;
double num9;
double num10;
double num11;
double num12;
double num13;
double num14;
double num15;
double num16;
double num17;
double num18;
double num19;
double num20;
double num21;
double num22;
double num23;
double num24;
double num25;
double num26;
double num27;
double num28;
double num29;
double num30;
double num31;
double num32;
double num33;

CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg2::IDD, pParent)
{

	
	//{{AFX_DATA_INIT(CDlg2)
	m_num9 = 80.0;
	m_num1 = 20.0;
	m_num10 = 60.0;
	m_num11 = 0.0;
	m_num12 = 450.0;
	m_num13 = 200.0;
	m_num14 = 0.0;
	m_num15 = 0.0;
	m_num16 = 0.0;
	m_num17 = 0.0;
	m_num18 = 0.1;              
	m_num19 = 0.0;
	m_num2 = 300.0;
	m_num20 = 0.0;
	m_num21 = 0.0;
	m_num22 = 0.0;
	m_num23 = 25.0;
	m_num24 = 15.0;
	m_num25 = 300.0;
	m_num3 = 2.9;
	m_num4 = 200.0;
	m_num5 = 40.0;
	m_num6 = 20.0;
	m_num7 = 0.0;
	m_num8 = 3.0;
	m_num26 = 0.0;
	m_num27 = 0.0;
	m_num28 = 0.0;
	m_num29 = 0.0;
	m_num30 = 0.0;
	m_num31 = 0.0;
	m_num32 = 0.0;
	m_num33 = 0.0;
	//}}AFX_DATA_INIT
}


void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg2)
	DDX_Text(pDX, IDC_EDIT9, m_num9);
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT10, m_num10);
	DDX_Text(pDX, IDC_EDIT11, m_num11);
	DDX_Text(pDX, IDC_EDIT12, m_num12);
	DDX_Text(pDX, IDC_EDIT13, m_num13);
	DDX_Text(pDX, IDC_EDIT14, m_num14);
	DDX_Text(pDX, IDC_EDIT15, m_num15);
	DDX_Text(pDX, IDC_EDIT16, m_num16);
	DDX_Text(pDX, IDC_EDIT17, m_num17);
	DDX_Text(pDX, IDC_EDIT18, m_num18);
	DDX_Text(pDX, IDC_EDIT19, m_num19);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT20, m_num20);
	DDX_Text(pDX, IDC_EDIT21, m_num21);
	DDX_Text(pDX, IDC_EDIT22, m_num22);
	DDX_Text(pDX, IDC_EDIT23, m_num23);
	DDX_Text(pDX, IDC_EDIT24, m_num24);
	DDX_Text(pDX, IDC_EDIT25, m_num25);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
	DDX_Text(pDX, IDC_EDIT4, m_num4);
	DDX_Text(pDX, IDC_EDIT5, m_num5);
	DDX_Text(pDX, IDC_EDIT6, m_num6);
	DDX_Text(pDX, IDC_EDIT7, m_num7);
	DDX_Text(pDX, IDC_EDIT8, m_num8);
	DDX_Text(pDX, IDC_EDIT26, m_num26);
	DDX_Text(pDX, IDC_EDIT27, m_num27);
	DDX_Text(pDX, IDC_EDIT28, m_num28);
	DDX_Text(pDX, IDC_EDIT29, m_num29);
	DDX_Text(pDX, IDC_EDIT30, m_num30);
	DDX_Text(pDX, IDC_EDIT31, m_num31);
	DDX_Text(pDX, IDC_EDIT32, m_num32);
	DDX_Text(pDX, IDC_EDIT33, m_num33);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg2, CDialog)
	//{{AFX_MSG_MAP(CDlg2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg2 message handlers

void CDlg2::OnOK() 
{
	// TODO: Add extra validation here
		UpdateData(true);
		num1=m_num1;
		num2=m_num2;
		num3=m_num3;
		num4=m_num4;
		num5=m_num5;
		num6=m_num6;
		num7=m_num7;
		num8=m_num8;
		num9=m_num9;
		num10=m_num10;
		num11=m_num11;
		num12=m_num12;
		num13=m_num13;
		num14=m_num14;
		num15=m_num15;
		num16=m_num16;
		num17=m_num17;
		num18=m_num18;
		num19=m_num19;
		num20=m_num20;
		num21=m_num21;
		num22=m_num22;
		num23=m_num23;
		num24=m_num24;
		num25=m_num25;
		num26=m_num26;
		num27=m_num27;
		num28=m_num28;
		num29=m_num29;
		num30=m_num30;
		num31=m_num31;
		num32=m_num32;
		num33=m_num33;
		
    	UpdateData(true);
	
	CDialog::OnOK();
}

BOOL CDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1¡¢³£¹æÂö³åÀ×´ï");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2¡¢ÂöÑ¹Ê½");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("3¡¢SAR");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("4¡¢Âö³å¶àÆÕÀÕÀ×´ï");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
