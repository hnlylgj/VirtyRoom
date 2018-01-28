

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jul 05 14:27:20 2012
 */
/* Compiler settings for _usg_ext1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___usg_ext1_h__
#define ___usg_ext1_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBext1_FWD_DEFINED__
#define __IBext1_FWD_DEFINED__
typedef interface IBext1 IBext1;
#endif 	/* __IBext1_FWD_DEFINED__ */


#ifndef __CBext1_FWD_DEFINED__
#define __CBext1_FWD_DEFINED__

#ifdef __cplusplus
typedef class CBext1 CBext1;
#else
typedef struct CBext1 CBext1;
#endif /* __cplusplus */

#endif 	/* __CBext1_FWD_DEFINED__ */


/* header files for imported files */
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"
#include "strmif.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBext1_INTERFACE_DEFINED__
#define __IBext1_INTERFACE_DEFINED__

/* interface IBext1 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBext1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D5CC2AE-BF85-45d4-B7FD-D66812D2C219")
    IBext1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScanConverterPlugin( 
            /* [in] */ IDispatch *plugin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_Start( 
            /* [in] */ LONG b_gain,
            /* [in] */ LONG b_dynamic_range,
            /* [in] */ LONG *tgc_values,
            /* [in] */ LONG tgc_values_count,
            /* [in] */ LONG tgc_idx_start,
            /* [in] */ LONG tgc_idx_end,
            /* [in] */ LONG depth_cur,
            /* [in] */ LONG depth_max,
            /* [in] */ LONG probe_type,
            /* [in] */ LONG freq,
            /* [in] */ LONG attempt_num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_GetValue( 
            /* [out] */ LONG *b_gain,
            /* [out] */ LONG *b_dynamic_range,
            /* [out] */ LONG *tgc_values,
            /* [out] */ LONG *tgc_values_count,
            /* [out] */ LONG *is_optimal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_FrameSkipSetNum( 
            /* [in] */ LONG skip_frm_num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_FrameSkipIsFinished( 
            /* [out] */ LONG *is_finished) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_StoreFrame( 
            /* [in] */ LONG idx) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_StoreFrameIsFinished( 
            /* [out] */ LONG *is_finished) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_SetParams( 
            /* [in] */ LONG beamformer_code,
            /* [in] */ LONG probe_code) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE B_AutoOptimize_IsEnabled( 
            /* [in] */ LONG beamformer_code,
            /* [in] */ LONG probe_code,
            /* [retval][out] */ LONG *enabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBext1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBext1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBext1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBext1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBext1 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBext1 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBext1 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBext1 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScanConverterPlugin )( 
            IBext1 * This,
            /* [in] */ IDispatch *plugin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_Start )( 
            IBext1 * This,
            /* [in] */ LONG b_gain,
            /* [in] */ LONG b_dynamic_range,
            /* [in] */ LONG *tgc_values,
            /* [in] */ LONG tgc_values_count,
            /* [in] */ LONG tgc_idx_start,
            /* [in] */ LONG tgc_idx_end,
            /* [in] */ LONG depth_cur,
            /* [in] */ LONG depth_max,
            /* [in] */ LONG probe_type,
            /* [in] */ LONG freq,
            /* [in] */ LONG attempt_num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_GetValue )( 
            IBext1 * This,
            /* [out] */ LONG *b_gain,
            /* [out] */ LONG *b_dynamic_range,
            /* [out] */ LONG *tgc_values,
            /* [out] */ LONG *tgc_values_count,
            /* [out] */ LONG *is_optimal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_Stop )( 
            IBext1 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_FrameSkipSetNum )( 
            IBext1 * This,
            /* [in] */ LONG skip_frm_num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_FrameSkipIsFinished )( 
            IBext1 * This,
            /* [out] */ LONG *is_finished);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_StoreFrame )( 
            IBext1 * This,
            /* [in] */ LONG idx);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_StoreFrameIsFinished )( 
            IBext1 * This,
            /* [out] */ LONG *is_finished);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_SetParams )( 
            IBext1 * This,
            /* [in] */ LONG beamformer_code,
            /* [in] */ LONG probe_code);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *B_AutoOptimize_IsEnabled )( 
            IBext1 * This,
            /* [in] */ LONG beamformer_code,
            /* [in] */ LONG probe_code,
            /* [retval][out] */ LONG *enabled);
        
        END_INTERFACE
    } IBext1Vtbl;

    interface IBext1
    {
        CONST_VTBL struct IBext1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBext1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBext1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBext1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBext1_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBext1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBext1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBext1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBext1_SetScanConverterPlugin(This,plugin)	\
    ( (This)->lpVtbl -> SetScanConverterPlugin(This,plugin) ) 

#define IBext1_B_AutoOptimize_Start(This,b_gain,b_dynamic_range,tgc_values,tgc_values_count,tgc_idx_start,tgc_idx_end,depth_cur,depth_max,probe_type,freq,attempt_num)	\
    ( (This)->lpVtbl -> B_AutoOptimize_Start(This,b_gain,b_dynamic_range,tgc_values,tgc_values_count,tgc_idx_start,tgc_idx_end,depth_cur,depth_max,probe_type,freq,attempt_num) ) 

#define IBext1_B_AutoOptimize_GetValue(This,b_gain,b_dynamic_range,tgc_values,tgc_values_count,is_optimal)	\
    ( (This)->lpVtbl -> B_AutoOptimize_GetValue(This,b_gain,b_dynamic_range,tgc_values,tgc_values_count,is_optimal) ) 

#define IBext1_B_AutoOptimize_Stop(This)	\
    ( (This)->lpVtbl -> B_AutoOptimize_Stop(This) ) 

#define IBext1_B_AutoOptimize_FrameSkipSetNum(This,skip_frm_num)	\
    ( (This)->lpVtbl -> B_AutoOptimize_FrameSkipSetNum(This,skip_frm_num) ) 

#define IBext1_B_AutoOptimize_FrameSkipIsFinished(This,is_finished)	\
    ( (This)->lpVtbl -> B_AutoOptimize_FrameSkipIsFinished(This,is_finished) ) 

#define IBext1_B_AutoOptimize_StoreFrame(This,idx)	\
    ( (This)->lpVtbl -> B_AutoOptimize_StoreFrame(This,idx) ) 

#define IBext1_B_AutoOptimize_StoreFrameIsFinished(This,is_finished)	\
    ( (This)->lpVtbl -> B_AutoOptimize_StoreFrameIsFinished(This,is_finished) ) 

#define IBext1_B_AutoOptimize_SetParams(This,beamformer_code,probe_code)	\
    ( (This)->lpVtbl -> B_AutoOptimize_SetParams(This,beamformer_code,probe_code) ) 

#define IBext1_B_AutoOptimize_IsEnabled(This,beamformer_code,probe_code,enabled)	\
    ( (This)->lpVtbl -> B_AutoOptimize_IsEnabled(This,beamformer_code,probe_code,enabled) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBext1_INTERFACE_DEFINED__ */



#ifndef __usg_ext1_LIBRARY_DEFINED__
#define __usg_ext1_LIBRARY_DEFINED__

/* library usg_ext1 */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_usg_ext1;

EXTERN_C const CLSID CLSID_CBext1;

#ifdef __cplusplus

class DECLSPEC_UUID("E1D11D71-2FA0-45e9-9531-B80BB9DE6A21")
CBext1;
#endif
#endif /* __usg_ext1_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


