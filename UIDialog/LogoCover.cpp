// LogoCover.cpp : 实现文件
//

#include "..\stdafx.h"

#include "LogoCover.h"
#include "afxdialogex.h"
#include "..\MainFrm.h"

extern CMainFrame* gpMainFrame;
// LogoCover 对话框

IMPLEMENT_DYNAMIC(LogoCover, CDialogEx)

LogoCover::LogoCover(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogoCover::IDD, pParent)
{
	pMyInitDlg = NULL;
}

LogoCover::~LogoCover()
{
}

void LogoCover::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogoCover, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCLINK_WuLiRoomTest, &LogoCover::OnBnClickedMfclinkWuliroomtest)
	ON_STN_CLICKED(IDC_STATIC_WuLiRoomDemo, &LogoCover::OnStnClickedStaticWuliroomdemo)
END_MESSAGE_MAP()

BOOL LogoCover::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	//CRect mRect;   
    //GetClientRect(&mRect); 
	//y=mRect.Height();
    //SetTimer(1,20,NULL);  

	//ShowWindow(SW_SHOWMAXIMIZED); //全屏显示
	ShowWindow(SW_SHOW); //非全屏显示
	//-------------------------------------------------------------------------------------------------
	///*
    //MyCBitmap.LoadBitmap(IDB_BITMAP1); 
    //BITMAP MyBITMAPSize;
     //获取位图信息
    //MyCBitmap.GetBitmap(&MyBITMAPSize);
    //int cx=MyBITMAPSize.bmWidth;  //得到图像宽度 
    //int cy=MyBITMAPSize.bmHeight; //得到图像高度 
    //CRect mClientRect; 
	//this->GetClientRect(&mClientRect); 
    //GetDlgItem(IDC_STATIC_RectangleVideoWindow)->GetWindowRect(&mClientRect); 
	//GetDlgItem(IDC_STATIC_RectangleVideoWindow)->MoveWindow(mClientRect.left,mClientRect.top,cx,cy,true);//调整大小  
    //ScreenToClient(&mClientRect); 
 	///this->MoveWindow(mClientRect.left,mClientRect.top,cx,cy,true);//调整大小  
	//
	return TRUE; 
	// return TRUE unless you set the focus to a control--//-- EXCEPTION: OCX Property Pages should return FALSE
	
}

// LogoCover 消息处理程序
void LogoCover::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不绘图消息调用 CDialogEx::OnPaint()
	CRect mClientRect;    
    GetClientRect(&mClientRect);    
	CDC   mMemDC;    
    mMemDC.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   bmpBackground;    
    bmpBackground.LoadBitmap(IDB_BITMAP1);  //对话框的背景图片  
                        
    BITMAP   mbitmapInfor;    
    bmpBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=mMemDC.SelectObject(&bmpBackground);    
    mCurrentDC.StretchBlt(0,0,mClientRect.Width(),mClientRect.Height(),&mMemDC,0,0,mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	mMemDC.DeleteDC(); 
	//新加的语句
	this->ReleaseDC(&mCurrentDC); 
	//---------------------------------------------------------------------------------------
    //CPaintDC mCurrentDC(this);      //若用此句,得到的是对话框的DC,图片将被绘制在对话框上. 
    //CDC mCurrentDC; 
    //mCurrentDC.m_hDC=::GetDC(NULL);  //若用此两句,得到的是屏幕的DC,图片将被绘制在屏幕上 
	//CPaintDC mCurrentDC(GetDlgItem(IDC_STATIC_RectangleVideoWindow)); //用此句,得到picture控件的DC,图像将被绘制在控件上   
    //----------------------------------------------------------------------------------------------------------------
	/*
	CRect rcclient; 
    //GetDlgItem(IDC_STATIC_RectangleVideoWindow)->GetClientRect(&rcclient); 
	this->GetClientRect(&rcclient); 
    CDC memdc; 
    memdc.CreateCompatibleDC(&mCurrentDC);   
    CBitmap mbitmapInfor; 
    mbitmapInfor.CreateCompatibleBitmap(&mCurrentDC, rcclient.Width(), rcclient.Height()); 
    memdc.SelectObject(&mbitmapInfor ); 
    CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC , 0); 
    CDC maskdc; 
    maskdc.CreateCompatibleDC(&mCurrentDC); 
    CBitmap maskbitmap; 
    maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL); 
    maskdc.SelectObject(&maskbitmap ); 
    maskdc.BitBlt( 0, 0, rcclient.Width(), rcclient.Height(), &memdc,
    rcclient.left, rcclient.top, SRCCOPY); 
    CBrush brush; 
    brush.CreatePatternBrush(&MyCBitmap); 
    mCurrentDC.FillRect(rcclient, &brush);   
    mCurrentDC.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(),&memdc, rcclient.left, rcclient.top,SRCPAINT); 
    brush.DeleteObject(); 
	*/
	 
	
}


void LogoCover::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
	//y--; 
	//释放设备对象
  if(y<=0)//-100
  { 
     //KillTimer(1);
	 //CDialogEx::OnCancel();
	 //显示完后，退出！
  }
  */

	CDialogEx::OnTimer(nIDEvent);
}
LRESULT LogoCover::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
 
 if ( message == WM_KEYDOWN ||message == WM_SYSKEYDOWN ||
   message == WM_LBUTTONDOWN ||message == WM_RBUTTONDOWN ||
   message == WM_MBUTTONDOWN ||message == WM_NCLBUTTONDOWN ||
   message == WM_NCRBUTTONDOWN ||message == WM_NCMBUTTONDOWN )
 {
       //如有事件发生，退出！
      
	  //KillTimer(1);
	  //CDialogEx::OnCancel();

	 if (pMyInitDlg != NULL)pMyInitDlg->ShowWindow(SW_HIDE);
	 this->ShowWindow(SW_HIDE);

	gpMainFrame->ShowWindow(SW_NORMAL); //SW_SHOW
	gpMainFrame->UpdateWindow();
	gpMainFrame->InvalidateRect(NULL, FALSE);//引发绘图事件[即时消息]
    
	return TRUE; 
 }
 
  return CWnd::WindowProc(message, wParam, lParam);
}


void LogoCover::OnBnClickedMfclinkWuliroomtest()
{
	// TODO: 



}


void LogoCover::OnStnClickedStaticWuliroomdemo()
{
	// TODO: 


}
