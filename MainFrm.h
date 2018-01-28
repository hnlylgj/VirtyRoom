
// ��Ȩ����(C) Maxenmed  Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "UIDialog\LogoCover.h" 
#include "UIDialog\InitianlizingText.h"
#include "MyPrivateStatusBar.h"
#include "BModeCtrlBox.h"
#include "vfw.h"
#include "SnapForm.h"

//--------vfw-----------------



LRESULT CALLBACK EXPORT ErrorCallbackProc(HWND hWnd, int nErrID, LPSTR lpErrorText);
LRESULT FAR PASCAL StatusCallbackProc(HWND hWnd, int nID, LPSTR lpStatusText);
LRESULT FAR PASCAL VideoCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr);
//-----------------------------
/*
namespace ilivemainwin
{


#define ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT 0x800
#define ILVLIVE_IMCMD_CUSTOM_UP_LIMIT 0x900

#define LiveNoti "LiveNotification" //�Զ���������

enum E_CustomCmd
{
	AVIMCMD_None,               // ���¼���0

	AVIMCMD_EnterLive,          // �û�����ֱ��, Group��Ϣ �� 1
	AVIMCMD_ExitLive,           // �û��˳�ֱ��, Group��Ϣ �� 2
	AVIMCMD_Praise,             // ������Ϣ, Demo��ʹ��Group��Ϣ �� 3
	AVIMCMD_Host_Leave,         // �����򻥶������뿪, Group��Ϣ �� 4
	AVIMCMD_Host_Back,          // �����򻥶����ڻ���, Group��Ϣ �� 5

	AVIMCMD_Multi = ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,  // ���˻�����Ϣ���� �� 2048

	AVIMCMD_Multi_Host_Invite,          // ������������������Ϣ, C2C��Ϣ �� 2049
	AVIMCMD_Multi_CancelInteract,       // �ѽ��뻥��ʱ���Ͽ�������Group��Ϣ�����Ͽ��ߵ�imUsreid���� �� 2050
	AVIMCMD_Multi_Interact_Join,        // ���˻������յ�AVIMCMD_Multi_Host_Invite���������ͬ�⣬C2C��Ϣ �� 2051
	AVIMCMD_Multi_Interact_Refuse,      // ���˻������յ�AVIMCMD_Multi_Invite��������󣬾ܾ���C2C��Ϣ �� 2052
};
 void OnGropuMessage(const TIMMessage& msg);
 void OnC2CMessage(const TIMMessage& msg);
 void onForceOffline();

 void OnLocalVideo(VideoFrame* video_frame, void* custom_data);
 void OnRemoteVideo(VideoFrame* video_frame, void* custom_data);


 void OnRoomDisconnect(int32 reason, std::string errorinfo, void* data);
 void OnMemStatusChange(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data);
 void OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list, void* data);
 void OnSemiAutoRecvScreenVideo(std::vector<std::string> identifier_list, void* data);
 void OnSemiAutoRecvMediaFileVideo(std::vector<std::string> identifier_list, void* data);
 
void sendC2CCustomCmd( CString dstUser, E_CustomCmd userAction, CString actionParam, SuccessCalllback suc = NULL, ErrorCallback err = NULL, void* data = NULL );
void sendGroupCustomCmd( E_CustomCmd userAction, CString actionParam, SuccessCalllback suc = NULL, ErrorCallback err = NULL, void* data = NULL );

}
*/


class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	
public:
	//int mFlag;
	//HomePageDlg mHomePageDlg;//��¼����������

	void LiveCreateRoom();
	void LiveCloseRoom();
protected:
	CAPDRIVERCAPS   m_CaptureDriverParams;
	//-----------------------------------------------------
	AVISTREAMINFO   m_AVIStreamInfor;             //AVI���ṹ��Ϣ
	PAVIFILE        m_pAVIFile;                   //AVI�ļ�
	PAVISTREAM      m_pAVIStream;                 //AVI��ָ��
	DWORD           m_FrameCount;                 //��¼֡��
												  //------------------------------------------------------
	BOOL InitiationID;
	DWORD   mMyCurrentFCCHandle;
// ����
public:
	//iLiveSDK* piLiveSDK;
	//iLiveLoginMgr* piLiveLoginMgr;
	//iLiveRoomMgr* piLiveRoomMgr;

	void ShowSnapForm(int flag);
	SnapForm* pMySnapForm;

	CUnkSinkLiveRoomHelper * pUnkSinkLiveRoomHelper;

#ifdef VersionStud 
	AxStudMgrDlg* pAxStudMgrDlg;
#else
	CAccountManager* pAccountManager;
#endif
	

// ��������
protected:
	
	CString				m_szServerUrl;
	CString			    m_szUserId;
	CString				m_szUserSig;
	CString				m_szUserToken;

	int					m_nAppId;
	int					m_nAccountType;	

	int					mLiveCount;
	CString mRoomTitle;

	
	LogoCover* pLogoCover;
	InitianlizingText* pInitianlizingText;
	


	//uint32	m_x0;
	//uint32	m_y0;
	//uint32	m_x1;
	//uint32	m_y1;
	//uint32	m_fps;



	//std::vector< std::pair<std::string/*id*/, std::string/*name*/> > m_cameraList;

	void InitiLiveSDK();
	void InitMiddleWare();

	void updatePushAndRecordStateUI();


	void ShowLogoCover(int flag);
	
	void ShowAccountManager(int flag);

	void OnButtonLogoutMIS();
	void OnButtonCreaterRoomMIS();
	void OnMasterReportRoomMIS(CString RoomTitle);
	void OnMasterJoinRoomMIS(int mUserType);

	void OnBtnHeartBeat(int mthumbup);
	void OnButtonMasterQuitRoomMIS();

private:
	/*
	static void OniLiveLoginSuccess(void* data);
	static void OniLiveLoginError(int code, const std::string& desc, void* data);
	static void OniLiveLogoutSuccess(void* data);
	static void OniLiveLogoutError(int code, const std::string& desc, void* data);

	//------�����˷������------------------------------------------------------------------------------
	static void OniLiveCreateRoomSuc(void* data);
	static void OniLiveCreateRoomErr(int code, const std::string& desc, void* data);

	static void OniLiveQuitRoomSuc(void* data);
	static void OniLiveQuitRoomErr(int code, const std::string& desc, void* data);

	static void OnMasterQuitRoomSuc(void* data);
	static void OnMasterQuitRoomErr(int code, const std::string& desc, void* data);


	//------���ڶ˷������------------------------------------------------------------------------------
	static void OniLiveGuestJoinRoomSuc(void* data);
	static void OniLiveGuestJoinRoomErr(int code, const std::string& desc, void* data);

	static void OnWatcherQuitRoomSuc(void* data);
	static void OnWatcherQuitRoomErr(int code, const std::string& desc, void* data);
	*/





// ����
public:
	INT isCloseFlag;
	INT isLiveFlag;

	long m_RoomID ;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
public:
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	//CMyPrivateStatusBar m_wndStatusBar;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;
	//----------------------------------------
	CProgressCtrl   m_Progress;
	CBModeCtrlBox mBModeAdustCtrlBox;
	CBModeCtrlBox* pMModeAdustCtrlBox;
	CDockablePane* m_pTabbedBar;


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//------------------------------------------------------------
	BOOL USGDeviceStateID;
	BOOL USGImagingRunModeID;
	BOOL USGFreezingID;
	afx_msg void OnUSGDeviceStateChange(UINT id);
	afx_msg void OnUpdateUSGDeviceStateChangUI(CCmdUI* pCmdUI);


	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnShowpropertywindow32771();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMyProcessMessage(WPARAM wParam, LPARAM lParam);
	//------------------------------------------------------------
	afx_msg LRESULT LiveLoginHandler(WPARAM,LPARAM);
	afx_msg LRESULT LiveRoomHandler(WPARAM,LPARAM);
	afx_msg LRESULT LiveStatusHandler(WPARAM, LPARAM);
	afx_msg LRESULT LiveStatusHandlerEx(WPARAM, LPARAM);

	afx_msg void OnPaint();
	afx_msg void OnClose();

	afx_msg void OnButtonLoginlive();
	afx_msg void OnButtonLoginoutlive();
	afx_msg void OnButtonLoginoutlive2();
	afx_msg void OnButtonCreateroom();
	afx_msg void OnButtonCloseroom();
	afx_msg void OnButtonJoinroom();
	afx_msg void OnButtonQuitroom();
	afx_msg void OnButtonStartvideo();
	afx_msg void OnButtonStartscreen();
	afx_msg void OnButtonClosescreen();
	afx_msg void OnButtonStopvideo();
	afx_msg void OnButtonInitvfw();
	afx_msg void OnButtonPreview();
	afx_msg void OnButtonSetuppara();
	afx_msg void OnButtonStartpreview();
	afx_msg void OnButton1Localpreview();
	afx_msg void OnButtonCreatevirtyroom();
	afx_msg void OnButtonClosevirtyroom();
	afx_msg void OnButtonlocalscreenshare2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonMasterquitroom();
	afx_msg void OnButtonMasterquitroom2();


	afx_msg void OnButtonWatcherjoinroom();
	afx_msg void OnButtonWatcherquitroom();
	afx_msg void OnButtonSlaverjoinmis();
	afx_msg void OnButtonSlaverquitmis();
	afx_msg void OnButtonSlaverjoinmis2();
	afx_msg void OnButtonSlaverquitmis2();
	afx_msg void OnButtonSlaverjoinmis3();
	afx_msg void OnButtonSlaverjoinbyteroom();
	afx_msg void OnButtonSlaverquitbyteroom();
	afx_msg void OnButtonSlaverquitmis3();
	afx_msg void OnButtonWatcherSendIM();

	afx_msg void OnButtonJoinlogicserver();
	afx_msg void OnButton7Quitlogicserver();
};


