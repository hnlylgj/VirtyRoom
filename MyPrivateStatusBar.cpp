// MyPrivateStatusBar.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "MyPrivateStatusBar.h"


// CMyPrivateStatusBar

IMPLEMENT_DYNAMIC(CMyPrivateStatusBar, CMFCRibbonStatusBar/*CStatusBar*/)

CMyPrivateStatusBar::CMyPrivateStatusBar()
{

}

CMyPrivateStatusBar::~CMyPrivateStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMyPrivateStatusBar, CMFCRibbonStatusBar/*CStatusBar*/)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMyPrivateStatusBar 消息处理程序




BOOL CMyPrivateStatusBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 CBrush backBrush(RGB(49,680,100));
	 CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	 CRect rect;
	 pDC->GetClipBox(&rect);
	 pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	 pDC->SelectObject(pOldBrush);
	 this->ReleaseDC(pDC); 
     return TRUE;

	//return CMFCRibbonStatusBar/*CStatusBar*/::OnEraseBkgnd(pDC);
}
