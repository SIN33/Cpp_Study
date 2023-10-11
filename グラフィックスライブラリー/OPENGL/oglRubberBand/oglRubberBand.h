// oglRubberBand.h : main header file for the OGLRUBBERBAND application
//

#if !defined(AFX_OGLRUBBERBAND_H__F4C50B46_6702_45C0_8774_28A0C42986B2__INCLUDED_)
#define AFX_OGLRUBBERBAND_H__F4C50B46_6702_45C0_8774_28A0C42986B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandApp:
// See oglRubberBand.cpp for the implementation of this class
//

class COglRubberBandApp : public CWinApp
{
public:
	COglRubberBandApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COglRubberBandApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COglRubberBandApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLRUBBERBAND_H__F4C50B46_6702_45C0_8774_28A0C42986B2__INCLUDED_)
