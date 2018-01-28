#pragma once

#include "USGFW2ForMX.h"
//#include "Usgfw2_h.h"
#include "usg_ext1.h"
#include <math.h> 
#define PI 3.14159265358979323846

// AutoAdjustment ÃüÁîÄ¿±ê
#include "Safe_ReleaseDefine.h"

typedef /* [v1_enum] */ 
enum tagProbe_Type
    {	probe_type_unknown	=0,
		probe_type_linear	= 1,
		probe_type_convex	= 2,
	} 	ProbeTypeFlag;

class AutoAdjustment : public CObject
{
public:
	AutoAdjustment();
	virtual ~AutoAdjustment();
	//IProbe* pProbe;
	//IUsgScanConverterPlugin *	pUsgScanConverterPlugin;// B scan-converter's plug-in
	
	CUSGFW2ForMX * pUSGFW2ForMX;
	
	IBext1* pBext1;
	BOOL IsAutoBMode; // is automatical B adjustment enabled for connected beamformer
	BOOL AutoStatusFlag;
    BOOL CreateUsgControls();
    void ReleaseUsgControls();
	void RunAutoAdjustment();

    private:void SetSingleStaticFocus();
	private:int GetProbeType();
    private: LONG DepthGetMax();
	private:void B_AutomaticalAdjustment2(int attempt_num, bool skip_at_end);	

};


		