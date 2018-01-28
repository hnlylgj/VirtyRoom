// WaitingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "..\VirtyRoom.h"
#include "WaitingDlg.h"
#include "afxdialogex.h"


// WaitingDlg 对话框

IMPLEMENT_DYNAMIC(WaitingDlg, CDialogEx)

WaitingDlg::WaitingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WaitingDlg::IDD, pParent)
	, mWaitingTextString(_T(""))
{

}

WaitingDlg::~WaitingDlg()
{
}

void WaitingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WaitingText_STATIC, mWaitingTextString);
}


BEGIN_MESSAGE_MAP(WaitingDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// WaitingDlg 消息处理程序


void WaitingDlg::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect mClientRect;    
    GetClientRect(&mClientRect);    
	CDC   mMemDC;    
    mMemDC.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   mWaitingDlgBackground;    
    mWaitingDlgBackground.LoadBitmap(IDB_BITMAP2);  //等待对话框的背景图片  
                        
    BITMAP   mbitmapInfor;    
    mWaitingDlgBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=mMemDC.SelectObject(&mWaitingDlgBackground);    
    mCurrentDC.StretchBlt(0,0,mClientRect.Width(),mClientRect.Height(),&mMemDC,0,0,    
    mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	mMemDC.DeleteDC();
	ReleaseDC(&mCurrentDC);

}
