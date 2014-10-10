// RadarDoc.h : interface of the CRadarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARDOC_H__947E2DAD_AF70_4350_B7A6_55B414709CD6__INCLUDED_)
#define AFX_RADARDOC_H__947E2DAD_AF70_4350_B7A6_55B414709CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRadarDoc : public CDocument
{
protected: // create from serialization only
	CRadarDoc();
	DECLARE_DYNCREATE(CRadarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRadarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRadarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARDOC_H__947E2DAD_AF70_4350_B7A6_55B414709CD6__INCLUDED_)
