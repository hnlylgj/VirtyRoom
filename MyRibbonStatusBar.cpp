// MyRibbonStatusBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "MyRibbonStatusBar.h"


// CMyRibbonStatusBar

IMPLEMENT_DYNAMIC(CMyRibbonStatusBar, CMFCStatusBar)

CMyRibbonStatusBar::CMyRibbonStatusBar()
{

}

CMyRibbonStatusBar::~CMyRibbonStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMyRibbonStatusBar, CMFCStatusBar)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMyRibbonStatusBar ��Ϣ�������




BOOL CMyRibbonStatusBar::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CBrush backBrush(RGB(255,0,0)); CBrush* pOldBrush = pDC->SelectObject(&backBrush);
    CRect rect;
    pDC->GetClipBox(&rect);
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);
    return TRUE;

	//return CMFCStatusBar::OnEraseBkgnd(pDC);
}
