// oglRubberBandDoc.cpp : implementation of the COglRubberBandDoc class
//

#include "stdafx.h"
#include "oglRubberBand.h"

#include "oglRubberBandDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandDoc

IMPLEMENT_DYNCREATE(COglRubberBandDoc, CDocument)

BEGIN_MESSAGE_MAP(COglRubberBandDoc, CDocument)
	//{{AFX_MSG_MAP(COglRubberBandDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandDoc construction/destruction

COglRubberBandDoc::COglRubberBandDoc()
{
	// TODO: add one-time construction code here

}

COglRubberBandDoc::~COglRubberBandDoc()
{
}

BOOL COglRubberBandDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COglRubberBandDoc serialization

void COglRubberBandDoc::Serialize(CArchive& ar)
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
// COglRubberBandDoc diagnostics

#ifdef _DEBUG
void COglRubberBandDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COglRubberBandDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandDoc commands
