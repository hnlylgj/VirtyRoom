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
//��ʼ��λͼ��
void CMemBitmap::init(CWnd *pwnd)
{ 
	RECT rect;            
	//���洰��ͻ�����Ĵ�С�ľ������ͱ���   
	pWnd = pwnd;                                   
	//��ȡ����ָ��   
	pwnd->GetClientRect(&rect); 
	//�õ�����ͻ�����Ĵ�С   
    CreateCompatibleBitmap( pwnd->GetDC(), rect.right, rect.bottom );
    //���ô������CDCָ�����ڴ��д���λͼ   

}
/* CreateCompatibleBitmap���������ǳ�ʼ��λͼ��
��ԭ�����£�
BOOL CreateCompatibleBitmap( CDC* pDC, int nWidth, int nHeight );
pDC���豸����ָ�룬�����ô�����豸����ָ�롣
nWidth��nHeight��ָ����λͼ�ߴ�ĸ߶����ȣ���λΪ���� */

//######################################################################

//TextOut����������ָ��λ����ָ���Ĵ�С����ɫ��ʾ�ı�

void CMemBitmap::TextOut(int x, int y, int iSize, LPCSTR strText, COLORREF color)
{       
	CDC* pDC = pWnd->GetDC();
	//��ȡ�����ָ�� 
    CFont  NewFont;  
	//�ı����������       
	CFont  *OldFont; 
	//������ǰ������ָ��       
	CDC    mMemDC ;   
	//�ڴ��е�DCָ�룬�Ա����GDI������λͼ�л�ͼ   
	mMemDC.CreateCompatibleDC(pDC);   
	//�����봰���豸����һ����СDC 
	
    mMemDC.SelectObject(this);       
	//���ڴ��е�DCѡ������λͼ����

	NewFont.CreatePointFont(iSize,_T("����"));
	//������ʾ�ı�������

	OldFont = mMemDC.SelectObject(&NewFont);   
	//ѡ�������� 
	
	mMemDC.SetTextColor(color);

	mMemDC.SetBkMode(TRANSPARENT );
	//����͸����ʽ

	CString tmpstr(strText);

	mMemDC.TextOut(x,y,tmpstr/*strText*/);
	//��ָ��λ����ʾ�ı� 
	
	mMemDC.SelectObject(OldFont);
	//�ͷ� 

    NewFont.DeleteObject();      
	
	mMemDC.DeleteDC();
	
	pWnd->ReleaseDC(pDC);
}

//////////////////////////////////////////////////////////////
//
//ʵ��һ�����λͼ�������Ա����ʵ�ʱ����ָ������ɫ��λͼ���
//�ﵽ��ͼ��Ч��,����x1,y1,x2,y2ָ���˾������ĳߴ磬colorָ�������ɫ��

void CMemBitmap::Clear(int x1, int y1, int x2, int y2, COLORREF color)
{       
	CDC* pDC = pWnd->GetDC();       
	CDC mMemDC ; //�ڴ��е�DCָ��
	
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


