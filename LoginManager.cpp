// LoginManager.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "LoginManager.h"
#include "afxdialogex.h"
#include "MainFrm.h"


//extern HomePageDlg* gpHomePageDlg;
//extern CMainFrame* gpMainFrame;

// LoginManager 对话框

IMPLEMENT_DYNAMIC(LoginManager, CDialogEx)

LoginManager::LoginManager(CWnd* pParent /*=NULL*/)	: CDialogEx(IDD_LOGINMANAGER, pParent)
{
	pParentWnd = pParent;
}

LoginManager::~LoginManager()
{

}

void LoginManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AccountID, m_AccountID);
	DDX_Control(pDX, IDC_EDIT_PassWord, m_PassWord);
}
BOOL LoginManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString AccountID = _T("lgj1");//张大仙
	CString PassWord = _T("123456");//●●●●●●
	CEdit* pee;

	pee = (CEdit*)GetDlgItem(IDC_EDIT_AccountID);
	pee->SetWindowText(AccountID);
	pee = (CEdit*)GetDlgItem(IDC_EDIT_PassWord);
	pee->SetWindowText(PassWord);

	m_brush.CreateSolidBrush(RGB(49, 69, 100)); // 生成一刷子：0, 255, 0

	//m_Font.CreateFont(11, 0, 0, 0, 100, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("宋体"));
	m_Font.CreatePointFont(160, _T("宋体"), NULL);
	CStatic *m_Static = (CStatic *)GetDlgItem(IDC_STATIC_LoginName);
	m_Static->SetFont(&m_Font, FALSE);

	m_Static = (CStatic *)GetDlgItem(IDC_STATIC_PassWord);
	m_Static->SetFont(&m_Font, FALSE);


	m_Font.CreatePointFont(140, _T("宋体"), NULL);
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT_AccountID);
	m_Edit->SetFont(&m_Font, FALSE);

	m_Edit = (CEdit *)GetDlgItem(IDC_EDIT_PassWord);
	m_Edit->SetFont(&m_Font, FALSE);

	return TRUE;


}

BEGIN_MESSAGE_MAP(LoginManager, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &LoginManager::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &LoginManager::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// LoginManager 消息处理程序


void LoginManager::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:
	pParentWnd->PostMessage(WM_LiveLogin,100,0);
	
	//gpHomePageDlg->FinallyFree();

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void LoginManager::OnPaint()
{
	CPaintDC dc(this); 
	// TODO: 
	RECT ViewDisplayRect;
	GetClientRect(&ViewDisplayRect);
	dc.FillSolidRect(&ViewDisplayRect, RGB(49, 69, 100));//修改背景色
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void LoginManager::OnBnClickedOk()
{
	// TODO: 启动登录操作

	//gpHomePageDlg->FinallyFree();
	//gpHomePageDlg->PostMessage(WM_LiveLogin, 100, 0);
	//pParentWnd->PostMessage(WM_LiveLogin, 1000, 1);

	m_AccountID.GetWindowText(theApp.m_szUserId);
	m_PassWord.GetWindowText(theApp.m_szPassWord);

	// gpHomePageDlg->LoginLiveRoom();
	//theApp.pUnkSinkLiveRoomHelper->Login(theApp.m_szUserId, theApp.m_szPassWord);
	pParentWnd->PostMessage(WM_LiveLogin, 10001, 1);

	//CDialogEx::OnOK();
}

void LoginManager::OnBnClickedCancel()
{
	// TODO: 
	//gpHomePageDlg->FinallyFree();
	//gpHomePageDlg->PostMessage(WM_LiveLogin, 100, 0);

	pParentWnd->PostMessage(WM_LiveLogin, 10002, 0);//直接退出系统
	//gpMainFrame->PostMessage(WM_LiveLogin, 1000, 2);//直接退出系统
	//gpMainFrame->PostMessage(WM_LiveRoom, 100, 0);

	//CDialogEx::OnCancel();
}




HBRUSH LoginManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)//对话框颜色  
		return hbr;//m_brush;//返会默认刷子    
	if (nCtlColor == CTLCOLOR_STATIC)//静态文本颜色  
	{
		//pDC->SetTextColor(RGB(255, 0, 0));
		//->SetBkColor(RGB(191, 219, 255));//静态控件的背景颜色设置，这里设置于背景颜色一致，则可以免设置透明  
		pDC->SetBkMode(TRANSPARENT);//模式设置透明的话，则忽略静态控件的背景颜色设置，与对话框颜色融合  
		hbr = (HBRUSH)m_brush;
	}
	if (nCtlColor == CTLCOLOR_EDIT)//文本编辑框颜色  
	{
		pDC->SetTextColor(RGB(0,0, 0));
		pDC->SetBkColor(RGB(191,219,255));//静态控件的背景颜色设置  
		
		//pDC->SetBkMode(TRANSPARENT);
		//hbr = (HBRUSH)m_brush;
	}

	if (nCtlColor == CTLCOLOR_BTN)//按钮颜色  
	{
		//pDC->SetTextColor(RGB(0, 0, 255));
		//pDC->SetBkColor(RGB(191,219,255));  //静态控件的背景颜色设置  
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_brush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
