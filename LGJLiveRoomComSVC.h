

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue May 16 16:20:42 2017
 */
/* Compiler settings for LGJLiveRoomComSVC.idl:
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

#ifndef __LGJLiveRoomComSVC_i_h__
#define __LGJLiveRoomComSVC_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITeniLiveRoomsvc_FWD_DEFINED__
#define __ITeniLiveRoomsvc_FWD_DEFINED__
typedef interface ITeniLiveRoomsvc ITeniLiveRoomsvc;
#endif 	/* __ITeniLiveRoomsvc_FWD_DEFINED__ */


#ifndef ___ITeniLiveRoomsvcEvents_FWD_DEFINED__
#define ___ITeniLiveRoomsvcEvents_FWD_DEFINED__
typedef interface _ITeniLiveRoomsvcEvents _ITeniLiveRoomsvcEvents;
#endif 	/* ___ITeniLiveRoomsvcEvents_FWD_DEFINED__ */


#ifndef ___ITeniLiveRoomsvcEvents2_FWD_DEFINED__
#define ___ITeniLiveRoomsvcEvents2_FWD_DEFINED__
typedef interface _ITeniLiveRoomsvcEvents2 _ITeniLiveRoomsvcEvents2;
#endif 	/* ___ITeniLiveRoomsvcEvents2_FWD_DEFINED__ */


#ifndef __ITeniLiveRoomsvcDelegate_FWD_DEFINED__
#define __ITeniLiveRoomsvcDelegate_FWD_DEFINED__
typedef interface ITeniLiveRoomsvcDelegate ITeniLiveRoomsvcDelegate;
#endif 	/* __ITeniLiveRoomsvcDelegate_FWD_DEFINED__ */


#ifndef __ITeniLiveRoomsvcEventEx_FWD_DEFINED__
#define __ITeniLiveRoomsvcEventEx_FWD_DEFINED__
typedef interface ITeniLiveRoomsvcEventEx ITeniLiveRoomsvcEventEx;
#endif 	/* __ITeniLiveRoomsvcEventEx_FWD_DEFINED__ */


#ifndef __TeniLiveRoomsvc_FWD_DEFINED__
#define __TeniLiveRoomsvc_FWD_DEFINED__

#ifdef __cplusplus
typedef class TeniLiveRoomsvc TeniLiveRoomsvc;
#else
typedef struct TeniLiveRoomsvc TeniLiveRoomsvc;
#endif /* __cplusplus */

#endif 	/* __TeniLiveRoomsvc_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITeniLiveRoomsvc_INTERFACE_DEFINED__
#define __ITeniLiveRoomsvc_INTERFACE_DEFINED__

/* interface ITeniLiveRoomsvc */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITeniLiveRoomsvc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0160043-EC28-4F0E-8331-17C83BBB6ADD")
    ITeniLiveRoomsvc : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Login( 
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserSig) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Loginout( void) = 0;
        
		virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPara(
			/* [in] */ LONG hClientWnd,
			/* [in] */ BSTR AllStr,
			/* [out][in] */ LONG *lpPara) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MasterCloseRoom( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MasterCreateRoom( 
            /* [in] */ LONG RoomID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MasterQuitRoom( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WatcherJoinRoom( 
            /* [in] */ LONG RoomID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WatcherQuitRoom( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE VideoManager( 
            /* [in] */ LONG Typeid,
            /* [in] */ LONG Flagid,
            /* [in] */ LONG x1,
            /* [in] */ LONG y1,
            /* [in] */ LONG x2,
            /* [in] */ LONG y2,
            /* [in] */ LONG fv) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CloseRoom( 
            /* [in] */ LONG Flagid) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSample(
			/* [in] */ LONG Channelid,
			/* [in] */ LONG sbSize,
			/* [length_is][size_is][out] */ BYTE *pSampleData) = 0;

		virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendIM(
			/* [in] */ LONG Flagid,
			/* [in] */ LONG TypeID,
			/* [in] */ BSTR Infor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITeniLiveRoomsvcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITeniLiveRoomsvc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITeniLiveRoomsvc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITeniLiveRoomsvc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Login )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserSig);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Loginout )( 
            ITeniLiveRoomsvc * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPara )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ IUnknown *cp,
            /* [in] */ LONG lp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MasterCloseRoom )( 
            ITeniLiveRoomsvc * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MasterCreateRoom )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ LONG RoomID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MasterQuitRoom )( 
            ITeniLiveRoomsvc * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WatcherJoinRoom )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ LONG RoomID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WatcherQuitRoom )( 
            ITeniLiveRoomsvc * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *VideoManager )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ LONG Typeid,
            /* [in] */ LONG Flagid,
            /* [in] */ LONG x1,
            /* [in] */ LONG y1,
            /* [in] */ LONG x2,
            /* [in] */ LONG y2,
            /* [in] */ LONG fv);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CloseRoom )( 
            ITeniLiveRoomsvc * This,
            /* [in] */ LONG Flagid);
        
        END_INTERFACE
    } ITeniLiveRoomsvcVtbl;

    interface ITeniLiveRoomsvc
    {
        CONST_VTBL struct ITeniLiveRoomsvcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITeniLiveRoomsvc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITeniLiveRoomsvc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITeniLiveRoomsvc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITeniLiveRoomsvc_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITeniLiveRoomsvc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITeniLiveRoomsvc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITeniLiveRoomsvc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITeniLiveRoomsvc_Login(This,UserID,UserSig)	\
    ( (This)->lpVtbl -> Login(This,UserID,UserSig) ) 

#define ITeniLiveRoomsvc_Loginout(This)	\
    ( (This)->lpVtbl -> Loginout(This) ) 

#define ITeniLiveRoomsvc_SetPara(This,cp,lp)	\
    ( (This)->lpVtbl -> SetPara(This,cp,lp) ) 

#define ITeniLiveRoomsvc_MasterCloseRoom(This)	\
    ( (This)->lpVtbl -> MasterCloseRoom(This) ) 

#define ITeniLiveRoomsvc_MasterCreateRoom(This,RoomID)	\
    ( (This)->lpVtbl -> MasterCreateRoom(This,RoomID) ) 

#define ITeniLiveRoomsvc_MasterQuitRoom(This)	\
    ( (This)->lpVtbl -> MasterQuitRoom(This) ) 

#define ITeniLiveRoomsvc_WatcherJoinRoom(This,RoomID)	\
    ( (This)->lpVtbl -> WatcherJoinRoom(This,RoomID) ) 

#define ITeniLiveRoomsvc_WatcherQuitRoom(This)	\
    ( (This)->lpVtbl -> WatcherQuitRoom(This) ) 

#define ITeniLiveRoomsvc_VideoManager(This,Typeid,Flagid,x1,y1,x2,y2,fv)	\
    ( (This)->lpVtbl -> VideoManager(This,Typeid,Flagid,x1,y1,x2,y2,fv) ) 

#define ITeniLiveRoomsvc_CloseRoom(This,Flagid)	\
    ( (This)->lpVtbl -> CloseRoom(This,Flagid) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITeniLiveRoomsvc_INTERFACE_DEFINED__ */



#ifndef __LGJLiveRoomComSVCLib_LIBRARY_DEFINED__
#define __LGJLiveRoomComSVCLib_LIBRARY_DEFINED__

/* library LGJLiveRoomComSVCLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_LGJLiveRoomComSVCLib;

#ifndef ___ITeniLiveRoomsvcEvents_DISPINTERFACE_DEFINED__
#define ___ITeniLiveRoomsvcEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITeniLiveRoomsvcEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITeniLiveRoomsvcEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("499F7A5F-B624-4BBE-93E3-C74A19B18733")
    _ITeniLiveRoomsvcEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITeniLiveRoomsvcEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITeniLiveRoomsvcEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITeniLiveRoomsvcEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITeniLiveRoomsvcEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITeniLiveRoomsvcEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITeniLiveRoomsvcEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITeniLiveRoomsvcEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITeniLiveRoomsvcEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITeniLiveRoomsvcEventsVtbl;

    interface _ITeniLiveRoomsvcEvents
    {
        CONST_VTBL struct _ITeniLiveRoomsvcEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITeniLiveRoomsvcEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITeniLiveRoomsvcEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITeniLiveRoomsvcEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITeniLiveRoomsvcEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ITeniLiveRoomsvcEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ITeniLiveRoomsvcEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ITeniLiveRoomsvcEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITeniLiveRoomsvcEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___ITeniLiveRoomsvcEvents2_INTERFACE_DEFINED__
#define ___ITeniLiveRoomsvcEvents2_INTERFACE_DEFINED__

/* interface _ITeniLiveRoomsvcEvents2 */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID__ITeniLiveRoomsvcEvents2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A72DC5F-EDEA-4BE9-AC01-D27E67A18AEC")
    _ITeniLiveRoomsvcEvents2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnCompleteHandleIU( 
            /* [in] */ LONG EventCode,
            /* [in] */ LONG EventValue,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnLocalVideoView( 
            /* [in] */ BYTE *pData,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRemoteVideoView( 
            /* [in] */ BYTE *pData,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _ITeniLiveRoomsvcEvents2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITeniLiveRoomsvcEvents2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITeniLiveRoomsvcEvents2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITeniLiveRoomsvcEvents2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnCompleteHandleIU )( 
            _ITeniLiveRoomsvcEvents2 * This,
            /* [in] */ LONG EventCode,
            /* [in] */ LONG EventValue,
            /* [retval][out] */ LONG *ReplyValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLocalVideoView )( 
            _ITeniLiveRoomsvcEvents2 * This,
            /* [in] */ BYTE *pData,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRemoteVideoView )( 
            _ITeniLiveRoomsvcEvents2 * This,
            /* [in] */ BYTE *pData,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue);
        
        END_INTERFACE
    } _ITeniLiveRoomsvcEvents2Vtbl;

    interface _ITeniLiveRoomsvcEvents2
    {
        CONST_VTBL struct _ITeniLiveRoomsvcEvents2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITeniLiveRoomsvcEvents2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITeniLiveRoomsvcEvents2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITeniLiveRoomsvcEvents2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITeniLiveRoomsvcEvents2_OnCompleteHandleIU(This,EventCode,EventValue,ReplyValue)	\
    ( (This)->lpVtbl -> OnCompleteHandleIU(This,EventCode,EventValue,ReplyValue) ) 

#define _ITeniLiveRoomsvcEvents2_OnLocalVideoView(This,pData,Flag,ReplyValue)	\
    ( (This)->lpVtbl -> OnLocalVideoView(This,pData,Flag,ReplyValue) ) 

#define _ITeniLiveRoomsvcEvents2_OnRemoteVideoView(This,pData,Flag,ReplyValue)	\
    ( (This)->lpVtbl -> OnRemoteVideoView(This,pData,Flag,ReplyValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___ITeniLiveRoomsvcEvents2_INTERFACE_DEFINED__ */


#ifndef __ITeniLiveRoomsvcDelegate_INTERFACE_DEFINED__
#define __ITeniLiveRoomsvcDelegate_INTERFACE_DEFINED__

/* interface ITeniLiveRoomsvcDelegate */
/* [object][unique][helpstring][uuid][oleautomation] */ 


EXTERN_C const IID IID_ITeniLiveRoomsvcDelegate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62A80A6C-607F-4C52-B318-94D8662992DB")
    ITeniLiveRoomsvcDelegate : public IUnknown
    {
    public:
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE CompleteDelegate( 
            /* [in] */ LONG EventCode,
            /* [in] */ LONG EventValue,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE LocalVideoViewDelegate( 
            /* [in] */ VARIANT *pData,
            /* [in] */ LONG nCount,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE RemoteVideoViewDelegate( 
            /* [in] */ BYTE *pData,
            /* [in] */ LONG nCount,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue) = 0;
        
		virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE OnStatusNotify(
			/* [in] */ LONG Flagid,
			/* [in] */ BYTE *pbSmaple,
			/* [in] */ BSTR *psSample,
			/* [in] */ BSTR MessageStr,
			/* [in] */ LONG mbSize,
			/* [out][in] */ LONG *mdResult,
			/* [in] */ BYTE *pbExtra) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITeniLiveRoomsvcDelegateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITeniLiveRoomsvcDelegate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITeniLiveRoomsvcDelegate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITeniLiveRoomsvcDelegate * This);
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CompleteDelegate )( 
            ITeniLiveRoomsvcDelegate * This,
            /* [in] */ LONG EventCode,
            /* [in] */ LONG EventValue,
            /* [retval][out] */ LONG *ReplyValue);
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE *LocalVideoViewDelegate )( 
            ITeniLiveRoomsvcDelegate * This,
            /* [in] */ BYTE *pData,
            /* [in] */ LONG nCount,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue);
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoteVideoViewDelegate )( 
            ITeniLiveRoomsvcDelegate * This,
            /* [in] */ BYTE *pData,
            /* [in] */ LONG nCount,
            /* [in] */ LONG Flag,
            /* [retval][out] */ LONG *ReplyValue);
		virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE OnStatusNotify(
			/* [in] */ LONG Flagid,
			/* [length_is][size_is][in] */ BYTE *pbSmaple,
			/* [in] */ BSTR *psSample,
			/* [in] */ BSTR MessageStr,
			/* [in] */ LONG mbSize,
			/* [out][in] */ LONG *mdResult,
			/* [length_is][size_is][in] */ BYTE *pbExtra) = 0;
        
        END_INTERFACE
    } ITeniLiveRoomsvcDelegateVtbl;

    interface ITeniLiveRoomsvcDelegate
    {
        CONST_VTBL struct ITeniLiveRoomsvcDelegateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITeniLiveRoomsvcDelegate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITeniLiveRoomsvcDelegate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITeniLiveRoomsvcDelegate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITeniLiveRoomsvcDelegate_CompleteDelegate(This,EventCode,EventValue,ReplyValue)	\
    ( (This)->lpVtbl -> CompleteDelegate(This,EventCode,EventValue,ReplyValue) ) 

#define ITeniLiveRoomsvcDelegate_LocalVideoViewDelegate(This,pData,nCount,Flag,ReplyValue)	\
    ( (This)->lpVtbl -> LocalVideoViewDelegate(This,pData,nCount,Flag,ReplyValue) ) 

#define ITeniLiveRoomsvcDelegate_RemoteVideoViewDelegate(This,pData,nCount,Flag,ReplyValue)	\
    ( (This)->lpVtbl -> RemoteVideoViewDelegate(This,pData,nCount,Flag,ReplyValue) ) 

#define ITeniLiveRoomsvcDelegate_OnStatusNotify(This,Flagid,pbSmaple,psSample,MessageStr,mbSize,mdResult,pbExtra)	\
    ( (This)->lpVtbl -> OnStatusNotify(This,Flagid,pbSmaple,psSample,MessageStr,mbSize,mdResult,pbExtra) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITeniLiveRoomsvcDelegate_INTERFACE_DEFINED__ */


#ifndef __ITeniLiveRoomsvcEventEx_DISPINTERFACE_DEFINED__
#define __ITeniLiveRoomsvcEventEx_DISPINTERFACE_DEFINED__

/* dispinterface ITeniLiveRoomsvcEventEx */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_ITeniLiveRoomsvcEventEx;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0E709BF1-F492-4794-9FC6-BD72D4054887")
    ITeniLiveRoomsvcEventEx : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITeniLiveRoomsvcEventExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITeniLiveRoomsvcEventEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITeniLiveRoomsvcEventEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITeniLiveRoomsvcEventEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITeniLiveRoomsvcEventEx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITeniLiveRoomsvcEventEx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITeniLiveRoomsvcEventEx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITeniLiveRoomsvcEventEx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITeniLiveRoomsvcEventExVtbl;

    interface ITeniLiveRoomsvcEventEx
    {
        CONST_VTBL struct ITeniLiveRoomsvcEventExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITeniLiveRoomsvcEventEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITeniLiveRoomsvcEventEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITeniLiveRoomsvcEventEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITeniLiveRoomsvcEventEx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITeniLiveRoomsvcEventEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITeniLiveRoomsvcEventEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITeniLiveRoomsvcEventEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITeniLiveRoomsvcEventEx_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TeniLiveRoomsvc;

#ifdef __cplusplus

class DECLSPEC_UUID("A1D4B256-B8F8-45D4-A866-B55F00C3270E")
TeniLiveRoomsvc;
#endif
#endif /* __LGJLiveRoomComSVCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


