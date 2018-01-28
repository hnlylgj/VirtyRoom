// LoginingMessageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "LoginingMessageDlg.h"
#include "afxdialogex.h"

//extern HomePageDlg* gpHomePageDlg;
// LoginingMessageDlg 对话框

IMPLEMENT_DYNAMIC(LoginingMessageDlg, CDialogEx)

LoginingMessageDlg::LoginingMessageDlg(CWnd* pParent /*=NULL*/)	: CDialogEx(IDD_DIALOG_LoginWaiting, pParent)
{
	pParentWnd = pParent;

}

LoginingMessageDlg::~LoginingMessageDlg()
{
}

void LoginingMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDOK, m_YesNo);
}


void  LoginingMessageDlg::DoLoginUpdateUI(CString STR,UINT FLAG)
{

	CStatic* pUiCtrl;
	pUiCtrl = (CStatic*)GetDlgItem(IDC_STATIC_LoginingMessage);
	pUiCtrl->SetWindowText(STR);

	//if(FLAG>0)
	//m_YesNo.ShowWindow(SW_NORMAL);
	//else
	//m_YesNo.ShowWindow(SW_HIDE);//SW_HIDE


	
}


BEGIN_MESSAGE_MAP(LoginingMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginingMessageDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// LoginingMessageDlg 消息处理程序


void LoginingMessageDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	pParentWnd->PostMessage(WM_LiveLogin, 1000, 3);

	CDialogEx::OnOK();
}


void LoginingMessageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不绘图消息调用 CDialogEx::OnPaint()
	RECT ViewDisplayRect;
	GetClientRect(&ViewDisplayRect);
	dc.FillSolidRect(&ViewDisplayRect, RGB(128, 138, 135));//修改背景色128,138,135



}


HBRUSH LoginingMessageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)//对话框颜色  
		return hbr;//m_brush;//返会默认刷子    
	if (nCtlColor == CTLCOLOR_STATIC&&pWnd->GetDlgCtrlID() == IDC_LoginingMessage_STATIC)//静态文本颜色，并且指定控件ID号  
	{
		pDC->SetTextColor(RGB(255, 255, 0));
		//->SetBkColor(RGB(191, 219, 255));//静态控件的背景颜色设置，这里设置于背景颜色一致，则可以免设置透明  
		pDC->SetBkMode(TRANSPARENT);//模式设置透明的话，则忽略静态控件的背景颜色设置，与对话框颜色融合  
		hbr = (HBRUSH)m_brush;
	}
	if (nCtlColor == CTLCOLOR_EDIT)//文本编辑框颜色  
	{
		//pDC->SetTextColor(RGB(0, 0, 255));
		//pDC->SetBkColor(RGB(191,219,255));  //静态控件的背景颜色设置  
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)m_brush;
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


BOOL LoginingMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_brush.CreateSolidBrush(RGB(128, 138, 135)); // 生成一刷子：0, 255, 0
	
	m_Font.CreatePointFont(160, _T("宋体"), NULL);
	CStatic *m_Static = (CStatic *)GetDlgItem(IDC_STATIC_LoginingMessage);
	m_Static->SetFont(&m_Font, FALSE);


	//m_YesNo.ShowWindow(SW_HIDE); //SW_NORMAL
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
