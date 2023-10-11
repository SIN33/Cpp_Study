// oglRubberBandDoc.h : interface of the COglRubberBandDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGLRUBBERBANDDOC_H__D8DA9D4E_4C82_433D_968F_5C416BDB19AD__INCLUDED_)
#define AFX_OGLRUBBERBANDDOC_H__D8DA9D4E_4C82_433D_968F_5C416BDB19AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COglRubberBandDoc : public CDocument
{
protected: // create from serialization only
	COglRubberBandDoc();
	DECLARE_DYNCREATE(COglRubberBandDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COglRubberBandDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COglRubberBandDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COglRubberBandDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLRUBBERBANDDOC_H__D8DA9D4E_4C82_433D_968F_5C416BDB19AD__INCLUDED_)
