/********************************************************************
	created:	2007/06/21
	created:	21:6:2005   21:55
	filename: 	imagetest\bmp.cpp
	file path:	imagetest
	file base:	bmp
	file mFileExtName:	cpp
	author:		LIGENGJUN
	
	  purpose:	读写BMP
	  //  [6/22/2005]　添加显示功能
	  
*********************************************************************/


#include "stdafx.h"
#include "LGJbmp.h"
//using namespace Gdiplus;
// 声明串行化过程
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
Description:    读取BMP图像
Input:          CFile *pFile
Output:         
Return:         BOOL  成功返回TRUE，否则返回FALSE
Others:         读取文件头、信息头、颜色表和图像数据 
*************************************************/
BOOL CLGJBmp::BMPRead(CFile *pFile)
{
	// 进行读操作
     int mReadCount=0;
	 int mBitMapHeaderSize=0;
     long mImageSize=0;
	try 
	{
		BITMAPFILEHEADER mFileHeaderInfor;
		
		// 步骤1　读取文件头
		int mReadCount = pFile->Read((LPVOID) &mFileHeaderInfor, sizeof(BITMAPFILEHEADER));
		
		// 判断是否是BMP格式的位图
		if(mFileHeaderInfor.bfType != BMP_HEADER_MARKER) 
		{
			//throw new CException;
			return FALSE;

		}
		// 计算信息头加上[颜色表\掩码表]的大小并分内存
		 mBitMapHeaderSize = mFileHeaderInfor.bfOffBits - sizeof(BITMAPFILEHEADER);
         pBitMapHeaderInfor = (LPBITMAPINFOHEADER) new BYTE[mBitMapHeaderSize];
	     // 步骤2　读取信息头[和颜色表\掩码表]
         mReadCount = pFile->Read(pBitMapHeaderInfor, mBitMapHeaderSize); 
		 if(pBitMapHeaderInfor->biCompression>4)
              mColorSpaceTypeID=YUV;
					
		// 步骤3　读取图象数据
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

	//创建调色板
	MakePalette();

	return TRUE;
}

/*************************************************
Function:       BMPWrite
Description:    写入BMP图像
Input:          CFile *pFile
Output:         
Return:         BOOL  成功返回TRUE，否则返回FALSE
Others:         BMP格式的图像以“BM”为开始标志
*************************************************/
BOOL CLGJBmp::BMPWrite(CFile *pFile)
{
	BITMAPFILEHEADER mFileHeaderInfor;
	
	// 设置文件头中文件类型 0x424D="BM"
	mFileHeaderInfor.bfType = BMP_HEADER_MARKER;  //0x4D42
	
	 ///////////////////////////////////////// 计算信息头和颜色表\掩码表大小
 	 int nSizeHeader;// = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();
	 if(pBitMapHeaderInfor->biCompression==3)
	 {
		
	    //计算信息头和掩码表大小
		 nSizeHeader = sizeof(BITMAPINFOHEADER) + 12;
	 }
	 else
	 {
		// 计算信息头和颜色表大小
	   nSizeHeader = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();
	 }
		//设置文件头信息
		mFileHeaderInfor.bfSize      = sizeof(BITMAPFILEHEADER) + nSizeHeader + GetImageSize();
		mFileHeaderInfor.bfReserved1 = 0;
		mFileHeaderInfor.bfReserved2 = 0;
     if(pBitMapHeaderInfor->biCompression==3)
	 {
	    //计算偏移量　文件头大小+信息头大小掩码表大小
		mFileHeaderInfor.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 12;	
	 }
	 else
	 {
     	//计算偏移量　文件头大小+信息头大小+颜色表大小
		mFileHeaderInfor.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetColorTableLenght();	
	 }
	// 进行写操作
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


//计算颜色表的大小
int CLGJBmp::GetColorTableLenght() const
{
	int ret = 0;

	if(pBitMapHeaderInfor->biClrUsed == 0) 	// 无颜色表存贮格式的【大小为2的biBitCount次方】	
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
	else // 有颜色表的存贮格式【大小为实际用到的颜色数】
	{
		ret = pBitMapHeaderInfor->biClrUsed;
	}

	return ret;
}

//串行化
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

	if(mArchive.IsStoring()) //写数据===============================
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
	else////读数据================================================================================================================
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
	   mMyBitMap.GetBitmap(&mBITMAPStruc);	    //取得源位图信息描述结构
	   scrW=mBITMAPStruc.bmWidth;	           //从源位图信息描述结构得到位图大小
	   scrH=mBITMAPStruc.bmHeight;
       desW=scrW,
	   desH=scrH;

        LPBITMAPINFOHEADER   pBitMapHeaderInfor=(LPBITMAPINFOHEADER)new BYTE[512];;		  //位图信息头
	    BYTE*		         pBitDataBuffer=(BYTE*)mBITMAPStruc.bmBits; 		          //位图数据
		pBitMapHeaderInfor->biSize = sizeof(BITMAPINFOHEADER);
		pBitMapHeaderInfor->biWidth =mBITMAPStruc.bmWidth ;
		pBitMapHeaderInfor->biHeight =mBITMAPStruc.bmHeight;
		pBitMapHeaderInfor->biPlanes = 1;     //固定为1;
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
       //先用背景色填充
	   mMyNewDC.FillSolidRect(0, 0, scrW, scrH, RGB(192, 192, 192));
      // 设置显示模式
	   pDC->SetStretchBltMode(COLORONCOLOR);
       // 在内存中画图
	   StretchDIBits(mMyNewDC.GetSafeHdc(), 
					0, 0,			//起始点
					desW,desH,      //长和宽
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
       scrW=pBitMapHeaderInfor->biWidth;	           //从源位图信息描述结构得到位图大小
	   scrH=pBitMapHeaderInfor->biHeight;
       desW=scrW,
	   desH=scrH;

       mMyNewDC.CreateCompatibleDC(NULL);
       mMyJunkBitmap.CreateCompatibleBitmap(pDC,scrW,scrH); 
       //CBitmap* pOldBitmap =
	   mMyNewDC.SelectObject(&mMyJunkBitmap); 
       //先用背景色填充
	   mMyNewDC.FillSolidRect(0, 0, scrW, scrH, RGB(192, 192, 192));
      // 设置显示模式
	   pDC->SetStretchBltMode(COLORONCOLOR);
       // 在内存中画图
	   StretchDIBits(mMyNewDC.GetSafeHdc(), 
					0, 0,			//起始点
					desW,desH,      //长和宽
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
//得到格式为StrFormat的图像文件的编码值，访问该格式图像的COM组件的GUID值保存在pCLSID中   
UINT   num   =   0;   
UINT   size   =   0;   
ImageCodecInfo* pImageCodecInfo   =   NULL;   
GetImageEncodersSize(&num,   &size);   
if(size   ==   0)   
  return   FALSE;   //   编码信息不可用   
//分配内存   
pImageCodecInfo   =   (ImageCodecInfo*)(malloc(size));   
if(pImageCodecInfo   ==   NULL)   
   return   FALSE;   //   分配失败   
//获得系统中可用的编码方式的所有信息   
GetImageEncoders(num,   size,   pImageCodecInfo);   
//在可用编码信息中查找format格式是否被支持   
for(UINT   i   =   0;   i   <   num;   ++i)   
{   //MimeType：编码方式的具体描述   
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

//创建调色板
BOOL CLGJBmp::MakePalette()
{
	// 如果不存在调色板，则返回FALSE
	int TestValue= GetColorTableLenght();
	if(TestValue == 0) 
	{
		return FALSE;
	}
	
	if(m_hPalette != NULL) 
	{
		::DeleteObject(m_hPalette);
	}
	
	// 给逻辑调色板分配内存
	LPLOGPALETTE pTempLogPalette = (LPLOGPALETTE) new char[2 * sizeof(WORD) + GetColorTableLenght() * sizeof(PALETTEENTRY)];
	
	// 设置逻辑调色板的信息
	pTempLogPalette->palVersion = 	0x300;
	pTempLogPalette->palNumEntries = GetColorTableLenght();
	
	// 拷贝DIB中的颜色表到逻辑调色板
	LPRGBQUAD pRGBQUADColorTable = (LPRGBQUAD) GetColorTable();
	for(int i = 0; i < GetColorTableLenght(); ++i) 
	{
		pTempLogPalette->palPalEntry[i].peRed = pRGBQUADColorTable->rgbRed;
		pTempLogPalette->palPalEntry[i].peGreen = pRGBQUADColorTable->rgbGreen;
		pTempLogPalette->palPalEntry[i].peBlue = pRGBQUADColorTable->rgbBlue;
		pTempLogPalette->palPalEntry[i].peFlags = 0;
		pRGBQUADColorTable++;
	}
	
	// 创建调色板
	m_hPalette = ::CreatePalette(pTempLogPalette);
	
	// 删除临时逻辑调色板并返回TRUE
	delete pTempLogPalette;
	
	return TRUE;
}

//图像的大小
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

//获取颜色表指针
LPVOID CLGJBmp::GetColorTable() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return (LPVOID) (pBitMapHeaderInfor + sizeof(BITMAPINFOHEADER));
}
//
//获取掩码表指针
LPVOID CLGJBmp::GetBitmasks() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return (LPVOID) (pBitMapHeaderInfor + sizeof(BITMAPINFOHEADER));
}
//返回图像数据
LPBYTE CLGJBmp::GetBits() const
{
	return pBitDataBuffer;
}
int CLGJBmp::GetBitCount() const
{
	ASSERT(pBitMapHeaderInfor != NULL);
	return pBitMapHeaderInfor->biBitCount;
}
//内存宽度，4字节的倍数
int CLGJBmp::GetWidthMemory()
{
	//int ret = (pBitMapHeaderInfor->biWidth * pBitMapHeaderInfor->biBitCount + 31) / 32 * 4;
    int ret = (pBitMapHeaderInfor->biWidth * pBitMapHeaderInfor->biBitCount/8 + 3) / 4 * 4;
	return ret;	
}
//获取信息头指针　
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

	//把文件名分成mDriveName,mDirName,mFileName,mFileExtName
	char  mANSIFilePath[MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, strFileName, -1, mANSIFilePath, MAX_PATH,NULL,NULL);//
  	_splitpath(mANSIFilePath, mDriveName, mDirName, mFileName, mFileExtName);//strFileName
	
     WCHAR  mUnicodeFileExt[10];
 	::MultiByteToWideChar(CP_ACP, 0, mFileExtName, -1, mUnicodeFileExt, 10);
	m_strImageType = mUnicodeFileExt;//mFileExtName
 
	//由文件名后辍确定文件类型
	m_strImageType = m_strImageType.Mid(1, 3);
	m_strImageType.MakeLower();
	//if(m_strImageType=="jpg")
     //m_strImageType="jpeg";

}

//显示图像
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
	// 如果信息头为空，返回FALSE
	if(pBitMapHeaderInfor == NULL) 
	{
		return;
	}
	
	// 如果使用调色板，则将调色板选入设备上下文
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	// 设置显示模式
	pDC->SetStretchBltMode(COLORONCOLOR);
	
	// 在设备的ptOrigin位置上画出大小为DestImageSize的图象
	::StretchDIBits(pDC->GetSafeHdc(), 
		            ptOrigin.x, ptOrigin.y,			//目标起始点
		            DestImageSize.cx,DestImageSize.cy,//目标长和宽
					0, 0, //------------------------源起始点
					pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,//源长和宽
					pBitDataBuffer, (LPBITMAPINFO) pBitMapHeaderInfor, 
					DIB_RGB_COLORS, SRCCOPY);
}

/*************************************************
Function:       DrawOnMemory
Description:    使用双缓存技术，在内存上显示图像
Input:          
Output:         
Return:        
Others:         
	步骤：
		1>定义内存显示设备环境
		2>在内存上画图
		3>将内存中的图像拷贝到屏幕上
*************************************************/
void CLGJBmp::DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
	// 如果信息头为空，返回FALSE
	if(pBitMapHeaderInfor == NULL) 
	{
		return;
	}
	
	// 如果使用调色板，则将调色板选入设备上下文
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}
	
	CDC memDC;				//定义显示设备环境
	CBitmap memBiitmap;		//定义位图对象

	//与屏幕显示设备兼容的内存DC
	memDC.CreateCompatibleDC(NULL);

	//与屏幕显示设备兼容的位图
	memBiitmap.CreateCompatibleBitmap(pDC, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight);
	
	//将位图选入内存设备环境
	CBitmap *pOldBit = memDC.SelectObject(&memBiitmap);

	//先用背景色填充
	memDC.FillSolidRect(0, 0, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight, RGB(192, 192, 192));
	
	// 设置显示模式
	pDC->SetStretchBltMode(COLORONCOLOR);
	
	// 在内存中画图
	::StretchDIBits(memDC.GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//起始点
		DestImageSize.cx,DestImageSize.cy,//长和宽
		0, 0, 
		pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,
		pBitDataBuffer, (LPBITMAPINFO) pBitMapHeaderInfor, 
		DIB_RGB_COLORS, SRCCOPY);
	
	//将内存中的图像拷贝拷贝到屏幕上
	pDC->BitBlt(0, 0, pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight, &memDC, 0, 0, SRCCOPY);

	//释放资源
	memBiitmap.DeleteObject();
	memDC.DeleteDC();	
}


/*************************************************
Function:      DrawUseVFW
Description:   使用VFW组件提高显示性能显示图像
Input:          
Output:         
Return:        
Others:         
	步骤：
		1>设置DrawDib环境
		2>开始画图
		3>清除DrawDib环境
*************************************************/
void CLGJBmp::DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize DestImageSize)
{
	//准备画图，设置DrawDib环境
	DrawDibBegin(hDrawDib, pDC->GetSafeHdc(), 
				 DestImageSize.cx, DestImageSize.cy, pBitMapHeaderInfor, 			 
				 pBitMapHeaderInfor->biWidth, pBitMapHeaderInfor->biHeight,
				 DDF_SAME_HDC);

	//开始画图－－代替SDK中的StretchDIBits函数
	DrawDibDraw(hDrawDib, pDC->GetSafeHdc(), 
				ptOrigin.x, ptOrigin.y,
				DestImageSize.cx, DestImageSize.cy,			
				pBitMapHeaderInfor, pBitDataBuffer,
				0, 0,
				pBitMapHeaderInfor->biWidth,pBitMapHeaderInfor->biHeight,
				DDF_SAME_HDC ) ;

	//画图结束，清除DrawDib环境
	DrawDibEnd(hDrawDib);
}
