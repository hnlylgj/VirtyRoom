

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "VirtyRoom.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace ilivemainwin;
//------全局变量及常量！-------------------------------------------------------------------------------------------
CMainFrame* gpMainFrame;
INT TestCount=0;

//uint32  lenght=1000000;
enum	VFW_STATE { PREVIEW, CODEC };
VFW_STATE	m_VFW_State = PREVIEW;

#define XDIM 1920			        //图像宽度，预设的足够大 
#define YDIM 1080			        //图像高度，预设的足够大
//unsigned char m_CaptureImageBuffer[XDIM*YDIM * 3 + 40+512];//需显示图像数据区，RGB格式3字节一个像素
unsigned char m_CaptureImageBuffer2[XDIM*YDIM * 3  + 40];//需显示图像数据区，RGB格式3字节一个像素
HWND		m_hCaptureWindow;		                  //VFW设备窗口句柄

//LPBITMAPINFOHEADER    pInputBitMapInfo;                //采集输入格式
LPBITMAPINFOHEADER    pInputBitMapInfo2;               //采集输入格式2
//LPBITMAPINFOHEADER    pJunkBitMapInfo;              //采集输入中间转换格式
//LPBITMAPINFOHEADER	pComprressBitMapInfo;         //编码器输出格式 
//LPBITMAPINFOHEADER    pDecomprressBitMapInfo;	      //解码器输出格式//

COMPVARS        mCompressProfileParam;	               //编码设置结构体

BOOL            IsKeyFrame;	                           //
BOOL			bSaveAVI = FALSE;	                   //
long            mCompresFrameSize;
int				mCurrentID;		                       //
BOOL			bPreview = FALSE;	                   //
BOOL			IsDirectSaveAVI = FALSE;	           //


 //=====VFW回调函数======================================================================
LRESULT CALLBACK EXPORT ErrorCallbackProc(HWND hWnd, int nErrID, LPSTR lpErrorText)
{
	if (nErrID == 0)
		return TRUE;
	//MessageBoxW(NULL, (LPCSTR)lpErrorText, _T(""), MB_OK);
	return TRUE;
}

LRESULT FAR PASCAL StatusCallbackProc(HWND hWnd, int nID, LPSTR lpStatusText)
{
	if (nID == IDS_CAP_END)
	{
		if ((mCurrentID == IDS_CAP_STAT_VIDEOAUDIO) || (mCurrentID == IDS_CAP_STAT_VIDEOONLY))
			return TRUE;
	}
	mCurrentID = nID;
	return (LRESULT)TRUE;
}

LRESULT FAR PASCAL VideoCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	//unsigned char *pSourceImageBuffer, *pCodedImageBuffer;
	//pSourceImageBuffer = new unsigned char[lpVHdr->dwBytesUsed];	//original image
	//memcpy((void *)(pSourceImageBuffer), lpVHdr->lpData, lpVHdr->dwBytesUsed);
	//pCodedImageBuffer = NULL;

	//memcpy(&m_CaptureImageBuffer[40], pSourceImageBuffer, lpVHdr->dwBytesUsed);	
	memcpy(&m_CaptureImageBuffer2[40], lpVHdr->lpData, lpVHdr->dwBytesUsed);//直接复制共享缓冲区
	gpMainFrame->GetActiveView()->InvalidateRect(NULL, FALSE);	//引发绘图事件[即时消息]
    //ExitFlag:
	//delete[]pSourceImageBuffer;

	return (LRESULT)TRUE;//测试通过
}


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_RIBBON_OpenDevice, ID_RIBBON_SaveImaging, &CMainFrame::OnUSGDeviceStateChange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_RIBBON_OpenDevice, ID_RIBBON_SaveImaging, &CMainFrame::OnUpdateUSGDeviceStateChangUI)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_ShowPropertyWindow_32771, &CMainFrame::OnShowpropertywindow32771)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MYMSG,OnMyProcessMessage)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_COMMAND(ID_BUTTON_LoginLive, &CMainFrame::OnButtonLoginlive)
	ON_COMMAND(ID_BUTTON_LoginoutLive, &CMainFrame::OnButtonLoginoutlive)
	ON_MESSAGE(WM_LiveLogin,&CMainFrame::LiveLoginHandler)
	ON_MESSAGE(WM_LiveRoom,&CMainFrame::LiveRoomHandler)
	ON_MESSAGE(WM_SERVERDATACHANGE, &CMainFrame::LiveStatusHandler)
	ON_MESSAGE(WM_EXTRADATACHANGE, &CMainFrame::LiveStatusHandlerEx)
	ON_COMMAND(ID_BUTTON_LoginoutLive2, &CMainFrame::OnButtonLoginoutlive2)
	ON_COMMAND(ID_BUTTON_CreateRoom, &CMainFrame::OnButtonCreateroom)
	ON_COMMAND(ID_BUTTON_CloseRoom, &CMainFrame::OnButtonCloseroom)
	ON_COMMAND(ID_BUTTON_JoinRoom, &CMainFrame::OnButtonJoinroom)
	ON_COMMAND(ID_BUTTON_QuitRoom, &CMainFrame::OnButtonQuitroom)
	ON_COMMAND(ID_BUTTON_StartVideo, &CMainFrame::OnButtonStartvideo)
	ON_COMMAND(ID_BUTTON_StartScreen, &CMainFrame::OnButtonStartscreen)
	ON_COMMAND(ID_BUTTON_CloseScreen, &CMainFrame::OnButtonClosescreen)
	ON_COMMAND(ID_BUTTON_StopVideo, &CMainFrame::OnButtonStopvideo)
	ON_COMMAND(ID_BUTTON_InitVFW, &CMainFrame::OnButtonInitvfw)
	ON_COMMAND(ID_BUTTON_Preview, &CMainFrame::OnButtonPreview)
	ON_COMMAND(ID_BUTTON_SetupPara, &CMainFrame::OnButtonSetuppara)
	ON_COMMAND(ID_BUTTON_StartPreView, &CMainFrame::OnButtonStartpreview)
	ON_COMMAND(ID_BUTTON1_LocalPreView, &CMainFrame::OnButton1Localpreview)
	ON_COMMAND(ID_BUTTON_CreateVirtyRoom, &CMainFrame::OnButtonCreatevirtyroom)
	ON_COMMAND(ID_BUTTON_CloseVirtyRoom, &CMainFrame::OnButtonClosevirtyroom)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_BUTTON_MasterQuitRoom, &CMainFrame::OnButtonMasterquitroom)
	ON_COMMAND(ID_BUTTON_MasterQuitRoom2, &CMainFrame::OnButtonMasterquitroom2)
	ON_COMMAND(ID_BUTTON_WatcherJoinRoom, &CMainFrame::OnButtonWatcherjoinroom)
	ON_COMMAND(ID_BUTTON_WatcherQuitRoom, &CMainFrame::OnButtonWatcherquitroom)
	ON_COMMAND(ID_BUTTON_localScreenShare2, &CMainFrame::OnButtonlocalscreenshare2)
	//ON_COMMAND(ID_BUTTON_SlaverJoinMis, &CMainFrame::OnButtonSlaverjoinmis)
	//ON_COMMAND(ID_BUTTON_SlaverQuitMIS, &CMainFrame::OnButtonSlaverquitmis)
	//ON_COMMAND(ID_BUTTON_SlaverJoinMis2, &CMainFrame::OnButtonSlaverjoinmis2)
	//ON_COMMAND(ID_BUTTON_SlaverQuitMIS2, &CMainFrame::OnButtonSlaverquitmis2)
	ON_COMMAND(ID_BUTTON_SlaverJoinMis3, &CMainFrame::OnButtonSlaverjoinmis3)
	ON_COMMAND(ID_BUTTON_SlaverJoinByteRoom, &CMainFrame::OnButtonSlaverjoinbyteroom)
	ON_COMMAND(ID_BUTTON_SlaverQuitByteRoom, &CMainFrame::OnButtonSlaverquitbyteroom)
	ON_COMMAND(ID_BUTTON_SlaverQuitMIS3, &CMainFrame::OnButtonSlaverquitmis3)
	ON_COMMAND(ID_BUTTON_JoinLogicServer, &CMainFrame::OnButtonJoinlogicserver)
	ON_COMMAND(ID_BUTTON7_QuitLogicServer, &CMainFrame::OnButton7Quitlogicserver)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	pMModeAdustCtrlBox=new CBModeCtrlBox(2);

	USGDeviceStateID=FALSE;
	USGImagingRunModeID=FALSE;;
	USGFreezingID=FALSE;;

	pInputBitMapInfo2 = NULL;
	isCloseFlag=0;
	isLiveFlag=0;
	mLiveCount= 0;

#ifdef VersionStud 
	pAxStudMgrDlg = NULL;
#else
	pAccountManager = NULL;
#endif
	
    pLogoCover = NULL;
	pInitianlizingText = NULL;

	pMySnapForm = NULL;

}

CMainFrame::~CMainFrame()
{
	delete pMModeAdustCtrlBox;
	pInputBitMapInfo2 = NULL;

#ifdef VersionStud 
	pAxStudMgrDlg = NULL;
#else
	pAccountManager = NULL;
#endif
	pLogoCover = NULL;
	pInitianlizingText = NULL;

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//------------------------------------------------------------------------------
	
	
	ShowLogoCover(0);
	
	//Sleep(6000);//测试语句
	//-----------------------------------------------------------------------------
	
	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);
	//---创建 Ribbon----------------------------
	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString SoftVersionTitlePane1;
	CString BeamformerStateTitlePane2;
	//--------------------------------------------------
	CString ScanModeTitlePane3;
	CString PositionInforTitlePane4;
	CString DtaeTimeTitlePane5;
	CString ProcessingTitlePane6;

	CString CustomerTitlePane7;
	CString UserTitlePane8;

	bNameValid = SoftVersionTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = BeamformerStateTitlePane2.LoadString(IDS_STATUS_PANE2);
	
	ASSERT(bNameValid);
	//-----------------------
	bNameValid = ScanModeTitlePane3.LoadString(IDS_STATUS_PANE3);
	ASSERT(bNameValid);
	bNameValid = PositionInforTitlePane4.LoadString(IDS_STATUS_PANE4);
	PositionInforTitlePane4=" (x=000,y=000) (R=000 G=000 B=000)     ";
	ASSERT(bNameValid);
	bNameValid = DtaeTimeTitlePane5.LoadString(IDS_STATUS_PANE5);
	ASSERT(bNameValid);
	DtaeTimeTitlePane5="0000-00-00-00-00:00:00 ";
	bNameValid = ProcessingTitlePane6.LoadString(IDS_STATUS_PANE6);
	ProcessingTitlePane6=" 进度...............................";
	ASSERT(bNameValid);

	CustomerTitlePane7=" 北京朝阳区高中物理教师";
	UserTitlePane8=" 张大仙";
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, SoftVersionTitlePane1, TRUE), SoftVersionTitlePane1);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, BeamformerStateTitlePane2, TRUE), BeamformerStateTitlePane2);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE3, ScanModeTitlePane3, TRUE), ScanModeTitlePane3);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE4, PositionInforTitlePane4, TRUE), PositionInforTitlePane4);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE5, DtaeTimeTitlePane5, TRUE), DtaeTimeTitlePane5);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE6, ProcessingTitlePane6, TRUE), ProcessingTitlePane6);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE7, CustomerTitlePane7, TRUE), CustomerTitlePane7);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE8, UserTitlePane8, TRUE), UserTitlePane8);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, BeamformerStateTitlePane2, TRUE), BeamformerStateTitlePane2);
	CRect mProgressRect;
	CMFCRibbonBaseElement * pElement;  
	pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE5); 
	mProgressRect=pElement->GetRect();

    m_Progress.Create(WS_CHILD | WS_VISIBLE,mProgressRect,&m_wndStatusBar,1088); 
	m_Progress.SetWindowPos(NULL,mProgressRect.left,mProgressRect.top,mProgressRect.Width(),mProgressRect.Height(),SWP_NOZORDER);  
	m_Progress.SetPos(0); 
		
	//---------------------------------------------------------------------------------------------------------------------------
	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);
	//-------My SELF ---------------------------------------------------------------------------------------------------------------
	if(!mBModeAdustCtrlBox.Create(_T("白板视图"),this,CRect(0,0,300,300),true,ID_BModeCtrlBox_View,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create dock window\n");
		return FALSE;
	}
   //pMModeAdustCtrlBox
	if(!pMModeAdustCtrlBox->Create(_T("视频视图"),this,CRect(0,0,300,300),true,ID_MModeCtrlBox_View,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create dock window\n");
		return FALSE;
	}



	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0(_T("未能创建停靠窗口\n"));
		return -1;
	}
	mBModeAdustCtrlBox.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&mBModeAdustCtrlBox);

	pMModeAdustCtrlBox->EnableDocking(CBRS_ALIGN_ANY); 
	DockPane(pMModeAdustCtrlBox);
	//----------------------------------------------------------------------------------------------------------------------------------------------------
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);

	mBModeAdustCtrlBox.AttachToTabWnd(pTabbedBar, DM_SHOW, TRUE, &pTabbedBar);
	pMModeAdustCtrlBox->AttachToTabWnd(pTabbedBar, DM_SHOW, TRUE, &pTabbedBar);
	//pMModeAdustCtrlBox->AttachToTabWnd(&mBModeAdustCtrlBox, DM_SHOW, TRUE, &pTabbedBar);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	//pMModeAdustCtrlBox->AttachToTabWnd(&m_wndProperties, DM_SHOW, TRUE, &pTabbedBar);
	//pMModeAdustCtrlBox->DockToWindow(&m_wndProperties, CBRS_ALIGN_BOTTOM);
	
		
	//--Clear Resource----------------------------------------------------------------
	//pLogoCover->DestroyWindow(); //CANCEL START SREEN;
	//pInitianlizingText->DestroyWindow();
	//delete pLogoCover;
	//delete pInitianlizingText;

	//ShowLogoCover(1);
	//pAccountManager = theApp.pAccountManager;

	//pLAccountManager = theApp.pAccountManager;
	//pLAccountManager->SetParentWnd(this);
	//pLAccountManager->set
	ShowAccountManager(1);


	//SetTimer(1, 1000, NULL); 

	//------------------------------------------------------
	gpMainFrame=this;

	/*
	pInputBitMapInfo = (LPBITMAPINFOHEADER)new BYTE[40];
	memset(pInputBitMapInfo, 0, sizeof(BITMAPINFOHEADER));
	
	pInputBitMapInfo->biSize = 40;
	pInputBitMapInfo->biBitCount = 3 * 8;//COLOR_FORMAT_RGB24	
	pInputBitMapInfo->biPlanes = 1;
	pInputBitMapInfo->biCompression = BI_RGB;//COLOR_FORMAT_RGB24	
	pInputBitMapInfo->biWidth = 1280;
	pInputBitMapInfo->biHeight = 768;	
	*/
	


	pInputBitMapInfo2 = (LPBITMAPINFOHEADER)new BYTE[40];
	memset(pInputBitMapInfo2, 0, sizeof(BITMAPINFOHEADER));
	
	pInputBitMapInfo2->biSize = 40;
	pInputBitMapInfo2->biBitCount = 3 * 8;//COLOR_FORMAT_RGB24	
	pInputBitMapInfo2->biPlanes = 1;
	pInputBitMapInfo2->biCompression = BI_RGB;//COLOR_FORMAT_RGB24	
	pInputBitMapInfo2->biWidth = 1280;
	pInputBitMapInfo2->biHeight = 768;	



	InitiLiveSDK();


	SetTimer(1, 1000, NULL);

	return 0;
	

	
}

void CMainFrame::ShowLogoCover(int flag)
{
	

	if (pLogoCover == NULL)
	{
		pLogoCover = new LogoCover(this);
		pLogoCover->Create(LogoCover::IDD, this);

		int  nFullWidth = GetSystemMetrics(SM_CXSCREEN);
		int  nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		int XPostion = 0;
		int YPostion = 0;
		pLogoCover->SetWindowPos(NULL, XPostion, YPostion, nFullWidth, nFullHeight-60, SWP_NOZORDER);


		
	}
	if (pInitianlizingText == NULL)
	{
		pInitianlizingText = new InitianlizingText(this);
		pInitianlizingText->Create(InitianlizingText::IDD, this);

		

		int  nFullWidth = GetSystemMetrics(SM_CXSCREEN);
		int  nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		int XPostion = (nFullWidth - 462) / 2;
		int YPostion = nFullHeight - 143 - 60-80;
		pInitianlizingText->SetWindowPos(NULL, XPostion, YPostion, 462, 143, SWP_NOZORDER);

		pLogoCover->pMyInitDlg = pInitianlizingText;
		
	}

	if (flag == 0)
	{

	
		pLogoCover->ShowWindow(SW_SHOW);
		pInitianlizingText->ShowWindow(SW_SHOW);
		pLogoCover->UpdateWindow();
		pInitianlizingText->UpdateWindow();

							
	}
	else
	{

		pLogoCover->ShowWindow(SW_HIDE);
		pLogoCover->UpdateWindow();
		pInitianlizingText->ShowWindow(SW_HIDE);
		pInitianlizingText->UpdateWindow();
	
	}


}

void CMainFrame::ShowSnapForm(int flag)
{

	if (pMySnapForm == NULL)
	{
		pMySnapForm = new SnapForm(this);
		pMySnapForm->Create(SnapForm::IDD, this);
	}

	

	if (flag == 0)
	{


		pMySnapForm->ShowWindow(SW_SHOW);
		pMySnapForm->UpdateWindow();
	

	}
	else
	{

		pMySnapForm->ShowWindow(SW_HIDE);
		pMySnapForm->UpdateWindow();
	

	}



}

void CMainFrame::ShowAccountManager(int flag)
{
#ifdef VersionStud 
	
	if (pAxStudMgrDlg == NULL)
	{
		pAxStudMgrDlg = new AxStudMgrDlg(this);
		pAxStudMgrDlg->Create(AxStudMgrDlg::IDD, this);


}
	if (flag == 0)
	{

		pAxStudMgrDlg->ShowWindow(SW_SHOW);
		pAxStudMgrDlg->UpdateWindow();

	}
	else
	{
		pAxStudMgrDlg->ShowWindow(SW_HIDE);
		pAxStudMgrDlg->UpdateWindow();


	}
	pAxStudMgrDlg->mAxStudMgrDlg.CopyParaTo(theApp.m_szUserId, theApp.m_szUserSig, theApp.m_szUserToken);
	
#else
	if (pAccountManager == NULL)
	{
		pAccountManager = new CAccountManager(this);
		pAccountManager->Create(CAccountManager::IDD, this);


	}
	if (flag == 0)
	{

		pAccountManager->ShowWindow(SW_SHOW);
		pAccountManager->UpdateWindow();

	}
	else
	{
		pAccountManager->ShowWindow(SW_HIDE);
		pAccountManager->UpdateWindow();


	}
	pAccountManager->mRestfulQtCOMCtrl.CopyParaTo(theApp.m_szUserId, theApp.m_szUserSig, theApp.m_szUserToken);
	mRoomTitle = _T("牛顿运动三定律");
#endif
	

}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	//----------------------------------------------------------------------------------------------------------------------------
	/*
	CString strBModeCtrlView;
	bNameValid = strBModeCtrlView.LoadString(IDS_BModeCtrl_VIEW);
	ASSERT(bNameValid);
	//mBModeAdustCtrlBar.Create(this,IDD_BModeAdjust_DIALOG,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI,IDD_BModeAdjust_DIALOG); 
	mBModeAdustCtrlBar.CreateEx(CreateEx(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI,strBModeCtrlView, 
			if (!mBModeAdustCtrlBar.CreateEx((strBModeCtrlView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“B模式控制箱”窗口\n");
		return FALSE; // 未能创建
	}
	*/
	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
//---------------------------------
void CMainFrame::OnUSGDeviceStateChange(UINT id)
{
	switch (id)
	{
	case ID_RIBBON_OpenDevice:
		USGDeviceStateID=TRUE;
		break;

	case ID_RIBBON_ColseDevice:
		USGDeviceStateID=FALSE;
		break;

	case ID_RIBBON_StartImaging:
		USGImagingRunModeID=TRUE;
		USGImagingRunModeID=TRUE;
		break;

	case ID_RIBBON_ColseImaging:
		USGImagingRunModeID=FALSE;
		break;
    case ID_RIBBON_FreezeImaging:
		USGFreezingID==TRUE;
		break;
   case ID_RIBBON_SaveImaging:
		
		break;

	}


}

void CMainFrame::OnUpdateUSGDeviceStateChangUI(CCmdUI* pCmdUI)
{
	
	switch (pCmdUI->m_nID)
	{
	case ID_RIBBON_OpenDevice:
		pCmdUI->Enable(!USGDeviceStateID);
		break;

	case ID_RIBBON_ColseDevice:
		pCmdUI->Enable(USGDeviceStateID);
		break;
	case ID_RIBBON_StartImaging:
		pCmdUI->Enable(USGDeviceStateID);
		break;
	case ID_RIBBON_ColseImaging:
		pCmdUI->Enable(USGImagingRunModeID);
		break;
	case ID_RIBBON_FreezeImaging:
		pCmdUI->Enable(USGImagingRunModeID);
		break;
    case ID_RIBBON_SaveImaging:
		pCmdUI->Enable(USGFreezingID);
		break;
	}
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnShowpropertywindow32771()
{
	// TODO: 在此添加命令处理程序代码
	//if（m_wndProperties.IsVisible()
	m_wndProperties.ShowWindow(m_wndProperties.IsVisible() ? SW_HIDE : SW_SHOW);
	m_wndProperties.UpdateWindow();  
	RecalcLayout(FALSE);
	//m_wndProperties.ShowWindow( 


}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	
	//----1.时间监视-----------------------
    CString strTime; 
    CMFCRibbonBaseElement * pElement;  
    strTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));  
    pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE5);  
    pElement->SetText(strTime);  
    pElement->Redraw();  
    //----2.启动时自动执行任务---------------------
	if (isLiveFlag == 0)
	{

		OnButtonLoginlive();

	}

	//----3.自动执行心跳任务---------------------
	if (isLiveFlag == 100)
	{
		mLiveCount++;
		if (mLiveCount> 10)
		{
		
			OnBtnHeartBeat(mLiveCount);
			mLiveCount = 0;
		}
		

	}


	/*
	CRect mProgressRect;
	CMFCRibbonBaseElement * pElement2;  
	pElement2 = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE6); 
	mProgressRect=pElement2->GetRect(); 
	m_Progress.SetWindowPos(NULL,mProgressRect.left,mProgressRect.top,mProgressRect.Width(),mProgressRect.Height(),SWP_NOZORDER);     
	m_Progress.StepIt(); 
	pElement2->Redraw(); 
	*/



	CFrameWndEx::OnTimer(nIDEvent);
}

LRESULT CMainFrame::OnMyProcessMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    CRect mProgressRect;
	CMFCRibbonBaseElement * pElement;  
	pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE6); 
	mProgressRect=pElement->GetRect(); 
	m_Progress.SetWindowPos(NULL,mProgressRect.left,mProgressRect.top,mProgressRect.Width(),mProgressRect.Height(),SWP_NOZORDER);     
	//m_Progress.StepIt(); 
	m_Progress.SetPos(int(wParam)); 
	//pElement->Redraw(); 
	//if(wParam==100)	m_Progress.SetPos(100); 
	//pElement->Redraw(); 
	return 0;
}

void CMainFrame::OnPaint()
{
	if (theApp.mFlag == 1)
	{

		//this->SendMessage(WM_CLOSE);
	}
	else
	{

		CPaintDC dc(this); // device context for painting
						   // TODO: 在此处添加消息处理程序代码
						   // 不为绘图消息调用 CFrameWndEx::OnPaint()
		CRect mProgressRect;
		CMFCRibbonBaseElement * pElement;
		pElement = m_wndStatusBar.FindElement(ID_STATUSBAR_PANE6);
		mProgressRect = pElement->GetRect();
		m_Progress.SetWindowPos(NULL, mProgressRect.left, mProgressRect.top, mProgressRect.Width(), mProgressRect.Height(), SWP_NOZORDER);
		m_Progress.SetPos(0);

	}


}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

 	if(isCloseFlag==100)
	{
	   KillTimer(1);
	 //if (pInputBitMapInfo != NULL)delete pInputBitMapInfo;
	 if (pInputBitMapInfo2 != NULL)delete pInputBitMapInfo2;

	if (pMySnapForm != NULL)
	{
		pMySnapForm->DestroyWindow();
		delete pMySnapForm;
	}

	if (pLogoCover != NULL)
	{
		pLogoCover->DestroyWindow(); 
		delete pLogoCover;
	}
	
	if (pInitianlizingText != NULL)
	{
		pInitianlizingText->DestroyWindow();
		delete pInitianlizingText;

	}



	

#ifdef VersionStud 

		if (pAxStudMgrDlg != NULL)
		{
			pAxStudMgrDlg->DestroyWindow();
			delete pAxStudMgrDlg;

	    }
#else
	if (pAccountManager != NULL)
	{
		pAccountManager->DestroyWindow();
		delete pAccountManager;

	}
#endif
	
	CFrameWndEx::OnClose();//基类函数

	}
	else
	{
		if(isLiveFlag==100)
		{
			//OnButtonCloseroom();
			
#ifdef VersionStud 
			OnButtonWatcherquitroom();
#else

			OnButtonClosevirtyroom();
#endif


		}
		else
		{
            //isCloseFlag=100;
			//m_wndOutput.PrintMessage(_T("Start Master Loginout......"));
	        //piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);
			//pUnkSinkLiveRoomHelper->Logout();

			OnButtonClosevirtyroom();
			//isCloseFlag == 100;
		}
		

	}
}


LRESULT CMainFrame::LiveLoginHandler(WPARAM W,LPARAM L)
{
	// TODO: 
     //AfxMessageBox("Hello,World!");
	
	LONG EventCode = W; 
	LONG EventValue=L;
	CString nRetStr;
	nRetStr.Format(_T("EventCode:%d;EventValue:%d"), EventCode, EventValue); 
	m_wndOutput.PrintMessage(nRetStr);


	if (EventCode == LoginLiveRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 1;
			isCloseFlag = 100;
			ShowLogoCover(1);
			//OnButtonCreatevirtyroom();

			
#ifdef VersionStud 
			OnButtonWatcherjoinroom();
#else
			OnButtonCreaterRoomMIS();
#endif
		}
		else
		{
			isLiveFlag = 1;
			isCloseFlag = 100;
			ShowLogoCover(1);
		
			//OnButtonCreatevirtyroom();
			//OnButtonCreaterRoomMIS();
		}



	}
	if (EventCode == LogoutLiveRoomID)
	{
		 //登出账号
		if (EventValue == 0)
		{
			isLiveFlag = 1;
			isCloseFlag = 100;
			ShowLogoCover(1);
			//OnButtonLoginoutlive();
			//OnButtonLogoutMIS();
#ifdef VersionStud 
			OnButtonSlaverquitbyteroom();
#else
			OnButtonMasterQuitRoomMIS();
#endif
			

		}
		else
		{
			
			isCloseFlag = 100;
			//isLiveFlag = 0;
			//ShowLogoCover(1);
			//isCloseFlag = 100;
			//OnButtonLogoutMIS();
			OnButtonMasterQuitRoomMIS();
		}

		/*
		if (AfxMessageBox(_T("师说数字课堂主播已经关闭退房,是否退出系统?"), MB_YESNO) == IDYES)
		{
			this->SendMessage(WM_CLOSE);
		}
		*/
		
		



	}

	if (EventCode == MasterCreateLiveRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 100;
			isCloseFlag = 0;
			ShowLogoCover(1);
			OnMasterJoinRoomMIS(1);
		}
		else
		{
			//isLiveFlag = 100;
			//isCloseFlag = 100;
			ShowLogoCover(1);
			

		}



	}
	if (EventCode == RoomDynamicID)
	{
		if (EventValue == 10)
		{
			//isLiveFlag = 90;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			//OnMasterJoinRoomMIS(1);

		}
		else
		{
			//isLiveFlag = 100;
			//isCloseFlag = 100;
			//ShowLogoCover(1);


		}



	}


	if (EventCode == MasterCloseLiveRoomID)
	{
		if (EventValue == 0)
		{
			//isLiveFlag = 1;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonMasterquitroom2();

		}
		else
		{
			//isLiveFlag = 1;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonMasterquitroom2();

		}



	}

	if (EventCode == MasterQuitLiveRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 90;
			mLiveCount = 0;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonLoginoutlive();

		}
		else
		{
			//isLiveFlag = 1;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonLoginoutlive();

		}



	}


	if (EventCode == SlaverJoinLiveRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 90;
			//isCloseFlag = 100;
			ShowLogoCover(1);
			OnButtonSlaverjoinmis3();
			OnButtonWatcherSendIM();

		}
		else
		{
			isLiveFlag = 90;
			ShowLogoCover(1);
			//isCloseFlag = 100;
			ShowLogoCover(1);


		}


	}
	if (EventCode == SlaverQuitLiveRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 90;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonSlaverquitmis3();

		}
		else
		{
			isLiveFlag = 90;
			//isCloseFlag = 100;
			ShowLogoCover(1);


		}



	}

	/*
	int  nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int  nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	int XPostion = 0;
	int YPostion = 0;
	SetWindowPos(NULL, XPostion, YPostion, nFullWidth, nFullHeight, SWP_NOZORDER);
	UpdateWindow();
	*/
	
	
	/*
	CString nRetStr;
	nRetStr.Format(TEXT("Login Status:%d,Code:%d"),W,L);
	m_wndOutput.PrintMessage(nRetStr);

	if(isCloseFlag==100)
	{
       if(W==20&&L==0)
	   {
	   this->SendMessage(WM_CLOSE);
	   }
       if(W==20&&L>1201)
	  {
	   this->SendMessage(WM_CLOSE);
	  }
	}
	else
	{
	   if(W==20&&L==0)
	   {
	     isCloseFlag=100;
	   }

	}
	
	*/
	
	
	
	if (EventCode == LogoutManagerID)
	{
		//登出MIS侧账号
		if (EventValue == 0)
		{
			isLiveFlag = 1;
			isCloseFlag = 100;
			ShowLogoCover(1);
			//OnButtonLoginoutlive();
			//pAccountManager->Loginout(theApp.m_szUserSig);


		}
		else
		{


			isLiveFlag = 1;
			ShowLogoCover(1);
			isCloseFlag = 100;


		}
		if (AfxMessageBox(_T("师说数字课堂主播已经关闭,是否退出系统?"), MB_YESNO) == IDYES)
		{
			this->SendMessage(WM_CLOSE);
		}

	}
	if (EventCode == MasterCreateRoomID)
	{
		//创建MIS房间号
		if (EventValue == 0)
		{
			//isLiveFlag = 0;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			//OnButtonCreatevirtyroom();
			OnMasterReportRoomMIS(mRoomTitle);


		}
		else
		{


			//isLiveFlag = 0;
			ShowLogoCover(1);
			//isCloseFlag = 100;
			//OnButtonCreatevirtyroom();
			OnMasterReportRoomMIS(mRoomTitle);
		}
		

	}
	if (EventCode == MasterReportRoomID)
	{
		//报告MIS房间信息
		if (EventValue == 0)
		{
			//isLiveFlag = 0;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonCreatevirtyroom();
			


		}
		else
		{


			//isLiveFlag = 0;
			//ShowLogoCover(1);
			//isCloseFlag = 100;
			OnButtonCreatevirtyroom();
			
		}


	}
	if (EventCode == MasterJoinRoomID)
	{
		if (EventValue == 0)
		{
			isLiveFlag = 100;
			//isCloseFlag = 100;
			ShowLogoCover(1);
			

		}
		else
		{
			//isLiveFlag = 100;
			//isCloseFlag = 100;
			ShowLogoCover(1);


		}



	}
	
	if (EventCode == MasterQuitRoomID)
	{
		//主播退出MIS侧房间号
		if (EventValue == 0)
		{
			//isLiveFlag = 0;
			//isCloseFlag = 100;
			//ShowLogoCover(1);
			OnButtonLogoutMIS();


		}
		else
		{


			//isLiveFlag = 0;
			//ShowLogoCover(1);
			//isCloseFlag = 100;
			OnButtonLogoutMIS();

		}


	}

	if (EventCode == SlaverJoinRoomID)
	{
		//进入MIS侧房间号
		if (EventValue == 0)
		{
			isLiveFlag = 100;
			isCloseFlag = 0;
			ShowLogoCover(1);
			//OnButtonLogoutMIS();


		}
		else
		{


			//isLiveFlag = 0;
			ShowLogoCover(1);
			//isCloseFlag = 100;
			//OnButtonLogoutMIS();

		}


	}

	if (EventCode == SlaverQuitRoomID)
	{
		//退出MIS侧房间号
		if (EventValue == 0)
		{
			isLiveFlag = 1;
			isCloseFlag = 100;
			ShowLogoCover(1);
			OnButtonLogoutMIS();


		}
		else
		{

			isLiveFlag = 1;
			ShowLogoCover(1);
			isCloseFlag = 100;
			//OnButtonLogoutMIS();

		}


	}



	return 0; 
}

LRESULT CMainFrame::LiveRoomHandler(WPARAM W,LPARAM L)
{
	// TODO: 
	/*
	CString nRetStr;
	nRetStr.Format(TEXT("LiveRoom Status:%d,Code:%d"),W,L);
	m_wndOutput.PrintMessage(nRetStr);

	if(W==30&&L==0)
	{
	   piLiveRoomMgr->getCameraList(m_cameraList);
	   CString nRetStr;
  	   nRetStr.Format(TEXT("CameraList:%d"),m_cameraList.size());
	   m_wndOutput.PrintMessage(nRetStr);

	   isLiveFlag=100;//建立直播间成功
	}
	
	if(W==40&&L==0)
	{
	   isLiveFlag=0;
	   piLiveRoomMgr->quitRoom(OnMasterQuitRoomSuc,OnMasterQuitRoomErr,this);
	   CString nRetStr;
  	   nRetStr.Format(TEXT("...Start MasterQuitRoom:%d"),0);
	   m_wndOutput.PrintMessage(nRetStr);
	}
	if(W==50&&L==0)
	{
	   
	   //CString nRetStr;
  	   //nRetStr.Format(TEXT("...Start MasterQuitRoom:%d"),0);
	   //m_wndOutput.PrintMessage(nRetStr);
		if(AfxMessageBox("懿达课堂主播已经关闭退房,是否退出帐号?",MB_YESNO)==IDYES)
		{
			isCloseFlag=100;
			m_wndOutput.PrintMessage("...Start Loginout......");
	        piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);
			
			//this->SendMessage(WM_CLOSE);
		}
		else
		{
			m_wndOutput.PrintMessage("...Start Loginout......");
	        piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);

		}

	}

	if(W==60&&L==0)
	{
	  isLiveFlag=100;//观众进入课堂成功
	}

	if(W==70)
	{
	   //观众退出课堂成功
		if(AfxMessageBox("懿达虚拟课堂已经关闭,是否退出?",MB_YESNO)==IDYES)
		{
			isCloseFlag=100;
			m_wndOutput.PrintMessage("...Start Loginout......");
	        piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);
			
			//this->SendMessage(WM_CLOSE);
		}
		else
		{
			m_wndOutput.PrintMessage("...Start Loginout......");
	        piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);

		}
			
	   //CString nRetStr;
  	   //nRetStr.Format(TEXT("WatcherQuitRoom Reply...:%d"),L);
	   //m_wndOutput.PrintMessage(nRetStr);
	}

	if(W==100)
	{	
	   //CString nRetStr;
  	   //nRetStr.Format(TEXT("WatcherJoinRoom Reply...:%d"),L);
	   //m_wndOutput.PrintMessage(nRetStr);
		//人员主动关闭课堂
		if(isLiveFlag==100)
		{
			OnButtonCloseroom();
		}
		else
		{
            isCloseFlag=100;
			m_wndOutput.PrintMessage("...Start Loginout......");
	        piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);

		}
		


	}
	
	if(W==1001)
	{
	   //一般由主播端主动关闭房间引起观众端接收到消息
	    OnButtonQuitroom();

	   //CString nRetStr;
  	   //nRetStr.Format(TEXT("Receive QuitRoom Message...:%d"),0);
	   //m_wndOutput.PrintMessage(nRetStr);
	}


	return 0; 
	*/


   return 0;
	
}

LRESULT CMainFrame::LiveStatusHandler(WPARAM W, LPARAM L)
{
	//AfxMessageBox("Hello,World!");
	//nRetStr.Format(TEXT("Login Status:%d,Code:%d"),W,L);

	//CString nRetStr = (LPCTSTR)L;
	//m_wndOutput.PrintMessage(nRetStr);
	
	
	UINT32 mSize = (UINT32)L;
	//memcpy(&m_CaptureImageBuffer[0], lpBuffer, mSize);//把获得的屏幕|图像视频复制视频全局缓冲区
	//pUnkSinkLiveRoomHelper->GetSample(mSize);
	
	pUnkSinkLiveRoomHelper->mSampleSize = mSize;
	if (W == 0)
	{
		//GetActiveView()->InvalidateRect(NULL, FALSE);
		//图像视频引发绘图事件
		
		
		pMModeAdustCtrlBox->UpDateVideoPreview();//图像视频数据
	}

	if (W == 1)
	{
		//GetActiveView()->InvalidateRect(NULL, FALSE);
		//屏幕视频引发绘图事件
		
		mBModeAdustCtrlBox.UpDateVideoPreview();//屏幕视频数据
		
	}
	




	return 0;
}

LRESULT CMainFrame::LiveStatusHandlerEx(WPARAM W, LPARAM L)
{
	CString PointInforStr;
	CMFCRibbonBaseElement * pElement;
	pElement =m_wndStatusBar.FindElement(ID_STATUSBAR_PANE4);
	//获取该点坐标
	PointInforStr.Format(_T("x=%i,y=%i"), (LONG)W, (LONG)L);
	//在状态栏中显示坐标值
	pElement->SetText(PointInforStr);
	pElement->Redraw();

	return 0;



}

void CMainFrame::LiveCreateRoom()
{
	OnButtonCreateroom();
}
void CMainFrame::LiveCloseRoom()
{
	
	OnButtonCloseroom();

}


void CMainFrame::InitiLiveSDK()
{
	pUnkSinkLiveRoomHelper = theApp.pUnkSinkLiveRoomHelper;
	pUnkSinkLiveRoomHelper->SetHandleWindow(this->GetSafeHwnd());


	//--MySet--------------------------------------------
	//m_nAppId = 1400019352;
	//m_nAccountType = 8970;

	//m_szUserId = "lgj1";
	//m_szUserToken = "bGdqMTE0OTExMzQ3MTIK";
	//m_szUserSig="eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//m_szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";
		
	//piLiveLoginMgr = iLiveLoginMgr::getInstance();
	//piLiveLoginMgr->setForceOfflineCallback(onForceOffline);

	

	//piLiveRoomMgr = iLiveRoomMgr::getInstance();
	///piLiveRoomMgr->setGroupMessageCallBack(OnGropuMessage);
	///piLiveRoomMgr->setC2CMessageCallBack(OnC2CMessage);	

	//piLiveRoomMgr->setLocalVideoCallBack(OnLocalVideo, this);
	//piLiveRoomMgr->setRemoteVideoCallBack(OnRemoteVideo, this);
	
	//piLiveSDK = iLiveSDK::getInstance();
	
	//lenght++;
//CTime time; 
//time= CTime::GetCurrentTime();
//m_RoomID=lenght+8888;//time.GetSecond();

//int width = GetSystemMetrics(SM_CXSCREEN);
//int height = GetSystemMetrics(SM_CYSCREEN);

//piLiveSDK->getTIMManager().set_mode(1);
//int nRet = piLiveSDK->initSdk(m_nAppId, m_nAccountType);
///CString nRetStr;
//nRetStr.Format(TEXT(_T("iLiveSDK init:%d; width:%d; height:%d;RoomID:%d,UserID:%s")), nRet, width, height,m_RoomID,m_szUserId);
//m_wndOutput.PrintMessage(nRetStr);	



}


void CMainFrame::InitMiddleWare()
{

	ShowSnapForm(1);

	//CString nRetStr;	
	//nRetStr.Format(TEXT("Find MainFrame: %d"), this->m_hWnd);
	//m_wndOutput.PrintMessage(nRetStr);

	CString Titlestr = this->GetTitle();
	LONG pmSnaphwnd = (LONG)pMySnapForm->GetSafeHwnd();
	_bstr_t str(Titlestr);
	pUnkSinkLiveRoomHelper->SetPara(this->m_hWnd, str, &pmSnaphwnd);

	//nRetStr.Format(TEXT("Get MainFrame: %d"), pmSnaphwnd);
	//m_wndOutput.PrintMessage(nRetStr);


}


//-----------------------------------------------------
void  CMainFrame::OnButtonLogoutMIS()
{
	
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Salverr Logout MIS:%s,%s"), theApp.m_szUserId, theApp.m_szUserToken);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.Logout();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Logout MIS:%s,%s"), theApp.m_szUserId, theApp.m_szUserToken);
	m_wndOutput.PrintMessage(nRetStr);
	pAccountManager->Loginout();
#endif
	


}
void CMainFrame::OnButtonCreaterRoomMIS()
{
	
#ifdef VersionStud 
	
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Create Room MIS:%s,%s"), theApp.m_szUserId, theApp.m_szUserToken);
	m_wndOutput.PrintMessage(nRetStr);

	pAccountManager->mRestfulQtCOMCtrl.MasterCreateRoom();
#endif
	


}

void CMainFrame::OnButtonMasterQuitRoomMIS()
{
	

#ifndef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Quit Room MIS:%s,%s,%s"), theApp.m_szUserId, theApp.m_szUserToken, theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);

	pAccountManager->mRestfulQtCOMCtrl.MasterQuitRoom();
#endif
}

void CMainFrame::OnMasterReportRoomMIS(CString RoomTitle)
{


	
#ifdef VersionStud 
	
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Report Room MIS:%s"), RoomTitle);
	m_wndOutput.PrintMessage(nRetStr);
	pAccountManager->mRestfulQtCOMCtrl.MasterReportRoom(RoomTitle);
#endif

}

void CMainFrame::OnMasterJoinRoomMIS(int mUserType)
{

#ifndef VersionStud 

	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Join Room MIS:%d"), mUserType);
	m_wndOutput.PrintMessage(nRetStr);
	pAccountManager->mRestfulQtCOMCtrl.MasterJoinRoom(mUserType);
#endif



}
void CMainFrame::OnBtnHeartBeat(int mthumbup)
{
	
	
#ifdef VersionStud 
	
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Heart Beat MIS:%d"), mthumbup);
	m_wndOutput.PrintMessage(nRetStr);
	pAccountManager->mRestfulQtCOMCtrl.MasterKeepLive(mthumbup);
#endif

}



void CMainFrame::OnButtonLoginlive()
{



	CString nRetStr;
#ifdef VersionStud 	
	nRetStr.Format(TEXT("Start Slaver Login:%s,%s"), theApp.m_szUserId, theApp.m_szUserSig);
	

#else
	nRetStr.Format(TEXT("Start Master Login:%s,%s"), theApp.m_szUserId, theApp.m_szUserSig);
	

#endif
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->Login(theApp.m_szUserId, theApp.m_szUserSig);
	InitMiddleWare();

}

void CMainFrame::OnButtonLoginoutlive()
{
	// TODO: 
	//m_wndOutput.PrintMessage("...Start Loginout......");
	//piLiveLoginMgr->iLiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);
	
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Slaver Logout......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->Logout();

#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Matser Logout......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->Logout();
#endif
}

void CMainFrame::OnButtonLoginoutlive2()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Slaver Logout......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->Logout();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Matser Logout......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->Logout();
#endif
	
}



void CMainFrame::OnButtonCreateroom()
{
	CString nRetStr;
	nRetStr.Format(TEXT("Start Matser Create Live Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	m_RoomID = 1000000 + 8888;
	pUnkSinkLiveRoomHelper->MasterCreateRoom(m_RoomID);

}
void CMainFrame::OnButtonCloseroom()
{
	// TODO: 
	ShowLogoCover(0);
	pUnkSinkLiveRoomHelper->StopScreen();
	

	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Close Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->MasterCloseRoom();


}

void CMainFrame::OnButtonJoinroom()
{
	// TODO: 观众进房
	/*
	
	
	ilivesdk::iLiveRoomOption roomOption;
	roomOption.roomId = m_RoomID;
	roomOption.auth_buffer = "";
	roomOption.control_role = Guest;
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//互动直播场景
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.screen_recv_mode = SCREEN_RECV_MODE_SEMI_AUTO_RECV_SCREEN_VIDEO;//半自动模式
	roomOption.m_roomDisconnectListener = OnRoomDisconnect;
	roomOption.m_memberStatusListener = OnMemStatusChange;
	roomOption.m_autoRecvCameraListener =OnSemiAutoRecvCameraVideo;
	roomOption.m_autoRecvScreenListener = OnSemiAutoRecvScreenVideo;
	roomOption.m_autoRecvMediaFileListener =OnSemiAutoRecvMediaFileVideo;
	roomOption.data = this;
	piLiveRoomMgr->joinRoom( roomOption, OniLiveGuestJoinRoomSuc, OniLiveGuestJoinRoomErr, this );
	*/
	m_RoomID = 1000000 + 8888;
	pUnkSinkLiveRoomHelper->WatcherJoinRoom(m_RoomID);


	CString nRetStr;
	nRetStr.Format(TEXT("Start WatcherJoinroom: %d"),0);
	m_wndOutput.PrintMessage(nRetStr);
}

void CMainFrame::OnButtonQuitroom()
{
	  // TODO: 观众退房
	   //piLiveRoomMgr->quitRoom(OnWatcherQuitRoomSuc,OnWatcherQuitRoomErr,this);
	 
	
	
	pUnkSinkLiveRoomHelper->WatcherQuitRoom();
	CString nRetStr;
  	nRetStr.Format(TEXT("Start WatcherQuitRoom:%d"),0);
	m_wndOutput.PrintMessage(nRetStr);

}

void CMainFrame::OnButtonStartvideo()
{
	// TODO: 
	/*
	if (m_cameraList.size()==0)
	{
		 CString nRetStr;
	     nRetStr.Format(TEXT("Openvideoshare: %d"),1);
	     m_wndOutput.PrintMessage(nRetStr);
		
	}
	else
	{
		int nRet = piLiveRoomMgr->openCamera(m_cameraList[0].first);
	    if (nRet==NO_ERR)
	    {

	     CString nRetStr;
	     nRetStr.Format(TEXT("Openvideoshare: %d"),0);
	     m_wndOutput.PrintMessage(nRetStr);
	    }
  	    else
	    {

		    CString nRetStr;
	       nRetStr.Format(TEXT("Openvideoshare: %d"),2);
	       m_wndOutput.PrintMessage(nRetStr);
	   }

	}
	*/
	

	CString nRetStr;
	nRetStr.Format(TEXT("Start Live Room  Video......"));
	m_wndOutput.PrintMessage(nRetStr);

	pUnkSinkLiveRoomHelper->StartVideo();

}

void CMainFrame::OnButtonStartscreen()
{
	// TODO: 
	/*
	int width = GetSystemMetrics ( SM_CXSCREEN ); 
    int height= GetSystemMetrics ( SM_CYSCREEN ); 
	m_x0=0;
	m_y0=0;
	m_x1=1920;//1280;//640;//320;//1280;//width;
	m_y1=1080;//720;//480;//240;//720;//height;
	m_fps=10;

	int M=piLiveRoomMgr->openScreenShare(m_x0,m_y0,m_x1,m_y1,m_fps);

	CString nRetStr;
	nRetStr.Format(TEXT("...Startboard: %d,X1:%d,Y1:%d"),M,m_x1,m_y1);
	m_wndOutput.PrintMessage(nRetStr);
	*/
	

	//updatePushAndRecordStateUI();
}

void CMainFrame::OnButtonClosescreen()
{
	// TODO: 
	//int M=piLiveRoomMgr->closeScreenShare();
	CString nRetStr;
	nRetStr.Format(TEXT("...Closeboard: %d"),0);
	m_wndOutput.PrintMessage(nRetStr);

}

void CMainFrame::OnButtonStopvideo()
{
	// TODO: 
	/*
	int nRet=piLiveRoomMgr->closeCamera();
	 if (nRet==NO_ERR)
	    {

	     CString nRetStr;
	     nRetStr.Format(TEXT("Closevideoshare: %d"),0);
	     m_wndOutput.PrintMessage(nRetStr);
	   }
  	   else
	   {

		    CString nRetStr;
	       nRetStr.Format(TEXT("Closevideoshare: %d"),1);
	       m_wndOutput.PrintMessage(nRetStr);
	  }
	*/
	

	CString nRetStr;
	nRetStr.Format(TEXT("Stop Master  Video......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->StopVideo();
}

void CMainFrame::updatePushAndRecordStateUI()
{

	/*
	if ( piLiveRoomMgr->getCurCameraState())
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("CameraState: %d[true]"),100);
	    m_wndOutput.PrintMessage(nRetStr);
	}
	else
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("CameraState: %d[false]"),200);
	    m_wndOutput.PrintMessage(nRetStr);
	}
	if (piLiveRoomMgr->getExternalCaptureState())
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("ExternalCaptureState: %d[true]"),101);
	    m_wndOutput.PrintMessage(nRetStr);
	}
	else
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("ExternalCaptureState: %d[false]"),201);
	    m_wndOutput.PrintMessage(nRetStr);
	}

	if (piLiveRoomMgr->getScreenShareState() )
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("ScreenShareState: %d[true]"),102);
	    m_wndOutput.PrintMessage(nRetStr);

		


	}
	else
	{
		CString nRetStr;
	    nRetStr.Format(TEXT("ScreenShareState: %d[false]"),202);
	    m_wndOutput.PrintMessage(nRetStr);
	}
	
	*/
	

	



}

void CMainFrame::OnButtonInitvfw()
{
	// TODO: 
	BOOL ResultFlag = FALSE;
	CString nRetStr;
	//--列举安装的所有VFW捕获设备---------------------------------------------------------------------------------------------------------------------------------
	DWORD DeviceIndexList[10];
	TCHAR szDeviceName[80];
	TCHAR szDeviceVersion[80];
	DWORD wIndex;
	int i = 0;
	for (wIndex = 0; wIndex < 10; wIndex++)
	{
		if (capGetDriverDescription(wIndex, szDeviceName, sizeof(szDeviceName), szDeviceVersion, sizeof(szDeviceVersion)))
		{
			// 加入到一个已经安装的设备列表中 
			DeviceIndexList[wIndex] = wIndex;
			i++;
			break;
		}

	}
	if (i == 0 || wIndex == 10)
	{
		AfxMessageBox(_T("初始化Faile:1(没有找到采集设备！)"));
		return;
	}
	//--创建视频采集窗口[隐藏窗口--套间线程]---------------------------------------------------------------------------------------------------------------------------
	//ResultFlag=m_BindSourceWindow.CreateEx(WS_EX_TOPMOST,NULL,_T("Source"),WS_OVERLAPPED|WS_CAPTION,CRect(0,0,352,288),NULL,0);
	// ResultFlag=m_BindSourceWindow.CreateEx(WS_EX_TOPMOST,NULL,_T("Source"),WS_OVERLAPPED|WS_CAPTION,CRect(0,0,0,0),NULL,0);
	////if(!ResultFlag)
	//{
	//	AfxMessageBox(_T("初始化Faile:1"));
	//	return;
	//}
	m_hCaptureWindow = capCreateCaptureWindow(_T("Capture Window"), WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, this->m_hWnd, 0);
	//m_hCaptureWindow = capCreateCaptureWindow(_T("Capture Window"),WS_CHILD|WS_VISIBLE, 0,0,352,288, m_BindSourceWindow.m_hWnd,0);

	// 注册回调函数--------------------------------------------------------------------------------------------------------------------------
	ResultFlag = capSetCallbackOnError(m_hCaptureWindow, (FARPROC)ErrorCallbackProc);
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:2"));
		return;
	}
	ResultFlag = capSetCallbackOnStatus(m_hCaptureWindow, (FARPROC)StatusCallbackProc);
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:3"));
		return;
	}
	ResultFlag = capSetCallbackOnVideoStream(m_hCaptureWindow, (FARPROC)VideoCallbackProc);
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:4"));
		return;
	}

	//--把视频采集窗口连接视频采集设备-------------------------------------------------------------------------------------------------------------------
	ResultFlag = capDriverConnect(m_hCaptureWindow, 0); //DeviceIndexList[0](HWND m_hCaptureWindow, int index);//index : 0--9
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:5"));
		return;
	}

	//--获得捕获驱动器的性能参数--------------------------------
	ResultFlag = capDriverGetCaps(m_hCaptureWindow, &m_CaptureDriverParams, sizeof(CAPDRIVERCAPS));
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:6"));
		return;
	}
	//--是否支持叠加显示
	ResultFlag = m_CaptureDriverParams.fHasOverlay;
	if (!ResultFlag)
	{
		capPreview(m_hCaptureWindow, TRUE);
	}

	//--设置预览速率-----------------------------------------------------------------------------------------------------------------------------------
	ResultFlag = capPreviewRate(m_hCaptureWindow, 1000 / 30);//25
	if (!ResultFlag)
	{
		AfxMessageBox(_T("初始化Faile:7"));
		return;
	}
	//---获得捕获视频帧格式---------------------------------------------------------------------------------------------------------------------------
	DWORD mCapVideoInfoHeadSize;
	mCapVideoInfoHeadSize = capGetVideoFormatSize(m_hCaptureWindow);
	if (mCapVideoInfoHeadSize <= 0)
	{
		AfxMessageBox(_T("初始化Faile:8"));
		return;
	}

	DWORD mReturnValue;
	pInputBitMapInfo2 = (LPBITMAPINFOHEADER)new BYTE[mCapVideoInfoHeadSize];
	mReturnValue = capGetVideoFormat(m_hCaptureWindow, pInputBitMapInfo2, mCapVideoInfoHeadSize);
	if (mReturnValue <= 0)
	{
		AfxMessageBox(_T("初始化Faile:9"));
		return;
	}

	//--设置捕获视频帧格式-------------------------------------------------------
	//pInputBitMapInfo->biBitCount      =24;////24;//32;// pInputBitMapInfo->biBitCount;;//24;
	//pInputBitMapInfo->biCompression   =BI_RGB;//mFCCYV12;//mFCCI420;//mFCCI420;//BI_RGB;//pInputBitMapInfo->biCompression ;//BI_RGB;//mFCCI420
	//pInputBitMapInfo->biSizeImage     =pInputBitMapInfo->biWidth*pInputBitMapInfo->biHeight*3;//pInputBitMapInfo->biWidth*pInputBitMapInfo->biHeight*3/2;//pInputBitMapInfo->biSizeImage;
	//ResultFlag=capSetVideoFormat(m_hCaptureWindow, pInputBitMapInfo, mCapVideoInfoHeadSize);
	//if(!ResultFlag)
	//{
	//AfxMessageBox(_T("初始化Faile:10"));
	//return;
	//}

	memcpy(m_CaptureImageBuffer2, pInputBitMapInfo2, pInputBitMapInfo2->biSize);//把获得的视频输入格式复制全局缓冲区去
	
	//Test
	
	nRetStr.Format(TEXT("视频输入格式 Width:%d,Height:%d,Size:%d"),pInputBitMapInfo2->biWidth,pInputBitMapInfo2->biHeight,pInputBitMapInfo2->biSizeImage);
	m_wndOutput.PrintMessage(nRetStr);

	
	//--设置捕获视频流的控制参数-----------------------------------------------------------------------------------------------------------------------
	CAPTUREPARMS mCaptureVideoParams;
	capCaptureGetSetup(m_hCaptureWindow, &mCaptureVideoParams, sizeof(CAPTUREPARMS));

	mCaptureVideoParams.dwIndexSize = 324000;
	mCaptureVideoParams.fMakeUserHitOKToCapture = !mCaptureVideoParams.fMCIControl;
	mCaptureVideoParams.wPercentDropForError = 100;
	mCaptureVideoParams.wNumVideoRequested = 5;
	mCaptureVideoParams.wChunkGranularity = 0;
	mCaptureVideoParams.fYield = TRUE;
	mCaptureVideoParams.fCaptureAudio = FALSE;
	mCaptureVideoParams.vKeyAbort = 0;
	mCaptureVideoParams.fAbortLeftMouse = mCaptureVideoParams.fAbortRightMouse = FALSE;
	mCaptureVideoParams.dwRequestMicroSecPerFrame = 1000000 / 25;//微秒

	capCaptureSetSetup(m_hCaptureWindow, &mCaptureVideoParams, sizeof(CAPTUREPARMS));
	capSetCallbackOnYield(m_hCaptureWindow, NULL);

	//AfxMessageBox(_T("初始化成功:11！"));
	InitiationID = TRUE;

	//CString nRetStr;
	nRetStr.Format(TEXT("初始化本机摄像头: %d"),0);
	m_wndOutput.PrintMessage(nRetStr);
}

void CMainFrame::OnButtonPreview()
{
	// TODO: 
	bPreview = !bPreview;
	if (bPreview) //TRUE
	{
		capCaptureSequenceNoFile(m_hCaptureWindow);//开始捕获预览
		m_VFW_State = PREVIEW;

	}
	else //FALSE
	{
		capCaptureAbort(m_hCaptureWindow);//中断捕获预览
	}

	CString nRetStr;
	nRetStr.Format(TEXT("开始捕获预览: %d"),0);
	m_wndOutput.PrintMessage(nRetStr);
}

void CMainFrame::OnButtonSetuppara()
{
	// TODO: 

	//-1视频源对话框----------------
	if (m_CaptureDriverParams.fHasDlgVideoSource)
	{
		capDlgVideoSource(m_hCaptureWindow);
	}
	//-2.视频格式对话框--------------
	DWORD mCapVideoInfoHeadSize;
	if (m_CaptureDriverParams.fHasDlgVideoFormat)
	{
		capDlgVideoFormat(m_hCaptureWindow);
		mCapVideoInfoHeadSize = capGetVideoFormatSize(m_hCaptureWindow);
		capGetVideoFormat(m_hCaptureWindow, pInputBitMapInfo2, mCapVideoInfoHeadSize);
	}
	memcpy(m_CaptureImageBuffer2, pInputBitMapInfo2, pInputBitMapInfo2->biSize);
	//-3.视频显示对话框--------------
	capDlgVideoDisplay(m_hCaptureWindow);

	//-4.视频压缩对话框-------------
	capDlgVideoCompression(m_hCaptureWindow);
}

void CMainFrame::OnButtonStartpreview()
{
	// TODO: 
	OnButtonPreview();


}

void CMainFrame::OnButton1Localpreview()
{
	// TODO：
	OnButtonPreview();
}

void CMainFrame::OnButtonlocalscreenshare2()
{
	// TODO: 
	CString nRetStr;
	RECT ViewDisplayRect;
	RECT ViewDisplayRect2;
	GetActiveView()->GetWindowRect(&ViewDisplayRect2);
	nRetStr.Format(TEXT("ViewDisplayRect2: %d,%d,%d,%d"), ViewDisplayRect2.left, ViewDisplayRect2.top, ViewDisplayRect2.right, ViewDisplayRect2.bottom);
	m_wndOutput.PrintMessage(nRetStr);

	GetActiveView()->GetClientRect(&ViewDisplayRect);
	nRetStr.Format(TEXT("ViewDisplayRect: %d,%d,%d,%d"), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom);
	m_wndOutput.PrintMessage(nRetStr);



	GetActiveView()->ClientToScreen(&ViewDisplayRect);
	nRetStr.Format(TEXT("ViewDisplayRectX: %d,%d,%d,%d"), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom);
	m_wndOutput.PrintMessage(nRetStr);


	CPoint MyPoint = this->GetCaretPos();
	nRetStr.Format(TEXT("MyPoint:%d,%d"), MyPoint.x, MyPoint.y);
	m_wndOutput.PrintMessage(nRetStr);



	CPoint S, E;
	S.SetPoint(0, 0);
	ClientToScreen(&S);

	E.SetPoint(ViewDisplayRect.right, ViewDisplayRect.bottom);
	ClientToScreen(&E);




}

void CMainFrame::OnButtonCreatevirtyroom()
{
	// TODO: 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Matser Create Live RoomID:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	long m_RoomID = _ttoi(theApp.m_RoomID);// 1000000 + 8888;(LPCTSTR)
	pUnkSinkLiveRoomHelper->MasterCreateRoom(m_RoomID);


}


void CMainFrame::OnButtonClosevirtyroom()
{
	// TODO: 
	ShowLogoCover(0);


	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Close Live Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->MasterCloseRoom();

}


void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWndEx::OnShowWindow(bShow, nStatus);

	// TODO: 
	if (theApp.mFlag == 1)
	{

		//this->PostMessage(WM_CLOSE);
	}

}


void CMainFrame::OnButtonMasterquitroom()
{
	// TODO: 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Quit Live Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->MasterQuitRoom();


}


void CMainFrame::OnButtonMasterquitroom2()
{
	// TODO:
	CString nRetStr;
	nRetStr.Format(TEXT("Start Master Quit Live Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->MasterQuitRoom();

}

void CMainFrame::OnButtonWatcherSendIM()
{

#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Send IM:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->SendIM(1, 0);
#else

#endif



}

void CMainFrame::OnButtonWatcherjoinroom()
{
	// TODO:

#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Live Room:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	m_RoomID = _ttoi(theApp.m_RoomID); // 1000000 + 8888;
	pUnkSinkLiveRoomHelper->WatcherJoinRoom(m_RoomID);
#else


#endif
	

}


void CMainFrame::OnButtonWatcherquitroom()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Live Room......"));
	m_wndOutput.PrintMessage(nRetStr);
	pUnkSinkLiveRoomHelper->WatcherQuitRoom();
#endif


}




void CMainFrame::OnButtonSlaverjoinmis()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else
	
#endif



}


void CMainFrame::OnButtonSlaverquitmis()
{
	// TODO:
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else

#endif



}


void CMainFrame::OnButtonSlaverjoinmis2()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else

#endif


}


void CMainFrame::OnButtonSlaverquitmis2()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else

#endif



}


void CMainFrame::OnButtonSlaverjoinmis3()
{
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else

#endif

}


void CMainFrame::OnButtonSlaverquitmis3()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else

#endif


}


void CMainFrame::OnButtonSlaverjoinbyteroom()
{
	// TODO:
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
#endif

}


void CMainFrame::OnButtonSlaverquitbyteroom()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
#endif



}


void CMainFrame::OnButtonJoinlogicserver()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverJoinRoom(2, theApp.m_RoomID);
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Join Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
#endif


}


void CMainFrame::OnButton7Quitlogicserver()
{
	// TODO: 
#ifdef VersionStud 
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
	pAxStudMgrDlg->mAxStudMgrDlg.SlaverQuitRoom();
#else
	CString nRetStr;
	nRetStr.Format(TEXT("Start Watcher Test Quit Room  MIS:%s"), theApp.m_RoomID);
	m_wndOutput.PrintMessage(nRetStr);
#endif



}
