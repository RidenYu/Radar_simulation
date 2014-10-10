// RadarDoc.cpp : implementation of the CRadarDoc class
//

#include "stdafx.h"
#include "Radar.h"

#include "RadarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarDoc

IMPLEMENT_DYNCREATE(CRadarDoc, CDocument)

BEGIN_MESSAGE_MAP(CRadarDoc, CDocument)
	//{{AFX_MSG_MAP(CRadarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarDoc construction/destruction

CRadarDoc::CRadarDoc()
{
	// TODO: add one-time construction code here

}

CRadarDoc::~CRadarDoc()
{
}

BOOL CRadarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRadarDoc serialization

void CRadarDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRadarDoc diagnostics

#ifdef _DEBUG
void CRadarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRadarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRadarDoc commands
