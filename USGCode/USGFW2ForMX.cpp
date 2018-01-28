// USGFW2ForMX.cpp : 实现文件
//

#include "stdafx.h"
#include "Safe_ReleaseDefine.h"
#include "USGFW2ForMX.h"
#include "DIBSectn.h"

 static HWND HUSGDisplayWindow;
 static UINT CustomMessageID;
 static bool DisplayFlag;
 static HANDLE	mEventSyncHandle;   // event handle
 static HRESULT	mhAsyncStatusResult; // HRESULT during async operations

 static USG_STATUS mGlobeUSGStatusID;
 //static long Result2;
 //static CString UsgCtrlNotifyStr;
  //-----------------------------------------------------------------
 //static const CLSID TargetCLSID =__uuidof(SocketCOMAPI);
 static const IID IID_UsgCtrlChangeCallBack =__uuidof(IUsgCtrlChangeCommon);
IMPLEMENT_DYNAMIC(CUSGFW2ForMX, CCmdTarget)


CUSGFW2ForMX::CUSGFW2ForMX()
{
    EnableAutomation();
    CoInitialize(NULL);
    UsgConnectionPointCookie = 0;
	DisplayFlag=true;
	ProbesCount = 0;
	ProbesAppIndex= 0;
	ReturnResultValue=0;
	USGFreezeStatus=0;
	LogicScanModeID=SCAN_MODE_B;//no:A,BA,BPW，BM,B2，BM,CFM,PDI ----B,M,PW,
	USGDeviceStatus=0;
	mGlobeUSGStatusID=USG_STATUS_NULL;
	
	
	pMainUSGFW2 = NULL;
	pUsgDataView = NULL;
	pProbe = NULL;
	pMixerControl = NULL;

	pUsgDepth = NULL;
	pUsgGain = NULL;
	//--------------------------
	pUsgPower= NULL;
	pUsgDynamicRange = NULL;
	pUsgProbeFrequency2= NULL;
	pUsgProbeFrequency3= NULL;
	pUsgImageOrientation= NULL;
	//-------------------------
	pUsgFrameAvg = NULL;;
	pUsgRejection2 = NULL;;
	pUsgLineDensity = NULL;;
	pUsgViewArea = NULL;
	//------------------------
	pUsgImageEnhancement= NULL;
	pUsgClearView= NULL;

	//------------------------
	pUsgFocus= NULL;
	pUsgTgc= NULL;
	pUsgPalette= NULL;
	pUsgPaletteCalculator= NULL;
	//-----------------------
	pUsgImageProperties=NULL;
	pUsgScanLineProperties=NULL;
	pUsgQualProp=NULL;;
	pUsgBioeffectsIndices=NULL;

	pUsgScanConverterPlugin=NULL;
	//-----------------------
	pDrawImage=NULL;
	//-----------------------
	pUsgConnectionPoint = NULL;
    mEventSyncHandle = NULL;
	mhAsyncStatusResult = E_FAIL;	
    
}

CUSGFW2ForMX::~CUSGFW2ForMX()
{

   //DisConnectionUsgCtrlChangeEventPoint();
   //ReleaseUsgControls();
   CoUninitialize();

}


BEGIN_MESSAGE_MAP(CUSGFW2ForMX, CCmdTarget)
END_MESSAGE_MAP()


// CUSGFW2ForMX 消息处理程序

void CUSGFW2ForMX::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。
	
    CCmdTarget::OnFinalRelease();
}
BOOL CUSGFW2ForMX::Init()
{
  //--------------------------------------------------------------------------------------------------
    //mEventSyncHandle = CreateEvent(NULL, FALSE, FALSE, NULL);//有时有点问题！

	CreateUsgControls();
	//InitializeUserInterfaceControls();
	//EnableDisableUserInterfaceControls();
		
	//HRESULT hr;
	//hr = CoCreateInstance(TargetCLSID, NULL,CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&m_pDispatch);
	// create main Usgfw2 library object
	//hr = CoCreateInstance(CLSID_Usgfw2, NULL, CLSCTX_INPROC_SERVER, IID_IUsgfw2,(LPVOID*) &pMainUSGFW2);
	//if (FAILED(hr)) 
	//{
	//	return FALSE;
	//}
	
   	return true;
}
BOOL CUSGFW2ForMX::Exit(void)
{
	//SAFE_RELEASE(mpHeaderInfo);
	//SAFE_RELEASE(mpWMVReader);
	//SAFE_ARRAY_DELETE(mURL);
	//DisConnectionUsgCtrlChangeEventPoint();
	//RepaintUSGDisplayWindow();
    ReleaseUsgControls();
	SAFE_CLOSEHANDLE(mEventSyncHandle);
	mGlobeUSGStatusID=USG_STATUS_NULL;
	return true;
}
void CUSGFW2ForMX::CreateUsgControl( IUsgDataView* pUsgDataView, const IID& type_id, ULONG scan_pUsgScanMode, ULONG stream_id, void** ctrl )
{
	IUsgControl* pUsgControl;
	pUsgControl = NULL;
	if (pUsgDataView == NULL) return;
	pUsgDataView->GetControlObj( &type_id, scan_pUsgScanMode, stream_id, &pUsgControl );
	if (pUsgControl != NULL)
	{
		HRESULT hr;
		hr = pUsgControl->QueryInterface( type_id, (void**)ctrl );
		if (hr != S_OK)
			*ctrl = NULL;
		SAFE_RELEASE(pUsgControl);
	}
}
void CUSGFW2ForMX::CreateUsgControls()
{
	HRESULT hr = S_OK;
	IUnknown* pIUnknown = NULL;

	do
	{
		// create main Usgfw2 library object
		hr = CoCreateInstance(CLSID_Usgfw2, NULL, CLSCTX_INPROC_SERVER, IID_IUsgfw2,(LPVOID*) &pMainUSGFW2);
		if (hr != S_OK)
		{
			pMainUSGFW2 = NULL;
			break;
		}

		IUsgCollection* pProbeCollection = NULL;

		// get collection of connected probes
		pIUnknown = NULL;
		pMainUSGFW2->get_ProbesCollection(&pIUnknown);
		if (pIUnknown == NULL)
		{
			pProbeCollection = NULL;
			break;
		}
		hr = pIUnknown->QueryInterface(IID_IUsgCollection,(void**)&pProbeCollection);
		pIUnknown->Release();
		if ( (hr != S_OK) || (pProbeCollection == NULL) )
		{
			pProbeCollection = NULL;
			break;
		}

		//LONG probes_count = 0;//
		pProbeCollection->get_Count(&ProbesCount);
		if (ProbesCount == 0)
		{
			pProbeCollection->Release();
			pProbeCollection = NULL;
			break;
		}

		pIUnknown = NULL;
		pProbeCollection->Item(ProbesAppIndex,&pIUnknown); // get first available probe
		pProbeCollection->Release();
		pProbeCollection = NULL;
		if (pIUnknown == NULL)
		{
			pProbe = NULL;
			break;
		}
		hr = pIUnknown->QueryInterface(IID_IProbe,(void**)&pProbe);
		pIUnknown->Release();
		if ( (hr != S_OK) || (pProbe == NULL) )
		{
			pProbe = NULL;
			break;
		}
		//----以上是设备和探头工作正常-----------------------------------------------------------------------------------------
		// create main ultrasound scanning object for selected probe
		pMainUSGFW2->CreateDataView(pProbe, &pUsgDataView);
		if (pUsgDataView == NULL)
		{
			break;
		}

		pUsgDataView->put_ScanState(SCAN_STATE_STOP);

		IUsgScanMode* pUsgScanMode = NULL;
		pUsgDataView->GetScanModeObj(SCAN_MODE_B,&pUsgScanMode);
		if (pUsgScanMode == NULL)
		{
			break;
		}

		// get mixer control
		pUsgScanMode->GetMixerControl(SCAN_MODE_B,0,&pMixerControl);
		pUsgScanMode->Release();
		pUsgScanMode = NULL;
		if (pMixerControl == NULL)
		{
			break;
		}

		// set B scanning pUsgScanMode
		 pUsgDataView->put_ScanMode(SCAN_MODE_B);
		//--set ultrasound output window (panel)
		pMixerControl->SetOutputWindow((LONG)HUSGDisplayWindow);
		
		tagRECT mOutputRectangle;
		mOutputRectangle.left		= 20;
		mOutputRectangle.top		= 20;
		mOutputRectangle.right		= mOutputRectangle.left + 512;
		mOutputRectangle.bottom	= mOutputRectangle.top + 512;

		// set ultrasound output rectangle
		pMixerControl->SetOutputRect(&mOutputRectangle);

		// set background color that surrounds ultrasound image to blue
		tagPALETTEENTRY mBackgroundColor;
		mBackgroundColor.peRed		= 0;
		mBackgroundColor.peGreen	= 0;
		mBackgroundColor.peBlue		= 255;//blue
		mBackgroundColor.peFlags	= 0;
		pMixerControl->put_BkColor(mBackgroundColor);
		//---以上是建立B模式成像------------------------------------------------------------------------------------------------
		// create depth control
		///*
		pIUnknown = NULL;
		CreateUsgControl( pUsgDataView, IID_IUsgDepth, SCAN_MODE_B, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
			pUsgDepth = (IUsgDepth*)pIUnknown;
		else
			pUsgDepth = NULL;

		// create B Mode gain control
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgGain, SCAN_MODE_B, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
			pUsgGain = (IUsgGain*)pIUnknown;
		else
			pUsgGain = NULL;

		// attach to control value change connection point in order to be informed about changed values
		/*--------------------------------------------
		IConnectionPointContainer* cpc = NULL;
		hr = pUsgDataView->QueryInterface(IID_IConnectionPointContainer,(void**)&cpc);
		if (hr != S_OK)
			cpc = NULL;

		if (cpc != NULL)
			hr = cpc->FindConnectionPoint(IID_IUsgCtrlChangeCommon,&pUsgConnectionPoint);

		if (hr != S_OK)
		{
			pUsgConnectionPoint = NULL;
			pUsgConnectionPointCookie = 0;
		}
		SAFE_RELEASE(cpc);

		hr = pUsgConnectionPoint->Advise((IUnknown*)this,&pUsgConnectionPointCookie);
		*/
		ConnectionUsgCtrlChangeEventPoint(); 
		// start ultrasound scanning (Run)--
		//pUsgDataView->put_ScanState(SCAN_STATE_RUN);

		return;
	} while (false);

	ReleaseUsgControls();

} // void CsampleDlg::CreateUsgControls()

void CUSGFW2ForMX::ReleaseUsgControls()
{
	 //HUSGDisplayWindow = NULL;-------
	/*
	if (pUsgDataView != NULL)
		pUsgDataView->put_ScanState(SCAN_STATE_STOP);
	if (pUsgConnectionPoint != NULL)
	{
		pUsgConnectionPoint->Unadvise(UsgConnectionPointCookie);
		UsgConnectionPointCookie = 0;
		SAFE_RELEASE(pUsgConnectionPoint);
	}

	DisConnectionUsgCtrlChangeEventPoint();

	SAFE_RELEASE(pUsgConnectionPoint);
	SAFE_RELEASE(pUsgDepth);
	SAFE_RELEASE(pUsgGain);

	SAFE_RELEASE(pUsgPower);
	SAFE_RELEASE(pUsgDynamicRange);
	SAFE_RELEASE(pUsgProbeFrequency3);
	SAFE_RELEASE(pUsgImageOrientation);
	SAFE_RELEASE(pUsgFocus);

	SAFE_RELEASE(pMixerControl);
	SAFE_RELEASE(pUsgDataView);
	*/
	//-----------------------------------------------------------------

	CloseUSGGenerator();
	SAFE_RELEASE(pProbe);
	SAFE_RELEASE(pMainUSGFW2);

}

void CUSGFW2ForMX::RepaintUSGDisplayWindow()
{
	if (pMixerControl != NULL)
		{
			if (HUSGDisplayWindow != NULL)
			{
				HDC hdc;
				hdc = ::GetDC(HUSGDisplayWindow);
				// repaint ultrasound (important if we are in freeze)
				pMixerControl->Repaint((LONG)HUSGDisplayWindow,(LONG)hdc);
				::ReleaseDC(HUSGDisplayWindow,hdc);
			}
		}
}

int CUSGFW2ForMX::ConnectionUsgCtrlChangeEventPoint() 
{
    int RetValue = 0;//0:false;1:Success
	if (UsgConnectionPointCookie != 0)
	{
		return 1;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtContainer;//---连接点容器接口指针----
	if ((pUsgDataView != NULL) && SUCCEEDED(pUsgDataView->QueryInterface(IID_IConnectionPointContainer,(LPVOID*)&pConnPtContainer)))
	{
		ASSERT(pConnPtContainer != NULL);
		LPCONNECTIONPOINT pUsgCtrlChangeConnectionPoint = NULL;//----连接点接口指针----
		DWORD dwCookie = 0;

		if (SUCCEEDED(pConnPtContainer->FindConnectionPoint(IID_UsgCtrlChangeCallBack, &pUsgCtrlChangeConnectionPoint)))
		{
			ASSERT(pUsgCtrlChangeConnectionPoint != NULL);
			HRESULT hResult =pUsgCtrlChangeConnectionPoint->Advise(&m_xEventSink, &dwCookie);
			UsgConnectionPointCookie = dwCookie;
			RetValue = 1;//成功连接到事件源接口！
			pUsgCtrlChangeConnectionPoint->Release();
		}

		pConnPtContainer->Release();
		UsgConnectionPointCookie = dwCookie;
	}
	return RetValue;
}

int CUSGFW2ForMX::DisConnectionUsgCtrlChangeEventPoint() 
{
	int  RetValue = 0;//0:false;1:Success
	if (UsgConnectionPointCookie == 0) 
	{
		return 1;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtContainer;
	if ((pUsgDataView != NULL) && SUCCEEDED(pUsgDataView->QueryInterface(IID_IConnectionPointContainer,(LPVOID*)&pConnPtContainer)))
	{
		ASSERT(pConnPtContainer != NULL);
		LPCONNECTIONPOINT pUsgCtrlChangeConnectionPoint = NULL;
		if (SUCCEEDED(pConnPtContainer->FindConnectionPoint(IID_UsgCtrlChangeCallBack, &pUsgCtrlChangeConnectionPoint)))
		{
			ASSERT(pUsgCtrlChangeConnectionPoint != NULL);
			HRESULT hResult =pUsgCtrlChangeConnectionPoint->Unadvise(UsgConnectionPointCookie);
			pUsgCtrlChangeConnectionPoint->Release();
			UsgConnectionPointCookie = 0;
			RetValue = 1;
		}

		pConnPtContainer->Release();
	}
	return RetValue;
}

//---接收器对象:嵌套类实现-----------------------------------------------------------------------------------------------
// CIDispatchSourceEventSink::XEventSink
STDMETHODIMP_(ULONG)  CUSGFW2ForMX::XEventSink::AddRef()
{
	return 1;
}

STDMETHODIMP_(ULONG)  CUSGFW2ForMX::XEventSink::Release()
{
	return 0;
}

STDMETHODIMP CUSGFW2ForMX::XEventSink::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CUSGFW2ForMX, EventSink)

	if (IsEqualIID(iid, IID_IUnknown) ||IsEqualIID(iid, IID_IDispatch) ||IsEqualIID(iid, IID_UsgCtrlChangeCallBack))//------------------------------------------------------------
	{
		*ppvObj = this;
		AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

STDMETHODIMP  CUSGFW2ForMX::XEventSink::GetTypeInfoCount(unsigned int*)
{
	return E_NOTIMPL;
}

STDMETHODIMP  CUSGFW2ForMX::XEventSink::GetTypeInfo(unsigned int, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

STDMETHODIMP  CUSGFW2ForMX::XEventSink::GetIDsOfNames(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
{
	return E_NOTIMPL;
}

STDMETHODIMP  CUSGFW2ForMX::XEventSink::Invoke(DISPID dispid, REFIID, LCID, unsigned short wFlags,DISPPARAMS* pDispParams, VARIANT* pvarResult,EXCEPINFO* pExcepInfo, unsigned int* puArgError)
{
	/*
	switch(dispid)
	{
	case 1:
		
        //Result=pDispParams->rgvarg[0].lVal; 
        //UsgCtrlNotifyStr.Format(_T("异步回调分派接口返回值： %d"),Result);
        //SetAsyncEvent(0);
	    break;
	case 2:
         //	
		 BSTR MyTestReturnString;
		 MyTestReturnString=pDispParams->rgvarg[0].bstrVal;
         UsgCtrlNotifyStr=MyTestReturnString;
         SetAsyncEvent(0);
         //AfxMessageBox((LPCTSTR)MyStrtemp);
		 //
		BSTR ctrlGUID = NULL;
		LONG scanMode = 0;
		LONG streamId = 0;
		IUsgControl *pControlObject = NULL;
		LONG dispId = 0;
		LONG flags = 0;

		if (pDispParams->cArgs != 6) // we need 6 arguments
			return S_OK;

		VARIANTARG* p1;
		VARIANTARG* p;
		p1 = pDispParams->rgvarg;

		p = p1;
		flags = p->lVal;
		p1++;

		p = p1;
		dispId = p->lVal;
		p1++;

		p = p1;
		pControlObject = (IUsgControl*)(p->pdispVal);
		p1++;

		p = p1;
		streamId = p->lVal;
		p1++;

		p = p1;
		scanMode = p->lVal;
		p1++;

		p = p1;
		ctrlGUID = p->bstrVal;
		p1++;
		//OnControlChangedBSTR(ctrlGUID,scanMode,streamId,pControlObject,dispId,flags);
		break;
  	default:
        BSTR ctrlGUID = NULL;
		LONG scanMode = 0;
		LONG streamId = 0;
		IUsgControl *pControlObject = NULL;
		LONG dispId = 0;
		LONG flags = 0;

		AfxMessageBox(L"I don't known the event!");
        break;

	}
	*/
	if (dispid == 2) // arrived OnControlChangedBSTR notification
	{
		BSTR ctrlGUID = NULL;
		LONG scanMode = 0;
		LONG streamId = 0;
		IUsgControl *pControlObject = NULL;
		LONG DispatchID = 0;
		LONG flags = 0;

		if (pDispParams->cArgs != 6) // we need 6 arguments
			return S_OK;

		VARIANTARG* p1;
		VARIANTARG* p;
		p1 = pDispParams->rgvarg;

		p = p1;
		flags = p->lVal;
		p1++;

		p = p1;
		DispatchID= p->lVal;
		p1++;

		p = p1;
		pControlObject = (IUsgControl*)(p->pdispVal);
		p1++;

		p = p1;
		streamId = p->lVal;
		p1++;

		p = p1;
		scanMode = p->lVal;
		p1++;

		p = p1;
		ctrlGUID = p->bstrVal;
		p1++;

		USGControlChangedCallBackBSTR(ctrlGUID,scanMode,streamId,pControlObject,DispatchID,flags);
	}
	return S_OK;
	
}
HRESULT CUSGFW2ForMX::USGControlChangedCallBackBSTR( BSTR ctrlGUID, LONG scanMode, LONG streamId, IUsgControl *pControlObject, LONG dispId, LONG flags )
{
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgDepth))
		OnUSGStatusChangeNotify(USG_STATUS_DEPTH);
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgGain))
	    OnUSGStatusChangeNotify(USG_STATUS_GAIN);
	//--------------------------------------------------------------------------------------------
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgPower))
	    OnUSGStatusChangeNotify(USG_STATUS_POWER);
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgProbeFrequency3))
	    OnUSGStatusChangeNotify(USG_STATUS_FREQUENCY);

	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgDynamicRange))
	    OnUSGStatusChangeNotify(USG_STATUS_DYNAMIC_RANGE);

	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgImageOrientation))
	    OnUSGStatusChangeNotify(USG_STATUS_IMAGE_ORIENTATION);
	//-------------------------------------------------------------------------------------------

	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgFrameAvg))
	    OnUSGStatusChangeNotify(USG_STATUS_FRAME_AVERAGING);

	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgRejection2))
	    OnUSGStatusChangeNotify(USG_STATUS_REJECTION);

	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgLineDensity))
	    OnUSGStatusChangeNotify(USG_STATUS_LINE_DENSITY);
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgViewArea))
	    OnUSGStatusChangeNotify(USG_STATUS_VIEW_ZOOM);
	//-------------------------------------------------------------------------------------------
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgImageEnhancement))
	    OnUSGStatusChangeNotify(USG_STATUS_IMAGE_ENHANCE);
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgClearView))
	    OnUSGStatusChangeNotify(USG_STATUS_SPECKLE_REDUCTION);
	//-------------------------------------------------------------------------------------------
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgFocus))
	    OnUSGStatusChangeNotify(USG_STATUS_FOCUS);
	if (CComBSTR(ctrlGUID) == CComBSTR(IID_IUsgTgc))
	    OnUSGStatusChangeNotify(USG_STATUS_TGC);

	
	return S_OK;
	   
}

HRESULT CUSGFW2ForMX::OnUSGStatusChangeNotify(USG_STATUS StatusID,HRESULT hr)
{
	mGlobeUSGStatusID=StatusID;
	SetAsyncEvent(hr);
	return S_OK;

}

//****************************************************************************************************************************************
 void CUSGFW2ForMX::WaitForEvent(HANDLE hEvent, DWORD msMaxWaitTime)
{
    MSG  msg;
	for (DWORD i = 0; i < msMaxWaitTime; i += 10)
	{
		//
		if (PeekMessage(&msg, (HWND) NULL, 0, 0, PM_REMOVE))
		{
		     TranslateMessage(&msg);
			 DispatchMessage(&msg);
						
		}
		//
		if (WAIT_TIMEOUT != WaitForSingleObject(hEvent, 10))
		{
			break;
		}
	}
   

}
 void CUSGFW2ForMX::WaitForMessage(DWORD msMaxWaitTime)
{
    MSG  msg;
	for (DWORD i = 0; i < msMaxWaitTime; i += 10)
	{
		
		   if (PeekMessage(&msg, (HWND) NULL, 0, 0, PM_REMOVE))
		    {
				if(msg.message ==CustomMessageID)
				{
                  //Result=msg.lParam;
                  //Result2=msg.wParam;
                  mhAsyncStatusResult=0;
                  AfxMessageBox(_T("异步回调完成Peeked！"));
				  break;
				}
				else
				{
		           TranslateMessage(&msg);
			       DispatchMessage(&msg);
			     }
						
	    	}
				
		
	}
   

}

void CUSGFW2ForMX::SetHandleWindow(HWND InHWindow)
{
  HUSGDisplayWindow=InHWindow;
  DisplayFlag=true;
  
}
void CUSGFW2ForMX::SetCustomMessage(UINT InMessageID)
{
  DisplayFlag=false;
  CustomMessageID=InMessageID;
 
}

 void CUSGFW2ForMX::SetAsyncEvent(HRESULT hrAsync)
 {
  mhAsyncStatusResult=hrAsync;
  SetEvent(mEventSyncHandle);

   
 }
 BOOL CUSGFW2ForMX::OpenDevice()
	{
        //SetHandleWindow(mhDisplayWindow);
		Init();
		return true;
	}
 BOOL CUSGFW2ForMX::CloseDevice()
	{
	   Exit();
       return true;
	}

//==========================================================================================================================================================
    BOOL CUSGFW2ForMX::ConnectToDevice()
	{
       	//create main Usgfw2 library object
		//----设备主对象工作是否正常-----------------------------------------------------------------------------------------
		if(USGDeviceStatus==1)return true;
		HRESULT hr = S_OK;
		USGDeviceStatus=0;
		IUnknown* pIUnknown = NULL;
		//---与超声设备进行连接---
		hr = CoCreateInstance(CLSID_Usgfw2, NULL, CLSCTX_INPROC_SERVER, IID_IUsgfw2,(LPVOID*) &pMainUSGFW2);
		if (hr != S_OK)
		{
			pMainUSGFW2 = NULL;
			ReturnResultValue=100;
			return false;
		}
		//---1.检测探头数目与工作情况------------------------------------------------------------------------
		IUsgCollection* pProbeCollection = NULL;//--IUsgCollection
		// get collection of connected probes
		pIUnknown = NULL;
		pMainUSGFW2->get_ProbesCollection(&pIUnknown);
		if (pIUnknown == NULL)
		{
			pProbeCollection = NULL;
			ReturnResultValue=101;
			return false;
		}
		hr = pIUnknown->QueryInterface(IID_IUsgCollection,(void**)&pProbeCollection);
		pIUnknown->Release();
		if ( (hr != S_OK) || (pProbeCollection == NULL) )
		{
			pProbeCollection = NULL;
			ReturnResultValue=102;
			return false;
		}

		//--------------------------------------------------------------------------------
		pProbeCollection->get_Count(&ProbesCount);
		if (ProbesCount == 0)
		{
			pProbeCollection->Release();
			pProbeCollection = NULL;
			ReturnResultValue=103;
			return false;
		}

		pIUnknown = NULL;
		pProbeCollection->Item(ProbesAppIndex,&pIUnknown); // get first available probe
		pProbeCollection->Release();
		pProbeCollection = NULL;
		if (pIUnknown == NULL)
		{
			pProbe = NULL;
			ReturnResultValue=104;
			return false;
		}
		hr = pIUnknown->QueryInterface(IID_IProbe,(void**)&pProbe);
		pIUnknown->Release();
		if ( (hr != S_OK) || (pProbe == NULL) )
		{
			pProbe = NULL;
			ReturnResultValue=105;
			return false;
		}
		//----2.Beamformer-------------------------------------------------------------------------------




		//-----------------------------------------------------------------------------------------------
		USGDeviceStatus=1;//表示设备已经打开！！！
		//if(mEventSyncHandle==NULL) 
	 	// mEventSyncHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		return true;
		
		
	}
	
	BOOL CUSGFW2ForMX::DisconnectToDevice()
   {      
	  //RepaintUSGDisplayWindow();
	   //Exit();
	   //-------------------------------------------------------------------------------------------
	   CloseUSGGenerator();
	   SAFE_RELEASE(pProbe);
	   SAFE_RELEASE(pMainUSGFW2);
	   SAFE_CLOSEHANDLE(mEventSyncHandle);
	   mGlobeUSGStatusID=USG_STATUS_NULL;

	   return true;
	}
	
	void CUSGFW2ForMX::SetScanpUsgScanMode(SCAN_MODE InpUsgScanModeID)
	{
        LogicScanModeID=InpUsgScanModeID;
		return ;
	}

	BOOL CUSGFW2ForMX::StartUSGGenerator(HWND mhDisplayWindow)
	{
	    //---建立[B]模式成像-------------------------------------------
		// create main ultrasound scanning object for selected probe
	   	ReturnResultValue=0;
		CString ReturnResultstr;
    	SetHandleWindow(mhDisplayWindow);

		IUnknown* pIUnknown = NULL;
		if(pMainUSGFW2== NULL|| pProbe==NULL)
			{
				ReturnResultValue=106;
				return false;
		     }
		//----------------------------------------------------------
		pMainUSGFW2->CreateDataView(pProbe, &pUsgDataView);
		
		if (pUsgDataView == NULL)
		{
			    ReturnResultValue=107;
				//AfxMessageBox(ReturnResultstr.Format(L"%d ",ReturnResultValue));
				return false;
		}

		pUsgDataView->put_ScanState(SCAN_STATE_STOP);
		//pUsgDataView->
		IUsgScanMode* pUsgScanMode = NULL;
		pUsgDataView->GetScanModeObj(LogicScanModeID,&pUsgScanMode);//SCAN_MODE_B
		if (pUsgScanMode == NULL)
		{
		    	ReturnResultValue=108;
				return false;//不支持扫描模式
		}

		// get mixer control
		pUsgScanMode->GetMixerControl(LogicScanModeID,0,&pMixerControl);
		pUsgScanMode->Release();
		pUsgScanMode = NULL;
		if (pMixerControl == NULL)
		{
			ReturnResultValue=109;
			return false;
		}

		// set B scanning pUsgScanMode
		 pUsgDataView->put_ScanMode(LogicScanModeID);
		//--set ultrasound output window (panel)
		pMixerControl->SetOutputWindow((LONG)HUSGDisplayWindow);
		
		//-----------------------------------------------------------------------------------
		// set ultrasound output rectangle
		pMixerControl->SetOutputRect(pRECT);
		/*
		LONG nFullWidth=(LONG)GetSystemMetrics(SM_CXSCREEN);     
        LONG nFullHeight=(LONG)GetSystemMetrics(SM_CYSCREEN);  
		LONG mUSGViewWidth=683;//512;//914;
		LONG mUSGViewHeight=521;//512;//588;
		tagRECT mOutputRectangle;
		mOutputRectangle.left		=(nFullWidth-mUSGViewWidth)/2;//3;//39;//10;// 20;50
		mOutputRectangle.top		=(nFullHeight-mUSGViewHeight)/2;;///37;//10;// 20;50
		mOutputRectangle.right		= mOutputRectangle.left + mUSGViewWidth;//512;//683;//512;
		mOutputRectangle.bottom	= mOutputRectangle.top +mUSGViewHeight;//512;//591;// 512;
		HRESULT hr2=pMixerControl->SetOutputRect(&mOutputRectangle);
		*/
		
		
		// set background color that surrounds ultrasound image to blue
		tagPALETTEENTRY mBackgroundColor;
		mBackgroundColor.peRed		= 128;//0;
		mBackgroundColor.peGreen	=138;//0;// 255;//0
		mBackgroundColor.peBlue		=135;//255;// 0;//255
		mBackgroundColor.peFlags	= 0;
		pMixerControl->put_BkColor(mBackgroundColor);
		
		// 1.create depth control
		pIUnknown = NULL;
		CreateUsgControl( pUsgDataView, IID_IUsgDepth, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgDepth = (IUsgDepth*)pIUnknown;
		}
		else
		{
			pUsgDepth = NULL;
			ReturnResultValue=110;
			return false;
		}
		

		// 2.create B Mode gain control
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgGain, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgGain = (IUsgGain*)pIUnknown;
		}
		else
		{
			pUsgGain = NULL;
			ReturnResultValue=112;
			return false;
		}

		//============================================================================================================================
		// 3.create B Mode power control
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgPower, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgPower = (IUsgPower*)pIUnknown;
		}
		else
		{
			pUsgPower = NULL;
			ReturnResultValue=113;
			return false;
		}

		
		// 4.create B Mode range control
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgDynamicRange, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgDynamicRange = (IUsgDynamicRange*)pIUnknown;
		}
		else
		{
			pUsgDynamicRange = NULL;
			ReturnResultValue=114;
			return false;
		}

		
		// 5.create B Mode Frequency control
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgProbeFrequency3, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgProbeFrequency3 = (IUsgProbeFrequency3*)pIUnknown;
		}
		else
		{
			pUsgProbeFrequency3 = NULL;
			ReturnResultValue=115;
			return false;
		}

	
		// 6.create B Mode Scan Direction control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgImageOrientation, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgImageOrientation = (IUsgImageOrientation*)pIUnknown;
		}
		else
		{
			pUsgImageOrientation = NULL;
			ReturnResultValue=116;
			return false;
		}

		
		//=================================================================================================
		// 7.create B Mode Frame Averaging control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgFrameAvg, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgFrameAvg = (IUsgFrameAvg*)pIUnknown;
		}
		else
		{
			pUsgFrameAvg = NULL;
			ReturnResultValue=117;
			return false;
		}

		// 8.create B Mode Rejection control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgRejection2, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgRejection2 = (IUsgRejection2*)pIUnknown;
		}
		else
		{
			pUsgRejection2 = NULL;
			ReturnResultValue=118;
			return false;
		}

		
		// 9.create B Mode Line Density control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgLineDensity, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgLineDensity = (IUsgLineDensity*)pIUnknown;
		}
		else
		{
			pUsgLineDensity = NULL;
			ReturnResultValue=119;
			return false;
		}

		// 10.create B Mode View Area control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgViewArea, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgViewArea = (IUsgViewArea*)pIUnknown;
		}
		else
		{
			pUsgViewArea = NULL;
			ReturnResultValue=120;
			return false;
		}

		//11.create B Mode Image Enhance control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgImageEnhancement, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgImageEnhancement = (IUsgImageEnhancement*)pIUnknown;
		}
		else
		{
			pUsgImageEnhancement= NULL;
			ReturnResultValue=121;
			return false;
		}


		//12.create B Mode Speckle Reduction control--
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgClearView, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgClearView = (IUsgClearView*)pIUnknown;
		}
		else
		{
			pUsgClearView = NULL;
			ReturnResultValue=122;
			return false;
		}

		//------------------------------------------------------------------------------------------------
		//**13.create B Mode Focus control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgFocus, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgFocus = (IUsgFocus*)pIUnknown;
		}
		else
		{
			pUsgFocus = NULL;
			ReturnResultValue=123;
			return false;
		}

		
		//------------------------------------------------------------------------------------------------
		//**14.create B Mode TGC control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgTgc, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgTgc = (IUsgTgc*)pIUnknown;
		}
		else
		{
			pUsgTgc = NULL;
			ReturnResultValue=124;
			return false;
		}

		//------------------------------------------------------------------------------------------------
		//**15.create B Mode Palette control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgPalette, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgPalette = (IUsgPalette*)pIUnknown;
		}
		else
		{
			pUsgPalette = NULL;
			ReturnResultValue=125;
			return false;
		}

		//**16.create B Mode Palette control of helper object************
		HRESULT hr = S_OK;
		hr = CoCreateInstance(CLSID_UsgPaletteCalculator, NULL, CLSCTX_INPROC_SERVER, IID_IUsgPaletteCalculator,(LPVOID*) &pUsgPaletteCalculator);
		if ( (hr != S_OK) || (pUsgPaletteCalculator == NULL) )
		{
			pUsgPaletteCalculator = NULL;
			ReturnResultValue=126;
			return false;
		}
		//------------------------------------------------------------------------------------------------------------------
		//**17.create B Mode ImageProperties control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgImageProperties, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgImageProperties = (IUsgImageProperties*)pIUnknown;
		}
		else
		{
			pUsgImageProperties = NULL;
			ReturnResultValue=127;
			return false;
		}
		//**18.create B Mode ScanLineProperties control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgScanLineProperties, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgScanLineProperties = (IUsgScanLineProperties*)pIUnknown;
		}
		else
		{
			pUsgScanLineProperties = NULL;
			ReturnResultValue=128;
			return false;
		}

		//**19.create B Mode frame rate control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgQualProp, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgQualProp = (IUsgQualProp*)pIUnknown;
		}
		else
		{
			pUsgQualProp = NULL;
			ReturnResultValue=129;
			return false;
		}
		//**20.create B Mode mechanical bioeffects control*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgBioeffectsIndices, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgBioeffectsIndices = (IUsgBioeffectsIndices*)pIUnknown;
		}
		else
		{
			pUsgBioeffectsIndices = NULL;
			ReturnResultValue=130;
			return false;
		}
		//------------------------------------------------------------------------------------------------------------------
		//**21.create B Mode B scan-converter plug-in*****************
		pIUnknown = NULL;
		CreateUsgControl(pUsgDataView, IID_IUsgScanConverterPlugin, LogicScanModeID, 0, (void**)&pIUnknown );
		if (pIUnknown != NULL)
		{
			pUsgScanConverterPlugin = (IUsgScanConverterPlugin*)pIUnknown;
		}
		else
		{
			pUsgScanConverterPlugin = NULL;
			ReturnResultValue=131;
			return false;
		}




		pDrawImage=new DrawImage();
		pDrawImage->pMixerControl=pMixerControl;
		pDrawImage->pUsgFocus=pUsgFocus;
		pDrawImage->pUsgTgc=pUsgTgc;
		pDrawImage->pUsgImageProperties=pUsgImageProperties; 
		//------------------------------------------------------------------------------------------------------------------
	   ConnectionUsgCtrlChangeEventPoint(); //--建立连接点--
       pUsgDataView ->put_ScanState(SCAN_STATE_RUN);
	   return true;
	}
	
	BOOL  CUSGFW2ForMX::CloseUSGGenerator()
	{

		if (pUsgDataView != NULL)
		pUsgDataView->put_ScanState(SCAN_STATE_STOP);
		DisConnectionUsgCtrlChangeEventPoint();
		SAFE_RELEASE(pUsgConnectionPoint);
		//---------------------------------------
		SAFE_RELEASE(pUsgDepth);
		SAFE_RELEASE(pUsgGain);
		//---------------------------------------
		SAFE_RELEASE(pUsgPower);
		SAFE_RELEASE(pUsgDynamicRange);
		SAFE_RELEASE(pUsgProbeFrequency3);
	    SAFE_RELEASE(pUsgImageOrientation);
		//--------------------------------------
		SAFE_RELEASE(pUsgFrameAvg);
	    SAFE_RELEASE(pUsgRejection2);
	    SAFE_RELEASE(pUsgLineDensity);
  	    SAFE_RELEASE(pUsgViewArea);
		 //----------------------------------------
		SAFE_RELEASE(pUsgImageEnhancement);
		SAFE_RELEASE(pUsgClearView);
		 //----------------------------------------
		 SAFE_RELEASE(pUsgFocus);
		 SAFE_RELEASE(pUsgTgc);
		 SAFE_RELEASE(pUsgPalette);
		 SAFE_RELEASE(pUsgPaletteCalculator);
		//----------------------------------------
		SAFE_RELEASE(pUsgImageProperties);
		SAFE_RELEASE(pUsgScanLineProperties);
		SAFE_RELEASE(pUsgQualProp);;
		SAFE_RELEASE(pUsgBioeffectsIndices);
		//--------------------------------------
		SAFE_RELEASE(pUsgScanConverterPlugin);

		SAFE_DELETE(pDrawImage);
		 //--------------------------------------
		SAFE_RELEASE(pMixerControl);
		SAFE_RELEASE(pUsgDataView);
	    return true;

	}
	//=======================================================================================================================================================
	void CUSGFW2ForMX::FreezeImage()
	{
       if (pUsgDataView == NULL) return;
		pUsgDataView ->put_ScanState(SCAN_STATE_FREEZE);
		USGFreezeStatus=!USGFreezeStatus;
		return;
	}
	void CUSGFW2ForMX::RunImageView()
	{
        if (pUsgDataView == NULL) return;
		pUsgDataView ->put_ScanState(SCAN_STATE_RUN);
		return;
	}

	void CUSGFW2ForMX::AcquireImage()
	{
       if (pUsgDataView == NULL) return;
		pUsgDataView ->put_ScanState(SCAN_STATE_ACQUIRE);
		return;
	}
	void CUSGFW2ForMX::StopImageView()
	{
        if (pUsgDataView == NULL) return;
		pUsgDataView ->put_ScanState(SCAN_STATE_STOP);
		return;
	}
	void CUSGFW2ForMX::SaveImageToFile(LPTSTR pwszUrl)
	{
   
		if (pUsgDataView == NULL) return;
		if (pMixerControl == NULL) return;

		HBITMAP bmp = NULL;
		HBITMAP bmp2 = NULL;
		pMixerControl->GetCurrentBitmap((LONG*)&bmp);
		if (bmp == NULL) return;

		bool need_flip;
		need_flip = false;

		LPBITMAPINFO    pbmi;
		pbmi = DSGetBITMAPINFOForDIBSection(bmp);
		if ( !pbmi )
		{
			::DeleteObject(bmp);
			bmp = NULL;
			return;
		}

		// begin: flip image up/down
		int h, pitch;
		h = abs(pbmi->bmiHeader.biHeight);
		pitch = BYTESPERLINE(abs(pbmi->bmiHeader.biWidth),pbmi->bmiHeader.biBitCount);
		free(pbmi);
		LPBYTE src;
		LPBYTE dst;
		bmp2 = DSCopyBitmap(bmp, NULL);
		src = DSGetPointerToDIBSectionImageBits(bmp);
		src += (pitch*(h-1));
		dst = DSGetPointerToDIBSectionImageBits(bmp2);
		for (int i1=0; i1<h; i1++)
		{
			memcpy(dst,src,pitch);
			dst += pitch;
			src -= pitch;
		}
		src = NULL;
		dst = NULL;
		if (bmp != NULL)
		{
			::DeleteObject(bmp);
			bmp = NULL;
		}
		// end: flip image up/down 
		/*
		CFileDialog dlg(FALSE,L"bmp",NULL,OFN_OVERWRITEPROMPT,L"Bitmap Files (*.bmp)|*.bmp|");
		if (dlg.DoModal() == IDOK)
		{
			CString fn;
			fn = dlg.GetPathName();
			if (bmp2 != NULL)
			{
				LPTSTR str = fn.GetBuffer();
				DSStoreDIBSectionInBMPFile(str,bmp2);
				fn.ReleaseBuffer();
			}
		}
		*/
		DSStoreDIBSectionInBMPFile(pwszUrl,bmp2);
		if (bmp2 != NULL)
		{
			::DeleteObject(bmp2);
			bmp2 = NULL;
		}
		return ;

	}
	LONG  CUSGFW2ForMX::GetProbesCount()
	{
		return ProbesCount;
	}

	//**************************************************************************************************************
	void CUSGFW2ForMX::DepthSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
{
	if (pUsgDepth == NULL) return;
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;
	//---1-读取初始值------------------------------------------------------
	pUsgDepth->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgDepth->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;
	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
				VARIANT item;
				LONG val_Temp;
				pUsgValues->Item( i, &item );
				val_Temp = item.lVal;
				if ( val_Current == val_Temp )
					val_Index = i;
				VariantClear(&item);
	}
	//--2.-开始设置初始值----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
				if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
				if (SetCurrentIndex < 0) SetCurrentIndex = 0;

				if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item(SetCurrentIndex, &item );
					val_Current = item.lVal;
					    LONG val_Temp;
						pUsgDepth->get_Current(&val_Temp);
						if (val_Temp != val_Current)
				    	pUsgDepth->put_Current(val_Current);
					VariantClear(&item);
				}
	      
				
	}

	else  //方向更新
	{
	
				if (val_Index >= 0)
				{
					val_Index +=  DirectionFlag;
					if ( (val_Index >= 0) && (val_Index < val_Count) )
					{
						VARIANT item;
						pUsgValues->Item( val_Index, &item );
						val_Current = item.lVal;
						LONG val_Temp;
						pUsgDepth->get_Current(&val_Temp);
						if (val_Temp != val_Current)
							pUsgDepth->put_Current(val_Current);
						VariantClear(&item);
					}
				}
 	}

	SAFE_RELEASE(pUsgValues);
} 
    void CUSGFW2ForMX::GainSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
{
	if (pUsgGain == NULL) return;
	/*

	if(DirectionFlag==0)
	{
		pUsgGain->put_Current(SetCurrentIndex);
		return;
	}
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;

	//---1-------------------------------------------------------
	pUsgGain->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgGain->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		LONG val_Temp;
		pUsgValues->Item( i, &item );
		val_Temp = item.lVal;
		if ( val_Current == val_Temp )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.----------------------------------------------------------
	if (val_Index >= 0)
	{
		val_Index +=  DirectionFlag;
		if ( (val_Index >= 0) && (val_Index < val_Count) )
		{
			VARIANT item;
			pUsgValues->Item( val_Index, &item );
			val_Current = item.lVal;
			LONG val_Temp;
			pUsgDepth->get_Current(&val_Temp);
			if (val_Temp != val_Current)
				pUsgDepth->put_Current(val_Current);
			VariantClear(&item);
		}
	}

	/*
	LONG val_Current;
	LONG val_Count;

	pUsgGain->get_Current(&val_Current);

	IUsgValues* pUsgValues = NULL;
	pUsgGain->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	if (idx >= val_Count) idx = val_Count - 1;
	if (idx < 0) idx = 0;

	if ( (idx >= 0) && (idx < val_Count) )
	{
		VARIANT item;
		pUsgValues->Item( idx, &item );
		val_Current = item.lVal;
		LONG val;
		pUsgGain->get_Current(&val);
		if (val != val_Current)
			pUsgGain->put_Current(val_Current);
		VariantClear(&item);
	}
	*/
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;

	//---1------------------------------------------------------------------
	pUsgGain->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgGain->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		LONG val_Temp;
		pUsgValues->Item( i, &item );
		val_Temp = item.lVal;
		if ( val_Current == val_Temp )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.-----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
			if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
			if (SetCurrentIndex < 0) SetCurrentIndex = 0;

			if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
			{
				VARIANT item;
				pUsgValues->Item(SetCurrentIndex, &item );
				val_Current = item.lVal;
				    LONG val_Temp;
					pUsgGain->get_Current(&val_Temp);
					if (val_Temp != val_Current)
				pUsgGain->put_Current(val_Current);
				VariantClear(&item);
			}
						
				
	}

	else  //按方向更新
	{
	
			if (val_Index >= 0)
			{
				val_Index +=  DirectionFlag;
				if ( (val_Index >= 0) && (val_Index < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item( val_Index, &item );
					val_Current = item.lVal;
					LONG val_Temp;
					pUsgGain->get_Current(&val_Temp);
					if (val_Temp != val_Current)
						pUsgGain->put_Current(val_Current);
					VariantClear(&item);
				}
			}
 	}


	SAFE_RELEASE(pUsgValues);
} 
    void CUSGFW2ForMX::PowerSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
{
	if (pUsgPower == NULL) return;
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;

	//---1------------------------------------------------------------------
	pUsgPower->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgPower->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		LONG val_Temp;
		pUsgValues->Item( i, &item );
		val_Temp = item.lVal;
		if ( val_Current == val_Temp )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.-----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
			if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
			if (SetCurrentIndex < 0) SetCurrentIndex = 0;

			if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
			{
				VARIANT item;
				pUsgValues->Item(SetCurrentIndex, &item );
				val_Current = item.lVal;
				    LONG val_Temp;
					pUsgPower->get_Current(&val_Temp);
					if (val_Temp != val_Current)
				pUsgPower->put_Current(val_Current);
				VariantClear(&item);
			}
						
				
	}

	else  //按方向更新
	{
	
			if (val_Index >= 0)
			{
				val_Index +=  DirectionFlag;
				if ( (val_Index >= 0) && (val_Index < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item( val_Index, &item );
					val_Current = item.lVal;
					LONG val_Temp;
					pUsgPower->get_Current(&val_Temp);
					if (val_Temp != val_Current)
						pUsgPower->put_Current(val_Current);
					VariantClear(&item);
				}
			}
 	}


	SAFE_RELEASE(pUsgValues);
} 
    void CUSGFW2ForMX::Frequency3SetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
{
	/*
	if (pUsgProbeFrequency3 == NULL) return;
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;

	//---1------------------------------------------------------------------
	pUsgProbeFrequency3->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgProbeFrequency3->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		LONG val_Temp;
		pUsgValues->Item( i, &item );
		val_Temp = item.lVal;
		if ( val_Current == val_Temp )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.-----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
			if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
			if (SetCurrentIndex < 0) SetCurrentIndex = 0;

			if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
			{
				VARIANT item;
				pUsgValues->Item(SetCurrentIndex, &item );
				val_Current = item.lVal;
				    LONG val_Temp;
					pUsgProbeFrequency3->get_Current(&val_Temp);
					if (val_Temp != val_Current)
				pUsgProbeFrequency3->put_Current(val_Current);
				VariantClear(&item);
			}
						
				
	}

	else  //按方向更新
	{
	
			if (val_Index >= 0)
			{
				val_Index +=  DirectionFlag;
				if ( (val_Index >= 0) && (val_Index < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item( val_Index, &item );
					val_Current = item.lVal;
					LONG val_Temp;
					pUsgProbeFrequency3->get_Current(&val_Temp);
					if (val_Temp != val_Current)
						pUsgProbeFrequency3->put_Current(val_Current);
					VariantClear(&item);
				}
			}
 	}


	SAFE_RELEASE(pUsgValues);
	*/
	if (pUsgProbeFrequency3 == NULL) return;
	FREQUENCY3  mCurrentFREQUENCY3Struc;
	LONG val_Index;
	LONG val_Count;
	//---1------------------------------------------------------------------
	pUsgProbeFrequency3->get_Current(& mCurrentFREQUENCY3Struc);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgProbeFrequency3->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		FREQUENCY3* mpFREQUENCY3StrucTemp;
		pUsgValues->Item( i, &item );
		mpFREQUENCY3StrucTemp =(FREQUENCY3*)item.pcyVal;
		if ( mCurrentFREQUENCY3Struc.nFrequency == mpFREQUENCY3StrucTemp->nFrequency )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.-----------------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
			if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
			if (SetCurrentIndex < 0) SetCurrentIndex = 0;
			if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
			{
				VARIANT item;
				pUsgValues->Item(SetCurrentIndex, &item );
				FREQUENCY3* mpFREQUENCY3StrucTemp;
				mpFREQUENCY3StrucTemp =(FREQUENCY3*)item.pcyVal;
				if ( mCurrentFREQUENCY3Struc.nFrequency != mpFREQUENCY3StrucTemp->nFrequency)
					{
				        mCurrentFREQUENCY3Struc.nFrequency =mpFREQUENCY3StrucTemp->nFrequency;
				        mCurrentFREQUENCY3Struc.nThiMode=mpFREQUENCY3StrucTemp->nThiMode;
					   pUsgProbeFrequency3->put_Current( mCurrentFREQUENCY3Struc);
					}
				VariantClear(&item);
			}
						
				
	}

	else  //按方向更新
	{
	
			if (val_Index >= 0)
			{
				val_Index +=  DirectionFlag;
				if ( (val_Index >= 0) && (val_Index < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item( val_Index, &item );
					FREQUENCY3* mpFREQUENCY3StrucTemp;
				    mpFREQUENCY3StrucTemp =(FREQUENCY3*)item.pcyVal;

					if ( mCurrentFREQUENCY3Struc.nFrequency != mpFREQUENCY3StrucTemp->nFrequency)
					{
				        mCurrentFREQUENCY3Struc.nFrequency =mpFREQUENCY3StrucTemp->nFrequency;
				        mCurrentFREQUENCY3Struc.nThiMode=mpFREQUENCY3StrucTemp->nThiMode;
					   pUsgProbeFrequency3->put_Current( mCurrentFREQUENCY3Struc);
					}
					
					VariantClear(&item);
				}
			}
 	}

	SAFE_RELEASE(pUsgValues);
} 
	void CUSGFW2ForMX::DynamicRangeSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
{
	if (pUsgDynamicRange == NULL) return;
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;

	//---1------------------------------------------------------------------
	pUsgDynamicRange->get_Current(&val_Current);
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgDynamicRange->get_Values(&pUsgValues);
	if (pUsgValues == NULL) return;

	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
		VARIANT item;
		LONG val_Temp;
		pUsgValues->Item( i, &item );
		val_Temp = item.lVal;
		if ( val_Current == val_Temp )
			val_Index = i;
		VariantClear(&item);
	}
	//--2.-----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
			if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
			if (SetCurrentIndex < 0) SetCurrentIndex = 0;

			if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
			{
				VARIANT item;
				pUsgValues->Item(SetCurrentIndex, &item );
				val_Current = item.lVal;
				    LONG val_Temp;
					pUsgDynamicRange->get_Current(&val_Temp);
					if (val_Temp != val_Current)
				pUsgDynamicRange->put_Current(val_Current);
				VariantClear(&item);
			}
						
				
	}

	else  //按方向更新
	{
	
			if (val_Index >= 0)
			{
				val_Index +=  DirectionFlag;
				if ( (val_Index >= 0) && (val_Index < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item( val_Index, &item );
					val_Current = item.lVal;
					LONG val_Temp;
					pUsgDynamicRange->get_Current(&val_Temp);
					if (val_Temp != val_Current)
						pUsgDynamicRange->put_Current(val_Current);
					VariantClear(&item);
				}
			}
 	}


	SAFE_RELEASE(pUsgValues);
} 
	void CUSGFW2ForMX::ScaningDirctionSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
    {
		if ( pUsgImageOrientation == NULL) return;
		if(DirectionFlag==0) // 0:	镜像变换
		{
			LONG val_Current;
	    	pUsgImageOrientation->get_Mirror(&val_Current);
			if(val_Current!=SetCurrentIndex)
			pUsgImageOrientation->put_Mirror(SetCurrentIndex);
		}
		else //1：旋转变换
		{
			LONG val_Current;
			IMAGE_ROTATE mImageRotateID;
			pUsgImageOrientation->get_Rotate(&mImageRotateID);
			val_Current=(LONG)mImageRotateID;
			if(val_Current!=SetCurrentIndex)
				pUsgImageOrientation->put_Rotate((IMAGE_ROTATE)SetCurrentIndex); ;
		}

		 return;

    } 
	void CUSGFW2ForMX::FrameAveragingSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
       
	if ( pUsgFrameAvg == NULL) return;//1.
	LONG val_Current;
	LONG val_Index;
	LONG val_Count;
	//---1-读取初始值------------------------------------------------------
	 pUsgFrameAvg->get_Current(&val_Current);//2.
	val_Index= -1;

	IUsgValues* pUsgValues = NULL;
	pUsgFrameAvg->get_Values(&pUsgValues);//3.
	if (pUsgValues == NULL) return;
	pUsgValues->get_Count(&val_Count);

	for (LONG i = 0; i < val_Count; i++)
	{
				VARIANT item;
				LONG val_Temp;
				pUsgValues->Item( i, &item );
				val_Temp = item.lVal;
				if ( val_Current == val_Temp )
					val_Index = i;
				VariantClear(&item);
	}
	//--2.-开始设置初始值----------------------------------------------------------------------
	if(DirectionFlag==0)//按索引号更新
	{
		
				if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
				if (SetCurrentIndex < 0) SetCurrentIndex = 0;
				if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
				{
					VARIANT item;
					pUsgValues->Item(SetCurrentIndex, &item );
					val_Current = item.lVal;
					    LONG val_Temp;
						pUsgFrameAvg->get_Current(&val_Temp);//4.
						if (val_Temp != val_Current)
				    	pUsgFrameAvg->put_Current(val_Current);//5.
					VariantClear(&item);
				}
	      
				
	}

	else  //方向更新
	{
	
				if (val_Index >= 0)
				{
					val_Index +=  DirectionFlag;
					if ( (val_Index >= 0) && (val_Index < val_Count) )
					{
						VARIANT item;
						pUsgValues->Item( val_Index, &item );
						val_Current = item.lVal;
						LONG val_Temp;
						 pUsgFrameAvg->get_Current(&val_Temp);//6.
						if (val_Temp != val_Current)
							pUsgFrameAvg->put_Current(val_Current);//7.
						VariantClear(&item);
					}
				}
 	}

	SAFE_RELEASE(pUsgValues);
	return;
	}
	void CUSGFW2ForMX::LineDensitySetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
         
		if ( pUsgLineDensity == NULL) return;//1.
			LONG val_Current;
			LONG val_Index;
			LONG val_Count;
			//---1-读取初始值------------------------------------------------------
			 pUsgLineDensity->get_Current(&val_Current);//2.
			val_Index= -1;

			IUsgValues* pUsgValues = NULL;
			pUsgLineDensity->get_Values(&pUsgValues);//3.
			if (pUsgValues == NULL) return;
			pUsgValues->get_Count(&val_Count);

			for (LONG i = 0; i < val_Count; i++)
			{
						VARIANT item;
						LONG val_Temp;
						pUsgValues->Item( i, &item );
						val_Temp = item.lVal;
						if ( val_Current == val_Temp )
							val_Index = i;
						VariantClear(&item);
			}
			//--2.-开始设置初始值----------------------------------------------------------------------
			if(DirectionFlag==0)//按索引号更新
			{
		
						if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
						if (SetCurrentIndex < 0) SetCurrentIndex = 0;
						if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
						{
							VARIANT item;
							pUsgValues->Item(SetCurrentIndex, &item );
							val_Current = item.lVal;
								LONG val_Temp;
								pUsgLineDensity->get_Current(&val_Temp);//4.
								if (val_Temp != val_Current)
				    			pUsgLineDensity->put_Current(val_Current);//5.
							VariantClear(&item);
						}
	      
				
			}

			else  //方向更新
			{
	
						if (val_Index >= 0)
						{
							val_Index +=  DirectionFlag;
							if ( (val_Index >= 0) && (val_Index < val_Count) )
							{
								VARIANT item;
								pUsgValues->Item( val_Index, &item );
								val_Current = item.lVal;
								LONG val_Temp;
								 pUsgLineDensity->get_Current(&val_Temp);//6.
								if (val_Temp != val_Current)
									pUsgLineDensity->put_Current(val_Current);//7.
								VariantClear(&item);
							}
						}
 			}

			SAFE_RELEASE(pUsgValues);
		
		return;
	}
	void CUSGFW2ForMX::RejectionSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
        if ( pUsgRejection2 == NULL) return;//1.
			LONG val_Current;
			LONG val_Index;
			LONG val_Count;
			//---1-读取初始值------------------------------------------------------
			 pUsgRejection2->get_Current(&val_Current);//2.
			val_Index= -1;

			IUsgValues* pUsgValues = NULL;
			pUsgRejection2->get_Values(&pUsgValues);//3.
			if (pUsgValues == NULL) return;
			pUsgValues->get_Count(&val_Count);

			for (LONG i = 0; i < val_Count; i++)
			{
						VARIANT item;
						LONG val_Temp;
						pUsgValues->Item( i, &item );
						val_Temp = item.lVal;
						if ( val_Current == val_Temp )
							val_Index = i;
						VariantClear(&item);
			}
			//--2.-开始设置初始值----------------------------------------------------------------------
			if(DirectionFlag==0)//按索引号更新
			{
		
						if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
						if (SetCurrentIndex < 0) SetCurrentIndex = 0;
						if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
						{
							VARIANT item;
							pUsgValues->Item(SetCurrentIndex, &item );
							val_Current = item.lVal;
								LONG val_Temp;
								pUsgRejection2->get_Current(&val_Temp);//4.
								if (val_Temp != val_Current)
				    			pUsgRejection2->put_Current(val_Current);//5.
							VariantClear(&item);
						}
	      
				
			}

			else  //方向更新
			{
	
						if (val_Index >= 0)
						{
							val_Index +=  DirectionFlag;
							if ( (val_Index >= 0) && (val_Index < val_Count) )
							{
								VARIANT item;
								pUsgValues->Item( val_Index, &item );
								val_Current = item.lVal;
								LONG val_Temp;
								 pUsgRejection2->get_Current(&val_Temp);//6.
								if (val_Temp != val_Current)
									pUsgRejection2->put_Current(val_Current);//7.
								VariantClear(&item);
							}
						}
 			}

			SAFE_RELEASE(pUsgValues);
		return;
	}
	void CUSGFW2ForMX::ViewZoomSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
        
		if ( pUsgViewArea == NULL) return;//1.
			LONG val_Current;
			LONG val_Index;
			LONG val_Count;
			//---1-读取初始值------------------------------------------------------
			pUsgViewArea->get_Current(&val_Current);//2.
			val_Index= -1;

			IUsgValues* pUsgValues = NULL;
			pUsgViewArea->get_Values(&pUsgValues);//3.
			if (pUsgValues == NULL) return;
			pUsgValues->get_Count(&val_Count);

			for (LONG i = 0; i < val_Count; i++)
			{
						VARIANT item;
						LONG val_Temp;
						pUsgValues->Item( i, &item );
						val_Temp = item.lVal;
						if ( val_Current == val_Temp )
							val_Index = i;
						VariantClear(&item);
			}
			//--2.-开始设置初始值----------------------------------------------------------------------
			if(DirectionFlag==0)//按索引号更新
			{
		
						if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
						if (SetCurrentIndex < 0) SetCurrentIndex = 0;
						if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
						{
							VARIANT item;
							pUsgValues->Item(SetCurrentIndex, &item );
							val_Current = item.lVal;
								LONG val_Temp;
								pUsgViewArea->get_Current(&val_Temp);//4.
								if (val_Temp != val_Current)
				    			pUsgViewArea->put_Current(val_Current);//5.
							VariantClear(&item);
						}
	      
				
			}

			else  //方向更新
			{
	
						if (val_Index >= 0)
						{
							val_Index +=  DirectionFlag;
							if ( (val_Index >= 0) && (val_Index < val_Count) )
							{
								VARIANT item;
								pUsgValues->Item( val_Index, &item );
								val_Current = item.lVal;
								LONG val_Temp;
								 pUsgViewArea->get_Current(&val_Temp);//6.
								if (val_Temp != val_Current)
									pUsgViewArea->put_Current(val_Current);//7.
								VariantClear(&item);
							}
						}
 			}

			SAFE_RELEASE(pUsgValues);
		  return;
	}
	void CUSGFW2ForMX::ImageEnhancementSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
            if ( pUsgImageEnhancement == NULL) return;//1.
			if(DirectionFlag==-2)//状态更新
			{
                LONG mIsEnable;
	            pUsgImageEnhancement->get_Enabled(&mIsEnable);
	           if(mIsEnable!=SetCurrentIndex)
	           {
                pUsgImageEnhancement->put_Enabled(SetCurrentIndex);
			   }
               return;
			}
		   //----------------------------------------------------------------------
		    LONG val_Current;
			LONG val_Index;
			LONG val_Count;
			//---1-读取初始值------------------------------------------------------
			pUsgImageEnhancement->get_Current(&val_Current);//2.
			val_Index= -1;
			IUsgValues* pUsgValues = NULL;
			pUsgImageEnhancement->get_Values(&pUsgValues);//3.
			if (pUsgValues == NULL) return;
			pUsgValues->get_Count(&val_Count);

			for (LONG i = 0; i < val_Count; i++)
			{
						VARIANT item;
						LONG val_Temp;
						pUsgValues->Item( i, &item );
						val_Temp = item.lVal;
						if ( val_Current == val_Temp )
							val_Index = i;
						VariantClear(&item);
			}
			//--2.-开始设置初始值----------------------------------------------------------------------
			if(DirectionFlag==0)//按索引号更新
			{
		
						if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
						if (SetCurrentIndex < 0) SetCurrentIndex = 0;
						if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
						{
							VARIANT item;
							pUsgValues->Item(SetCurrentIndex, &item );
							val_Current = item.lVal;
								LONG val_Temp;
								pUsgImageEnhancement->get_Current(&val_Temp);//4.
								if (val_Temp != val_Current)
				    			pUsgImageEnhancement->put_Current(val_Current);//5.
							VariantClear(&item);
						}
	      
				
			}

			else  //方向更新
			{
	
						if (val_Index >= 0)
						{
							val_Index +=  DirectionFlag;
							if ( (val_Index >= 0) && (val_Index < val_Count) )
							{
								VARIANT item;
								pUsgValues->Item( val_Index, &item );
								val_Current = item.lVal;
								LONG val_Temp;
								 pUsgImageEnhancement->get_Current(&val_Temp);//6.
								if (val_Temp != val_Current)
									pUsgImageEnhancement->put_Current(val_Current);//7.
								VariantClear(&item);
							}
						}
 			}
 		  SAFE_RELEASE(pUsgValues);
		  return;

	}
	void CUSGFW2ForMX::ClearViewSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
	{
        if ( pUsgClearView == NULL) return;//1.
		   if(DirectionFlag==-2)//状态更新
			{
                LONG mIsEnable;
	            pUsgClearView->get_Enabled(&mIsEnable);
	           if(mIsEnable!=SetCurrentIndex)
	           {
                pUsgClearView->put_Enabled(SetCurrentIndex);
			   }
               return;
			}
		   //-----------------------------------------------------------------------

			LONG val_Current;
			LONG val_Index;
			LONG val_Count;
			//---1-读取初始值------------------------------------------------------
			pUsgClearView->get_Current(&val_Current);//2.
			val_Index= -1;

			IUsgValues* pUsgValues = NULL;
			pUsgClearView->get_Values(&pUsgValues);//3.
			if (pUsgValues == NULL) return;
			pUsgValues->get_Count(&val_Count);

			for (LONG i = 0; i < val_Count; i++)
			{
						VARIANT item;
						LONG val_Temp;
						pUsgValues->Item( i, &item );
						val_Temp = item.lVal;
						if ( val_Current == val_Temp )
							val_Index = i;
						VariantClear(&item);
			}
			//--2.-开始设置初始值----------------------------------------------------------------------
			if(DirectionFlag==0)//按索引号更新
			{
		
						if (SetCurrentIndex >= val_Count) SetCurrentIndex = val_Count - 1;
						if (SetCurrentIndex < 0) SetCurrentIndex = 0;
						if ( (SetCurrentIndex >= 0) && (SetCurrentIndex < val_Count) )
						{
							VARIANT item;
							pUsgValues->Item(SetCurrentIndex, &item );
							val_Current = item.lVal;
								LONG val_Temp;
								pUsgClearView->get_Current(&val_Temp);//4.
								if (val_Temp != val_Current)
				    			pUsgClearView->put_Current(val_Current);//5.
							VariantClear(&item);
						}
	      
				
			}

			else  //方向更新
			{
	
						if (val_Index >= 0)
						{
							val_Index +=  DirectionFlag;
							if ( (val_Index >= 0) && (val_Index < val_Count) )
							{
								VARIANT item;
								pUsgValues->Item( val_Index, &item );
								val_Current = item.lVal;
								LONG val_Temp;
								 pUsgClearView->get_Current(&val_Temp);//6.
								if (val_Temp != val_Current)
									pUsgClearView->put_Current(val_Current);//7.
								VariantClear(&item);
							}
						}
 			}

			SAFE_RELEASE(pUsgValues);
		  return;

	}
	//---------------------------------------------------------------------------------------
	void CUSGFW2ForMX::FocusSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
    {
		if ( pUsgFocus == NULL) return;
		if(DirectionFlag==0) //update mode
		{
			LONG CurrentMode;
	    	pUsgFocus->get_CurrentMode(&CurrentMode);
			if(CurrentMode!=SetCurrentIndex)
			   pUsgFocus->put_CurrentMode(SetCurrentIndex);
			// 2:dynamic focus; 1：static focus
			//if(SetCurrentIndex==2)
			// {
			//   pUsgFocus->put_FocusSet(CurrentMode,0);
		   //  }
			//else
			// {
            //   pUsgFocus->put_FocusSet(CurrentMode,SetCurrentIndex);
			// }
		}
		if(DirectionFlag==1)  //update dynamic mode focalzone
		{
				//LONG CurrentMode;
				//LONG FocusSetCount;
				//LONG FocalZonesIndex=-1;
				LONG ActiveFocusSetID;
				LONG FocalZonesCount;
				BOOL IsUpdateFocalZones=FALSE;
			    //pUsgFocus->get_FocusSetCount(2,&FocusSetCount);
				pUsgFocus->get_FocusSet(2,&ActiveFocusSetID);//default:0
				pUsgFocus->GetFocalZonesCount(2,ActiveFocusSetID,&FocalZonesCount);
				//---------------------------------------------------------------------------------
				LONG* pFocusState=new LONG[FocalZonesCount];
				pUsgFocus->GetFocusState(2,ActiveFocusSetID,FocalZonesCount,pFocusState);
				 for (LONG i = 0; i< FocalZonesCount; i++)
				{
					
					 if(pFocusState[i]==1)
						{
							if(SetCurrentIndex!=i)
							{
                                pFocusState[i]=0;//close;
								IsUpdateFocalZones=TRUE;
							}
												
				      	}
				
									
			   }
				 if(IsUpdateFocalZones)
				 {
				 	 pFocusState[SetCurrentIndex]=1;//start
					 pUsgFocus->SetFocusState(2,ActiveFocusSetID,FocalZonesCount,pFocusState);
                    
				 }
				delete [] pFocusState;

			
		}
		//-------------------------------------------------------------------------------------------------------
		if(DirectionFlag==2)//update static mode focus
		{
         LONG ActiveFocusSetID;
		 pUsgFocus->get_FocusSet(1,&ActiveFocusSetID);
		 if(ActiveFocusSetID!=SetCurrentIndex)
		  pUsgFocus->put_FocusSet(1,SetCurrentIndex);

		}

		if(DirectionFlag==3)//update static mode focus zone
		{
				LONG ActiveFocusSetID;
				LONG FocalZonesCount;
				BOOL IsUpdateFocalZones=FALSE;
				LONG FocalZonesNumber=0;
			    //pUsgFocus->get_FocusSetCount(1,&FocusSetCount);
				pUsgFocus->get_FocusSet(1,&ActiveFocusSetID);
				pUsgFocus->GetFocalZonesCount(1,ActiveFocusSetID,&FocalZonesCount);
				//---------------------------------------------------------------------------------
				LONG* pFocusState=new LONG[FocalZonesCount];
				pUsgFocus->GetFocusState(1,ActiveFocusSetID,FocalZonesCount,pFocusState);
				//----1.---------------------------------------------------
				 for (LONG i = 0; i< FocalZonesCount; i++)
					{
					
						if(pFocusState[i]==1)
							{
								FocalZonesNumber++;
										
				      		}
						
									
					 }
				 //--2.-----------------------------------------------------
				  if(SetCurrentIndex!=FocalZonesNumber)
				  {	
							 for (LONG i = 0; i< FocalZonesCount; i++)
							 {
						    	pFocusState[i]=0;
							 }
							IsUpdateFocalZones=TRUE;
			       }
					
				  //--3.------------------------------------------------------
				 if(IsUpdateFocalZones)
				 {
				 	/*
							 switch(SetCurrentIndex)
						{
							 case 1:
                                 pFocusState[0]=1;
								 break;

                              case 2:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								 break;
                             
							   case 3:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								   pFocusState[2]=1;
								 break;
                               case 4:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								   pFocusState[2]=1;
								   pFocusState[3]=1;
								 break;


						 }*/

					
                     for (LONG i = 0; i< SetCurrentIndex; i++)
							{
						   pFocusState[i]=1;
									      										
							 }
					 
					 pUsgFocus->SetFocusState(1,ActiveFocusSetID,FocalZonesCount,pFocusState);
                    
				 }
				delete [] pFocusState;


		}
		if(DirectionFlag==4)//update static mode focus zone begin
		{
				LONG ActiveFocusSetID;
				LONG FocalZonesCount;
				BOOL IsUpdateFocalZones=FALSE;
				LONG FocalZonesNumber=0;//统计个数
				LONG FocalZonesIndex=-1;//说明起点
			    //pUsgFocus->get_FocusSetCount(1,&FocusSetCount);
				pUsgFocus->get_FocusSet(1,&ActiveFocusSetID);
				pUsgFocus->GetFocalZonesCount(1,ActiveFocusSetID,&FocalZonesCount);
				//---------------------------------------------------------------------------------
				LONG* pFocusState=new LONG[FocalZonesCount];
				pUsgFocus->GetFocusState(1,ActiveFocusSetID,FocalZonesCount,pFocusState);
				//----1.---------------------------------------------------
				 for (LONG i = 0; i< FocalZonesCount; i++)
					{
					
						if(pFocusState[i]==1)
							{
								
                                if(FocalZonesIndex==-1)FocalZonesIndex=i;
								FocalZonesNumber++;
										
				      		}
						
									
					 }
				 //--2.-----------------------------------------------------
				  if(SetCurrentIndex!=FocalZonesIndex)
				  {	
							 for (LONG i = 0; i< FocalZonesCount; i++)
							 {
						    	pFocusState[i]=0;
							 }
							IsUpdateFocalZones=TRUE;
			       }
					
				  //--3.------------------------------------------------------
				 if(IsUpdateFocalZones)
				 {
				 	  /*
							 switch(SetCurrentIndex)
						{
							 case 1:
                                 pFocusState[0]=1;
								 break;

                              case 2:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								 break;
                             
							   case 3:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								   pFocusState[2]=1;
								 break;
                               case 4:
								   pFocusState[0]=1;
								   pFocusState[1]=1;
								   pFocusState[2]=1;
								   pFocusState[3]=1;
								 break;


						 }
							 */
					 LONG mCount=0;
                     for (LONG i = 0; i< FocalZonesCount; i++)
					{
						 
						  if(i>=SetCurrentIndex)
							{
					            pFocusState[i]=1;
								mCount++;
										
				      		}
						 if(mCount>=FocalZonesNumber)break;
									
					 }
    				 pUsgFocus->SetFocusState(1,ActiveFocusSetID,FocalZonesCount,pFocusState);
                    
				 }
				delete [] pFocusState;


		}

		 return;

    } 
	void CUSGFW2ForMX::TGCSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
    {
		if (pUsgTgc == NULL) return;
		if(DirectionFlag==0) //update-- CtlPointsCount
		{
			LONG CurrentCount;
	    	pUsgTgc->get_CtlPointsCount(&CurrentCount);
			if(CurrentCount!=SetCurrentIndex)pUsgTgc->put_CtlPointsCount(SetCurrentIndex);
			
		}
		if(DirectionFlag>0&&DirectionFlag<10)//1--10: update Current control point value
		{
            LONG CurrentTGCValue;
			pUsgTgc->get_Current(DirectionFlag-1,&CurrentTGCValue); 
			if(CurrentTGCValue!=SetCurrentIndex)pUsgTgc->put_Current(DirectionFlag-1,SetCurrentIndex); 
				
		}

		if(DirectionFlag>99&&DirectionFlag<200)//>99:Set TGC values (%) for each TGC curve point,advanced TGC adjustment[A]
		{
            LONG TGCCurvePointSize;
			LONG CurrentTGCCurveValue;
			LONG* pTGCCurvePointValue;
			pUsgTgc->GetTgcSize(&TGCCurvePointSize); 
			pTGCCurvePointValue=new LONG[TGCCurvePointSize];
			HRESULT hr=pUsgTgc->GetTgcEntries(0,TGCCurvePointSize,pTGCCurvePointValue); 
			switch(SetCurrentIndex)
			{
			case 1: CurrentTGCCurveValue=10;break;
			case 2: CurrentTGCCurveValue=20;break;
            case 3: CurrentTGCCurveValue=30;break;
			case 4: CurrentTGCCurveValue=40;break;
            case 5: CurrentTGCCurveValue=50;break;
            case 6: CurrentTGCCurveValue=60;break;
            case 7: CurrentTGCCurveValue=70;break;
			default:  CurrentTGCCurveValue=100;break;
			}
			for(int i=0;i<TGCCurvePointSize;i++)
			{
				pTGCCurvePointValue[i]=CurrentTGCCurveValue;
				
			}
			HRESULT hrX=pUsgTgc->SetTgcEntries(0,TGCCurvePointSize,pTGCCurvePointValue); 

			delete [] pTGCCurvePointValue;
				
		}

		if(DirectionFlag>199)//>199:Set TGC values (%) for each TGC curve point,advanced TGC adjustment[B]
		{
			LONG PositionOfDepth;
         	pUsgTgc->DepthToPosition(SetCurrentIndex,&PositionOfDepth); 
			int test1=0;
			test1++;




		}

		 return;

    } 
	void CUSGFW2ForMX::PaletteSetByIndex(LONG DirectionFlag,LONG SetCurrentIndex)
    {
		if (pUsgPalette == NULL) return;
		int PaletteLength=256;
		PALETTEENTRY* PaletteArray=new PALETTEENTRY[PaletteLength];
		LONG* ReferenceDataArrayIn=new LONG[256];
		LONG* ReferenceDataArrayOut=new LONG[256];
		///BOOL mIsNegative;
		pUsgPalette->GetPaletteEntries(0, PaletteLength,PaletteArray);
		for(int i=0;i<PaletteLength;i++)
		{
            ReferenceDataArrayIn[i]=i;//PaletteArray[i].peBlue;
				
		}
		pUsgPaletteCalculator->SetReferenceData(255,256,ReferenceDataArrayIn);
		//-------------------------------------------------------------------
		if(DirectionFlag==0) //--Negative--
		{
			//-----------------------------------------
			pUsgPaletteCalculator->put_Gamma(100);
		    pUsgPaletteCalculator->put_Brightness(0);
		    pUsgPaletteCalculator->put_Contrast(0);
			pUsgPaletteCalculator->put_Negative(SetCurrentIndex); 
			pUsgPaletteCalculator->Calculate(0,256,ReferenceDataArrayOut);
			for(int i=0;i<PaletteLength;i++)
			{
				PaletteArray[i].peBlue=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peGreen=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peRed=(BYTE)ReferenceDataArrayOut[i];   
				
			}
		
		    /*
			//--My Define------------------------------
			if(SetCurrentIndex!=0)
			{
						for(int i=0;i<PaletteLength;i++)
						{
							PaletteArray[i].peBlue=255-i;
							PaletteArray[i].peGreen=255-i;
							PaletteArray[i].peRed=255-i;   
				
						}
			}
			else
			{
						for(int i=0;i<PaletteLength;i++)
						{
							PaletteArray[i].peBlue=i;
							PaletteArray[i].peGreen=i;
							PaletteArray[i].peRed=i;   
				
						}
			}
			  */

				
		}		
			
		if(DirectionFlag==1)//----Set Default value----
		{
     
			pUsgPaletteCalculator->put_Gamma(100);
		    pUsgPaletteCalculator->put_Brightness(0);
		    pUsgPaletteCalculator->put_Contrast(0);
			pUsgPaletteCalculator->put_Negative(0); 
			pUsgPaletteCalculator->Calculate(0,256,ReferenceDataArrayOut);
			for(int i=0;i<PaletteLength;i++)
			{
				PaletteArray[i].peBlue=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peGreen=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peRed=(BYTE)ReferenceDataArrayOut[i];   
				
			}
			
				
		}

		if(DirectionFlag==3)//----Change Gamma value----
		{
     
			pUsgPaletteCalculator->put_Gamma(SetCurrentIndex);
		   // pUsgPaletteCalculator->put_Brightness(0);
		   // pUsgPaletteCalculator->put_Contrast(0);
		   pUsgPaletteCalculator->put_Negative(0); 
			pUsgPaletteCalculator->Calculate(0,256,ReferenceDataArrayOut);
			for(int i=0;i<PaletteLength;i++)
			{
				PaletteArray[i].peBlue=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peGreen=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peRed=(BYTE)ReferenceDataArrayOut[i];   
				
			}
			
				
		}
		if(DirectionFlag==4)//----Change Brightness value----
		{
             pUsgPaletteCalculator->put_Brightness(SetCurrentIndex);
			//pUsgPaletteCalculator->put_Gamma(SetCurrentIndex);
		    //pUsgPaletteCalculator->put_Contrast(0);
		    pUsgPaletteCalculator->put_Negative(0); 
			pUsgPaletteCalculator->Calculate(0,256,ReferenceDataArrayOut);
			for(int i=0;i<PaletteLength;i++)
			{
				PaletteArray[i].peBlue=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peGreen=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peRed=(BYTE)ReferenceDataArrayOut[i];   
				
			}
			
				
		}
		if(DirectionFlag==5)//----Change Contrast value----
		{
             pUsgPaletteCalculator->put_Contrast(SetCurrentIndex);
			//pUsgPaletteCalculator->put_Gamma(SetCurrentIndex);
		    //pUsgPaletteCalculator->put_Brightness(SetCurrentIndex);
		    pUsgPaletteCalculator->put_Negative(0); 
			pUsgPaletteCalculator->Calculate(0,256,ReferenceDataArrayOut);
			for(int i=0;i<PaletteLength;i++)
			{
				PaletteArray[i].peBlue=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peGreen=(BYTE)ReferenceDataArrayOut[i];
				PaletteArray[i].peRed=(BYTE)ReferenceDataArrayOut[i];   
				
			}
			
				
		}
		pUsgPalette->SetPaletteEntries(0, PaletteLength,PaletteArray);
		delete [] PaletteArray;
		delete [] ReferenceDataArrayIn;
	    delete [] ReferenceDataArrayOut;
		return;

    } 

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++==
 LONG  CUSGFW2ForMX::UpdateUSGStatus(USG_STATUS USGStatusID,LONG SetWayID,LONG SetCurrentValue)
{
	mGlobeUSGStatusID=USG_STATUS_NULL;
	LONG GetCurrentValue=-1;
	//if(mEventSyncHandle==NULL) mEventSyncHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	ResetEvent(mEventSyncHandle);//--开始准备同步------------
		//----------------------------------------------------------------------------------------
		switch(USGStatusID)
		{

		case USG_STATUS_DEPTH:
	    DepthSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		//-----------
		/*
		if(mGlobeUSGStatusID==USG_STATUS_DEPTH)
		{
           this->pUsgDepth->get_Current(&GetCurrentValue);

		}
		*/
		break;

		case USG_STATUS_GAIN:
        GainSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		if(mhAsyncStatusResult==S_OK)//
		{
          GetCurrentValue=0;
		}
		break;

		case USG_STATUS_POWER:
        PowerSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		
		case USG_STATUS_FREQUENCY:
        Frequency3SetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_DYNAMIC_RANGE:
        DynamicRangeSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_IMAGE_ORIENTATION:
        ScaningDirctionSetByIndex(SetWayID,SetCurrentValue);//旋转与镜像变换用同一个函数！
		WaitForEvent(mEventSyncHandle);
		break;
		//-------------------------------------------------------
		case USG_STATUS_FRAME_AVERAGING:
        FrameAveragingSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_REJECTION:
        RejectionSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_LINE_DENSITY:
        LineDensitySetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;
		
		case USG_STATUS_VIEW_ZOOM:
        ViewZoomSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		
		case USG_STATUS_IMAGE_ENHANCE:
        ImageEnhancementSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_SPECKLE_REDUCTION:
        ClearViewSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;
		
		//------------------------------------------------------
		case USG_STATUS_FOCUS:
        FocusSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_TGC:
        TGCSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;

		case USG_STATUS_PALETTE:
        PaletteSetByIndex(SetWayID,SetCurrentValue);
		WaitForEvent(mEventSyncHandle);
		break;
		//------------------------------------------------------
		default:
		break;

    	}
     //SAFE_CLOSEHANDLE(mEventSyncHandle) 
	 mhAsyncStatusResult= E_FAIL;
 	 return GetCurrentValue;
		
	
}

  