#pragma once
#define SAFE_DELETE(x) { if (x) delete x; x = NULL; }
#include "Usgfw2_h.h"
using namespace Gdiplus;
class DrawImage
{
public:
	DrawImage(void);
	~DrawImage(void);
	IUsgMixerControl* pMixerControl;
	IUsgImageProperties* pUsgImageProperties;
	IUsgFocus* pUsgFocus;
	IUsgTgc* pUsgTgc; //ÏßÐÔÔö²¹
	//RECT* pOutputRectangle;
	Rect* pOutputRectangle;
	//HDC mhdc;
private:

 CSemaphore* pSemaphore; 
 USG_MIXING_BITMAP mMixingBmpParams;
 Bitmap* pBitmap;
 Graphics* pGraphics;
 RECT mOutputRectangle;
 int BitmapBytesNumber;
 BitmapData* pBitmapData;
 PixelFormat mPixelFormat;
 
void DrawBImage(Graphics* pGraphics, int x1, int y1, int x2, int y2);
public:
	
void UpdateAlphaBitmap();

};

