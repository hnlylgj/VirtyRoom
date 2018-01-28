
#pragma once
typedef /* [v1_enum] */ 
enum tagUSGStatus
    {	USG_STATUS_NULL	=0,
		USG_STATUS_POWER	= 1,
		USG_STATUS_DEPTH	= 2,
		USG_STATUS_GAIN	= 3,
		USG_STATUS_IMAGE_ORIENTATION	= 4,
		USG_STATUS_DYNAMIC_RANGE	= 5,
		USG_STATUS_FREQUENCY	= 6,
		USG_STATUS_FRAME_AVERAGING	=7,
		USG_STATUS_REJECTION	= 8,
	    USG_STATUS_LINE_DENSITY	=9,
		USG_STATUS_VIEW_ZOOM=10,
		USG_STATUS_IMAGE_ENHANCE	=11,
		USG_STATUS_SPECKLE_REDUCTION=12,
		USG_STATUS_FOCUS	= 13,
		USG_STATUS_TGC	= 14,
		USG_STATUS_PALETTE	= 15,
		USG_STATUS_IMAGE_PROPERTY	= 16,
	} 	USG_STATUS;

typedef /* [v1_enum] */ 
enum tagUSGControlType
    {	USG_ControlType_NULL	=0,
		USG_ControlType_POWER	= 1,
		USG_ControlType_DEPTH	= 2,
		USG_ControlType_GAIN	= 3,
		USG_ControlType_FOCUS	= 4,
		USG_ControlType_SCAN_DIRECTION	= 5,
		USG_ControlType_DYNAMIC_RANGE	= 6,
		USG_ControlType_FREQUENCY	= 7,
		USG_ControlType_XX1	= 8,
	
	} 	USGControlType;

typedef
struct tagUSG_Control_Values
{
    LONG CurrentValue;
	LONG IndexValue;
	LONG CountValue;

}USG_Control_Values;
//#define WM_USGStatusChangeMessage (WM_USER + 10)
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#include "Usgfw2_h.h"
#include  "DrawImage.h"
// CUSGFW2ForMX 命令目标
class CUSGFW2ForMX : public CCmdTarget   /*, public IUsgCtrlChangeCommon */
{
	DECLARE_DYNAMIC(CUSGFW2ForMX)

public:
	CUSGFW2ForMX();
	virtual ~CUSGFW2ForMX();
	virtual void OnFinalRelease();//自己加的语句！
protected:
	DECLARE_MESSAGE_MAP()
	
//------------------------------------------------------------------------------------------------------------
public:
//protected: 
    
	LONG ProbesCount;//探头总数
	LONG ProbesAppIndex;//当前选择的探头的序号
    //---------------------------------------------
	IUsgfw2* pMainUSGFW2;
	//---------------------------------------------
	IProbe* pProbe;
	//IProbe2* pProbe2;

	IBeamformer* pBeamformer;//++
	//-------------------------------------------------------------
	IUsgDataView* pUsgDataView;
	IUsgDataStream* pUsgDataStream;//++

	IUsgMixerControl* pMixerControl;
	//-------------------------------------------------------------
	IUsgDepth* pUsgDepth;
	IUsgGain* pUsgGain;
	//--------------------------------------------------------------
	IUsgPower* pUsgPower;
	IUsgProbeFrequency2* pUsgProbeFrequency2;
	IUsgProbeFrequency3* pUsgProbeFrequency3;

	IUsgDynamicRange* pUsgDynamicRange;
	IUsgImageOrientation* pUsgImageOrientation;//镜像变换与--旋转变换
	//---------------------------------------------------------------
	IUsgFrameAvg* pUsgFrameAvg;
	IUsgRejection2* pUsgRejection2;
	IUsgLineDensity* pUsgLineDensity;
	IUsgViewArea* pUsgViewArea;//显示区域调节
	//----------------------------------------------------------------
	IUsgImageEnhancement* pUsgImageEnhancement;//图像增强
	IUsgClearView* pUsgClearView;//椒盐噪声处理--Speckle Reduction
   	//----------------------------------------------------------------
	IUsgFocus* pUsgFocus;//焦点调整
	IUsgTgc* pUsgTgc; //线性增补
	//---------------------------------------------------------------
	IUsgPalette* pUsgPalette; 
	IUsgPaletteCalculator* pUsgPaletteCalculator; 
	//---------------------------------------------------------------
 	IUsgImageProperties* pUsgImageProperties;
	IUsgScanLineProperties* pUsgScanLineProperties;
	//---------------------------------------------
	IUsgQualProp* pUsgQualProp;
	IUsgBioeffectsIndices* pUsgBioeffectsIndices;
	//--------------------------------------------------------------
    IUsgFileStorage* pUsgFileStorage;
	//---------------------------------------------------------------
	DrawImage* pDrawImage;
	//---------------------------------------------------------------
	IUsgScanConverterPlugin *	pUsgScanConverterPlugin;

	//-----------------------------------------------------------------
protected:
	IConnectionPoint* pUsgConnectionPoint;//连接点指针
	DWORD UsgConnectionPointCookie;       //连接点会话ID
	//--------------------------------------------------
	void CreateUsgControl(IUsgDataView* pUsgDataView, const IID& type_id, ULONG scan_pUsgScanMode, ULONG stream_id, void** ctrl );
	void CreateUsgControls();
	void ReleaseUsgControls();
	BOOL Init();//---
	BOOL Exit();//---
	
	int ConnectionUsgCtrlChangeEventPoint();
	int DisConnectionUsgCtrlChangeEventPoint();
	
	//void InitializeUserInterfaceControls();
	//void EnableDisableUserInterfaceControls();

	//void DepthUpdateGUI();
	//void DepthSetByIndex(int dir);

	//void B_GainUpdateGUI();
	//void B_GainSetByIdx(int idx);

   //==========================================================================================================
   /*
public:
	//--- IUnknown-------
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
	ULONG m_refCount;

public:
	//---IDispatch--------
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(const IID &riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, const IID &riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
public:
	// IUsgCtrlChangeCommon
	virtual HRESULT STDMETHODCALLTYPE OnControlChanged( REFIID riidCtrl, ULONG scanpUsgScanMode, LONG streamId, IUsgControl *pControlObj, LONG dispId, LONG flags )
		{return S_OK;}
	virtual HRESULT STDMETHODCALLTYPE OnControlChangedBSTR( BSTR ctrlGUID, LONG scanpUsgScanMode, LONG streamId, IUsgControl *pControlObject, LONG dispId, LONG flags );
  */
public:	
	//--加入嵌套类：接收器对象(EventSink)--------------
   BEGIN_INTERFACE_PART(EventSink, IDispatch)
		INIT_INTERFACE_PART(CUSGFW2ForMX, EventSink)
		STDMETHOD(GetTypeInfoCount)(unsigned int*);
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**);
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*);
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*, VARIANT*, EXCEPINFO*, unsigned int*);
	END_INTERFACE_PART(EventSink)

	//============================================================================================================
public:
	//------------------------------------------------------------------
	LONG ReturnResultValue;
	SCAN_MODE LogicScanModeID;
	LONG USGDeviceStatus;
	BOOL USGFreezeStatus;
	RECT* pRECT; 
	//-------------------------------------------------------------------
   void WaitForEvent(HANDLE hEvent, DWORD msMaxWaitTime = INFINITE);
   void WaitForMessage(DWORD msMaxWaitTime = INFINITE);	
  //--基本设置方法接口--------------------------------------------------------------------------------------------
   void SetHandleWindow(HWND InHWindow);
   void SetCustomMessage(UINT InMessageID);
  
    static  void SetAsyncEvent(HRESULT hrAsync);
	static HRESULT STDMETHODCALLTYPE OnUSGStatusChangeNotify(USG_STATUS StatusID,HRESULT hr= S_OK);
	static HRESULT STDMETHODCALLTYPE USGControlChangedCallBackBSTR( BSTR ctrlGUID, LONG scanMode, LONG streamId, IUsgControl *pControlObject, LONG dispId, LONG flags );
    //--功能调用接口---------------------------------------------------------------------------------------------
	BOOL OpenDevice();
	BOOL CloseDevice();
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	BOOL ConnectToDevice();
	BOOL DisconnectToDevice();
	BOOL StartUSGGenerator(HWND mhDisplayWindow);
	BOOL CloseUSGGenerator();
	//---------------------------------------------------------
	void FreezeImage();
	void RunImageView();
	void StopImageView();
	void AcquireImage();
	void SetScanpUsgScanMode(SCAN_MODE InpUsgScanModeID);
	void SaveImageToFile(LPTSTR pwszUrl);
	LONG GetProbesCount();
	void RepaintUSGDisplayWindow();
	//-------------------------------------------------------------
	void DepthSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void GainSetByIndex(LONG  DirectionFlag,LONG SetCurrentIndex);
	//-------------------------------------------------------------
	void PowerSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void Frequency3SetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void DynamicRangeSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void ScaningDirctionSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);//DirectionFlag 0:	镜像变换；1：旋转变换
	//---------------------------------------------------------------
	void FrameAveragingSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void LineDensitySetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void RejectionSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void ViewZoomSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);

	void ImageEnhancementSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void ClearViewSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);

	//--------------------------------------------------------------
	void FocusSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void TGCSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);
	void PaletteSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex);

	LONG UpdateUSGStatus(USG_STATUS USGStatusID,LONG SetWayID,LONG SetCurrentIndex=-1);//SetWayID:1,-1表示方向更新；0：表示直接通过索引号更新

	

	//------------------------------------------------------------------------------------------------------------

  





};


