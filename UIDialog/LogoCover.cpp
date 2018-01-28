// LogoCover.cpp : ʵ���ļ�
//

#include "..\stdafx.h"

#include "LogoCover.h"
#include "afxdialogex.h"
#include "..\MainFrm.h"

extern CMainFrame* gpMainFrame;
// LogoCover �Ի���

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

	//ShowWindow(SW_SHOWMAXIMIZED); //ȫ����ʾ
	ShowWindow(SW_SHOW); //��ȫ����ʾ
	//-------------------------------------------------------------------------------------------------
	///*
    //MyCBitmap.LoadBitmap(IDB_BITMAP1); 
    //BITMAP MyBITMAPSize;
     //��ȡλͼ��Ϣ
    //MyCBitmap.GetBitmap(&MyBITMAPSize);
    //int cx=MyBITMAPSize.bmWidth;  //�õ�ͼ���� 
    //int cy=MyBITMAPSize.bmHeight; //�õ�ͼ��߶� 
    //CRect mClientRect; 
	//this->GetClientRect(&mClientRect); 
    //GetDlgItem(IDC_STATIC_RectangleVideoWindow)->GetWindowRect(&mClientRect); 
	//GetDlgItem(IDC_STATIC_RectangleVideoWindow)->MoveWindow(mClientRect.left,mClientRect.top,cx,cy,true);//������С  
    //ScreenToClient(&mClientRect); 
 	///this->MoveWindow(mClientRect.left,mClientRect.top,cx,cy,true);//������С  
	//
	return TRUE; 
	// return TRUE unless you set the focus to a control--//-- EXCEPTION: OCX Property Pages should return FALSE
	
}

// LogoCover ��Ϣ�������
void LogoCover::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ����ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect mClientRect;    
    GetClientRect(&mClientRect);    
	CDC   mMemDC;    
    mMemDC.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   bmpBackground;    
    bmpBackground.LoadBitmap(IDB_BITMAP1);  //�Ի���ı���ͼƬ  
                        
    BITMAP   mbitmapInfor;    
    bmpBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=mMemDC.SelectObject(&bmpBackground);    
    mCurrentDC.StretchBlt(0,0,mClientRect.Width(),mClientRect.Height(),&mMemDC,0,0,mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	mMemDC.DeleteDC(); 
	//�¼ӵ����
	this->ReleaseDC(&mCurrentDC); 
	//---------------------------------------------------------------------------------------
    //CPaintDC mCurrentDC(this);      //���ô˾�,�õ����ǶԻ����DC,ͼƬ���������ڶԻ�����. 
    //CDC mCurrentDC; 
    //mCurrentDC.m_hDC=::GetDC(NULL);  //���ô�����,�õ�������Ļ��DC,ͼƬ������������Ļ�� 
	//CPaintDC mCurrentDC(GetDlgItem(IDC_STATIC_RectangleVideoWindow)); //�ô˾�,�õ�picture�ؼ���DC,ͼ�񽫱������ڿؼ���   
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
	//y--; 
	//�ͷ��豸����
  if(y<=0)//-100
  { 
     //KillTimer(1);
	 //CDialogEx::OnCancel();
	 //��ʾ����˳���
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
       //�����¼��������˳���
      
	  //KillTimer(1);
	  //CDialogEx::OnCancel();

	 if (pMyInitDlg != NULL)pMyInitDlg->ShowWindow(SW_HIDE);
	 this->ShowWindow(SW_HIDE);

	gpMainFrame->ShowWindow(SW_NORMAL); //SW_SHOW
	gpMainFrame->UpdateWindow();
	gpMainFrame->InvalidateRect(NULL, FALSE);//������ͼ�¼�[��ʱ��Ϣ]
    
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
