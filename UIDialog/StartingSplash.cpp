// StartingSplash.cpp : 实现文件
//
#include "..\stdafx.h"
#include "StartingSplash.h"
#include "afxdialogex.h"


// StartingSplash 对话框

IMPLEMENT_DYNAMIC(StartingSplash, CDialogEx)

StartingSplash::StartingSplash(CWnd* pParent /*=NULL*/)
	: CDialogEx(StartingSplash::IDD, pParent)
{
	pFlagChar=NULL;
	pUserName=NULL;;
	pAppName=NULL;;
	pDeveloperName=NULL;;
	pCoprRightName=NULL;;
	pUsableName=NULL;;
}

StartingSplash::~StartingSplash()
{
	if(pFlagChar!=NULL)delete pFlagChar;
	//SAFE_DELETE(pFlagChar);
	
	//SAFE_DELETE(pUserName);
	//SAFE_DELETE(pAppName);
	//SAFE_DELETE(pDeveloperName);
	//SAFE_DELETE(pCoprRightName);
	//SAFE_DELETE(pUsableName);

}

void StartingSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(StartingSplash, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL StartingSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect mRect;   
    GetClientRect(&mRect); 
	y=mRect.Height();

	int CharCount=120;
    pFlagChar=new CHAR[CharCount];//分个字符串
	for(int i=0;i<CharCount;i++)
    {
	   pFlagChar[i]='=';
    }
    pFlagChar[CharCount-1]='\0';
	//----------------------------------------------------------------
	 pUserName="王大同【蔚来课堂】高中物理同步辅导 ";
	 pAppName="全方位传道授业解惑新型教学系统 ";
	 pDeveloperName="授权单位:蔚来课堂教育科技有限公司 ";
	 pCoprRightName="Version 1.0 Copyright@2017";
	 pUsableName="专为K12学生设计的个性化学习新环境 使优质教育资源“无远弗届”";
	 //---------------------------------------------------------------
	 mUserNameFontCout=200;
	 mAppNameFontCout=250;
	 mDeveloperNameFontCout=180;
	 mCoprRightNameFontCout=120;
	 mUsableNameFontCout=180;
	 mFlagCharFontCout=80;
	 //----------------------------------------------------------------

	 CDC*  pDC = GetDC();
	 CFont  NewOutTextFont;//文本的字体对象       
	 CFont  *pOldFont;   //保存以前的字体指针 

	 NewOutTextFont.CreatePointFont(mUserNameFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mUserNameSize=pDC->GetTextExtent((CString)pUserName);//获得字符串长度
	
	
	 NewOutTextFont.DeleteObject(); 
	 NewOutTextFont.CreatePointFont(mAppNameFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mAppNameSize=pDC->GetTextExtent((CString)pAppName);//获得字符串长度

	 NewOutTextFont.DeleteObject(); 
	 NewOutTextFont.CreatePointFont(mFlagCharFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mFlagCharSize=pDC->GetTextExtent((CString)pFlagChar);//获得字符串长度


	 NewOutTextFont.DeleteObject(); 
	 NewOutTextFont.CreatePointFont(mDeveloperNameFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mDeveloperNameSize=pDC->GetTextExtent((CString)pDeveloperName);//获得字符串长度

	 NewOutTextFont.DeleteObject(); 
	 NewOutTextFont.CreatePointFont(mCoprRightNameFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mCoprRightNameSize=pDC->GetTextExtent((CString)pCoprRightName);//获得字符串长度

	 NewOutTextFont.DeleteObject(); 
	 NewOutTextFont.CreatePointFont(mUsableNameFontCout,_T("宋体"));
	 pOldFont=pDC->SelectObject(&NewOutTextFont);//选择你需要的字体 
	 mUsableNameSize=pDC->GetTextExtent((CString)pUsableName);//获得字符串长度


	ShowWindow(SW_SHOWMAXIMIZED); //全屏显示
    m_MemBitmap.init(this);  
    SetTimer(1,20,NULL);  
	
	//-------MyCBitmap------------------------------------------------------------------------------------------
    /*
	MyCBitmap.LoadBitmap(IDB_BITMAP4); 
    BITMAP MyBITMAPSize;
     //获取位图信息
    MyCBitmap.GetBitmap(&MyBITMAPSize);
    int cx=MyBITMAPSize.bmWidth;  //得到图像宽度 
    int cy=MyBITMAPSize.bmHeight; //得到图像高度 
    CRect mRect; 
    GetDlgItem(IDC_STATIC_RectangleVideoWindow)->GetWindowRect(&mRect); 
    ScreenToClient(&mRect); 
    GetDlgItem(IDC_STATIC_RectangleVideoWindow)->MoveWindow(mRect.left,mRect.top,cx,cy,true);//调整大小  
	*/
	 
	return TRUE;  // return TRUE unless you set the focus to a control // EXCEPTION: OCX Property Pages should return FALSE
}



// StartingSplash 消息处理程序


void StartingSplash::OnTimer(UINT_PTR nIDEvent)
{
	//添加的消息处理程序代码
  CRect   mRect;    
  CDC*    pDC = GetDC();
  CDC     mDC;
  this->GetClientRect(&mRect); 
  LONG mOutTextPointX;
  //mOutTextPointX=(int)(mRect.Width()/2);
  mOutTextPointX=mRect.Width();
  //int CharCount;
  //CharCount=120;
  //CHAR * pFlagChar=new CHAR[CharCount];
  //pFlagChar=new CHAR[CharCount];
  //for(int i=0;i<CharCount;i++)
  //{
  //  pFlagChar[i]='=';
  //}
  //pFlagChar[CharCount-1]='\0';
  y--;
  m_MemBitmap.Clear(mRect.left, mRect.top, mRect.right, mRect.bottom, RGB(00,00,00)); //冷灰128,138,135--象牙黑41,36,33-棕黑色的RGB值94 38 18--69, 33,21
  
  LONG OutTextPosionX,OutTextPosionY,mDistanceValue;
  OutTextPosionX=(mOutTextPointX-mUserNameSize.cx)/2;
  mDistanceValue=0;
  OutTextPosionY=(LONG)y+mDistanceValue;
  m_MemBitmap.TextOut((int)OutTextPosionX ,(int)OutTextPosionY/*y*/,mUserNameFontCout, pUserName,RGB(0,250,0)); //1

  OutTextPosionX=(mOutTextPointX-mAppNameSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy-20;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+60*/,mAppNameFontCout, pAppName,RGB(0,250,0)); //2

  OutTextPosionX=(mOutTextPointX-mFlagCharSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy+mFlagCharSize.cy+30;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+130*/,mFlagCharFontCout,pFlagChar,RGB(0,250,0));//3

  OutTextPosionX=(mOutTextPointX-mDeveloperNameSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy+mFlagCharSize.cy+mDeveloperNameSize.cy+30;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+180*/,mDeveloperNameFontCout,pDeveloperName,RGB(255,0,0)); //4

  OutTextPosionX=(mOutTextPointX-mCoprRightNameSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy+mFlagCharSize.cy+mDeveloperNameSize.cy+mCoprRightNameSize.cy+50;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+240*/,mCoprRightNameFontCout,pCoprRightName,RGB(255,0,0)); //5

  OutTextPosionX=(mOutTextPointX-mFlagCharSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy+mFlagCharSize.cy+mDeveloperNameSize.cy+mCoprRightNameSize.cy+mFlagCharSize.cy+70;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+300*/,mFlagCharFontCout,pFlagChar,RGB(0,250,0));//6

  OutTextPosionX=(mOutTextPointX-mUsableNameSize.cx)/2;
  mDistanceValue=mUserNameSize.cy+ mAppNameSize.cy+mFlagCharSize.cy+mDeveloperNameSize.cy+mCoprRightNameSize.cy+mFlagCharSize.cy+mUsableNameSize.cy+70;
  OutTextPosionY=(LONG)y+mDistanceValue; 
  m_MemBitmap.TextOut((int)OutTextPosionX,(int)OutTextPosionY/*y+340*/,mUsableNameFontCout, pUsableName,RGB(0,250,0));//7

  /*
  m_MemBitmap.Clear(mRect.left, mRect.top, mRect.right, mRect.bottom, RGB(00,00,00)); //冷灰128,138,135--象牙黑41,36,33-棕黑色的RGB值94 38 18--69, 33,21
  m_MemBitmap.TextOut(mOutTextPointX-125,y,200,  "北京天坛医院 ",RGB(0,250,0));  
  m_MemBitmap.TextOut(mOutTextPointX-280,y+60,250,  "量化靶控区域麻醉可视超声系统 ",RGB(0,250,0));  
  m_MemBitmap.TextOut(mOutTextPointX-400,y+130,80, pFlagChar,RGB(0,250,0)); 
  m_MemBitmap.TextOut(mOutTextPointX-250,y+180,180, "授权单位:曼翔(德国)医疗器械有限公司 ",RGB(255,0,0)); 
  m_MemBitmap.TextOut(mOutTextPointX-160,y+240,120,"Version 1.0 Copyright@2012",RGB(255,0,0)); 
  m_MemBitmap.TextOut(mOutTextPointX-400,y+300,80,pFlagChar,RGB(0,250,0));
  m_MemBitmap.TextOut(mOutTextPointX-350,y+340,180, "专为麻醉科设计的穿刺导航仪 使医生手指上长出“眼睛”",RGB(0,250,0));
  */
  /*
  m_MemBitmap.TextOut(280,y,180,  " 北京天坛医院 ",RGB(0,250,0));  
  m_MemBitmap.TextOut(180,y+30,180,  "量化靶控区域麻醉可视超声波系统 ",RGB(0,250,0));  
  m_MemBitmap.TextOut(10,y+60,120, "===============================================================================================",RGB(0,0,250)); 
  //m_MemBitmap.TextOut(10,y+60,120, "授权人: 黄大仙 ",RGB(0,250,0));   
  m_MemBitmap.TextOut(240,y+90,120, "授权单位:曼翔医疗器械有限公司 ",RGB(0,250,0)); 
  m_MemBitmap.TextOut(240,y+120,120,"Version 1.0 Copyright@2012",RGB(0,250,0)); 
  m_MemBitmap.TextOut(10,y+150,120,"===============================================================================================",RGB(0,0,250));
  m_MemBitmap.TextOut(280,y+180,150, "专业、可靠、先进、卓越",RGB(0,250,0));
  */
  mDC.CreateCompatibleDC(pDC); 
  mDC.SelectObject(&m_MemBitmap);  //内存设备环境将位图对象选入 
  pDC->BitBlt(0, 0, mRect.Width() , mRect.Height(),  &mDC,  0,0,SRCCOPY); //用位传输函数显示出来
  mDC.DeleteDC();    
  ReleaseDC(pDC); //当前窗口-释放设备对象
  if(y<=-180)//-180
  { 
     KillTimer(1);
	 CDialogEx::OnCancel(); //文字显示完后退出！
  }
  //delete pFlagChar;
  //--------------------
  
  CDialogEx::OnTimer(nIDEvent);
}
LRESULT StartingSplash::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
 if ( message == WM_KEYDOWN ||message == WM_SYSKEYDOWN ||
   message == WM_LBUTTONDOWN ||message == WM_RBUTTONDOWN ||
   message == WM_MBUTTONDOWN ||message == WM_NCLBUTTONDOWN ||
   message == WM_NCRBUTTONDOWN ||message == WM_NCMBUTTONDOWN )
 {//如有事件发生，退出！
      
	  KillTimer(1);
	  CDialogEx::OnCancel();
      return TRUE; 
 }
  return CWnd::WindowProc(message, wParam, lParam);
}



void StartingSplash::OnPaint()
{

	// device context for painting
	CPaintDC mCurrentDC(this); 
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//---------------------------------------------------------------------------------------
    //CPaintDC mCurrentDC(this);      //若用此句,得到的是对话框的DC,图片将被绘制在对话框上. 
    //CDC mCurrentDC; 
    //mCurrentDC.m_hDC=::GetDC(NULL);  //若用此两句,得到的是屏幕的DC,图片将被绘制在屏幕上 
	//CPaintDC mCurrentDC(GetDlgItem(IDC_STATIC_RectangleVideoWindow)); //用此句,得到picture控件的DC,图像将被绘制在控件上   
    //----------------------------------------------------------------------------------------------------------------
	/*
	CRect rcclient; 
    GetDlgItem(IDC_STATIC_RectangleVideoWindow)->GetClientRect(&rcclient); 
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
