// FirstPageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "FirstPageDlg.h"
#include "afxdialogex.h"


// FirstPageDlg 对话框

IMPLEMENT_DYNAMIC(FirstPageDlg, CDialogEx)

FirstPageDlg::FirstPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIRSTPAGEDLG, pParent)
{

}

FirstPageDlg::~FirstPageDlg()
{
}

void FirstPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FirstPageDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL FirstPageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect mRect;
	GetClientRect(&mRect);

	ShowWindow(SW_SHOWMAXIMIZED); //全屏显示

	return TRUE;


}


// FirstPageDlg 消息处理程序


void FirstPageDlg::OnPaint()
{
	CPaintDC mCurrentDC(this);  
					   // TODO: 在此处添加消息处理程序代码
					   // 不绘图消息调用 CDialogEx::OnPaint()

	CRect mClientRect;
	GetClientRect(&mClientRect);
	CDC   mMemDC;
	mMemDC.CreateCompatibleDC(&mCurrentDC);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP4);  //对话框的背景图片  

	BITMAP   mbitmapInfor;
	bmpBackground.GetBitmap(&mbitmapInfor);
	CBitmap   *pbmpOld = mMemDC.SelectObject(&bmpBackground);
	mCurrentDC.StretchBlt(0, 0, mClientRect.Width(), mClientRect.Height(), &mMemDC, 0, 0, mbitmapInfor.bmWidth, mbitmapInfor.bmHeight, SRCCOPY);
	mMemDC.DeleteDC();
	//新加的语句
	this->ReleaseDC(&mCurrentDC);

}
