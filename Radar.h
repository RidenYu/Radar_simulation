// Radar.h : main header file for the RADAR application
//

#if !defined(AFX_RADAR_H__C3343286_7C89_4674_A556_8866633DD185__INCLUDED_)
#define AFX_RADAR_H__C3343286_7C89_4674_A556_8866633DD185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRadarApp:
// See Radar.cpp for the implementation of this class
//

class CRadarApp : public CWinApp
{
public:
	CRadarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRadarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADAR_H__C3343286_7C89_4674_A556_8866633DD185__INCLUDED_)
