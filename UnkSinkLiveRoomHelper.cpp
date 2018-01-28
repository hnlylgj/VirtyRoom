#pragma once
#include "StdAfx.h"
#include "MainFrm.h"
#include "UnkSinkLiveRoomHelper.h"


//extern unsigned char m_CaptureImageBuffer[];
//extern LPBITMAPINFOHEADER  pInputBitMapInfo;

#define XDIM 1920			        //图像宽度，预设的足够大 
#define YDIM 1080			        //图像高度，预设的足够大
unsigned char m_CaptureImageBuffer[XDIM*YDIM * 3 + 40];//需显示图像数据区，RGB格式3字节一个像素
//HWND		m_hCaptureWindow;		 //VFW设备窗口句柄
LPBITMAPINFOHEADER    pInputBitMapInfo;   //采集输入格式

//extern CMainFrame* gpMainFrame;

 static HWND HDisplayWindow;
 static UINT CustomMessageID;
 static bool DisplayFlag;
 static const CLSID TargetCLSID = __uuidof(TeniLiveRoomsvc);//关键语句---
 static const IID TargetOBJAPICall = __uuidof(ITeniLiveRoomsvc);//关键语句---
 static const IID TargetSinkSourceCallBack = __uuidof(ITeniLiveRoomsvcDelegate);//关键语句---
//---------------------------------------------------------------------------------------------------------------------

 IMPLEMENT_DYNAMIC(CUnkSinkLiveRoomHelper, CCmdTarget)

CUnkSinkLiveRoomHelper::CUnkSinkLiveRoomHelper(void)
{
//CoInitialize(NULL);
CoInitializeEx(NULL, COINIT_MULTITHREADED);

pITeniLiveRoomsvc = NULL;
m_cRef = 1;
m_dwCookie = 0;
//InitCreateInstance();
DisplayFlag=true;
m_hDrawDIB = NULL;
mSampleSize = 0;
}

CUnkSinkLiveRoomHelper::~CUnkSinkLiveRoomHelper(void)
{
 //DisconnectionEventSource(); 
 pITeniLiveRoomsvc =NULL;
 m_hDrawDIB = NULL;
 //CloseAllCall();
 //pUnknown=NULL;
CoUninitialize();

}
BEGIN_MESSAGE_MAP(CUnkSinkLiveRoomHelper, CCmdTarget)

END_MESSAGE_MAP()



LRESULT  CUnkSinkLiveRoomHelper::LiveLoginHandler(WPARAM W, LPARAM L)
{

	if (W = 1000)
	{

		LoginLiveRoom();
	}

	return 0;

}
void CUnkSinkLiveRoomHelper::LoginLiveRoom()
{
	// TODO: 
	// m_szUserId = "lgj1";
	// std::string szUserId=CT2A(m_szUserId);
	//std::string szUserId = "lgj1";
	//std::string szUserId = "lgj2";
	// std::string  szUserSig = "eJxljl1PwjAYhe-3K5bdarTtaKDe4YC4ZMr4EKY3zdJ18x1j1K4gxfjf1UnCEs-t85yc8*m4rusto8VNKsRuXxturJKee*d6yLu*QKUg46nhvs7*QXlUoCVPcyN1CzGllCDUdSCTtYEczkZVlLhDm2zD24m-eu*ni5lPSVeBooWP45cgnI1klR-qFX3drwezTUDw062Oi4YsmEUPNh6DSMCi3N*K*yJ8G04z8h6rKnweCcnK5NQrpxNhdHK6ivpLOozma3EUE-pho6AzaWArz4cYYn0yQH6HHqRuYFe3AkGYYuKj33jOl-MNpJxc8Q__";
	//std::string  szUserSig = "eJxljl1PgzAARd-5FU2fjbSFoviGUBK2YfYlCb40BMrW6Qp0RVmM-13FJWK8r*fc3PtuAQDgdrG5Lsqy6ZXh5twKCO4ARPDqF7atrHhhuKOrf1AMrdSCF7UReoSYUkoQmjqyEsrIWl6Ml92BTOipeubjxE-d-epi36F-FLkbYcryMFlF4cLcdqJX6WZg9rmfzwKCmfdkH-xy7kVKx-bKyzBbhnWQ7IOldssue4j2x7fHtOnZNrDvUYbWXZIPboRZfLOedaFAfpxPJo08isshHyOHUORN6KvQJ9moUSAIU0wc9B1ofVifunVasA__";

	///piLiveLoginMgr->iLiveLogin(szUserId, szUserSig, OniLiveLoginSuccess, OniLiveLoginError, this);

	Login(m_szUserId, m_szPassWord);

}

//---------------------------------------------------------------------------------------------------------------==
HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::QueryInterface(REFIID riid,	void __RPC_FAR *__RPC_FAR *ppvObject) 
{
	if (( __uuidof(ITeniLiveRoomsvcDelegate) == riid) || (IID_IUnknown == riid))
	{
		*ppvObject = static_cast<ITeniLiveRoomsvcDelegate*> (this);
		AddRef();
		return S_OK;
	}
	*ppvObject = NULL;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::Release()
{
	if (0 == InterlockedDecrement(&m_cRef))
	{
		delete this;
		return 0;
	}
	return m_cRef;
}
//--------------------------------------------------------------------------------------------------------------------
/*
HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::AddCompleteEX(LONG ResultValue)
{

CString MyStrtemp;
MyStrtemp.Format(_T("异步回调定制接口返回值： %d"), ResultValue); //(LPCTSTR)
if (DisplayFlag == true)
{
	SendMessage(HDisplayWindow, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MyStrtemp);
}
else
{
	SendMessage(HDisplayWindow, CustomMessageID, 0, (LPARAM)(LPCTSTR)MyStrtemp);

}

//AfxMessageBox((LPCTSTR)MyStrtemp);
//return S_OK;;
}
*/

HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::CompleteDelegate( LONG EventCode, LONG EventValue, LONG *ReplyValue)
{
	//CString MyStrtemp;
	//LONG mReplyValue = *ReplyValue;
	//MyStrtemp.Format(_T("EventCode:%d;EventValue:%d;ReplyValue:%d"), EventCode, EventValue, mReplyValue); //(LPCTSTR)
	
	LONG mEventCode = EventCode;

	if (mEventCode == 6000)
	{
		//SendMessage(HDisplayWindow, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)MyStrtemp);
		//::SendMessage(HDisplayWindow, WM_LiveLogin, 0, (LPARAM)(LPCTSTR)MyStrtemp);
		//this->GetSample(EventValue);


	}
	else
	{
		//SendMessage(HDisplayWindow, CustomMessageID, 0, (LPARAM)(LPCTSTR)MyStrtemp);
		//::SendMessage(HDisplayWindow, WM_LiveLogin, 0, (LPARAM)(LPCTSTR)MyStrtemp);
		//AfxMessageBox((LPCTSTR)MyStrtemp);
		//*ReplyValue = 188;

	}
	
	::SendMessage(HDisplayWindow, WM_LiveLogin, EventCode, EventValue);

	*ReplyValue = 188;
	return S_OK;;

}
HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::LocalVideoViewDelegate(VARIANT *pData, LONG nCount, LONG Flag, LONG *ReplyValue)
{

	//SAFEARRAY *psa = pData->parray;

	//BYTE *buf= &m_CaptureImageBuffer[0];
	//SafeArrayAccessData(psa, (void **)&buf); //安全指针
											 //直接接作buf即可
	

	//memcpy(&m_CaptureImageBuffer[0], pData, nCount);//内存复制共享缓冲区
	//gpMainFrame->GetActiveView()->InvalidateRect(NULL, FALSE);	//引发绘图事件[即时消息]

	//GetSample(nCount);
	//SafeArrayUnaccessData(psa); //关闭后仍然可读取数据，但不能写入
	//SafeArrayDestroy(psa);

	return S_OK;;
}
HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::RemoteVideoViewDelegate(BYTE *pData, LONG nCount, LONG Flag, LONG *ReplyValue)
{


	//memcpy(&m_CaptureImageBuffer[0], pData, nCount);//直接复制共享缓冲区
	//gpMainFrame->GetActiveView()->InvalidateRect(NULL, FALSE);	//引发绘图事件[即时消息]


	return S_OK;;

}
HRESULT STDMETHODCALLTYPE CUnkSinkLiveRoomHelper::OnStatusNotify(LONG Flagid,BYTE* pbSmaple,BSTR* psSample, BSTR MessageStr,LONG mbSize,LONG* mdResult, BYTE* pbExtra)
{

	

	LONG mReplyValue = *mdResult;

	//----------------------------------------
	//BYTE* pbBuuff;
	//::SafeArrayAccessData(pSA,(void**)&pbBuuff);

	BYTE mb1 = *(&pbSmaple[0]);
	BYTE mb2 = *(&pbSmaple[1]);

	//::SafeArrayUnaccessData(pSA);
	//::SafeArrayDestroy(pSA);
	//-----------------------------------------

	CString MyStrtemp1(*psSample);
	CString MyStrtemp2(MessageStr);


	BYTE mb3 = *(&pbExtra[0]);
	BYTE mb4 = *(&pbExtra[1]);

	CString MyStrtemp;
	MyStrtemp.Format(_T("1:%d；2::%d；3::%d；4::%d；5::%d；6:%d；7:%s；8:%s"), Flagid, mb1, mb2, mb3, mb4, mReplyValue, MyStrtemp1, MyStrtemp2); //(LPCTSTR)


	::SendMessage(HDisplayWindow, WM_LiveLogin, 0, (LPARAM)(LPCTSTR)MyStrtemp);
	//AfxMessageBox((LPCTSTR)MyStrtemp);
	*mdResult = 100088;

	return S_OK;;

}



//--------------------------------------------------------------------------------------------------------------------
int CUnkSinkLiveRoomHelper::ConnectionEventSource() 
{
		
	int RetValue = -1;
	if (m_dwCookie != 0)
	{
		return 0;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtCont;
	if ((pITeniLiveRoomsvc != NULL) && SUCCEEDED(pITeniLiveRoomsvc->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;
		DWORD dwCookie = 0;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(TargetSinkSourceCallBack, &pConnPt)))//关键语句
		{
			ASSERT(pConnPt != NULL);
			HRESULT hResult = pConnPt->Advise(this, &dwCookie);//关键语句---
			if (SUCCEEDED(hResult))
			{
				m_dwCookie = dwCookie;
				RetValue = 0;//成功连接到事件源接口！
			}
			else
			{
				RetValue =-1;//未成功连接到事件源接口！
			}
		
			pConnPt->Release();
		}

		pConnPtCont->Release();
		//m_dwCookie = dwCookie;
	}
	return RetValue;
	
	//return 0;

}

int CUnkSinkLiveRoomHelper::DisconnectionEventSource() 
{
	
	int RetValue = -1;
	if (m_dwCookie == 0)
	{
		return 0;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((pITeniLiveRoomsvc != NULL) && SUCCEEDED(pITeniLiveRoomsvc->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(TargetSinkSourceCallBack, &pConnPt)))//关键语句---
		{
			ASSERT(pConnPt != NULL);
			HRESULT hResult = pConnPt->Unadvise(m_dwCookie);
			pConnPt->Release();
			m_dwCookie = 0;
			RetValue = 0;
		}

		pConnPtCont->Release();
	}
	return RetValue;
	//return 0;

}


void CUnkSinkLiveRoomHelper::InitiShareMemory()
{
	//CString Titlestr = this->GetTitle();
	mhShareMemory = OpenFileMapping(FILE_MAP_READ, false, _T("LiveRoomSharedMemory"));
	if (NULL == mhShareMemory)
	{

		DWORD ldwError = GetLastError();
		//CString nRetStr;
		//nRetStr.Format(TEXT("[客户端]%s InitiShareMemory unsuccessfully:%d"), Titlestr, ldwError);
		//m_wndOutput.PrintMessage(nRetStr);

		return;
	}
	lpBuffer = (BYTE*)MapViewOfFile(mhShareMemory, FILE_MAP_READ, 0, 0, XDIM*YDIM * 3 + 40);
	if (NULL == lpBuffer)
	{

		//CString nRetStr;
		//nRetStr.Format(TEXT("[客户端]%s InitiShareMemory unsuccessfully:%d"), Titlestr, 0);
		//m_wndOutput.PrintMessage(nRetStr);

	}
	else
	{

		//CString nRetStr;
		//nRetStr.Format(TEXT("[客户端]%s InitiShareMemory successfully:%d"), Titlestr, XDIM*YDIM * 3 + 40);
		//m_wndOutput.PrintMessage(nRetStr);


	}
}



 HRESULT CUnkSinkLiveRoomHelper:: InitCreateInstance()
 {

	 HRESULT hr;
	 hr = CoCreateInstance(TargetCLSID, NULL, CLSCTX_LOCAL_SERVER, TargetOBJAPICall, (void **)&pITeniLiveRoomsvc);
	 if (hr == S_OK)
	 {
		 int nRET = ConnectionEventSource();
		 if (nRET == 0)
		 {


			 m_hDrawDIB = DrawDibOpen();

			 InitiShareMemory();

			 return S_OK;

		 }
		 else
		 {
			
			 return S_FALSE;
		 }
	 }
	 else
	 {
		 return S_FALSE;
	 }
	
     
	
 }
 void CUnkSinkLiveRoomHelper::CloseAllCall()
 {
	
	 DisconnectionEventSource();
	 if (pITeniLiveRoomsvc != NULL)
	 {

		 pITeniLiveRoomsvc->Release();
	 }

	 DrawDibClose(m_hDrawDIB);

	 if (lpBuffer != NULL)
	 UnmapViewOfFile(lpBuffer);

 }
 void CUnkSinkLiveRoomHelper::OnRender(CWnd* pwnd, CDC* pDC)
 {
	 if(mSampleSize!=0)
	 GetSample(mSampleSize);//先复制

	 pInputBitMapInfo = (LPBITMAPINFOHEADER)m_CaptureImageBuffer;
	 RECT ViewDisplayRect;
	 pwnd->GetClientRect(&ViewDisplayRect);
	 int w = pInputBitMapInfo->biWidth;
	 int h = pInputBitMapInfo->biHeight;

	 //DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, ViewDisplayRect.right, ViewDisplayRect.bottom, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0, 0, -1, -1, 0);

	 //DrawDibDraw(m_hDrawDIB,pDC->GetSafeHdc(),ViewDisplayRect.left,ViewDisplayRect.top,	ViewDisplayRect.right,	ViewDisplayRect.bottom,(LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40],0,0, -1,-1,0);

	 //DrawDibDraw(m_hDrawDIB, pDC->GetSafeHdc(), ViewDisplayRect.left, ViewDisplayRect.top, w, h, (LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40], 0, 0, w, h, 0);

	 DrawDibDraw(m_hDrawDIB,pDC->GetSafeHdc(),ViewDisplayRect.left,ViewDisplayRect.top,	ViewDisplayRect.right,	ViewDisplayRect.bottom,(LPBITMAPINFOHEADER)m_CaptureImageBuffer, &m_CaptureImageBuffer[40],0,0, w,h,0);

	  mSampleSize = 0;//渲染完成后清零


 }

 void CUnkSinkLiveRoomHelper::GetSample(LONG mSize)
 {
	 if(lpBuffer!=NULL)
	 memcpy(&m_CaptureImageBuffer[0], lpBuffer, mSize);//把获得的图像视频复制视频全局缓冲区
	 /*
	 if (pITeniLiveRoomsvc != NULL)
	 {
		 BYTE* pBuffer = new BYTE;// new BYTE[mSize];
		 for (long i = 0; i < mSize; i++)
		 {

			 //BYTE* pBuffer = new BYTE;// new BYTE[mSize];
			 HRESULT hr;
			 hr = pITeniLiveRoomsvc->GetSample(0, i, pBuffer);
			 //if (pBuffer != NULL)
			 //{
				 //CoTaskMemFree(pBuffer);//负责释放！
				 //memcpy(&m_CaptureImageBuffer[i], pBuffer, 1);
				 m_CaptureImageBuffer[i]=*pBuffer;

			 //}
			

			 if (hr == S_OK)
			 {
				 //BYTE mb1 = *(&pBuffer[0]);
				 //BYTE mb2 = *(&pBuffer[1]);
				 //CString MyStrtemp;
				 //MyStrtemp.Format(_T("1::%d；2::%d"), mb1, mb2); //(LPCTSTR)
				 //::SendMessage(HDisplayWindow, WM_LiveLogin, 0, (LPARAM)(LPCTSTR)MyStrtemp);
				 //--直接复制共享缓冲区
				 //memcpy(&m_CaptureImageBuffer[i], pBuffer, 1);				
				 //gpMainFrame->GetActiveView()->InvalidateRect(NULL, FALSE);//引发绘图事件[即时消息]

			 }
			 else
			 {

				 //CString MyStrtemp;
				 //MyStrtemp.Format(_T("pBuffer Len: %d"), mSize);
				 //::SendMessage(HDisplayWindow, WM_LiveLogin, 0, (LPARAM)(LPCTSTR)MyStrtemp);
			 }

		 }
		
		gpMainFrame->GetActiveView()->InvalidateRect(NULL, FALSE);//引发绘图事件[即时消息]
		
		delete pBuffer;

		 /*
		 if (pBuffer!=NULL)
		 {
		 CoTaskMemFree(pBuffer);//负责释放！

		 }
		
	   }
	 */
	 
	 

 }
  
 void CUnkSinkLiveRoomHelper::Login(CString userid, CString usersig)
{
	 _bstr_t user(userid); // ::SysAllocString(L"lgj1lgj1lgj1lgj");
	 _bstr_t sig(usersig);// = ;// ::SysAllocString(L"qwertttyuioojhfdffghhjjkklmdxssszwerrrtlgkjjjvsssdwerr");

	 if (pITeniLiveRoomsvc != NULL)
	 {

		 pITeniLiveRoomsvc->Login(user, sig);
	 }

}
void CUnkSinkLiveRoomHelper::Logout()
{
	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->Loginout();

	}


}

void CUnkSinkLiveRoomHelper::SetHandleWindow(HWND InHWindow)
{
  HDisplayWindow=InHWindow;
  DisplayFlag=true;

  


  
}

void CUnkSinkLiveRoomHelper::SetPara(HWND InHWindow, BSTR TitlStr, LONG * IPPARA)
{
	HDisplayWindow = InHWindow;
	if (pITeniLiveRoomsvc != NULL)
	{
		_bstr_t ALLstr(_T("酷炫互动直播"));

		LONG NM = (LONG)InHWindow;
		pITeniLiveRoomsvc->SetPara(NM, ALLstr,IPPARA);

	}



}
void CUnkSinkLiveRoomHelper::SetCustomMessage(UINT InMessageID)
{
  DisplayFlag=false;
  CustomMessageID=InMessageID;
 
}



void CUnkSinkLiveRoomHelper::SendIM(LONG Flagid, LONG TypeID)
{


	if (pITeniLiveRoomsvc != NULL)
	{
		_bstr_t ALLstr(_T("酷炫互动直播"));
		pITeniLiveRoomsvc->SendIM(Flagid, TypeID, ALLstr);

	}

}

void CUnkSinkLiveRoomHelper::MasterCreateRoom(long RoomID)
{

	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->MasterCreateRoom(RoomID);

	}

}
void CUnkSinkLiveRoomHelper::MasterCloseRoom()
{

	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->MasterCloseRoom();

	}



}


void CUnkSinkLiveRoomHelper::WatcherJoinRoom(long RoomID)
{



	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->WatcherJoinRoom(RoomID);

	}

}

void CUnkSinkLiveRoomHelper::WatcherQuitRoom()
{

	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->WatcherQuitRoom();

	}
}


void CUnkSinkLiveRoomHelper::MasterQuitRoom()
{
	if (pITeniLiveRoomsvc != NULL)
	{

		pITeniLiveRoomsvc->MasterQuitRoom();

	}

}

void CUnkSinkLiveRoomHelper::StartVideo()
{

	if (pITeniLiveRoomsvc != NULL)
	{
		pITeniLiveRoomsvc->VideoManager(20, 0, 0, 0, 0, 0, 0);
	}

}
void CUnkSinkLiveRoomHelper::StopVideo()
{

	if (pITeniLiveRoomsvc != NULL)
	{
		pITeniLiveRoomsvc->VideoManager(20, 1, 0, 0, 0, 0, 0);
	}
}

HRESULT CUnkSinkLiveRoomHelper::StartScreen(LONG X1, LONG Y1, LONG X2, LONG Y2, LONG FPS)
{
	HRESULT hr;
	hr = S_FALSE;
	if (pITeniLiveRoomsvc != NULL)
	{
		hr = pITeniLiveRoomsvc->VideoManager(10, 0, X1,Y1, X2, Y2, 10);
	}
	return hr;


}

HRESULT CUnkSinkLiveRoomHelper::ChangeScreen(LONG X1, LONG Y1, LONG X2, LONG Y2, LONG FPS)
{

	HRESULT hr;
	hr = S_FALSE;
	if (pITeniLiveRoomsvc != NULL)
	{
		hr = pITeniLiveRoomsvc->VideoManager(10, 1, X1, Y1, X2, Y2, 10);
	}
	return hr;

}
void CUnkSinkLiveRoomHelper::StopScreen()
{
	if (pITeniLiveRoomsvc != NULL)
	{
		pITeniLiveRoomsvc->VideoManager(10, 2, 0, 0, 0, 0, 0);
	}

}
