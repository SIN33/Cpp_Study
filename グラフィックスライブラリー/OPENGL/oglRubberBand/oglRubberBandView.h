// oglRubberBandView.h : interface of the COglRubberBandView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGLRUBBERBANDVIEW_H__9642EBEB_B765_4832_8795_515A20F84C40__INCLUDED_)
#define AFX_OGLRUBBERBANDVIEW_H__9642EBEB_B765_4832_8795_515A20F84C40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/gl.h>

class COglRubberBandView : public CView
{
protected: // create from serialization only
	COglRubberBandView();
	DECLARE_DYNCREATE(COglRubberBandView)

// Attributes
public:
	COglRubberBandDoc* GetDocument();

	HGLRC m_hRC ; 			//OpenGL Rendering Context
	double m_dDocSize;
	BOOL jxglSetPixelFormat(HDC hDC);
	BOOL jxglCreateRC(HGLRC& hRC, HDC hDC);
	void jxglDestroyRC(HGLRC& hRC) ;
	void jxglSetupMatrix();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COglRubberBandView)
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
	virtual ~COglRubberBandView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COglRubberBandView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in oglRubberBandView.cpp
inline COglRubberBandDoc* COglRubberBandView::GetDocument()
   { return (COglRubberBandDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLRUBBERBANDVIEW_H__9642EBEB_B765_4832_8795_515A20F84C40__INCLUDED_)
