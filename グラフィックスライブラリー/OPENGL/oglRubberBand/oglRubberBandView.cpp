// oglRubberBandView.cpp : implementation of the COglRubberBandView class
//

#include "stdafx.h"
#include "oglRubberBand.h"

#include "oglRubberBandDoc.h"
#include "oglRubberBandView.h"
#include "jxglTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView

IMPLEMENT_DYNCREATE(COglRubberBandView, CView)

BEGIN_MESSAGE_MAP(COglRubberBandView, CView)
//{{AFX_MSG_MAP(COglRubberBandView)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView construction/destruction

COglRubberBandView::COglRubberBandView()
{
	m_hRC = NULL;
	m_dDocSize = 100;
}

COglRubberBandView::~COglRubberBandView()
{
}

BOOL COglRubberBandView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN; 
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView drawing

void COglRubberBandView::OnDraw(CDC* pDC)
{
	COglRubberBandDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView printing

BOOL COglRubberBandView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COglRubberBandView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COglRubberBandView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


BOOL COglRubberBandView::jxglSetPixelFormat(HDC hDC)
{
	// define default desired video mode (pixel format)
	PIXELFORMATDESCRIPTOR pixelDesc;
	
	pixelDesc.nSize				= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion			= 1;
	pixelDesc.dwFlags	=		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;  
	pixelDesc.iPixelType		= PFD_TYPE_RGBA;
	pixelDesc.cColorBits		= 32;	// with transparency support
	//pixelDesc.cColorBits		= 24;	// without transparency support
	pixelDesc.cRedBits			= 8;
	pixelDesc.cRedShift			= 16;
	pixelDesc.cGreenBits		= 8;
	pixelDesc.cGreenShift		= 8;
	pixelDesc.cBlueBits			= 8;
	pixelDesc.cBlueShift		= 0;
	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits		= 64;	
	pixelDesc.cAccumRedBits		= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved			= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;
	
	int nPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	::DescribePixelFormat(hDC, nPixelIndex, pixelDesc.nSize, &pixelDesc);
	
	if (SetPixelFormat( hDC, nPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}
	
	return TRUE;
}


BOOL COglRubberBandView::jxglCreateRC(HGLRC& hRC, HDC hDC)
{
	if ( (hRC = wglCreateContext(hDC)) == NULL ||
		wglMakeCurrent(hDC, hRC) == FALSE)
	{
		return FALSE;
	}
	
	return TRUE;
}


void COglRubberBandView::jxglDestroyRC(HGLRC& hRC) 
{
	wglMakeCurrent(NULL, NULL) ; 
	if (hRC) 
	{
		wglDeleteContext(hRC) ;
		hRC = NULL ;
	}		
	
}

void COglRubberBandView::jxglSetupMatrix()
{
	CRect rect;
	GetClientRect(&rect);
	int nCx = rect.Width();
	int nCy = rect.Height();
	double fAspect = (double)nCy / (double)nCx;
	
	// setup orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(nCx >= nCy) {
		glOrtho(0, m_dDocSize, 0, m_dDocSize * fAspect, -m_dDocSize, m_dDocSize);
	}
	else {
		glOrtho(0, m_dDocSize / fAspect, 0, m_dDocSize, -m_dDocSize, m_dDocSize);
	} 
	glViewport(-1, -1, nCx + 2, nCy + 2);
}

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView diagnostics

#ifdef _DEBUG
void COglRubberBandView::AssertValid() const
{
	CView::AssertValid();
}

void COglRubberBandView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COglRubberBandDoc* COglRubberBandView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COglRubberBandDoc)));
	return (COglRubberBandDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COglRubberBandView message handlers

int COglRubberBandView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CPaintDC dc(this); // device context for painting
	if ( jxglSetPixelFormat(dc.m_hDC) == FALSE || 
		jxglCreateRC(m_hRC, dc.m_hDC) == FALSE )
	{
		return -1;
	}		
	return 0;
}

void COglRubberBandView::OnDestroy() 
{
	CPaintDC dc(this); // device context for painting
	wglMakeCurrent(dc.m_hDC, m_hRC);
	jxglDestroyRC(m_hRC);
	
	CView::OnDestroy();	
}

BOOL COglRubberBandView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

double GetRandomFloat(double a, double b)
{
	double f = (rand() % 10001 ) * 0.0001;
	return f * (b - a) + a;
}

void COglRubberBandView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	wglMakeCurrent(dc.m_hDC, m_hRC);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	jxglSetupMatrix();

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glRotated(45, 0, 0, 1);
    //double a[16] = {0};
    //glGetDoublev(GL_MODELVIEW_MATRIX, a);
	
	const int nLines = 100;  // let's draw quite a few lines

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	for(int i = 0; i < nLines; i++)
	{
		double f1 = GetRandomFloat(0, m_dDocSize);
		double f2 = GetRandomFloat(0, m_dDocSize);
		double f3 = GetRandomFloat(0, m_dDocSize);
		double f4 = GetRandomFloat(0, m_dDocSize);
		glVertex3d(f1, f2, 0);
		glVertex3d(f3, f4, 0);
	}
	glEnd();
	
	SwapBuffers(dc.m_hDC);

	// 11-18-2009 somehow Windows 7 needs this line of code, strange
    wglMakeCurrent(0, 0);
}

void COglRubberBandView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPaintDC dc(this); // device context for painting
	jxglTracker tracker;
	tracker.SetContext(dc.m_hDC, m_hRC);
	BOOL bSuccess = tracker.TrackRubberBand(this, point, TRUE);
	if(bSuccess)
	{
		CString strMsg;
		CRect rect = tracker.GetTrackRect();
		strMsg.Format("(left = %d, top = %d, right = %d, bottom = %d)",
						rect.left, rect.top, rect.right, rect.bottom);
		OutputDebugString(strMsg);
	}
	CView::OnLButtonDown(nFlags, point);
}


