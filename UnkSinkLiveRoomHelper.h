#pragma once
#include <vfw.h>
//#include "LGJLiveRoomComSVC.c"
#include "LGJLiveRoomComSVC.h"
//#import "LGJLiveRoomComSVC.tlb"

class CUnkSinkLiveRoomHelper:public ITeniLiveRoomsvcDelegate, public CCmdTarget
{

	DECLARE_DYNAMIC(CUnkSinkLiveRoomHelper)


public:
	CUnkSinkLiveRoomHelper(void);
	virtual ~CUnkSinkLiveRoomHelper(void);


private:
	LONG			m_cRef;              // reference count
	HANDLE			mEventSynchHandle;   // event handle
	HRESULT			mhAsynchStateResult; // HRESULT during async operations
	long            RerurnValue;
	//----------------------------------------
    //IUnknown *pUnknown;
    //LPDISPATCH pDispatch;
	ITeniLiveRoomsvc *pITeniLiveRoomsvc;

	//CComPtr<ITeniLiveRoomsvc> PTen;//÷«ƒ‹÷∏’Î
	

//public:
	DWORD    m_dwCookie;

	HDRAWDIB m_hDrawDIB;

	HANDLE mhShareMemory; 
	BYTE* lpBuffer;

	void InitiShareMemory();


	int ConnectionEventSource();
	int DisconnectionEventSource();

public:
	CString				m_szServerUrl;
	CString			    m_szUserId;
	CString			    m_szPassWord;
	CString				m_szUserSig;
	CString				m_szUserToken;


	LONG mSampleSize;

	// --- IUnknown methods --- 
protected:
	HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject ); 
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	virtual HRESULT STDMETHODCALLTYPE CompleteDelegate( LONG EventCode,LONG EventValue,LONG *ReplyValue);
	virtual HRESULT STDMETHODCALLTYPE LocalVideoViewDelegate(VARIANT *pData, LONG nCount, LONG Flag,LONG *ReplyValue);
	virtual HRESULT STDMETHODCALLTYPE RemoteVideoViewDelegate( BYTE *pData, LONG nCount, LONG Flag,LONG *ReplyValue);
	virtual HRESULT STDMETHODCALLTYPE OnStatusNotify(LONG Flagid,/*[in, out]*/BYTE* pbSmaple, /*[in, out]*/ BSTR* psSample, /*[in]*/ BSTR MessageStr, /*[in]*/ LONG mbSize,/* [in, out]*/ LONG* mdResult,/* [in] */BYTE* pbExtra);

public:
   HRESULT InitCreateInstance();
   void CloseAllCall();

   void Login(CString userid,CString usersig);
   void Logout();

   void MasterCreateRoom(long RoomID);
   void MasterCloseRoom();
   void MasterQuitRoom();


   void WatcherJoinRoom(long RoomID);

   void WatcherQuitRoom();

   void StartVideo();
   HRESULT StartScreen(LONG X1, LONG Y1, LONG X2, LONG Y2, LONG FPS);
   HRESULT ChangeScreen(LONG X1, LONG Y1, LONG X2, LONG Y2, LONG FPS);
   void StopScreen();
   void StopVideo();  

   void SetHandleWindow(HWND InHWindow);
   void SetCustomMessage(UINT InMessageID);

   void GetSample(LONG mSize);
   void OnRender(CWnd* pwnd,CDC* pDC);
   void SetPara(HWND InHWindow,BSTR TitlStr,LONG * IPPARA);


   void SendIM(LONG Flagid, LONG TypeID);

protected:
	DECLARE_MESSAGE_MAP()


	void LoginLiveRoom();
	afx_msg LRESULT LiveLoginHandler(WPARAM, LPARAM);

};
