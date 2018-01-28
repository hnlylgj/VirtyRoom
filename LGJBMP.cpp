/********************************************************************
	created:	2007/06/21
	created:	21:6:2005   21:55
	filename: 	imagetest\bmp.cpp
	file path:	imagetest
	file base:	bmp
	file mFileExtName:	cpp
	author:		LIGENGJUN
	
	  purpose:	��дBMP
	  //  [6/22/2005]�������ʾ����
	  
*********************************************************************/


#include "stdafx.h"
#include "LGJbmp.h"
//using namespace Gdiplus;
// �������л�����
IMPLEMENT_SERIAL(CLGJBmp, CObject, 0);


CLGJBmp::CLGJBmp() 
{
	pBitMapHeaderInfor = NULL;
	pBitDataBuffer = NULL;
	m_hPalette = NULL;
    mColorSpaceTypeID=RGB;
    pImageBufferFromFile=NULL;
	pGPImage=NULL;
    GDIPlusReadID=0;
    pGdiplusImage=NULL;
	pGdiplusGraphics=NULL;

}

CLGJBmp::~CLGJBmp()
{
	if (pBitMapHeaderInfor != NULL)
	{
		delete pBitMapHeaderInfor;
		pBitMapHeaderInfor = NULL;
	}

	if(pBitDataBuffer != NULL)
	{
		pBitDataBuffer = NULL;
	}

	if(m_hPalette != NULL)
	{
		::DeleteObject(m_hPalette);
	}
	if(pGPImage!=NULL)
       delete pGPImage;

	if(pImageBufferFromFile!=NULL)
     delete pImageBufferFromFile;
	if(pGdiplusImage!=NULL)
		delete pGdiplusImage;
    if(pGdiplusGraphics!=NULL)
		delete pGdiplusGraphics;
}

/*************************************************
Function:       BMPRead
Description:    ��ȡBMPͼ��
Input:          CFile *pFile
Output:         
Return:         BOOL  �ɹ�����TRUE�����򷵻�FALSE
Others:         ��ȡ�ļ�ͷ����Ϣͷ����ɫ���ͼ������ 
*************************************************/
BOOL CLGJBmp::BMPRead(CFile *pFile)
{
	// ���ж�����
     int mReadCount=0;
	 int mBitMapHeaderSize=0;
     long mImageSize=0;
	try 
	{
		BITMAPFILEHEADER mFileHeaderInfor;
		
		// ����1����ȡ�ļ�ͷ
		int mReadCount = pFile->Read((LPVOID) &mFileHeaderInfor, sizeof(BITMAPFILEHEADER));
		
		// �ж��Ƿ���BMP��ʽ��λͼ
		if(mFileHeaderInfor.bfType != BMP_HEADER_MARKER) 
		{
			//throw new CException;
			return FALSE;

		}
		// ������Ϣͷ����[��ɫ��\�����]�Ĵ�С�����ڴ�
		 mBitMapHeaderSize = mFileHeaderInfor.bfOffBits - sizeof(BITMAPFILEHEADER);
         pBitMapHeaderInfor = (LPBITMAPINFOHEADER) new BYTE[mBitMapHeaderSize];
	     // ����2����ȡ��Ϣͷ[����ɫ��\�����]
         mReadCount = pFile->Read(pBitMapHeaderInfor, mBitMapHeaderSize); 
		 if(pBitMapHeaderInfor->biCompression>4)
              mColorSpaceTypeID=YUV;
					
		// ����3����ȡͼ������
       	if(pBitMapHeaderInfor->biSizeImage==0)
		{
            mImageSize=pBitMapHeaderInfor->biWidth* pBitMapHeaderInfor->biHeight*pBitMapHeaderInfor->biBitCount/8;  
			pBitDataBuffer = (LPBYTE) new BYTE[mImageSize];
			mReadCount = pFile->Read(pBitDataBuffer, mImageSize); 

		}
		else
		{
			pBitDataBuffer = (LPBYTE) new BYTE[pBitMapHeaderInfor->biSizeImage];
			mReadCount = pFile->Read(pBitDataBuffer, pBitMapHeaderInfor->biSizeImage); 
		}

	}

	catch(CException* pe) 
	{
		AfxMessageBox(_T("BMPRead error"));
		pe->Delete();
		return FALSE;
	}

	//������ɫ��
	MakePalette();

	return TRUE;
}

/*************************************************
Function:       BMPWrite
Description:    д��BMPͼ��
Input:          CFile *pFile
Output:         
Return:         BOOL  �ɹ�����TRUE�����򷵻�FALSE
Others:         BMP��ʽ��ͼ���ԡ�BM��Ϊ��ʼ��־
*************************************************/
BOOL CLGJBmp::BMPWrite(CFile *pFile)
{
	BITMAPFILEHEADER mFileHeaderInfor;
	
	// �����ļ�ͷ���ļ����� 0x424D="BM"
	mFileHeaderInfor.bfType = BMP_HEADER_MARKER;  //0x4D42
	
	 ///////////////////////////////////////// ������Ϣͷ����ɫ��\������С
 	 int nSizeHeader;// = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();
	 if(pBitMapHeaderInfor->biCompression==3)
	 {
		
	    //������Ϣͷ��������С
		 nSizeHeader = sizeof(BITMAPINFOHEADER) + 12;
	 }
	 else
	 {
		// ������Ϣͷ����ɫ���С
	   nSizeHeader = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();
	 }
		//�����ļ�ͷ��Ϣ
		mFileHeaderInfor.bfSize      = sizeof(BITMAPFILEHEADER) + nSizeHeader + GetImageSize();
		mFileHeaderInfor.bfReserved1 = 0;
		mFileHeaderInfor.bfReserved2 = 0;
     if(pBitMapHeaderInfor->biCompression==3)
	 {
	    //����ƫ�������ļ�ͷ��С+��Ϣͷ��С������С
		mFileHeaderInfor.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 12;	
	 }
	 else
	 {
     	//����ƫ�������ļ�ͷ��С+��Ϣͷ��С+��ɫ���С
		mFileHeaderInfor.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();	
	 }
	// ����д����
	try 
	{
		pFile->Write((LPVOID) &mFileHeaderInfor, sizeof(BITMAPFILEHEADER));
		pFile->Write((LPVOID) pBitMapHeaderInfor,  nSizeHeader);
		pFile->Write((LPVOID) pBitDataBuffer, GetImageSize());
	}	

	catch(CException* pe)
	{
		pe->Delete();
		AfxMessageBox(_T("write error"));
		return FALSE;
	}
	
	return TRUE;
}


//������ɫ��Ĵ�С
int CLGJBmp::GetColorTableLenght() const
{
	int ret = 0;

	if(pBitMapHeaderInfor->biClrUsed == 0) 	// ����ɫ�������ʽ�ġ���СΪ2��biBitCount�η���	
	{
		switch(pBitMapHeaderInfor->biBitCount)
		{
		case 1:
			ret = 2;
			break;
		case 4:
			ret = 16;
			break;
		case 8:
			ret = 256;
			break;
		case 16:
             ret = 0;
		case 24:
             ret = 0;
		case 32:
			ret = 0;
			break;
		default:
			ret = 0;
		}
	}	
	else // ����ɫ��Ĵ�����ʽ����СΪʵ���õ�����ɫ����
	{
		ret = pBitMapHeaderInfor->biClrUsed;
	}

	return ret;
}

//���л�
void CLGJBmp::Serialize(CArchive &ar)
{
  	CArchive &mArchive=ar;
	SetImageType(mArchive.m_strFileName);	
   if(m_strImageType==_T("bmp")&&GDIPlusReadID==0)
   {
		if(mArchive.IsStoring()) 
		{
			BMPWrite(mArchive.GetFile());
		}
		else 
		{
			BMPRead(mArchive.GetFile());
		}
   }
   else
   {
		 GDIPlusReadID=1;
		 GDIPlusSerialize(mArchive);
   }

}


void CLGJBmp::GDIPlusSerialize(CArchive &ar)
{
    CArchive &mArchive=ar;
    HRESULT hr;
	Status stat = Ok;
    IStream* pIStream=NULL;

	if(mArchive.IsStoring()) //д����===============================
		{
           
			HGLOBAL hDestGLOBAL=GlobalAlloc(GMEM_MOVEABLE, 0);
            hr = CreateStreamOnHGlobal(hDestGLOBAL, TRUE, &pIStream);
            
#if 0 //8GDIPlusImageID  ////*/
        	 GUID mFileTypeGUID;
			 if(m_strImageType=="jpg")
             m_strImageType="jpeg";
             CString MyImageType=_T("image/")+m_strImageType;
             int Test1=GetImageCLSID(MyImageType.GetBuffer(), &mFileTypeGUID);
			 //--------------------------------------------------------------
             if(pGdiplusImage==NULL)
			 {
				  GlobalFree(hDestGLOBAL);
				  pIStream->Release();
				  return ;
			 }
            stat=pGdiplusImage->Save(pIStream,&mFileTypeGUID);//
			if(stat != Ok)
         	 {
				  GlobalFree(hDestGLOBAL);
				  pIStream->Release();
				   return ;
			 }
			
			
			
#else
       ///*/
			if(m_strImageType=="bmp")
                  hr = pGPImage->Save(pIStream,ImageFormatBMP);//Gdiplus::
			   else if(m_strImageType=="jpg")
                  hr = pGPImage->Save(pIStream,ImageFormatJPEG);//Gdiplus::
			       else if(m_strImageType=="png")
                      hr = pGPImage->Save(pIStream,ImageFormatPNG);//Gdiplus:: 
				         else if(m_strImageType=="gif")
                             hr = pGPImage->Save(pIStream,ImageFormatGIF);//Gdiplus::  
			                   else if(m_strImageType=="tif")
					                hr = pGPImage->Save(pIStream,ImageFormatTIFF);//Gdiplus::  
			                          else if(m_strImageType=="ico")
									       {
					                       hr = pGPImage->Save(pIStream,ImageFormatIcon);//Gdiplus:: 

							               }
										   else
										   {
											GlobalFree(hDestGLOBAL);
                                             return ;
										   }
		     
       //*/
#endif				
			
			 //--3.ToFile---------------------------------------------------------------------------------------
             LPBYTE pGlobalDestBuffer = (LPBYTE)GlobalLock(hDestGLOBAL);
			 LONG DestGLOBALLenght=GlobalSize(hDestGLOBAL);
             int ByteCount=512;
           	 while(true)
			 {
				  mArchive.Write(pGlobalDestBuffer,ByteCount);
				  DestGLOBALLenght=DestGLOBALLenght-ByteCount;
				  if(DestGLOBALLenght<=512)
				  {
					 pGlobalDestBuffer=pGlobalDestBuffer+ByteCount;
					 mArchive.Write(pGlobalDestBuffer,DestGLOBALLenght);
					 break;

				  }
				  pGlobalDestBuffer=pGlobalDestBuffer+ByteCount;

			  }
             GlobalFree(hDestGLOBAL);
             pIStream->Release();
             //pGPImage->Destroy(); 
            //-------------------------------------------------------------------------------------------
			

    	}
	else////������================================================================================================================
		{
         	//--1.FromFile----------------------------------------------------------------
			 pImageFile=mArchive.GetFile();
			 FileDataLenght=pImageFile->GetLength();
		     pImageBufferFromFile=new BYTE[FileDataLenght];
             BYTE* pTemp=pImageBufferFromFile;
             BYTE* pTempReadBuffer=new BYTE[4096];
             int Count=0;
			 int ReadLenght=4096;
             while(true)
			 {
				  Count=pImageFile->Read(pTempReadBuffer,ReadLenght);
				  if(Count==0)
					  break;
                  memcpy(pImageBufferFromFile, pTempReadBuffer,Count);
				  pImageBufferFromFile=pImageBufferFromFile+Count;
		     }
             pImageBufferFromFile=pTemp;
            //-2.----------------------------------------------------------------------
             HGLOBAL hDestGLOBAL =GlobalAlloc(GHND, FileDataLenght);
             LPBYTE pGlobalDestBuffer = (LPBYTE)GlobalLock(hDestGLOBAL);
             memcpy(pGlobalDestBuffer, pImageBufferFromFile, FileDataLenght);
             GlobalUnlock(hDestGLOBAL);
             hr = CreateStreamOnHGlobal(hDestGLOBAL, TRUE, &pIStream);
#if 0 ////GDIPlusImageID //*/

             pGdiplusImage=new Image(pIStream);
			 //pGdiplusImage=Image::FromStream(pIStream, FALSE);  
             //stat =pGdiplusImage->GetLastStatus();  



#else
             pGPImage=new CImage();
			 pGPImage->Load(pIStream);
             GlobalFree(hDestGLOBAL);
             pIStream->Release(); 

#endif			
           
			delete pImageBufferFromFile;
            pImageBufferFromFile=NULL;
            delete pTempReadBuffer;
		
		}
  }

  BOOL CLGJBmp::FromPasteInit(HBITMAP hp)
  {
  	if(pGPImage==NULL)
	{
      pGPImage=new CImage();

	}
	else
	{
      pGPImage->Destroy(); 
	}

 	 pGPImage->Attach(hp); 
     GDIPlusReadID=1;
	 return TRUE;

  }

 BOOL CLGJBmp::CopyToClipBoard(CDC *pDC)
   {
     if(pGPImage==NULL)
		 return CopyToClipBoardEx(pDC);

    if (OpenClipboard(pDC->GetWindow()->GetSafeHwnd()))
     {
	  EmptyClipboard(); 

      CBitmap  mMyJunkBitmap; 
      //CClientDC mMyClientDC(this); 
       ///HDC hdc=pDC->m_hDC;
	  CDC  mMyNewDC; 
     
       long scrW,scrH,desW,desH;
       CBitmap mMyBitMap;
      
	  HBITMAP mhBITMAP=pGPImage->Detach();//--------------------
	  mMyBitMap.Detach();
	  mMyBitMap.Attach(mhBITMAP);

	   BITMAP mBITMAPStruc;
	   mMyBitMap.GetBitmap(&mBITMAPStruc);	    //ȡ��Դλͼ��Ϣ�����ṹ
	   scrW=mBITMAPStruc.bmWidth;	           //��Դλͼ��Ϣ�����ṹ�õ�λͼ��С
	   scrH=mBITMAPStruc.bmHeight;
       desW=scrW,
	   desH=scrH;

        LPBITMAPINFOHEADER   pBitMapHeaderInfor=(LPBITMAPINFOHEADER)new BYTE[512];;		  //λͼ��Ϣͷ
	    BYTE*		         pBitDataBuffer=(BYTE*)mBITMAPStruc.bmBits; 		          //λͼ����
		pBitMapHeaderInfor->biSize = sizeof(BITMAPINFOHEADER);
		pBitMapHeaderInfor->biWidth =mBITMAPStruc.bmWidth ;
		pBitMapHeaderInfor->biHeight =mBITMAPStruc.bmHeight;
		pBitMapHeaderInfor->biPlanes = 1;     //�̶�Ϊ1;
		pBitMapHeaderInfor->biBitCount =mBITMAPStruc.bmBitsPixel;
		pBitMapHeaderInfor->biCompression =0;
		pBitMapHeaderInfor->biSizeImage =mBITMAPStruc.bmWidthBytes*mBITMAPStruc.bmHeight;
		pBitMapHeaderInfor->biClrUsed = 0;
		pBitMapHeaderInfor->biXPelsPerMeter = 0;
		pBitMapHeaderInfor->biYPelsPerMeter = 0;
		pBitMapHeaderInfor->biClrImportant = 0;



	   mMyNewDC.CreateCompatibleDC(NULL);
       mMyJunkBitmap.CreateCompatibleBitmap(pDC,scrW,scrH); 
       //CBitmap* pOldBitmap =
	   mMyNewDC.SelectObject(&mMyJunkBitmap); 
       //���ñ���ɫ���
	   mMyNewDC.FillSolidRect(0, 0, scrW, scrH, RGB(192, 192, 192));
      // ������ʾģʽ
	   pDC->SetStretchBltMode(COLORONCOLOR);
       // ���ڴ��л�ͼ
	   StretchDIBits(mMyNewDC.GetSafeHdc(), 
					0, 0,			//��ʼ��
					desW,desH,      //���Ϳ�
					0, 0, 
					scrW, scrH,
					pBitDataBuffer, 
					(LPBITMAPINFO) pBitMapHeaderInfor, 
					DIB_RGB_COLORS, SRCCOPY);


      
	  
      HANDLE hl=SetClipboardData(CF_BITMAP,mMyJunkBitmap.m_hObject); 
	  CloseClipboard();
	  mMyJunkBitmap.Detach();  
      mMyNewDC.DeleteDC();
      delete pBitMapHeaderInfor;

      pGPImage->Attach((HBITMAP)mMyBitMap.Detach());//mMyBitMap
      return true;
	
}
 return false;

}





BOOL CLGJBmp::CopyToClipBoardEx(CDC *pDC)
   {
     if (OpenClipboard(pDC->GetWindow()->GetSafeHwnd()))
     {
	  EmptyClipboard(); 

      CBitmap  mMyJunkBitmap; 
      CDC  mMyNewDC; 
     
       long scrW,scrH,desW,desH;
       // CBitmap mMyBitMap;
       scrW=pBitMapHeaderInfor->biWidth;	           //��Դλͼ��Ϣ�����ṹ�õ�λͼ��С
	   scrH=pBitMapHeaderInfor->biHeight;
       desW=scrW,
	   desH=scrH;

       mMyNewDC.CreateCompatibleDC(NULL);
       mMyJunkBitmap.CreateCompatibleBitmap(pDC,scrW,scrH); 
       //CBitmap* pOldBitmap =
	   mMyNewDC.SelectObject(&mMyJunkBitmap); 
       //���ñ���ɫ���
	   mMyNewDC.FillSolidRect(0, 0, scrW, scrH, RGB(192, 192, 192));
      // ������ʾģʽ
	   pDC->SetStretchBltMode(COLORONCOLOR);
       // ���ڴ��л�ͼ
	   StretchDIBits(mMyNewDC.GetSafeHdc(), 
					0, 0,			//��ʼ��
					desW,desH,      //���Ϳ�
					0, 0, 
					scrW, scrH,
					pBitDataBuffer, 
					(LPBITMAPINFO) pBitMapHeaderInfor, 
					DIB_RGB_COLORS, SRCCOPY);


      
	  
      HANDLE hl=SetClipboardData(CF_BITMAP,mMyJunkBitmap.m_hObject); 
	  CloseClipboard();
	  mMyJunkBitmap.Detach();  
      mMyNewDC.DeleteDC();
     return true;
	
}
 return false;

}










 int CLGJBmp::GetImageCLSID(const WCHAR* StrFormat,CLSID* pCLSID)
 {
//�õ���ʽΪStrFormat��ͼ���ļ��ı���ֵ�����ʸø�ʽͼ���COM�����GUIDֵ������pCLSID��   
UINT   num   =   0;   
UINT   size   =   0;   
ImageCodecInfo* pImageCodecInfo   =   NULL;   
GetImageEncodersSize(&num,   &size);   
if(size   ==   0)   
  return   FALSE;   //   ������Ϣ������   
//�����ڴ�   
pImageCodecInfo   =   (ImageCodecInfo*)(malloc(size));   
if(pImageCodecInfo   ==   NULL)   
   return   FALSE;   //   ����ʧ��   
//���ϵͳ�п��õı��뷽ʽ��������Ϣ   
GetImageEncoders(num,   size,   pImageCodecInfo);   
//�ڿ��ñ�����Ϣ�в���format��ʽ�Ƿ�֧��   
for(UINT   i   =   0;   i   <   num;   ++i)   
{   //MimeType�����뷽ʽ�ľ�������   
	if(wcscmp(pImageCodecInfo[i].MimeType,StrFormat) ==0)   
	{   
	*pCLSID   =   pImageCodecInfo[i].Clsid;   
	free(pImageCodecInfo);   
	return   TRUE;   
	}   
}   
free(pImageCodecInfo);   
  return   FALSE;

}

//������ɫ��
BOOL CLGJBmp::MakePalette()
{
	// ��������ڵ�ɫ�壬�򷵻�FALSE
	int TestValue= GetColorTableLenght();
	if(TestValue == 0) 
	{
		return FALSE;
	}
	
	if(m_hPalette != NULL) 
	{
		::DeleteObject(m_hPalette);
	}
	
	// ���߼���ɫ������ڴ�
	LPLOGPALETTE pTempLogPalette = (LPLOGPALETTE) new char[2 * sizeof(WORD) + GetColorTableLenght() * sizeof(PALETTEENTRY)];
	
	// �����߼���ɫ�����Ϣ
	pTempLogPalette->palVersion = 	0x300;
	pTempLogPalette->palNumEntries = GetColorTableLenght();
	
	// ����DIB�е���ɫ���߼���ɫ��
	LPRGBQUAD pRGBQUADColorTable = (LPRGBQUAD) GetColorTable();
	for(int i = 0; i < GetColorTableLenght(); ++i) 
	{
		pTempLogPalette->palPalEntry[i].peRed = pRGBQUADColorTable->rgbRed;
		pTempLogPalette->palPalEntry[i].peGreen = pRGBQUADColorTable->rgbGreen;
		pTempLogPalette->palPalEntry[i].peBlue = pRGBQUADColorTable->rgbBlue;
		pTempLogPalette->palPalEntry[i].peFlags = 0;
		pRGBQUADColorTable++;
	}
	
	// ������ɫ��
	m_hPalette = ::CreatePalette(pTempLogPalette);
	
	// ɾ����ʱ�߼���ɫ�岢����TRUE
	delete pTempLogPalette;
	
	return TRUE;
}

//ͼ��Ĵ�С
DWORD CLGJBmp::GetImageSize() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	if(pBitMapHeaderInfor->biSizeImage!=0)
	{
	return pBitMapHeaderInfor->biSizeImage;
	}
	else
	{
	return pBitMapHeaderInfor->biWidth* pBitMapHeaderInfor->biHeight*pBitMapHeaderInfor->biBitCount/8;  
	}
}

//��ȡ��ɫ��ָ��
LPVOID CLGJBmp::GetColorTable() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return (LPVOID) (pBitMapHeaderInfor + sizeof(BITMAPINFOHEADER));
}
//
//��ȡ�����ָ��
LPVOID CLGJBmp::GetBitmasks() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return (LPVOID) (pBitMapHeaderInfor + sizeof(BITMAPINFOHEADER));
}
//����ͼ������
LPBYTE CLGJBmp::GetBits() const
{
	return pBitDataBuffer;
}
int CLGJBmp::GetBitCount() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return pBitMapHeaderInfor->biBitCount;
}
//�ڴ��ȣ�4�ֽڵı���
int CLGJBmp::GetWidthMemory()
{
	//int ret = (pBitMapHeaderInfor->biWidth * pBitMapHeaderInfor->biBitCount + 31) / 32 * 4;
    int ret = (pBitMapHeaderInfor->biWidth * pBitMapHeaderInfor->biBitCount/8 + 3) / 4 * 4;
	return ret;	
}
//��ȡ��Ϣͷָ�롡
LPBITMAPINFOHEADER CLGJBmp::GetpBitMapInfoHeader() const
{
	return pBitMapHeaderInfor;
}

int CLGJBmp::GetWidth() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return pBitMapHeaderInfor->biWidth;
}

int CLGJBmp::GetHeight() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return pBitMapHeaderInfor->biHeight;
}


CString CLGJBmp::GetImageType(const CString& strName)
{
	return m_strImageType;
}

void CLGJBmp::SetImageType(const CString& strFileName)
{
	char mDriveName[_MAX_DRIVE];   
	char mDirName[_MAX_DIR];
	char mFileName[_MAX_FNAME];
	char mFileExtName[_MAX_EXT];

	//���ļ����ֳ�mDriveName,mDirName,mFileName,mFileExtName
	char  mANSIFilePath[MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, strFileName, -1, mANSIFilePath, MAX_PATH,NULL,NULL);//
  	_splitpath(mANSIFilePath, mDriveName, mDirName, mFileName, mFileExtName);//strFileName
	
     WCHAR  mUnicodeFileExt[10];
 	::MultiByteToWideChar(CP_ACP, 0, mFileExtName, -1, mUnicodeFileExt, 10);
	m_strImageType = mUnicodeFileExt;//mFileExtName
 
	//���ļ������ȷ���ļ�����
	m_strImageType = m_strImageType.Mid(1, 3);
	m_strImageType.MakeLower();
	//if(m_strImageType=="jpg")
     //m_strImageType="jpeg";

}

//��ʾͼ��
void CLGJBmp::DrawAnyImage(CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
  
	if(pGPImage!=NULL)
	{
	   pGPImage->Draw(pDC->m_hDC,0,0);
	}
	else if(pGdiplusImage!=NULL)
	{
       pGdiplusGraphics=new Graphics(pDC->m_hDC);
       pGdiplusGraphics->DrawImage(pGdiplusImage,80,50);
    
	}

}

void CLGJBmp::Draw(CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
	// �����ϢͷΪ�գ�����FALSE
	if(pBitMapHeaderInfor == NULL) 
	{
		return;
	}
	
	// ���ʹ�õ�ɫ�壬�򽫵�ɫ��ѡ���豸������
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	// ������ʾģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);
	
	// ���豸��ptOriginλ���ϻ�����СΪDestImageSize��ͼ��
	::StretchDIBits(pDC->GetSafeHdc(), 
		            ptOrigin.x, ptOrigin.y,			//Ŀ����ʼ��
		            DestImageSize.cx,DestImageSize.cy,//Ŀ�곤�Ϳ�
					0, 0, //------------------------Դ��ʼ��
					pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,//Դ���Ϳ�
					pBitDataBuffer, (LPBITMAPINFO) pBitMapHeaderInfor, 
					DIB_RGB_COLORS, SRCCOPY);
}

/*************************************************
Function:       DrawOnMemory
Description:    ʹ��˫���漼�������ڴ�����ʾͼ��
Input:          
Output:         
Return:        
Others:         
	���裺
		1>�����ڴ���ʾ�豸����
		2>���ڴ��ϻ�ͼ
		3>���ڴ��е�ͼ�񿽱�����Ļ��
*************************************************/
void CLGJBmp::DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
	// �����ϢͷΪ�գ�����FALSE
	if(pBitMapHeaderInfor == NULL) 
	{
		return;
	}
	
	// ���ʹ�õ�ɫ�壬�򽫵�ɫ��ѡ���豸������
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}
	
	CDC memDC;				//������ʾ�豸����
	CBitmap memBiitmap;		//����λͼ����

	//����Ļ��ʾ�豸���ݵ��ڴ�DC
	memDC.CreateCompatibleDC(NULL);

	//����Ļ��ʾ�豸���ݵ�λͼ
	memBiitmap.CreateCompatibleBitmap(pDC, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight);
	
	//��λͼѡ���ڴ��豸����
	CBitmap *pOldBit = memDC.SelectObject(&memBiitmap);

	//���ñ���ɫ���
	memDC.FillSolidRect(0, 0, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight, RGB(192, 192, 192));
	
	// ������ʾģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);
	
	// ���ڴ��л�ͼ
	::StretchDIBits(memDC.GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//��ʼ��
		DestImageSize.cx,DestImageSize.cy,//���Ϳ�
		0, 0, 
		pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,
		pBitDataBuffer, (LPBITMAPINFO) pBitMapHeaderInfor, 
		DIB_RGB_COLORS, SRCCOPY);
	
	//���ڴ��е�ͼ�񿽱���������Ļ��
	pDC->BitBlt(0, 0, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight, &memDC, 0, 0, SRCCOPY);

	//�ͷ���Դ
	memBiitmap.DeleteObject();
	memDC.DeleteDC();	
}


/*************************************************
Function:      DrawUseVFW
Description:   ʹ��VFW��������ʾ������ʾͼ��
Input:          
Output:         
Return:        
Others:         
	���裺
		1>����DrawDib����
		2>��ʼ��ͼ
		3>���DrawDib����
*************************************************/
void CLGJBmp::DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
	//׼����ͼ������DrawDib����
	DrawDibBegin(hDrawDib, pDC->GetSafeHdc(), 
				 DestImageSize.cx, DestImageSize.cy, pBitMapHeaderInfor, 			 
				 pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,
				 DDF_SAME_HDC);

	//��ʼ��ͼ��������SDK�е�StretchDIBits����
	DrawDibDraw(hDrawDib, pDC->GetSafeHdc(), 
				ptOrigin.x, ptOrigin.y,
				DestImageSize.cx, DestImageSize.cy,			
				pBitMapHeaderInfor, pBitDataBuffer,
				0, 0,
				pBitMapHeaderInfor->biWidth,pBitMapHeaderInfor->biHeight,
				DDF_SAME_HDC ) ;

	//��ͼ���������DrawDib����
	DrawDibEnd(hDrawDib);
}
