// BModeCtrlBox.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "BModeCtrlBox.h"


// CBModeCtrlBox

IMPLEMENT_DYNAMIC(CBModeCtrlBox, CDockablePane)

CBModeCtrlBox::CBModeCtrlBox()
{
   pBModeCtrlFormView=NULL;
   pMModeCtrlFormView=NULL;
   FormViewID=1;
   pBModeCtrlFormView = (CBModeCtrlFormView*)(RUNTIME_CLASS(CBModeCtrlFormView)->CreateObject());
}

CBModeCtrlBox::CBModeCtrlBox(int nFormViewID)
{
   pBModeCtrlFormView=NULL;
   pMModeCtrlFormView=NULL;
	FormViewID=nFormViewID;
	switch(FormViewID)
	{
	case 1:
		 pBModeCtrlFormView = (CBModeCtrlFormView*)(RUNTIME_CLASS(CBModeCtrlFormView)->CreateObject());break;
     case 2:
		 pMModeCtrlFormView = (CMModeCtrlFormVIEW*)(RUNTIME_CLASS(CMModeCtrlFormVIEW)->CreateObject());break;

	}
 
}

CBModeCtrlBox::~CBModeCtrlBox()
{
}


BEGIN_MESSAGE_MAP(CBModeCtrlBox, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CBModeCtrlBox::UpDateVideoPreview()
{
	
	if(FormViewID==1&&pBModeCtrlFormView!=NULL)
	{
			pBModeCtrlFormView->InvalidateRect(NULL, FALSE);	//引发绘图事件[即时消息]
	}
	else
	{
       if(FormViewID==2&&pMModeCtrlFormView!=NULL)
		 {
		   pMModeCtrlFormView->InvalidateRect(NULL, FALSE);	//引发绘图事件[即时消息]
	     }
	}
	

}

// CBModeCtrlBox 消息处理程序




int CBModeCtrlBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	RECT rect;
    GetClientRect(&rect);
    //pBModeCtrlFormView->Create(NULL, NULL, WS_CHILD|WS_VISIBLE, rect, this, 0, NULL);
	switch(FormViewID)
	{
	case 1:
		{
		  pBModeCtrlFormView->Create(NULL, NULL, WS_CHILD|WS_VISIBLE, rect, this, 0, NULL);
		}
		break;
	case 2:
		 pMModeCtrlFormView->Create(NULL, NULL, WS_CHILD|WS_VISIBLE, rect, this, 0, NULL);
		break;

	}
	return 0;
}


void CBModeCtrlBox::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	 if (GetSafeHwnd() == NULL)
	 {
	     return;
	 }
	 //if( pBModeCtrlFormView->GetSafeHwnd()!=NULL)
	 switch(FormViewID)
	{
	case 1:
		{
          if( pBModeCtrlFormView->GetSafeHwnd()!=NULL)
	      {
		    CRect rect;
		    GetClientRect(rect);
		    pBModeCtrlFormView->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		   }
		 
		}
		break;
	case 2:
		 if( pMModeCtrlFormView->GetSafeHwnd()!=NULL)
	      {
		    CRect rect;
		    GetClientRect(rect);
		    pMModeCtrlFormView->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		   }
		break;

	}
	 
}
