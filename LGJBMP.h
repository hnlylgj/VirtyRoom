/********************************************************************
	created:	2009/06/21
	created:	21:6:2005   21:53
	filename: 	imagetest\bmp.h
	file path:	imagetest
	file base:	bmp
	file ext:	h
	author:		LIGENGJUN
	purpose:	读写BMP
	// [6/22/2009]　添加显示功能
	
*********************************************************************/

#define GDIPlusImage

#ifdef GDIPlusImage
#define GDIPlus  1
#else
#define GDIPlus  0
#endif
#define GDIPlusImageID 1

#ifndef _BMP_H__
#define _BMP_H__
//#include <atlimage.h>
//添加VFW组件
#include  <vfw.h>
#include <gdiplus.h>
using namespace Gdiplus;
//BMP文件头标志
#define BMP_HEADER_MARKER	((WORD) ('M' << 8) | 'B') 

typedef struct tagBitmasks{
        DWORD       biRed;
        DWORD       biGreen;
        DWORD       biBlue;
 } Bitmasks, FAR *LPBitmasks, *PBitmasks;

enum ColorSpaceType{RGB=0,YUV};

class CLGJBmp : public CObject
{
public:
	DECLARE_SERIAL(CLGJBmp)
		
//Construction and Destruction
	CLGJBmp();
	~CLGJBmp();

//Operations
	BOOL BMPRead(CFile *pFile);
	BOOL BMPWrite(CFile *pFile);
	void Serialize(CArchive &ar);	

	void Draw(CDC *pDC, CPoint ptOrigin, CSize DestImageSize);	
	//在内存中画图
	void DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize DestImageSize);  	
	//使用VFW组件画图
	void DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize DestImageSize);
	void DrawAnyImage(CDC *pDC, CPoint ptOrigin, CSize DestImageSize);	
private:
	BOOL MakePalette();						       //创建调色板
public:
   
	int GetHeight() const;
	int GetWidth() const;
    CString GetImageType(const CString& strName);	  //获取图像类型BMP,JPG
    void SetImageType(const CString& strFileName);	   //设置图像类型BMP,JPG

	int GetColorTableLenght() const;			      //颜色表大小
	DWORD GetImageSize() const;				           //图像大小

	LPVOID GetColorTable() const;			           //颜色表指针
    LPVOID GetBitmasks() const;			              //掩码表指针
	LPBITMAPINFOHEADER GetpBitMapInfoHeader() const;   //位图信息头
    int GetBitCount() const;				           //Bpp
	LPBYTE GetBits() const;					          //返回图像数据
	int GetWidthMemory();					           //内存宽度，4的倍数
    ColorSpaceType mColorSpaceTypeID;
	//-------------------------------------------------------------------------------------
   CImage* pGPImage;
   IStream* pIStream;
   BYTE* pImageBufferFromFile;
   LONG FileDataLenght;
   CFile* pImageFile; 
   int GDIPlusReadID;
   //--------------------------------------------------------
   int GetImageCLSID(const WCHAR* StrFormat,CLSID* pCLSID);  
   void GDIPlusSerialize(CArchive &ar);
   Image* pGdiplusImage;
   Graphics* pGdiplusGraphics;
   BOOL FromPasteInit(HBITMAP hp);
   BOOL CopyToClipBoard(CDC *pDC);
   BOOL CopyToClipBoardEx(CDC *pDC);
   //--------------------------------------------------------------------------------------

//Data
private:
	LPBITMAPINFOHEADER  pBitMapHeaderInfor;		  //位图信息头
	LPBYTE		        pBitDataBuffer;		      //位图数据
	HPALETTE            m_hPalette;               //调色板句柄
    CString m_strImageType;		                  //图像类型BMP,JPG
   
    LPBitmasks          pBitmasks;
};

#endif
