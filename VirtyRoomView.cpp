

// UltrasoundBiopsyView.cpp : CVirtyRoomView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "VirtyRoom.h"
#endif
#include "MainFrm.h"
#include "VirtyRoomDoc.h"
#include "VirtyRoomView.h"
#include "UIDialog\WaitingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//extern unsigned char m_CaptureImageBuffer[];
//extern LPBITMAPINFOHEADER  pInputBitMapInfo;
extern CMainFrame* gpMainFrame;
// CVirtyRoomView

IMPLEMENT_DYNCREATE(CVirtyRoomView, CView)

BEGIN_MESSAGE_MAP(CVirtyRoomView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//ON_COMMAND_RANGE(ID_ShowPropertyWindow_32771, (UINT)ID_ShowLeftToolWindow_Menu,ID_ShowRibbonWindow_32776,ID_ShowOutputWindow_32773,ID_ShowStatusWindow_32789, &CVirtyRoomView::OnAppMainVieChange)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_ShowPropertyWindow_32771, ID_ShowLeftToolWindow_Menu,ID_ShowRibbonWindow_32776,ID_ShowOutputWindow_32773,ID_ShowStatusWindow_32789, &CVirtyRoomView::OnUpdateApplicationViewUI)

	ON_COMMAND(ID_ShowPropertyWindow_32771, &CVirtyRoomView::OnShowpropertywindow32771)
	ON_COMMAND(ID_ShowLeftToolWindow_Menu, &CVirtyRoomView::OnShowlefttoolwindowMenu)
	ON_COMMAND(ID_ShowRibbonWindow_32776, &CVirtyRoomView::OnShowribbonwindow32776)
	ON_COMMAND(ID_ShowOutputWindow_32773, &CVirtyRoomView::OnShowoutputwindow32773)
	ON_COMMAND(ID_ShowStatusWindow_32789, &CVirtyRoomView::OnShowstatuswindow32789)
	
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MininSystem_32792, &CVirtyRoomView::OnMininsystem32792)
	ON_COMMAND(ID_CloseMainApp_32779, &CVirtyRoomView::OnClosemainapp32779)
	ON_COMMAND(ID_ColseDevice_32795, &CVirtyRoomView::OnColsedevice32795)
	ON_COMMAND(ID_OpenDevice_32794, &CVirtyRoomView::OnOpendevice32794)
	ON_COMMAND(ID_StartImageing_32797, &CVirtyRoomView::OnStartimageing32797)
	ON_COMMAND(ID_ColseImaging_32798, &CVirtyRoomView::OnColseimaging32798)
	ON_COMMAND(ID_FreezeImaging_32799, &CVirtyRoomView::OnFreezeimaging32799)
	ON_COMMAND(ID_SaveImaging_32800, &CVirtyRoomView::OnSaveimaging32800)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_AutoHideRibbon_32834, &CVirtyRoomView::OnAutohideribbon32834)
	ON_UPDATE_COMMAND_UI(ID_ShowRibbonWindow_32776, &CVirtyRoomView::OnUpdateShowribbonwindow32776)
	ON_UPDATE_COMMAND_UI(ID_AutoHideRibbon_32834, &CVirtyRoomView::OnUpdateAutohideribbon32834)
	ON_UPDATE_COMMAND_UI(ID_ShowStatusWindow_32789, &CVirtyRoomView::OnUpdateShowstatuswindow32789)
	ON_UPDATE_COMMAND_UI(ID_ShowOutputWindow_32773, &CVirtyRoomView::OnUpdateShowoutputwindow32773)
	ON_UPDATE_COMMAND_UI(ID_ShowPropertyWindow_32771, &CVirtyRoomView::OnUpdateShowpropertywindow32771)
	ON_UPDATE_COMMAND_UI(ID_ShowLeftToolWindow_Menu, &CVirtyRoomView::OnUpdateShowlefttoolwindowMenu)
	ON_UPDATE_COMMAND_UI(ID_OpenDevice_32794, &CVirtyRoomView::OnUpdateOpendevice32794)
	ON_UPDATE_COMMAND_UI(ID_ColseDevice_32795, &CVirtyRoomView::OnUpdateColsedevice32795)
	ON_UPDATE_COMMAND_UI(ID_ColseImaging_32798, &CVirtyRoomView::OnUpdateColseimaging32798)
	ON_UPDATE_COMMAND_UI(ID_FreezeImaging_32799, &CVirtyRoomView::OnUpdateFreezeimaging32799)
	ON_UPDATE_COMMAND_UI(ID_SaveImaging_32800, &CVirtyRoomView::OnUpdateSaveimaging32800)
	ON_UPDATE_COMMAND_UI(ID_StartImageing_32797, &CVirtyRoomView::OnUpdateStartimageing32797)
	ON_BN_CLICKED(IDC_Test_BUTTON, &CVirtyRoomView::OnBnClickedTestButton)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_localScreenShare, &CVirtyRoomView::OnButtonlocalscreenshare)
	ON_COMMAND(ID_BUTTON_ChangeScreen, &CVirtyRoomView::OnButtonChangescreen)
	ON_COMMAND(ID_BUTTON_FullScreenShare, &CVirtyRoomView::OnButtonFullscreenshare)
	ON_COMMAND(ID_BUTTON1_CloseScreenShare, &CVirtyRoomView::OnButton1Closescreenshare)
	ON_COMMAND(ID_BUTTON_CreateVirtyRoom, &CVirtyRoomView::OnButtonCreatevirtyroom)
	ON_COMMAND(ID_BUTTON_CloseVirtyRoom, &CVirtyRoomView::OnButtonClosevirtyroom)
	ON_COMMAND(ID_BUTTON_SlaverJoinByteRoom, &CVirtyRoomView::OnButtonSlaverjoinbyteroom)
	ON_COMMAND(ID_BUTTON_SlaverQuitByteRoom, &CVirtyRoomView::OnButtonSlaverquitbyteroom)
	ON_COMMAND(ID_BUTTON_SlaverJoinMis3, &CVirtyRoomView::OnButtonSlaverjoinmis3)
	ON_COMMAND(ID_BUTTON_SlaverQuitMIS3, &CVirtyRoomView::OnButtonSlaverquitmis3)
END_MESSAGE_MAP()

// CVirtyRoomView 构造/析构

CVirtyRoomView::CVirtyRoomView()
{
	// TODO: 在此处添加构造代码
	 m_ViewBackgroundColor=RGB(49,69,100);//象牙黑41,36,33
	 DetectMouseMoveID=0;
	 AutohideribbonID=FALSE;
	 pOutSTR= _T("★师说数字课堂★");
	 m_hDrawDIB = DrawDibOpen();
	 mFontCout=300;
	 DetectMouseMoveID=1;
	 isScreenStatus=false;
}

CVirtyRoomView::~CVirtyRoomView()
{

	DrawDibClose(m_hDrawDIB);
}

BOOL CVirtyRoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(m_ViewBackgroundColor),0);//这里默认为白色画刷 WHITE_BRUSH ,现在修改为m_ViewBackgroundColor
	return CView::PreCreateWindow(cs);
}
int CVirtyRoomView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  
	m_MemBitmap.init(this);

	CFont  NewOutTextFont;//文本的字体对象       
	CFont  *pOldFont;   //保存以前的字体指针 
	
	CDC*  pDC = GetDC();
	NewOutTextFont.CreatePointFont(mFontCout, _T("宋体"));
	pOldFont = pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	mUserNameSize = pDC->GetTextExtent((CString)pOutSTR);//获得字符串长度

	return 0;
}
// CVirtyRoomView 绘制

void CVirtyRoomView::OnDraw(CDC* pDC)
{
	CVirtyRoomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 
	if (pDC == NULL)return;

	
	// TODO: 在此处添加绘制代码
	//RECT ViewDisplayRect;
	//GetClientRect(&ViewDisplayRect);
	//int w = pInputBitMapInfo->biWidth;
	//int h = pInputBitMapInfo->biHeight;

	 //DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0, 0, -1, -1, 0);
	 //DrawDibDraw(m_hDrawDIB,pDC->GetSafeHdc(),ViewDisplayRect.left,ViewDisplayRect.top,	ViewDisplayRect.right,	ViewDisplayRect.bottom,(LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40],0,0, -1,-1,0);
    
	 //DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, w, h, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0, 0, w, h, 0);
	 // DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, w, h, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0,0, w,h,0);//DDF_SAME_DRAW|DDF_SAME_HDC
	 //pDC->TextOutA(500,50,"牛顿运动三定律");
	
	OnDrawText(pOutSTR,300,pDC);


	if(isScreenStatus)
	{
		if(gpMainFrame->isLiveFlag==100)
	    {
			OnButtonChangescreen();
		}
       
	}


}

void CVirtyRoomView::OnDrawText(LPCTSTR pOutSTR,int mFontCout,CDC* pDC)
{
	CRect  ViewDisplayRect;
	GetClientRect(&ViewDisplayRect);
	CFont m_Font;
	m_Font.CreatePointFont(300, _T("宋体"), NULL);
	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(RGB(255,0, 0));
	//pDC->SetBkColor(RGB(191,219,255));//背景颜色设置  
	pDC->SetBkMode(TRANSPARENT);//背景透明色

	CSize mOutSTRSize;
	mOutSTRSize =pDC->GetTextExtent((LPCTSTR)pOutSTR);//获得字符串宽度长度||CString
	LONG mOutTextPointX;
	LONG OutTextPointX;
	mOutTextPointX = ViewDisplayRect.Width();
	OutTextPointX = (mOutTextPointX - mOutSTRSize.cx) / 2;
	pDC->TextOut(OutTextPointX,20,pOutSTR);//居中输出文字


	CPen *pOldPen,newPen,newPen2;
	newPen.CreatePen(PS_SOLID,2,RGB(0,255,255));
	pOldPen = pDC->SelectObject(&newPen);

	pDC->MoveTo(OutTextPointX,mOutSTRSize.cy+22);
	pDC->LineTo(OutTextPointX+mOutSTRSize.cx,mOutSTRSize.cy+22);//宽度画直线|ViewDisplayRect.Width()


	pDC->MoveTo(0, 0);
	pDC->LineTo(OutTextPointX, mOutSTRSize.cy + 22);//画边角直线|ViewDisplayRect.Width()

	pDC->MoveTo(OutTextPointX + mOutSTRSize.cx, mOutSTRSize.cy + 22);
	pDC->LineTo(ViewDisplayRect.Width(), 0);//画边角直线|
	pDC->SelectObject(pOldPen);
	



	 // CRect cr;//矩形结构
     // GetClientRect(&cr);//获得客户区窗口 


	 //绘制椭圆
     ///int cx=ViewDisplayRect.right;//右
     ///int cy=ViewDisplayRect.bottom;//底 
    /// pDC->SetMapMode(MM_ISOTROPIC);//X=Y   
     ///pDC->SetWindowExt(1000,1000);//设置逻辑窗口，默认窗口原点为（0，0）
     ///pDC->SetViewportExt(cx,-cy);//定义输出视口,X右Y上为正
	 ///pDC->SetViewportOrg(cx/2,cy/2);//定义视口原点为客户区中心
     ///pDC->Ellipse(-200,200,200,-200);//绘制椭圆与客户区外切的椭圆
     
	 ;;
	////绘制椭圆四条半径
	 ///newPen2.CreatePen(PS_SOLID,4,RGB(15,10,255));
	 ///pOldPen = pDC->SelectObject(&newPen2);
     ///pDC->MoveTo(0,0);pDC->LineTo(200,0);
     ///pDC->MoveTo(0,0);pDC->LineTo(-200,0);
     ///pDC->MoveTo(0,0);pDC->LineTo(0,200);
     ///pDC->MoveTo(0,0);pDC->LineTo(0,-200);
	 ///pDC->SelectObject(pOldPen);
	 



	/*
	CDC     mDC;
	CRect   mRect;	
	
	this->GetClientRect(&mRect);
	LONG mOutTextPointX,mOutTextPointY;
	//mOutTextPointX=(int)(mRect.Width()/2);
	mOutTextPointX = mRect.Width();
	mOutTextPointY=10;
	//StartY--;

	m_MemBitmap.Clear(mRect.left, mRect.top, mRect.right, mRect.bottom, RGB(49,69,100)); //标准黑:00, 00, 00，冷灰128,138,135--象牙黑41,36,33-棕黑色的RGB值94 38 18--69, 33,21

	LONG OutTextPosionX, OutTextPosionY, mDistanceValue;
	OutTextPosionX = (mOutTextPointX - mUserNameSize.cx) / 2;
	mDistanceValue = 0;
	OutTextPosionY = mOutTextPointY + mDistanceValue;
	m_MemBitmap.TextOut((int)OutTextPosionX, (int)OutTextPosionY, mFontCout, pOutSTR, RGB(0, 250, 0)); //1

																															 
	//mDC.CreateCompatibleDC(pDC);
	//mDC.SelectObject(&m_MemBitmap);  //内存设备环境将位图对象选入 
	//pDC->BitBlt(0, 0, mRect.Width(), mRect.Height(), &mDC, 0, 0, SRCCOPY); //用位传输函数显示出来
	//mDC.DeleteDC();
	//*/
	//ReleaseDC(pDC); //释放设备对象



}


void CVirtyRoomView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(DetectMouseMoveID==1)
	{
		CString PointInforStr;
		CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
		CClientDC dc(this);
		CMFCRibbonBaseElement * pElement;  
        pElement = pMainFrame->m_wndStatusBar.FindElement(ID_STATUSBAR_PANE4); 
		//获取该点像素值
		COLORREF color=dc.GetPixel(point);
		BYTE R,G,B,temp;
		PointInforStr.Format(_T("(x=%i,y=%i) (R=%i G=%i B=%i)"),point.x, point.y,GetRValue(color),GetGValue(color),GetBValue(color));
		//在状态栏中显示像素值
		pElement->SetText(PointInforStr);  
		pElement->Redraw(); 

		CDC*  pDC = GetDC();
		pDC->SetPixel(point,RGB(255,0,0));
		ReleaseDC(pDC); //释放设备对象

		if(AutohideribbonID)
		{
				if(pMainFrame->m_wndRibbonBar.IsVisible()==FALSE)
				{
					if(point.y<=8)
					pMainFrame->m_wndRibbonBar.ShowWindow(SW_SHOW); 
	  				pMainFrame->RecalcLayout(FALSE);
				}
				else
				{
					if(point.y>30)
					pMainFrame->m_wndRibbonBar.ShowWindow(SW_HIDE); 
	  				pMainFrame->RecalcLayout(FALSE);

			   }
		}






		
	}
	CView::OnMouseMove(nFlags, point);
}

void CVirtyRoomView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVirtyRoomView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CVirtyRoomView 诊断

#ifdef _DEBUG
void CVirtyRoomView::AssertValid() const
{
	CView::AssertValid();
}

void CVirtyRoomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVirtyRoomDoc* CVirtyRoomView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVirtyRoomDoc)));
	return (CVirtyRoomDoc*)m_pDocument;
}
#endif //_DEBUG

// CVirtyRoomView 消息处理程序


void CVirtyRoomView::OnShowpropertywindow32771()
{
	// TODO: 在此添加命令处理程序代码
	//CMainFrame* pFrame = (CMainFrame*)(AfxGetApp->m_pMainWnd); 
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndProperties.ShowWindow(pMainFrame->m_wndProperties.IsVisible() ? SW_HIDE : SW_SHOW);
	pMainFrame->m_wndProperties.ShowPane(!(pMainFrame->m_wndProperties.IsVisible()), FALSE, TRUE);
	//pMainFrame->m_wndProperties.UpdateWindow();  
	//pMainFrame->RecalcLayout(FALSE);
}

void CVirtyRoomView::OnShowlefttoolwindowMenu()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pMainFrame->m_wndFileView.ShowPane(!(pMainFrame->m_wndFileView.IsVisible()), FALSE, TRUE);
	pMainFrame->m_wndClassView.ShowPane(!(pMainFrame->m_wndClassView.IsVisible()), FALSE, TRUE);
	pMainFrame->pMModeAdustCtrlBox->ShowPane(!(pMainFrame->pMModeAdustCtrlBox->IsVisible()), FALSE, TRUE);
	pMainFrame->mBModeAdustCtrlBox.ShowPane(!(pMainFrame->mBModeAdustCtrlBox.IsVisible()), FALSE, TRUE);
	//CDockablePane* pTabbedBar = NULL;
	//pMainFrame->m_wndClassView.AttachToTabWnd(&(pMainFrame->m_wndFileView), DM_SHOW, TRUE, &pTabbedBar);
	//pTabbedBar->ShowWindow(1); 
	//pMainFrame->m_wndFileView.ShowWindow(pMainFrame->m_wndFileView.IsVisible() ? SW_HIDE : SW_SHOW);
	//pMainFrame->m_wndClassView.ShowWindow(pMainFrame->m_wndClassView.IsVisible() ? SW_HIDE : SW_SHOW);
	//pMainFrame->RecalcLayout(FALSE);
}

void CVirtyRoomView::OnShowribbonwindow32776()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndRibbonBar.ShowWindow(pMainFrame->m_wndRibbonBar.IsVisible() ? SW_HIDE : SW_SHOW);
	//pMainFrame->RecalcLayout(FALSE);
	pMainFrame->m_wndRibbonBar.ShowPane(!(pMainFrame->m_wndRibbonBar.IsVisible()), FALSE, TRUE);

}

void CVirtyRoomView::OnShowoutputwindow32773()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndOutput.ShowWindow(pMainFrame->m_wndOutput.IsVisible() ? SW_HIDE : SW_SHOW);
	//pMainFrame->RecalcLayout(FALSE);
	pMainFrame->m_wndOutput.ShowPane(!(pMainFrame->m_wndOutput.IsVisible()), FALSE, TRUE);
	
}

/*
void CVirtyRoomView::OnShowapptitlewindow32778()
{
	// TODO: 在此添加命令处理程序代码m_MainButton
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pMainFrame->m_MainButton.SetVisible(pMainFrame->m_MainButton.IsVisible() ? SW_HIDE : SW_SHOW);
	pMainFrame->RecalcLayout(FALSE);
}
*/

void CVirtyRoomView::OnShowstatuswindow32789()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndStatusBar.ShowWindow(pMainFrame->m_wndStatusBar.IsVisible() ? SW_HIDE : SW_SHOW);
	//pMainFrame->RecalcLayout(FALSE);
	pMainFrame->m_wndStatusBar.ShowPane(!(pMainFrame->m_wndStatusBar.IsVisible()), FALSE, TRUE);
}

BOOL CVirtyRoomView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect mClientRect;   
	GetClientRect(&mClientRect);   
	CBrush  mBrush;   
	mBrush.CreateSolidBrush(m_ViewBackgroundColor);   
	pDC->FillRect(&mClientRect,&mBrush);  
	return CView::OnEraseBkgnd(pDC);
}

void CVirtyRoomView::OnMininsystem32792()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);//窗口中发送最小化消息

}

void CVirtyRoomView::OnClosemainapp32779()
{
	// TODO: 在此添加命令处理程序代码
	if(AfxMessageBox(_T("是否真的要退出当前系统？"),MB_YESNO)==IDYES)
      AfxGetMainWnd()->SendMessage(WM_CLOSE);

}

void CVirtyRoomView::OnOpendevice32794()
{
	// TODO: 在此添加命令处理程序代码
	if(theApp.mPUSGFW2ForMX==NULL)
	{
		
		WaitingDlg* pWaitingDlg=new WaitingDlg(this);
		pWaitingDlg->Create(WaitingDlg::IDD,this);
		pWaitingDlg->mWaitingTextString="正在打开设备，请稍等..."; 
		pWaitingDlg->ShowWindow(SW_SHOW);
		pWaitingDlg->UpdateWindow();
	    pWaitingDlg->UpdateData(0);
		/*
		CProgressCtrl*   pProcessProgress=new CProgressCtrl();
		CRect mProgressRect;
		mProgressRect.SetRect(700,500,50,20);
		pProcessProgress->Create(WS_CHILD | WS_VISIBLE,mProgressRect,this->GetActiveWindow(),1089); 
		pProcessProgress->SetRange(0,10);
		pProcessProgress->SetWindowPos(NULL,mProgressRect.left,mProgressRect.top,mProgressRect.Width(),mProgressRect.Height(),SWP_NOZORDER);   
		pProcessProgress->ShowWindow(SW_SHOW);
		pProcessProgress->UpdateWindow();
	    pProcessProgress->SetPos(1); 
		Sleep(200);
		  pProcessProgress->SetPos(2); 
		Sleep(200);
		 pProcessProgress->SetPos(3); 
		 Sleep(200);
		 pProcessProgress->SetPos(4); 
			Sleep(200);
		 pProcessProgress->SetPos(10); 
		 pProcessProgress->DestroyWindow();
		 delete pProcessProgress;
		 */
		/*
		CRect mProgressRect;
	    CMFCRibbonBaseElement * pElement;  
		CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
     	pElement = pMainFrame->m_wndStatusBar.FindElement(ID_STATUSBAR_PANE6); 
	    mProgressRect=pElement->GetRect(); 
	    pMainFrame->m_Progress.SetWindowPos(NULL,mProgressRect.left,mProgressRect.top,mProgressRect.Width(),mProgressRect.Height(),SWP_NOZORDER);     
	    pMainFrame->m_Progress.StepIt(); 
	    pElement->Redraw(); 

		 pMainFrame->m_Progress.StepIt(); 
	    pElement->Redraw(); 

		 pMainFrame->m_Progress.StepIt(); 
	     pElement->Redraw(); 
		 */
		AfxGetMainWnd()->SendMessage(WM_MYMSG, 10,0);//窗口中发送最小化消息
		// Sleep(1000);
		// AfxGetMainWnd()->SendMessage(WM_MYMSG, 20,0);//窗口中发送消息
		//  Sleep(1000);
		// AfxGetMainWnd()->SendMessage(WM_MYMSG, 30,0);//窗口中发送消息

		theApp.mPUSGFW2ForMX=new CUSGFW2ForMX;
	    if(theApp.mPUSGFW2ForMX->ConnectToDevice())
		{
		  //GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(L"Connect to Beamformer Success!");
          //pTestResultBoxOne->SetWindowText(L"Connect to Beamformer Success!/r/n");
			/*
          CString ResultStr;
		  mCurrentTimer=CTime::GetCurrentTime();
		  int h = mCurrentTimer.GetHour();
		  int m = mCurrentTimer.GetMinute();
		  int s = mCurrentTimer.GetSecond();
          ResultStr.Format(L"%d:%d:%d Connect to Beamformer Success",h,m,s);
		  ResultStr=ResultStr+L"\r\n";
		  ReturnResultstr= ReturnResultstr+ResultStr;
		  pTestResultBoxOne->SetWindowText(ReturnResultstr);
		  
		  //EnableDisableUserInterfaceControls(1);
		  mConnectDeviceBtn.EnableWindow(0);
	      mDisconnectDeviceBtn.EnableWindow(1);
	      mStartGeneratorBtn.EnableWindow(1);
	      mGetProbsBtn.EnableWindow(1);
		  */

        }
	    else 
		{
            
			//GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(L"Connect to Beamformer Failse！");
			 //pTestResultBoxOne->SetWindowText(L"Connect to Beamformer Failse!/r/n");
			/*
			 CString ResultStr;
		     mCurrentTimer=CTime::GetCurrentTime();
		     int h = mCurrentTimer.GetHour();
		     int m = mCurrentTimer.GetMinute();
		     int s = mCurrentTimer.GetSecond();
             ResultStr.Format(L"%d:%d:%d Connect to Beamformer Failse!",h,m,s);
		     ResultStr=ResultStr+L"\r\n";
			 pTestResultBoxOne->GetWindowText(ReturnResultstr); 
		     ReturnResultstr= ReturnResultstr+ResultStr;
		     pTestResultBoxOne->SetWindowText(ReturnResultstr);
			 */
		}
	    
		 Sleep(1000);
		 AfxGetMainWnd()->SendMessage(WM_MYMSG, 40,0);//窗口中发送消息
		 Sleep(1000);
		 AfxGetMainWnd()->SendMessage(WM_MYMSG, 60,0);//窗口中发送消息
		 //Sleep(2000);
		 //AfxGetMainWnd()->SendMessage(WM_MYMSG, 80,0);//窗口中发送消息
		  Sleep(800);
		 AfxGetMainWnd()->SendMessage(WM_MYMSG, 100,0);//窗口中发送消息
		 Sleep(200);
		 AfxGetMainWnd()->SendMessage(WM_MYMSG, 0,0);//窗口中发送消息

		pWaitingDlg->DestroyWindow(); //CANCEL Wait SCREEN;
		delete pWaitingDlg;



	}
		
	
}

void CVirtyRoomView::OnColsedevice32795()
{
	// TODO: 在此添加命令处理程序代码
	theApp.mPUSGFW2ForMX->DisconnectToDevice(); 
	delete theApp.mPUSGFW2ForMX; 
	theApp.mPUSGFW2ForMX=NULL;
	Invalidate();//重绘窗口命令！
	/*
	//Invalidate();//重绘窗口命令！
	//GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(L"Disconnect to Beamformer Success！");
	//pTestResultBoxOne->SetWindowText(L"Disconnect to Beamformer Success!/r/n");
	CString ResultStr;
	mCurrentTimer=CTime::GetCurrentTime();
	int h = mCurrentTimer.GetHour();
	int m = mCurrentTimer.GetMinute();
	int s = mCurrentTimer.GetSecond();
    ResultStr.Format(L"%d:%d:%d Disconnect to Beamformer Success",h,m,s);
	ResultStr=ResultStr+L"\r\n";
	pTestResultBoxOne->GetWindowText(ReturnResultstr); 
	ReturnResultstr= ReturnResultstr+ResultStr;
	pTestResultBoxOne->SetWindowText(ReturnResultstr);
	EnableDisableUserInterfaceControls(0);
	mConnectDeviceBtn.EnableWindow(1);
	*/
}

void CVirtyRoomView::OnStartimageing32797()
{
	// TODO: 在此添加命令处理程序代码
	CString ReturnResultstr;
	if(theApp.mPUSGFW2ForMX->USGDeviceStatus!=1)
	{
       //GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(L"Device may not be Connected！");
		//----
		//----
	   return;
	}
	theApp.mPUSGFW2ForMX->LogicScanModeID=(SCAN_MODE)1;//mModeSelectCombox.GetCurSel()--B Mode ;
	///*
	LONG nFullWidth=(LONG)GetSystemMetrics(SM_CXSCREEN);     
    LONG nFullHeight=(LONG)GetSystemMetrics(SM_CYSCREEN);  
	LONG mUSGViewWidth=512;//683;//512;//914;
	LONG mUSGViewHeight=512;//512;//588;//521
	CRect ScreeRect;
	GetWindowRect(&ScreeRect);
	//CRect mClientRect;
    //GetClientRect(mClientRect);
	//LONG mWidth=(LONG)mClientRect.Width();
	//LONG mHight=(LONG)mClientRect.Height();
	tagRECT mOutputRectangle ;
    mOutputRectangle.left=(nFullWidth-mUSGViewWidth-ScreeRect.left-10)/2;
	mOutputRectangle.top=(nFullHeight-mUSGViewHeight-ScreeRect.top-10)/2;
	mOutputRectangle.right=mOutputRectangle.left+mUSGViewWidth;
	mOutputRectangle.bottom=mOutputRectangle.top+mUSGViewHeight; 
	theApp.mPUSGFW2ForMX->pRECT=&mOutputRectangle;
	
	//------------------------------------------
	WaitingDlg* pWaitingDlg=new WaitingDlg(this);
	pWaitingDlg->Create(WaitingDlg::IDD,this);
	pWaitingDlg->mWaitingTextString="正在生成图像，请稍等..."; 
	pWaitingDlg->ShowWindow(SW_SHOW);
	pWaitingDlg->UpdateWindow();
	pWaitingDlg->UpdateData(0);
	if(theApp.mPUSGFW2ForMX->StartUSGGenerator(this->GetSafeHwnd()))
	{
		/*
		//ReturnResultstr.Format(L"%d [Start B_Mode Scaning Generator Success！]",mPUSGFW2ForMX->ReturnResultValue);
		//GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(ReturnResultstr);
		CString ResultStr;
		mCurrentTimer=CTime::GetCurrentTime();
		int h = mCurrentTimer.GetHour();
		int m = mCurrentTimer.GetMinute();
		int s = mCurrentTimer.GetSecond();
        ResultStr.Format(L"%d:%d:%d %d[Start B_Mode Generator Success]",h,m,s,mPUSGFW2ForMX->ReturnResultValue);
		ResultStr=ResultStr+L"\r\n";
		pTestResultBoxOne->GetWindowText(ReturnResultstr); 
		ReturnResultstr= ReturnResultstr+ResultStr;
		pTestResultBoxOne->SetWindowText(ReturnResultstr);
		InitializeUserInterfaceControls();
	    EnableDisableUserInterfaceControls(1);
		mConnectDeviceBtn.EnableWindow(0);
		mStartGeneratorBtn.EnableWindow(0);
	    mSaveFileBtn.EnableWindow(0);
	    mRunViewBtn.EnableWindow(0);
		//-----------------------------------------------
		ImageEnhancementUpdateGUI();
	    ClearViewUpdateGUI();
	    FocusUpdateGUI();
		//------------------------------------------------
		*/
		theApp.mPUSGFW2ForMX->pDrawImage->UpdateAlphaBitmap();  
		DetectMouseMoveID=1;
		//pAutoAdjustment=new AutoAdjustment();
		//pAutoAdjustment->pUSGFW2ForMX=theApp.mPUSGFW2ForMX; 
		

	}
	else
	{
		//-------------------------------------------------
		theApp.mPUSGFW2ForMX->CloseUSGGenerator(); 
		/*
		//ReturnResultstr.Format(L"%d [Start B_Mode Scaning Generator False！]",mPUSGFW2ForMX->ReturnResultValue);
		//GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(ReturnResultstr);
		CString ResultStr;
		mCurrentTimer=CTime::GetCurrentTime();
		int h = mCurrentTimer.GetHour();
		int m = mCurrentTimer.GetMinute();
		int s = mCurrentTimer.GetSecond();
        ResultStr.Format(L"%d:%d:%d %d[Start B_Mode Generator False]",h,m,s,mPUSGFW2ForMX->ReturnResultValue);
		ResultStr=ResultStr+L"\r\n";
		pTestResultBoxOne->GetWindowText(ReturnResultstr); 
		ReturnResultstr= ReturnResultstr+ResultStr;
		pTestResultBoxOne->SetWindowText(ReturnResultstr);
		*/
			
	}
	pWaitingDlg->DestroyWindow(); 
	delete pWaitingDlg;
	return;
}

void CVirtyRoomView::OnColseimaging32798()
{
	// TODO: 在此添加命令处理程序代码
	theApp.mPUSGFW2ForMX->CloseUSGGenerator(); 
	Invalidate();//重绘窗口命令！
}

void CVirtyRoomView::OnFreezeimaging32799()
{
	// TODO: 在此添加命令处理程序代码
	theApp.mPUSGFW2ForMX->FreezeImage(); 
	/*
	//GetDlgItem(IDC_Return_Result_EDIT)->SetWindowText(L"Freeze Scaning Image Success！");
	CString ResultStr;
	mCurrentTimer=CTime::GetCurrentTime();
	int h = mCurrentTimer.GetHour();
	int m = mCurrentTimer.GetMinute();
	int s = mCurrentTimer.GetSecond();
    ResultStr.Format(L"%d:%d:%d Freeze Scaning Image Success",h,m,s);
	ResultStr=ResultStr+L"\r\n";
	pTestResultBoxOne->GetWindowText(ReturnResultstr); 
	ReturnResultstr= ReturnResultstr+ResultStr;
	pTestResultBoxOne->SetWindowText(ReturnResultstr);
	EnableDisableUserInterfaceControls(0);
	mRunViewBtn.EnableWindow(1);
	mConnectDeviceBtn.EnableWindow(0);
	mDisconnectDeviceBtn.EnableWindow(1);
	mStartGeneratorBtn.EnableWindow(0);
	mCloseGeneratorBtn.EnableWindow(1);
	mSaveFileBtn.EnableWindow(1);

	mEnableEnhanceCheck.EnableWindow(1);;
	mEnableSpeckleCheck.EnableWindow(1);;
	//mScaningDirectionCheck.EnableWindow(1);
	mViewRotateSlider.EnableWindow(1);
	mViewRotateCombox.EnableWindow(1);
	mRejectionCombox.EnableWindow(1);
	mRejectionSlider.EnableWindow(1);
	mNegativeCheck.EnableWindow(1);
	mDefaultPaletteBtn.EnableWindow(1);
	mGammaSetSlider.EnableWindow(1);;
	mBrightnessSetSlider.EnableWindow(1);;
	mContrastSetSlider.EnableWindow(1);;

	ImageEnhancementUpdateGUI();
	ClearViewUpdateGUI();
	FocusUpdateGUI();
	*/
}

void CVirtyRoomView::OnSaveimaging32800()
{
	// TODO: 在此添加命令处理程序代码
       CFileDialog dlg(FALSE,_T("bmp"),NULL,OFN_OVERWRITEPROMPT,_T("Bitmap Files (*.bmp)|*.bmp|"));
		if (dlg.DoModal() == IDOK)
		{
			CString mFileNameURL;
			mFileNameURL = dlg.GetPathName();
			LPTSTR FileNamestr = mFileNameURL.GetBuffer();
		    theApp.mPUSGFW2ForMX->SaveImageToFile(FileNamestr); 
			mFileNameURL.ReleaseBuffer();
			
		}
	
}


void CVirtyRoomView::OnAutohideribbon32834()
{
	// TODO: 在此添加命令处理程序代码
	//return;
	AutohideribbonID=!AutohideribbonID;
	//if(AutohideribbonID
	//CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndRibbonBar.ShowWindow(AutohideribbonID==TRUE ? SW_HIDE : SW_SHOW);
	//pMainFrame->RecalcLayout(FALSE);
}

void CVirtyRoomView::OnApplicationView(UINT id)
{
		

	switch (id)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
	
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
	
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
	
		break;

	
	}

	
}


void CVirtyRoomView::OnUpdateApplicationViewUI(CCmdUI* pCmdUI)
{
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pMainFrame->m_wndRibbonBar.ShowWindow(pMainFrame->m_wndRibbonBar.IsVisible() ? SW_HIDE : SW_SHOW);
	
	switch(pCmdUI->m_nID)
	{
	case ID_ShowRibbonWindow_32776:
		pCmdUI->SetCheck(pMainFrame->m_wndRibbonBar.IsVisible() ? 1 : 0); 
		break;
	case ID_ShowStatusWindow_32789:
		pCmdUI->SetCheck(pMainFrame->m_wndStatusBar.IsVisible() ? 1 : 0); 
		break;
    case ID_AutoHideRibbon_32834:
		pCmdUI->SetCheck(AutohideribbonID==TRUE? 1 : 0); 
		break;

	}

	//pCmdUI->SetCheck( == pCmdUI->m_nID);
}

void CVirtyRoomView::OnUpdateShowribbonwindow32776(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pCmdUI->SetCheck(pMainFrame->m_wndRibbonBar.IsVisible() ? 1 : 0); 
	//---test---
	CClientDC mClientDC(this); 
	mClientDC.SetTextColor(RGB(33,45,120)); 
	CString strTime; 
    strTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));  
	mClientDC.TextOut(200,300,strTime); 

}


void CVirtyRoomView::OnUpdateAutohideribbon32834(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pCmdUI->SetCheck(AutohideribbonID==TRUE? 1 : 0); 

}


void CVirtyRoomView::OnUpdateShowstatuswindow32789(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pCmdUI->SetCheck(pMainFrame->m_wndStatusBar.IsVisible() ? 1 : 0); 
}


void CVirtyRoomView::OnUpdateShowoutputwindow32773(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pCmdUI->SetCheck(pMainFrame->m_wndOutput.IsVisible() ? 1 : 0); 
}


void CVirtyRoomView::OnUpdateShowpropertywindow32771(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pCmdUI->SetCheck(pMainFrame->m_wndProperties.IsVisible() ? 1 : 0); 
}


void CVirtyRoomView::OnUpdateShowlefttoolwindowMenu(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//CMainFrame* pMainFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pCmdUI->SetCheck(pMainFrame->m_wndRibbonBar.IsVisible() ? 1 : 0); 
}


void CVirtyRoomView::OnUpdateOpendevice32794(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	 // if(theApp.mPUSGFW2ForMX->ConnectToDevice())
	if(theApp.mPUSGFW2ForMX!=NULL)
	 pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->USGDeviceStatus==1 ? 0 : 1); 	

}


void CVirtyRoomView::OnUpdateColsedevice32795(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(theApp.mPUSGFW2ForMX!=NULL)
	 pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->USGDeviceStatus==1 ? 1: 0); 	

}


void CVirtyRoomView::OnUpdateStartimageing32797(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(theApp.mPUSGFW2ForMX!=NULL)
	 pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->USGDeviceStatus==1 ? 1: 0); 
	
}


void CVirtyRoomView::OnUpdateColseimaging32798(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码=131
	if(theApp.mPUSGFW2ForMX!=NULL)
	pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->ReturnResultValue==0 ? 1: 0);

}


void CVirtyRoomView::OnUpdateFreezeimaging32799(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(theApp.mPUSGFW2ForMX!=NULL)
    pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->ReturnResultValue==1 ? 1: 0);


}


void CVirtyRoomView::OnUpdateSaveimaging32800(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(theApp.mPUSGFW2ForMX!=NULL)
	pCmdUI->SetCheck(theApp.mPUSGFW2ForMX->USGFreezeStatus==TRUE ? 1: 0);


}


void CVirtyRoomView::OnAppMainVieChange(UINT nID)
{
}


void CVirtyRoomView::OnUpdateAppMainViewUI(CCmdUI* pCmdUI)
{
}


void CVirtyRoomView::OnBnClickedTestButton()
{
	// TODO: 在此添加控件通知处理程序代码
    MessageBox(_T("Hello World!"));

}





void CVirtyRoomView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:
	/*
	RECT ViewDisplayRect;
	GetClientRect(&ViewDisplayRect);
	CPoint S,E;
	S.SetPoint(0,0);
	this->ClientToScreen(&S);
	E.SetPoint(ViewDisplayRect.right,ViewDisplayRect.bottom);
	this->ClientToScreen(&E);

	uint32 m_x0=S.x;
	uint32 m_y0=S.y;
	uint32 m_x1=E.x;
	uint32 m_y1=E.y;
	uint32 m_fps=10;
	int M=theApp.piLiveRoomMgr->openScreenShare(m_x0,m_y0,m_x1,m_y1,m_fps);
	*/

}


void CVirtyRoomView::OnButtonlocalscreenshare()
{
	// TODO: 
	//gpMainFrame->ShowSnapForm(0);
	//return;

	CString nRetStr;
	RECT ViewDisplayRect;
	gpMainFrame->pMySnapForm->GetClientRect(&ViewDisplayRect);
	nRetStr.Format(TEXT("SnapForm Rect: %d,%d,%d,%d"), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);

	CPoint S,E;
	S.SetPoint(0,0);
	this->ClientToScreen(&S);
	E.SetPoint(ViewDisplayRect.right,ViewDisplayRect.bottom);
	this->ClientToScreen(&E);

	//this->ClientToScreen(&ViewDisplayRect);

	//int width = GetSystemMetrics ( SM_CXSCREEN ); 
    //int height= GetSystemMetrics ( SM_CYSCREEN ); 
	


	int  nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int  nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	int XPostion = 0;
	int YPostion = 0;

	LONG m_x0 = S.x;
	LONG m_y0 = S.y;
	LONG m_x1 = ViewDisplayRect.right;// E.x;//1280;//640;//320;//1280;//width;
	LONG m_y1 = ViewDisplayRect.bottom;// E.y;//720;//480;//240;//720;//height;
	LONG m_fps=10;



	int result = gpMainFrame->pUnkSinkLiveRoomHelper->StartScreen(m_x0,m_y0,m_x1,m_y1,m_fps);
	if(result==0)
	{
      isScreenStatus=true;

	}
	
	nRetStr.Format(TEXT("Open Local Screen: %d;;%d,%d,%d,%d"), result, m_x0, m_y0, m_x1, m_y1);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	
}


void CVirtyRoomView::OnButtonChangescreen()
{
	// TODO: 
	CString nRetStr;
	RECT ViewDisplayRect;
	//GetClientRect(&ViewDisplayRect);
	gpMainFrame->pMySnapForm->GetClientRect(&ViewDisplayRect);
	nRetStr.Format(TEXT("SnapForm Rect: %d,%d,%d,%d"), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);

	CPoint S,E;
	S.SetPoint(0,0);
	this->ClientToScreen(&S);
	E.SetPoint(ViewDisplayRect.right,ViewDisplayRect.bottom);
	this->ClientToScreen(&E);


	//this->ClientToScreen(&ViewDisplayRect);	

	LONG m_x0 =  S.x;
	LONG m_y0 =  S.y;
	LONG m_x1 = ViewDisplayRect.right;// E.x;//1280;//640;//320;//1280;//width;
	LONG m_y1 = ViewDisplayRect.bottom;// E.y;//720;//480;//240;//720;//height;
	
	LONG m_fps = 10;

	
	int result= gpMainFrame->pUnkSinkLiveRoomHelper->ChangeScreen(m_x0,m_y0,m_x1,m_y1,10);
	nRetStr.Format(TEXT("Update Local Screen: %d;;%d,%d,%d,%d"), result, m_x0, m_y0, m_x1, m_y1);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
}


void CVirtyRoomView::OnButtonFullscreenshare()
{
	// TODO:
	//RECT ViewDisplayRect;
	//GetClientRect(&ViewDisplayRect);
	//CPoint S,E;
	//S.SetPoint(0,0);
	//this->ClientToScreen(&S);
	//E.SetPoint(ViewDisplayRect.right,ViewDisplayRect.bottom);
	//this->ClientToScreen(&E);

	int width = GetSystemMetrics ( SM_CXSCREEN ); 
    int height= GetSystemMetrics ( SM_CYSCREEN ); 
	//uint32 m_x0=0;
	//uint32 m_y0=0;
	//uint32 m_x1=width; //1280;//640;//320;//1280;//width;
	//uint32 m_y1=height;//720;//480;//240;//720;//height;
	//uint32 m_fps=10;

	//int result=theApp.piLiveRoomMgr->openScreenShare(m_x0,m_y0,m_x1,m_y1,m_fps);
	//if(result==0)
	//{
    //  isScreenStatus=false;

	//}
	//CString nRetStr;
	//nRetStr.Format(TEXT("...FullOpenScreen: %d;%d,%d,%d,%d"),result,m_x0,m_y0,m_x1,m_y1);
	//gpMainFrame->m_wndOutput.PrintMessage(nRetStr);




}


void CVirtyRoomView::OnButton1Closescreenshare()
{
	// TODO: 
	//int M=gpMainFrame->piLiveRoomMgr->closeScreenShare();
	//CString nRetStr;
	//nRetStr.Format(TEXT("...Closeboard: %d"),M);
	//gpMainFrame->m_wndOutput.PrintMessage(nRetStr);

	//gpMainFrame->ShowSnapForm(1);
	//return;


	CString nRetStr;
	nRetStr.Format(TEXT("Stop Master Screen......"));
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	gpMainFrame->pUnkSinkLiveRoomHelper->StopScreen();

	isScreenStatus = false;

}


void CVirtyRoomView::OnButtonCreatevirtyroom()
{
	// TODO: 
	

	gpMainFrame->LiveCreateRoom();



}


void CVirtyRoomView::OnButtonClosevirtyroom()
{
	// TODO: 
	gpMainFrame->LiveCloseRoom();
}


void CVirtyRoomView::OnButtonSlaverjoinbyteroom()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	gpMainFrame->pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Join Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
#endif

}


void CVirtyRoomView::OnButtonSlaverquitbyteroom()
{
	// TODO: 

#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	gpMainFrame->pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Quit Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
#endif

}


void CVirtyRoomView::OnButtonSlaverjoinmis3()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	gpMainFrame->pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Join Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
#endif

}


void CVirtyRoomView::OnButtonSlaverquitmis3()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
	gpMainFrame->pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Quit Room  MIS:%s"), theApp.m_RoomID);
	gpMainFrame->m_wndOutput.PrintMessage(nRetStr);
#endif
}
