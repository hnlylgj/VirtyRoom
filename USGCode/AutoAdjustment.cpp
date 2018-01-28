// AutoAdjustment.cpp : 实现文件
//

#include "..\stdafx.h"
#include "AutoAdjustment.h"


// AutoAdjustment

AutoAdjustment::AutoAdjustment()
{
	pBext1=NULL;
	IsAutoBMode=FALSE;
	AutoStatusFlag=FALSE;
}

AutoAdjustment::~AutoAdjustment()
{
   ReleaseUsgControls();
}
// AutoAdjustment 成员函数
BOOL AutoAdjustment::CreateUsgControls()
{
	HRESULT hr = S_OK;
	IUnknown* pIUnknown = NULL;
	do
	{
		// create usg_ext1 callback object object
		hr = CoCreateInstance(CLSID_CBext1, NULL, CLSCTX_INPROC_SERVER, IID_IBext1,(LPVOID*) &pBext1);
		if (hr != S_OK)
		{
			pBext1 = NULL;
			break;
		}
		pBext1->SetScanConverterPlugin(pUSGFW2ForMX->pUsgScanConverterPlugin); 
	// begin: check if auto B is enabled
	// check if automatical B mode image optimization is supported for connected
	// beamformer and probe
	if(pUSGFW2ForMX->pProbe==NULL)break;
	IBeamformer*  pBeamformer;
	LONG BeamformerCode, ProbeCode,IsEnabled;
	pUSGFW2ForMX->pProbe->get_Beamformer(&pIUnknown);
	pUSGFW2ForMX->pProbe->get_Code(&ProbeCode); 
	pBeamformer=(IBeamformer*)pIUnknown;
	pBeamformer->get_Code(&BeamformerCode); 
	//beamformer_code = beamformer->Code;
	//probe_code = probe->Code;
	//Marshal::ReleaseComObject(beamformer);
	//amformer = nullptr;
	pBeamformer->Release(); pBeamformer=NULL;
	//if (b_ext1_obj->B_AutoOptimize_IsEnabled(beamformer_code, probe_code) == 1)
		//auto_b_enabled_hw = true;
	pBext1->B_AutoOptimize_IsEnabled(BeamformerCode,ProbeCode,&IsEnabled);
	if(IsEnabled!=1)break;
	IsAutoBMode=TRUE;

	// end: check if auto B is enabled

	SetSingleStaticFocus();
	//----------------------------------------------------------------------------------------------------------------------------
		//create B Mode Frequency control
		IUsgControl* pUsgControl;
		pUsgControl = NULL;
		if (pUSGFW2ForMX->pUsgDataView == NULL) break;
		pUSGFW2ForMX->pUsgDataView->GetControlObj( &IID_IUsgProbeFrequency2, 1/*scan_pUsgScanMode*/, 0/*stream_id*/, &pUsgControl );
		if (pUsgControl != NULL)
		{
				HRESULT hr;
				hr = pUsgControl->QueryInterface( IID_IUsgProbeFrequency2, (void**)&pIUnknown );
				if (hr != S_OK)
					{
						pIUnknown = NULL;
						SAFE_RELEASE(pUsgControl);
						break;
					}
				else
					{
					   pUSGFW2ForMX->pUsgProbeFrequency2 = (IUsgProbeFrequency2*)pIUnknown;
					   SAFE_RELEASE(pUsgControl);
					}
					
		}
      AutoStatusFlag=TRUE;//初始化完成
	  return true ;
	} while (false);

	ReleaseUsgControls();
	return false ;
} // void CreateUsgControls()

void AutoAdjustment::ReleaseUsgControls()
{
	 
	SAFE_RELEASE(pBext1);
	SAFE_RELEASE(pUSGFW2ForMX->pUsgProbeFrequency2);
	AutoStatusFlag=FALSE;
}

void AutoAdjustment::SetSingleStaticFocus()
{
	//if (data_view == nullptr) return;
	//IUsgFocus^ b_focus_ctrl;
	//CreateUsgControl( data_view, IUsgFocus::typeid, (unsigned int)tagScanMode::SCAN_MODE_B, 0, tmp_ctrl );
	//if (tmp_ctrl != nullptr)
		//b_focus_ctrl = (IUsgFocus^)tmp_ctrl;
	//if (b_focus_ctrl == nullptr) return;
	/*
	int focus_mode;
	int focus_set;
	int focal_zones_count;

	focus_mode = (int)tagFocusMode::FOCUS_MODE_MULTI;
	focus_set = 0;

	b_focus_ctrl->CurrentMode = focus_mode;
	b_focus_ctrl->FocusSet[focus_mode] = focus_set;

	focal_zones_count = b_focus_ctrl->GetFocalZonesCount(focus_mode, focus_set);

	array<System::Int32,1>^ arr;
	arr = gcnew cli::array< System::Int32 >(focal_zones_count);

	for (int i1=0; i1<focal_zones_count; i1++)
		arr[i1]=0;

	arr[0]=1;

	b_focus_ctrl->SetFocusState(focus_mode,focus_set,focal_zones_count,arr[0]);

	ReleaseUsgControl( b_focus_ctrl ); 
	*/
	//-------------------------------------------------
	LONG CurrentMode=1;
	LONG ActiveFocusSetID=0;
	LONG FocalZonesCount;
	pUSGFW2ForMX->pUsgFocus->put_CurrentMode(CurrentMode);
	pUSGFW2ForMX->pUsgFocus->put_FocusSet(CurrentMode,ActiveFocusSetID);
	pUSGFW2ForMX->pUsgFocus->GetFocalZonesCount(CurrentMode,ActiveFocusSetID,&FocalZonesCount);
	LONG* pFocusState=new LONG[FocalZonesCount];
	for (LONG i = 0; i< FocalZonesCount; i++)
	  {
		  pFocusState[i]=0;
	  }
	pFocusState[0]=1;
	pUSGFW2ForMX->pUsgFocus->SetFocusState(CurrentMode,ActiveFocusSetID,FocalZonesCount,pFocusState); 
	delete [] pFocusState;


}

int AutoAdjustment::GetProbeType()
{
    //int tmp_type;
	ProbeTypeFlag tmp_type;
	tmp_type = probe_type_unknown;

	if (pUSGFW2ForMX->pUsgScanLineProperties== NULL) return tmp_type;

	int nProbeLeftAngle;
	int nProbeRightAngle;
	LONG tmp_min_line;
	LONG tmp_max_line;
	float tmp_angle1;
	float tmp_angle2;
	float tmp_x1;
	float tmp_x2;
	float tmp_y1;
	float tmp_y2;

	// get indexes of first and last B mode scan-lines
	//b_scan_line_properties_obj->GetScanLinesRange( tmp_min_line, tmp_max_line );
	pUSGFW2ForMX->pUsgScanLineProperties->GetScanLinesRange(&tmp_min_line, &tmp_max_line);
	if ( (tmp_min_line==0) && (tmp_max_line==0) )
		return tmp_type;

	tmp_angle1 = 0;
	tmp_angle2 = 0;
	//try
	//{
		// get coordinates and angles of first and last B mode scan-lines
		//b_scan_line_properties_obj->GetCoordinates(tmp_min_line, tmp_angle1, tmp_x1, tmp_y1);
		//b_scan_line_properties_obj->GetCoordinates(tmp_max_line, tmp_angle2, tmp_x2, tmp_y2);
		pUSGFW2ForMX->pUsgScanLineProperties->GetCoordinates(tmp_min_line, &tmp_angle1, &tmp_x1, &tmp_y1); 
		pUSGFW2ForMX->pUsgScanLineProperties->GetCoordinates(tmp_max_line, &tmp_angle2, &tmp_x2, &tmp_y2); 

		//pUSGFW2ForMX->pUsgScanLineProperties->GetCoordinates2( 
        //pUSGFW2ForMX->pUsgScanLineProperties->GetPointDepth();
		//pUSGFW2ForMX->pUsgScanLineProperties->GetScanLine() 

	//nProbeLeftAngle = 1000*(int)Math::Round(tmp_angle1*180/Math::PI);
	//nProbeRightAngle = 1000*(int)Math::Round(tmp_angle2*180/Math::PI);
	nProbeLeftAngle = 1000*(int)(tmp_angle1*180/PI+0.5);
	nProbeRightAngle = 1000*(int)(tmp_angle2*180/PI+0.5);
	
	// for liniear probe angles of first and last scan-lines are equal
	if (nProbeLeftAngle == nProbeRightAngle)
	{tmp_type = probe_type_linear;}
	else
	{tmp_type = probe_type_convex;}
	return tmp_type;

}

void AutoAdjustment::RunAutoAdjustment()
{
	B_AutomaticalAdjustment2(1, true);
	B_AutomaticalAdjustment2(2, true);
	B_AutomaticalAdjustment2(3, false);
}

void AutoAdjustment::B_AutomaticalAdjustment2(int attempt_num, bool skip_at_end)
{
	/*
	if (data_view == nullptr) return;
	if (b_ext1_obj == nullptr) return;

	if (b_frame_averaging_ctrl == nullptr) return;
	if (b_gain_ctrl == nullptr) return;
	if (b_dynamic_range_ctrl == nullptr) return;
	if (b_frequency_ctrl == nullptr) return;
	if (b_power_ctrl == nullptr) return;
	if (tgc_ctrl == nullptr) return;
	if (depth_ctrl == nullptr) return;

	if (data_view->ScanState != tagScanState::SCAN_STATE_RUN) return;
	*/
	LONG tmp_auto_gain_in, tmp_auto_gain_out;
	LONG tmp_auto_dynamic_range_in, tmp_auto_dynamic_range_out;
	LONG tmp_auto_b_is_optimal;
	int tmp_auto_b_loop_count;
	LONG tmp_auto_b_power;
	LONG tmp_auto_b_depth_current;
	LONG tmp_auto_b_depth_max;
	int tmp_auto_b_probe_type;
	LONG tmp_auto_b_frequency;
	//FREQUENCY3  mCurrentFREQUENCY3Struc;

	tmp_auto_b_is_optimal = 0;
	tmp_auto_b_loop_count = 0;

	tmp_auto_b_probe_type		= GetProbeType();

	//tmp_auto_b_depth_current	= DepthGetCurrent();
	pUSGFW2ForMX->pUsgDepth->get_Current(&tmp_auto_b_depth_current);
	tmp_auto_b_depth_max		= DepthGetMax();
	//tmp_auto_gain_in			= B_GainGet();
	pUSGFW2ForMX->pUsgGain->get_Current(&tmp_auto_gain_in);  
	//tmp_auto_dynamic_range_in	= B_DynamicRangeGet();
	pUSGFW2ForMX->pUsgDynamicRange->get_Current(&tmp_auto_dynamic_range_in);  
	//tmp_auto_b_power			= B_PowerGet();
	pUSGFW2ForMX->pUsgPower->get_Current(&tmp_auto_b_power);  
	//tmp_auto_b_frequency		= B_FrequencyGet();
	//pUSGFW2ForMX->pUsgProbeFrequency3->get_Current(&mCurrentFREQUENCY3Struc);
	pUSGFW2ForMX->pUsgProbeFrequency2->get_Current(&tmp_auto_b_frequency);

	tmp_auto_gain_out = tmp_auto_gain_in;
	tmp_auto_dynamic_range_out = tmp_auto_dynamic_range_in;
	//---------------------------------------------------------------------------------------------------------------------
	//if(pUSGFW2ForMX->pProbe==NULL)break;
	IUnknown* pIUnknown = NULL;
	IBeamformer*  pBeamformer;
	LONG BeamformerCode, ProbeCode;
	pUSGFW2ForMX->pProbe->get_Beamformer(&pIUnknown);
	pUSGFW2ForMX->pProbe->get_Code(&ProbeCode); 
	pBeamformer=(IBeamformer*)pIUnknown;
	pBeamformer->get_Code(&BeamformerCode); 
	pBeamformer->Release(); pBeamformer=NULL;
	//set what beamformer and probe is used
	pBext1->B_AutoOptimize_SetParams(BeamformerCode,ProbeCode);
	//-----------------------------------------------------------------------------------------------------------------------
	LONG tmp_tgc_values_count;
	//ArrayList^ tmp_auto_tgc_arr;
	LONG tmp_auto_tgc_idx1;
	LONG tmp_auto_tgc_idx2;
	LONG tmp_auto_tgc_control_points_count;
	//array<int,1>^ tmp_tgc_values_in;
	//array<int,1>^ tmp_tgc_values_out;
	LONG* tmp_tgc_values_in;
	LONG* tmp_tgc_values_out;


	//tmp_auto_tgc_arr = TGC_GetEntries();
	LONG TGCCurvePointSize;
	LONG* pTGCCurvePointValue;
	pUSGFW2ForMX->pUsgTgc->GetTgcSize(&TGCCurvePointSize); 
	pTGCCurvePointValue=new LONG[TGCCurvePointSize];
	HRESULT hr=pUSGFW2ForMX->pUsgTgc->GetTgcEntries(0,TGCCurvePointSize,pTGCCurvePointValue); 
	//delete [] pTGCCurvePointValue;
	//----------------------------------------------------------------------------------------
	tmp_auto_tgc_control_points_count = 5;//TGC_ControlPointsNumGet();5
	//get indexes of starting and ending points of visible TGC curve part inside full TGC curve
	//tmp_auto_tgc_idx1 = TGC_GetDepthIdx(TGC_ControlPointGetDepth(0));
	//tmp_auto_tgc_idx2 = TGC_GetDepthIdx(TGC_ControlPointGetDepth(tmp_auto_tgc_control_points_count-1));
	LONG StartPointPosition,EndPointPosition;
	LONG StartPointDepth,EndPointDepth;
	LONG StartPointPositionx,EndPointPositionx;
	if (tmp_auto_tgc_control_points_count > 1)
	{
		pUSGFW2ForMX->pUsgTgc->get_CtlPointPos(0,&StartPointPosition); 
		pUSGFW2ForMX->pUsgTgc->get_CtlPointPos(tmp_auto_tgc_control_points_count-1,&EndPointPosition); 
		pUSGFW2ForMX->pUsgTgc->PositionToDepth(StartPointPosition,&StartPointDepth);
		pUSGFW2ForMX->pUsgTgc->PositionToDepth(EndPointPosition,&EndPointDepth);
		pUSGFW2ForMX->pUsgTgc->DepthToPosition(StartPointDepth,&StartPointPositionx);
		pUSGFW2ForMX->pUsgTgc->DepthToPosition(EndPointDepth,&EndPointPositionx);
	}
	tmp_auto_tgc_idx1 = StartPointPositionx;
	tmp_auto_tgc_idx2 = EndPointPositionx;


	tmp_tgc_values_count = TGCCurvePointSize;//tmp_auto_tgc_arr->Count;64--//512
	if (tmp_tgc_values_count > 0)
	{
		//tmp_tgc_values_in = gcnew cli::array<int>(tmp_tgc_values_count);
		//tmp_tgc_values_out = gcnew cli::array<int>(tmp_tgc_values_count);
		tmp_tgc_values_in =new LONG[tmp_tgc_values_count];
		tmp_tgc_values_out=new LONG[tmp_tgc_values_count];


	}
	for (int i=0; i<tmp_tgc_values_count; i++)
	{
		//int tmp_val2;
		//tmp_val2 = (int)(tmp_auto_tgc_arr[i1]);
		//tmp_tgc_values_in[i1] = tmp_val2;
		//tmp_tgc_values_out[i1] = tmp_val2;
		tmp_tgc_values_in[i]=pTGCCurvePointValue[i];
		tmp_tgc_values_out[i]=pTGCCurvePointValue[i];

	}
	//-------------------------------------------------------------------------------------------------------------------------
	// store current frame
	LONG tmp_auto_store_frame_idx;
	LONG tmp_auto_store_frame_is_finished;
	LONG tmp_auto_store_frame_count;
	tmp_auto_store_frame_idx = 0;
	tmp_auto_store_frame_is_finished = 0;
	tmp_auto_store_frame_count = 0;

	pBext1->B_AutoOptimize_StoreFrame(tmp_auto_store_frame_idx);
	while ( (tmp_auto_store_frame_is_finished == 0) && (tmp_auto_store_frame_count < 30) )
	{
		Sleep(100);
		pBext1->B_AutoOptimize_StoreFrameIsFinished(&tmp_auto_store_frame_is_finished);
		tmp_auto_store_frame_count++;
	}

	LONG tmp_auto_b_frame_averaging;
	//tmp_auto_b_frame_averaging = B_FrameAveragingGet();
	//tmp_auto_b_frame_averaging = (int)Math::Max(2,tmp_auto_b_frame_averaging);
	LONG tmp_frame_skip_is_finished, tmp_frame_skip_count;
	pUSGFW2ForMX->pUsgFrameAvg->get_Current(&tmp_auto_b_frame_averaging);  
	if(tmp_auto_b_frame_averaging<=2)tmp_auto_b_frame_averaging=2;

	// set zero power
	//B_PowerSet(0);
	pUSGFW2ForMX->pUsgPower->put_Current(0);  

	// skip frames in order to get image that corresponds to new parameters
	tmp_frame_skip_is_finished = 0;
	tmp_frame_skip_count = 0;
	pBext1->B_AutoOptimize_FrameSkipSetNum(tmp_auto_b_frame_averaging);
	while ( (tmp_frame_skip_is_finished == 0) && (tmp_frame_skip_count < 50) )
	{
		Sleep(100);
		pBext1->B_AutoOptimize_FrameSkipIsFinished(&tmp_frame_skip_is_finished);
		tmp_frame_skip_count++;
	}

	// calculate optimized parameters
	pBext1->B_AutoOptimize_Start(tmp_auto_gain_in,tmp_auto_dynamic_range_in,tmp_tgc_values_in/*tmp_tgc_values_in[0]*/,tmp_tgc_values_count,tmp_auto_tgc_idx1,tmp_auto_tgc_idx2,tmp_auto_b_depth_current,tmp_auto_b_depth_max,tmp_auto_b_probe_type,tmp_auto_b_frequency,attempt_num);
	while ( (tmp_auto_b_is_optimal == 0) && (tmp_auto_b_loop_count < 20) )
	{
		Sleep(100);
		int tmp_val1;
		tmp_val1 = 0;
		pBext1->B_AutoOptimize_GetValue(&tmp_auto_gain_out,&tmp_auto_dynamic_range_out,tmp_tgc_values_out/*tmp_tgc_values_out[0]*/,&tmp_tgc_values_count,&tmp_auto_b_is_optimal);
		tmp_auto_b_loop_count++;
	}

	// set calculated values to controls
	if (tmp_auto_b_is_optimal == 1)
	{
		//for (int i1=0; i1<tmp_tgc_values_count; i1++)
			//tmp_auto_tgc_arr[i1] = (int)(tmp_tgc_values_out[i1]);
		//TGC_SetEntries(tmp_auto_tgc_arr);
		//TGC_UpdateGUI_All(false);
		for (int i=0; i<tmp_tgc_values_count; i++)
		{
			pTGCCurvePointValue[i]=tmp_tgc_values_out[i];
		}
		pUSGFW2ForMX->pUsgTgc->SetTgcEntries(0,TGCCurvePointSize,pTGCCurvePointValue); 

		

		//B_GainSet(tmp_auto_gain_out);
		//B_GainUpdateGUI(false);
		pUSGFW2ForMX->pUsgGain->put_Current(tmp_auto_gain_out);  
		

		//B_DynamicRangeSet(tmp_auto_dynamic_range_out);
		//B_DynamicRangeUpdateGUI(false);
		pUSGFW2ForMX->pUsgDynamicRange->put_Current(tmp_auto_dynamic_range_out);  

	}

	// restore power value
	//B_PowerSet(tmp_auto_b_power);
	pUSGFW2ForMX->pUsgPower->put_Current(tmp_auto_b_power);  
	if (skip_at_end == true)
	{
		// skip frames in order to get image that corresponds to new parameters
		// and prepare for next call
		tmp_frame_skip_is_finished = 0;
		tmp_frame_skip_count = 0;
		pBext1->B_AutoOptimize_FrameSkipSetNum(tmp_auto_b_frame_averaging);
		while ( (tmp_frame_skip_is_finished == 0) && (tmp_frame_skip_count < 50) )
		{
			Sleep(100);
			pBext1->B_AutoOptimize_FrameSkipIsFinished(&tmp_frame_skip_is_finished);
			tmp_frame_skip_count++;
		}
	}
	delete[] tmp_tgc_values_in;
	delete[] tmp_tgc_values_out;
	delete[] pTGCCurvePointValue;

}

LONG AutoAdjustment::DepthGetMax()
{
	/*
	if (depth_ctrl == nullptr) return 0;
	int ret;
	int val_count;
	IUsgValues^ values;
	ret = 0;
	values = depth_ctrl->Values;
	val_count = values->Count;
	if (val_count > 0)
		ret = (int)(values->Item(val_count-1));
	ReleaseUsgControl(values);
	return ret;
	*/
	LONG val_Count;
	VARIANT mItem;
	LONG DepthMax;
	IUsgValues* pUsgValues = NULL;
	pUSGFW2ForMX->pUsgDepth->get_Values(&pUsgValues);
	if(pUsgValues == NULL) return -1;
	pUsgValues->get_Count(&val_Count);//组合值个数
	pUsgValues->Item(val_Count-1, &mItem );
	DepthMax=mItem.lVal;
	VariantClear(&mItem);
	SAFE_RELEASE(pUsgValues);
	return DepthMax;
} 