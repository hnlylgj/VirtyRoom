// MemBitmap.cpp: implementation of the CMemBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MemBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBitmap::CMemBitmap()
{

}

CMemBitmap::~CMemBitmap()
{

}
////////////////////////////////////////////////////////
//初始化位图类
void CMemBitmap::init(CWnd *pwnd)
{ 
	RECT rect;            
	//保存窗体客户区域的大小的矩形类型变量   
	pWnd = pwnd;                                   
	//获取窗体指针   
	pwnd->GetClientRect(&rect); 
	//得到窗体客户区域的大小   
    CreateCompatibleBitmap( pwnd->GetDC(), rect.right, rect.bottom );
    //利用窗体类的CDC指针在内存中创建位图   

}
/* CreateCompatibleBitmap函数作用是初始化位图类
其原型如下：
BOOL CreateCompatibleBitmap( CDC* pDC, int nWidth, int nHeight );
pDC是设备环境指针，本例用窗体的设备环境指针。
nWidth和nHeight是指定该位图尺寸的高度与宽度，单位为象素 */

//######################################################################

//TextOut函数用于在指定位置用指定的大小，颜色显示文本

void CMemBitmap::TextOut(int x, int y, int iSize, LPCSTR strText, COLORREF color)
{       
	CDC* pDC = pWnd->GetDC();
	//获取窗体的指针 
    CFont  NewFont;  
	//文本的字体对象       
	CFont  *OldFont; 
	//保存以前的字体指针       
	CDC    mMemDC ;   
	//内存中的DC指针，以便调用GDI函数在位图中绘图   
	mMemDC.CreateCompatibleDC(pDC);   
	//创建与窗体设备环境一样大小DC 
	
    mMemDC.SelectObject(this);       
	//将内存中的DC选择该类的位图对象

	NewFont.CreatePointFont(iSize,_T("宋体"));
	//创建显示文本的字体

	OldFont = mMemDC.SelectObject(&NewFont);   
	//选择新字体 
	
	mMemDC.SetTextColor(color);

	mMemDC.SetBkMode(TRANSPARENT );
	//设置透明方式

	CString tmpstr(strText);

	mMemDC.TextOut(x,y,tmpstr/*strText*/);
	//在指定位置显示文本 
	
	mMemDC.SelectObject(OldFont);
	//释放 

    NewFont.DeleteObject();      
	
	mMemDC.DeleteDC();
	
	pWnd->ReleaseDC(pDC);
}

//////////////////////////////////////////////////////////////
//
//实现一个清除位图函数，以便在适当时候用指定的颜色将位图填充
//达到清图的效果,参数x1,y1,x2,y2指定了矩形区的尺寸，color指定了填充色。

void CMemBitmap::Clear(int x1, int y1, int x2, int y2, COLORREF color)
{       
	CDC* pDC = pWnd->GetDC();       
	CDC mMemDC ; //内存中的DC指针
	
	mMemDC.CreateCompatibleDC(pDC);          
	
	mMemDC.SelectObject(this);
	
	CBrush  *OldBrush , blbrush(color);        
	     
	mMemDC.SetBkColor(color);
	
	OldBrush = mMemDC.SelectObject( &blbrush );
	
	mMemDC.Rectangle( x1 , y1 , x2 , y2 );
	
	mMemDC.SelectObject(OldBrush);       
	
	mMemDC.DeleteDC();       

	pWnd->ReleaseDC(pDC);
}


