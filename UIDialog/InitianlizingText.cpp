// InitianlizingText.cpp : 实现文件
//

#include "..\stdafx.h"
#include "..\VirtyRoom.h"
#include "InitianlizingText.h"
#include "afxdialogex.h"


// InitianlizingText 对话框

IMPLEMENT_DYNAMIC(InitianlizingText, CDialogEx)

InitianlizingText::InitianlizingText(CWnd* pParent /*=NULL*/)
	: CDialogEx(InitianlizingText::IDD, pParent)
{

}

InitianlizingText::~InitianlizingText()
{
}

void InitianlizingText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InitianlizingText, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// InitianlizingText 消息处理程序


void InitianlizingText::OnPaint()
{
	CPaintDC mCurrentDC(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//*
	CRect rect;    
    GetClientRect(&rect);    
	CDC   dcMem;    
    dcMem.CreateCompatibleDC(&mCurrentDC);    
    CBitmap   bmpBackground;    
    bmpBackground.LoadBitmap(IDB_BITMAP2);  //初始化对话框的背景图片  
             
    BITMAP   mbitmapInfor;    
    bmpBackground.GetBitmap(&mbitmapInfor);    
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);    
    mCurrentDC.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,    
    mbitmapInfor.bmWidth,mbitmapInfor.bmHeight,SRCCOPY);  
	dcMem.DeleteDC(); 
	ReleaseDC(&mCurrentDC); 
	//*/


}
