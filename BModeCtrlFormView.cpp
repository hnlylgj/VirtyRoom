// BModeCtrlFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "BModeCtrlFormView.h"
#include "MainFrm.h"


//extern unsigned char m_CaptureImageBuffer[];
//extern LPBITMAPINFOHEADER  pInputBitMapInfo;
extern CMainFrame* gpMainFrame;

// CBModeCtrlFormView

IMPLEMENT_DYNCREATE(CBModeCtrlFormView, CFormView)

CBModeCtrlFormView::CBModeCtrlFormView(): CFormView(CBModeCtrlFormView::IDD)
{
	 //m_hDrawDIB = DrawDibOpen();
}

CBModeCtrlFormView::~CBModeCtrlFormView()
{
	//DrawDibClose(m_hDrawDIB);
}
/*
int CBModeCtrlFormView::Create()
{
	this->cre
	return 0;
}
*/
int CBModeCtrlFormView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
		int nResult = 0;
		CFrameWnd* pParentFrame = GetParentFrame();
		if( pParentFrame == pDesktopWnd )
		{
 		 // When this is docked
		 nResult= CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
 		}
		else
		{
 		// When this is not docked
 		 BOOL isMiniFrameWnd = pDesktopWnd->IsKindOf( RUNTIME_CLASS( CMiniFrameWnd ) );
		 BOOL isPaneFrameWnd = pDesktopWnd->IsKindOf( RUNTIME_CLASS( CPaneFrameWnd ) );
		 BOOL isMultiPaneFrameWnd = pDesktopWnd->IsKindOf( RUNTIME_CLASS( CMultiPaneFrameWnd ) );
 
		// pDesktopWnd is the frame window for CDockablePane
 		 nResult = CWnd::OnMouseActivate( pDesktopWnd, nHitTest, message );
 
		}
		return nResult;

}

void CBModeCtrlFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBModeCtrlFormView, CFormView)
	ON_BN_CLICKED(IDC_Test_BUTTON, &CBModeCtrlFormView::OnBnClickedTestButton)
	ON_BN_CLICKED(IDC_TestFormViewBUTTON, &CBModeCtrlFormView::OnBnClickedTestformviewbutton)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CBModeCtrlFormView 诊断

#ifdef _DEBUG
void CBModeCtrlFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBModeCtrlFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBModeCtrlFormView 消息处理程序


BOOL CBModeCtrlFormView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CBModeCtrlFormView::OnBnClickedTestButton()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("BModeCtrl:Hello World!"));
	CClientDC mClientDC(this->GetParent()->GetActiveWindow()); 
	mClientDC.SetTextColor(RGB(255,0,0)); 
	CString strTime; 
    strTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));  
	mClientDC.TextOut(700,300,strTime); 



}


void CBModeCtrlFormView::OnBnClickedTestformviewbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("BModeCtrl:Hello World!"));
	CClientDC mClientDC(this->GetParent()->GetActiveWindow()); 
	mClientDC.SetTextColor(RGB(255,0,0)); 
	CString strTime; 
    strTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));  
	mClientDC.TextOut(700,300,strTime); 

}


void CBModeCtrlFormView::OnPaint()
{
	CPaintDC dc(this); 
	// device context for painting
	// TODO: 
	// TODO: 在此处添加绘制代码
	CDC* pDC=&dc;
	
	if(pDC!=NULL)
	{

		gpMainFrame->pUnkSinkLiveRoomHelper->OnRender(this, pDC);
	
		/*
     RECT ViewDisplayRect;
	 GetClientRect(&ViewDisplayRect);
	 int w = pInputBitMapInfo->biWidth;
	 int h = pInputBitMapInfo->biHeight;
	 if(ViewDisplayRect.right==0||ViewDisplayRect.bottom==0)
	 {
		// 不绘图消息调用 
	   CFormView::OnPaint();
	 }
	 else
	 {
		  DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0, 0, -1, -1, 0);
	
	 }
	*/
	
	

	}
	else
	{
	   // 不绘图消息调用 
	   CFormView::OnPaint();
	}

	
}


void CBModeCtrlFormView::OnClose()
{
	// TODO: 


	CFormView::OnClose();
}
