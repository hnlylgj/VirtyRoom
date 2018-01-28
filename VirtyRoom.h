
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// UltrasoundBiopsy.h : UltrasoundBiopsy Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "UIDialog\StartingSplash.h"   
#include "USGCode\USGFW2ForMX.h"

#include "UnkSinkLiveRoomHelper.h"

#include "AxStudMgrDlg.h"
#include "HomePageDlg.h"
// CVirtyRoomApp:
// �йش����ʵ�֣������ UltrasoundBiopsy.cpp
//

//void OnGropuMessage(const TIMMessage& msg);
//void OnC2CMessage(const TIMMessage& msg);

//void onForceOffline();

//void OnLocalVideo(VideoFrame* video_frame, void* custom_data);
//void OnRemoteVideo(VideoFrame* video_frame, void* custom_data);

class CVirtyRoomApp : public CWinAppEx
{
public:
	CVirtyRoomApp();

   //---------------------------
public:
	 int mFlag;
	 HomePageDlg mHomePageDlg;//��¼����������

	 AxStudMgrDlg mAxStudMgrDlg;
	
	//--�ҵĴ���-----------------------------------------------
	CUSGFW2ForMX* mPUSGFW2ForMX; 
	//---------------------------------------------------------
	CUnkSinkLiveRoomHelper * pUnkSinkLiveRoomHelper;

	CAccountManager* pAccountManager;

	// ����
public:
	
// ��������

	//iLiveSDK* piLiveSDK;
	//iLiveLoginMgr* piLiveLoginMgr;
	//iLiveRoomMgr* piLiveRoomMgr;

	CString				m_szServerUrl;
	CString			    m_szUserId;
	CString			    m_szPassWord;
	CString				m_szUserSig;
	CString				m_szUserToken;

	CString				m_RoomID;

	int					m_nAppId;
	int					m_nAccountType;
	//uint32              m_RoomID;

	void LoginLiveRoom();

protected:
	void InitiLiveSDK();


	

private:
	//static void OniLiveLoginSuccess(void* data);
	//static void OniLiveLoginError(int code, const std::string& desc, void* data);

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAppExit();

	afx_msg LRESULT LiveLoginHandler(WPARAM, LPARAM);
};

extern CVirtyRoomApp theApp;
