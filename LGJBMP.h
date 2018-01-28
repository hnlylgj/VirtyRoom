/********************************************************************
	created:	2009/06/21
	created:	21:6:2005   21:53
	filename: 	imagetest\bmp.h
	file path:	imagetest
	file base:	bmp
	file ext:	h
	author:		LIGENGJUN
	purpose:	��дBMP
	// [6/22/2009]�������ʾ����
	
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
//���VFW���
#include  <vfw.h>
#include <gdiplus.h>
using namespace Gdiplus;
//BMP�ļ�ͷ��־
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
	//���ڴ��л�ͼ
	void DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize DestImageSize);  	
	//ʹ��VFW�����ͼ
	void DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize DestImageSize);
	void DrawAnyImage(CDC *pDC, CPoint ptOrigin, CSize DestImageSize);	
private:
	BOOL MakePalette();						       //������ɫ��
public:
   
	int GetHeight() const;
	int GetWidth() const;
    CString GetImageType(const CString& strName);	  //��ȡͼ������BMP,JPG
    void SetImageType(const CString& strFileName);	   //����ͼ������BMP,JPG

	int GetColorTableLenght() const;			      //��ɫ���С
	DWORD GetImageSize() const;				           //ͼ���С

	LPVOID GetColorTable() const;			           //��ɫ��ָ��
    LPVOID GetBitmasks() const;			              //�����ָ��
	LPBITMAPINFOHEADER GetpBitMapInfoHeader() const;   //λͼ��Ϣͷ
    int GetBitCount() const;				           //Bpp
	LPBYTE GetBits() const;					          //����ͼ������
	int GetWidthMemory();					           //�ڴ��ȣ�4�ı���
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
	LPBITMAPINFOHEADER  pBitMapHeaderInfor;		  //λͼ��Ϣͷ
	LPBYTE		        pBitDataBuffer;		      //λͼ����
	HPALETTE            m_hPalette;               //��ɫ����
    CString m_strImageType;		                  //ͼ������BMP,JPG
   
    LPBitmasks          pBitmasks;
};

#endif
