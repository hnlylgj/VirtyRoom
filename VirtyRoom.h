
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// UltrasoundBiopsy.h : UltrasoundBiopsy 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "UIDialog\StartingSplash.h"   
#include "USGCode\USGFW2ForMX.h"

#include "UnkSinkLiveRoomHelper.h"

#include "AxStudMgrDlg.h"
#include "HomePageDlg.h"
// CVirtyRoomApp:
// 有关此类的实现，请参阅 UltrasoundBiopsy.cpp
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
	 HomePageDlg mHomePageDlg;//登录控制主窗口

	 AxStudMgrDlg mAxStudMgrDlg;
	
	//--我的代码-----------------------------------------------
	CUSGFW2ForMX* mPUSGFW2ForMX; 
	//---------------------------------------------------------
	CUnkSinkLiveRoomHelper * pUnkSinkLiveRoomHelper;

	CAccountManager* pAccountManager;

	// 特性
public:
	
// 变量定义

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

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
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
