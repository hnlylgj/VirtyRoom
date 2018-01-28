// SnapForm.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtyRoom.h"
#include "SnapForm.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// SnapForm 对话框

IMPLEMENT_DYNAMIC(SnapForm, CDialogEx)

SnapForm::SnapForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SNAPFORM, pParent)
{

}

SnapForm::~SnapForm()
{
}

void SnapForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SnapForm, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// SnapForm 消息处理程序


HBRUSH SnapForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (nCtlColor == CTLCOLOR_DLG)//对话框颜色  
		return m_brush;//返会自定义刷子改变对话框背景颜色  



	//return hbr;
}


void SnapForm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	 // TODO: 在此处添加消息处理程序代码
	CDC* pDC = &dc;	
	OnDrawText(pOutSTR, 300, pDC);


	// 不绘图消息调用 CDialogEx::OnPaint()



}
void SnapForm::OnDrawText(LPCTSTR pOutSTR, int mFontCout, CDC* pDC)
{
	CRect  ViewDisplayRect;
	GetClientRect(&ViewDisplayRect);
	CFont m_Font;
	m_Font.CreatePointFont(300, _T("宋体"), NULL);
	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(RGB(0, 0, 255));
	//pDC->SetBkColor(RGB(191,219,255));//背景颜色设置  
	pDC->SetBkMode(TRANSPARENT);//背景透明色

	CSize mOutSTRSize;
	mOutSTRSize = pDC->GetTextExtent((CString)pOutSTR);//获得字符串长度

	LONG mOutTextPointX;
	LONG OutTextPointX;
	mOutTextPointX = ViewDisplayRect.Width();
	OutTextPointX = (mOutTextPointX - mOutSTRSize.cx) / 2;
	pDC->TextOut(OutTextPointX, 20, pOutSTR);//"牛顿运动三定律"

	CPen *pOldPen, newPen, newPen2;
	newPen.CreatePen(PS_SOLID, 6, RGB(126, 255, 0));
	pOldPen = pDC->SelectObject(&newPen);

	pDC->MoveTo(0, mOutSTRSize.cy + 22);
	pDC->LineTo(ViewDisplayRect.Width(), mOutSTRSize.cy + 22);
	pDC->SelectObject(pOldPen);




	// CRect cr;//矩形结构
	// GetClientRect(&cr);//获得客户区窗口 
	int cx = ViewDisplayRect.right;//右
	int cy = ViewDisplayRect.bottom;//底 
	pDC->SetMapMode(MM_ISOTROPIC);//X=Y   
	pDC->SetWindowExt(1000, 1000);//设置逻辑窗口，默认窗口原点为（0，0）
	pDC->SetViewportExt(cx, -cy);//定义输出视口,X右Y上为正
	pDC->SetViewportOrg(cx / 2, cy / 2);//定义视口原点为客户区中心
	pDC->Ellipse(-200, 200, 200, -200);//绘制椭圆与客户区外切的椭圆
									   //绘制水平垂直的四条半径
	newPen2.CreatePen(PS_SOLID, 4, RGB(15, 10, 255));
	pOldPen = pDC->SelectObject(&newPen2);
	pDC->MoveTo(0, 0); pDC->LineTo(200, 0);
	pDC->MoveTo(0, 0); pDC->LineTo(-200, 0);
	pDC->MoveTo(0, 0); pDC->LineTo(0, 200);
	pDC->MoveTo(0, 0); pDC->LineTo(0, -200);

	pDC->SelectObject(pOldPen);



}


BOOL SnapForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_brush.CreateSolidBrush(RGB(128, 138, 135)); // 生成一刷子：0, 255, 0

	pOutSTR = _T("牛顿运动三定律 ");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SnapForm::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString PointInforStr;
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CClientDC dc(this);
	CMFCRibbonBaseElement * pElement;
	pElement = pMainFrame->m_wndStatusBar.FindElement(ID_STATUSBAR_PANE4);
	//获取该点像素值
	COLORREF color = dc.GetPixel(point);
	BYTE R, G, B, temp;
	PointInforStr.Format(_T("(x=%i,y=%i) (R=%i G=%i B=%i)"), point.x, point.y, GetRValue(color), GetGValue(color), GetBValue(color));
	//在状态栏中显示像素值
	pElement->SetText(PointInforStr);
	pElement->Redraw();

	CDC*  pDC = GetDC();
	pDC->SetPixel(point, RGB(255, 0, 0));
	ReleaseDC(pDC); //释放设备对象


	CDialogEx::OnMouseMove(nFlags, point);
}
