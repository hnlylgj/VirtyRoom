#if !defined(AFX_MEMBITMAP_H__3B96ADAC_FC6D_4D34_A7D0_639BFFE2D168__INCLUDED_)
#define AFX_MEMBITMAP_H__3B96ADAC_FC6D_4D34_A7D0_639BFFE2D168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemBitmap : public CBitmap  
{

private:  
	CWnd* pWnd;
public:
	CMemBitmap();
	virtual ~CMemBitmap();
public:

	void init(CWnd* pwnd);
    void Clear(int x1, int y1, int x2, int y2, COLORREF color);
	void TextOut(int x, int y, int iSize, LPCSTR strText,COLORREF color);
	
};

#endif // !defined(AFX_MEMBITMAP_H__3B96ADAC_FC6D_4D34_A7D0_639BFFE2D168__INCLUDED_)
