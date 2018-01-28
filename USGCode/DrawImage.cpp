#include "StdAfx.h"
#include "DrawImage.h"

DrawImage::DrawImage(void)
{
	pSemaphore=NULL;
	pBitmap=NULL;
	pGraphics=NULL;
	pBitmapData=NULL;
	//pSemaphore=new CSemaphore();

}


DrawImage::~DrawImage(void)
{
   SAFE_DELETE(pSemaphore);
   SAFE_DELETE(pBitmap);
   SAFE_DELETE(pGraphics);
   SAFE_DELETE(pBitmapData);
   
}

void DrawImage::UpdateAlphaBitmap()
{
	if (pMixerControl ==NULL) return;
	INT mWidth,mHeight;
	//pSemaphore=new CSemaphore();
	//BOOL BL=pSemaphore->Lock(); 
	HRESULT hr=pMixerControl->GetOutputRect(&mOutputRectangle); 
	mWidth=(INT)(mOutputRectangle.right- mOutputRectangle.left); 
	mHeight=(INT)(mOutputRectangle.bottom- mOutputRectangle.top); 
	Rect mGDIPlusRect;
	//Rectangle aa;
	//rect1.left		= rect.Left;
	//rect1.right		= rect.Right;
	//rect1.top		= rect.Top;
	//rect1.bottom	= rect.Bottom;
	//mGDIPlusRect.X= mOutputRectangle.left;
	//mGDIPlusRect.Y= mOutputRectangle.top;
	mGDIPlusRect.Height=mHeight;
	mGDIPlusRect.Width =mWidth;

	mPixelFormat=PixelFormat32bppARGB; //--2498570--
	pBitmap=new Bitmap(mWidth,mHeight,mPixelFormat);
	pGraphics=new Graphics(pBitmap);
	//if (draw_bitmap == NULL)
	//{
		//draw_bitmap_rect = ultrasound_panel->ClientRectangle;
		//draw_bitmap = gcnew Bitmap(draw_bitmap_rect.Width, draw_bitmap_rect.Height, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
		//draw_bitmap_g = Graphics::FromImage(draw_bitmap);
		//draw_bitmap_pixel_format = draw_bitmap->PixelFormat;
	//}

	// clear current drawings in order to paint new drawings
	//ImageLockMode flags,
	//const Rect* pTempRectangle=(Rect*)&mOutputRectangle;
	pGraphics->Clear(Color(0,0,0,0));
	//draw_bitmap_g->DrawRectangle(gcnew Pen(Color::FromArgb(255,0,0)),10,10,100,100);
	// draw scale lines and maybe other graphics that will be put over ultrasound image
	DrawBImage(pGraphics,0,0,mWidth - 1, mHeight - 1);
	pBitmapData=new BitmapData();
    //ImageLockModeRead        = 0x0001,
    //ImageLockModeWrite       = 0x0002,
    //ImageLockModeUserInputBuf= 0x0004
	ImageLockMode mImageLockModeID=ImageLockModeRead;
	PixelFormat mmPixelFormat=pBitmap->GetPixelFormat();
	Status st=pBitmap->LockBits(&mGDIPlusRect, mImageLockModeID, mmPixelFormat,pBitmapData);
	//try {
	//	draw_bitmap_data = draw_bitmap->LockBits( draw_bitmap_rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, draw_bitmap_pixel_format );
    //
	//}
	//catch (Exception^)
	//{
	//}

	//BitmapBytesNumber =  (int)(pBitmapData->Height) * (int)(pBitmapData->Stride);
	mMixingBmpParams.clrSrcKey = (unsigned int)0;
	mMixingBmpParams.fAlpha = 1;
	mMixingBmpParams.rcSrc.left =0;
	mMixingBmpParams.rcSrc.top =0;
	mMixingBmpParams.rcSrc.right =mGDIPlusRect.GetRight();
	mMixingBmpParams.rcSrc.bottom = mGDIPlusRect.GetBottom();
	mMixingBmpParams.rcDest.left =mOutputRectangle.left;
	mMixingBmpParams.rcDest.top = mOutputRectangle.top;
	mMixingBmpParams.rcDest.right =mGDIPlusRect.GetRight()+mOutputRectangle.left;
	mMixingBmpParams.rcDest.bottom =mGDIPlusRect.GetBottom()+mOutputRectangle.top;

	mMixingBmpParams.dwFlags = (unsigned int)(UsgMixingBitmap_SrcColorKey) | (unsigned int)(UsgMixingBitmap_MixBitmap);
	mMixingBmpParams.mixBitmap.bmWidth = pBitmapData->Width;
	mMixingBmpParams.mixBitmap.bmHeight =-(pBitmapData->Height);
	mMixingBmpParams.mixBitmap.bmPlanes = 1;
	mMixingBmpParams.mixBitmap.bmBitsPixel = 32;
	mMixingBmpParams.mixBitmap.bmWidthBytes = pBitmapData->Stride;

	if (pBitmapData != NULL)
	{
		mMixingBmpParams.mixBitmap.bmBits =(HBITMAP)pBitmapData->Scan0;
		pMixerControl->SetAlphaBitmap(&mMixingBmpParams);
	}

	//try
	//{
		pBitmap->UnlockBits(pBitmapData );
	//}
	//catch (Exception^)
	//{
	//}

	//UpdateAlphaBitmap_semaphore->Release();
	//pSemaphore->Unlock(); 
	delete pBitmap;pBitmap=NULL;
	delete pGraphics;pGraphics=NULL;
    delete pBitmapData;pBitmapData=NULL;

} 

void DrawImage::DrawBImage(Graphics* pGraphics, int x1, int y1, int x2, int y2)
{
	if (pGraphics == NULL) return;
	//pGraphics->DrawLine(gcnew Pen(Color::FromArgb(255,0,0)),x1,y1,x2,y1);
	//pGraphics->DrawLine(gcnew Pen(Color::FromArgb(255,0,0)),x1,y2,x2,y2);
	//pGraphics->DrawLine(gcnew Pen(Color::FromArgb(255,0,0)),x1,y1,x1,y2);
	//pGraphics->DrawLine(gcnew Pen(Color::FromArgb(255,0,0)),x2,y1,x2,y2);
	if (pUsgImageProperties == NULL) return;
	tagPOINT mProbeCenterPoint;
	HRESULT hr=pUsgImageProperties->GetOrigin((POINT*)&mProbeCenterPoint,PIXELS_ORIGIN_OUTPUTRECT,0);
	// draw ellipse at probe center
	//Color mColor=Color(255,0,0);
	//Color mColor(255,0,0);
	Pen mPen(Color(255,0,0)); 
	//mPen.SetColor(mColor); 
	//pGraphics->DrawEllipse(new Pen(Color::FromArgb(255,0,0)),mProbeCenterPoint.x-2,mProbeCenterPoint.y-2,4,4);
	Status st=pGraphics->DrawEllipse(&mPen,mProbeCenterPoint.x-2,mProbeCenterPoint.y-2,4,4); 
	//mResolution - pixels per meter
	IMAGE_RESOLUTION mResolution;
	HRESULT hr1=pUsgImageProperties->GetResolution((IMAGE_RESOLUTION*)&mResolution,0);

	//draw vertical scale line (ticks every 10 mm)//||
	float VerticalLine;
	VerticalLine = (float)(mProbeCenterPoint.y);
	while (VerticalLine < (float)y2)
	{
		Status st=pGraphics->DrawLine(new Pen(Color(0,255,255)),(float)x1,VerticalLine,(float)x1+5,VerticalLine);
		VerticalLine = VerticalLine + (float)mResolution.nYPelsPerUnit/100;
	}

	// draw horizontal scale line (ticks every 10 mm)//--
	float HorizontalLine;
	HorizontalLine = (float)x1;
	while (HorizontalLine < (float)x2)
	{
		Status st=pGraphics->DrawLine(new Pen(Color(0,255,255)),HorizontalLine,(float)y2,HorizontalLine,(float)y2-5);
		HorizontalLine = HorizontalLine + (float)mResolution.nXPelsPerUnit/100;
	}
	// paint focusing points of active focusing zones for selected focusing mode and focusing set
	if (pUsgFocus == NULL) return;

	LONG CurrentMode;
	LONG ActiveFocusSetID;
	LONG FocalZonesCount;
	pUsgFocus->get_CurrentMode(&CurrentMode);
	pUsgFocus->get_FocusSet(CurrentMode,&ActiveFocusSetID);
	pUsgFocus->GetFocalZonesCount(CurrentMode,ActiveFocusSetID,&FocalZonesCount);
	//focus_mode = pUsgFocus->CurrentMode;
	//focus_set = pUsgFocus->put_CurrentMode(focus_mode);
	//focal_zones_count = pUsgFocus->GetFocalZonesCount(focus_mode, focus_set);
	/*
	array<System::Int32,1>^ arr;
	arr = gcnew cli::array< System::Int32 >(focal_zones_count);

	for (int i1=0; i1 < focal_zones_count; i1++)
		arr[i1] = 0;
	*/
	// get currently active focus zones for selected focusing mode and focusing set
	//pUsgFocus->GetFocusState( focus_mode, focus_set, focal_zones_count, arr[0] );
	 LONG* pFocusState=new LONG[FocalZonesCount];
		pUsgFocus->GetFocusState(CurrentMode,ActiveFocusSetID,FocalZonesCount,pFocusState);

	 for (LONG i = 0; i< FocalZonesCount; i++)
		 {
           if(pFocusState[i]==1)
			{
				FOCAL_ZONE mFocalZoneInfor;
				LONG ZoneCenterPoint=-1;
				LONG FocalCenterNumber=0;

				pUsgFocus->GetFocalZone(CurrentMode,ActiveFocusSetID,i,&mFocalZoneInfor);
				//pUsgFocus->GetFocalZone(focus_mode, focus_set, i1, zone);
				//zone_center = zone.nFocusPoint;
				ZoneCenterPoint=mFocalZoneInfor.nFocusPoint; 
				FocalCenterNumber = mProbeCenterPoint.y + (ZoneCenterPoint * mResolution.nYPelsPerUnit/1000);

				if (CurrentMode ==2)
					Status st=pGraphics->DrawLine(new Pen(Color(255,255,0),5),x1+5,FocalCenterNumber,x1+15,FocalCenterNumber);
				else
					Status st=pGraphics->DrawLine(new Pen(Color(255,0,255),5),x1+5,FocalCenterNumber,x1+15,FocalCenterNumber);
			}
		 }
	 /*
	for (int i1=0; i1 < focal_zones_count; i1++)
	{
		if (arr[i1] == 1)
		{
			// get depth of central point for each focusing zone
			tagFocalZone zone;
			int zone_center;
			int zone_center_pt;
			pUsgFocus->GetFocalZone(focus_mode, focus_set, i1, zone);
			zone_center = zone.nFocusPoint;

			zone_center_pt = mProbeCenterPoint.y + (zone_center * mResolution.nYPelsPerUnit/1000);

			if (focus_mode == (int)tagFocusMode::FOCUS_MODE_DYNAMIC)
				pGraphics->DrawLine(new Pen(Color(255,255,0),5),x1+5,zone_center_pt,x1+15,zone_center_pt);
			else
				pGraphics->DrawLine(new Pen(Color(255,0,255),5),x1+5,zone_center_pt,x1+15,zone_center_pt);
		}
	} 
	*/
   delete [] pFocusState;
   //==================================================================================================================================
   // begin: draw TGC curve
   	if (pUsgTgc == NULL) return;
	// NOTE. Here we paint not every curve point, but but connect with lines 5 points
	// (control points) that correspond to 5 user interface trackbars
	// point is created form control point depth (mm) and its Gain value (0-100%)

	Pen TgcCurvePen(Color(0,255,0)); 
	REAL* pTempFloatArray=new REAL[2];//***
	pTempFloatArray[0]=4.0F;
	pTempFloatArray[1]=2.0F;
	TgcCurvePen.SetDashPattern(pTempFloatArray,2);  

	int CtrlPointCount;
	LONG PositionFromTGCCurve;
	LONG DepthFromPosition;
	LONG TgcPointYValue;
	LONG CurrentTGCValue;

	CtrlPointCount = 5;
	Point* pTgcPointArray=new Point[CtrlPointCount];//***
  
	LONG TGCMarkerLength = 6; // length of horizontal TGC marker
	LONG TGCShiftToRight;
	TGCShiftToRight = (pBitmap->GetWidth() - 100);  // TGC shift from right image border--
	for (int i=0; i < CtrlPointCount; i++)
	{
		//pUsgTgc->PositionToDepth(i,&DepthFromPosition);//test
		pUsgTgc->get_CtlPointPos(i,&PositionFromTGCCurve);
		pUsgTgc->PositionToDepth(PositionFromTGCCurve,&DepthFromPosition);
		TgcPointYValue	= mProbeCenterPoint.y + (LONG)((float)DepthFromPosition * ((float)mResolution.nYPelsPerUnit/1000));
		pUsgTgc->get_Current(i,&CurrentTGCValue); 
		pTgcPointArray[i]= Point((INT)(CurrentTGCValue + TGCShiftToRight), (INT)(TgcPointYValue));
		// paint horizontal ticks at TGC curve that correspond to control points
		Status st1=pGraphics->DrawLine(new Pen(Color(255,0,255)), pTgcPointArray[i].X-TGCMarkerLength, pTgcPointArray[i].Y, pTgcPointArray[i].X, pTgcPointArray[i].Y);
	}
	// paint TGC curve itself (straight lines that connect control points)
	Status st2=pGraphics->DrawLines(&TgcCurvePen, pTgcPointArray,5);
	delete [] pTgcPointArray;delete []pTempFloatArray;
	// end: draw TGC curve
	
	
} 

