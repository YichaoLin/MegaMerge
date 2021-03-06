
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "MegaGraph.h"
#include "ChildView.h"
#include "GraphInPaper.h"
#include "NodeInPaper.h"
#include "EdgeInPaper.h"
#include "NodeRelation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	:m_pGraphData(NULL)
	, m_fRadius(10)
	, m_pBtnNext(NULL)
	, m_pBtnRun(NULL)
	, m_bButtonDown(FALSE)
	, m_nPhase(0)
	, m_bIsRunning(FALSE)
	, m_nMessageCount(0)
	, m_pTestDataCreater(NULL)
	, m_nMessageInOneIteration(0)
	, m_nIterationId(0)
	, m_nCityCount(0)
{

	m_crEdgeRelationFill = RGB(50, 100, 50);
	m_crEdgeRelationBound = RGB(100, 200, 100);
	m_crEdgeInsideFill = RGB(100, 100, 50);
	m_crEdgeInsideBound = RGB(200, 200, 100);
	m_crEdgeOutsideFill = RGB(50, 50, 50);
	m_crEdgeOutsideBound = RGB(50, 50, 50);
	m_crEdgeWishFill = RGB(100, 50, 50);
	m_crEdgeWishBound = RGB(200, 100, 100);

	m_crNodeCommonFill = RGB(200, 130, 130);
	m_crNodeCommonBound = RGB(200, 100, 100);
	m_crNodeChargeFill = RGB(180, 50, 50);
	m_crNodeChargeBound = RGB(180, 50, 50);

	m_nScreenUp = 60;
	m_nScreenDown = 40;
	m_nScreenLeft = 20;
	m_nScreenRight = 150;
}

void CChildView::SetGraphData(CGraphInPaper * pGraphData)
{
	if (pGraphData)
	{
		m_pGraphData = pGraphData;
		return;
	}
	m_pGraphData = new CGraphInPaper();
	m_pGraphData->Init(10, 10, 5, 200, 200);
	m_pGraphData->m_nNodeCount = 5;
	m_pGraphData->m_pNodes[0].SetValue(100, 100);
	m_pGraphData->m_pNodes[1].SetValue(300, 150);
	m_pGraphData->m_pNodes[2].SetValue(100, 400);
	m_pGraphData->m_pNodes[3].SetValue(350, 350);
	m_pGraphData->m_pNodes[4].SetValue(300, 450);
	CNodeInPaper * pNodes = m_pGraphData->m_pNodes;
	m_pGraphData->m_nEdgeCount = 8;
	int i = 0;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 0, pNodes + 1);
	m_pGraphData->m_pEdges[i - 1].m_eRelation = E_NODERELATION_CHILD;
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 0, pNodes + 2);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 0, pNodes + 3);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 1, pNodes + 2);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 1, pNodes + 3);
	m_pGraphData->m_pEdges[i - 1].m_eRelation = E_NODERELATION_CHILD;
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 2, pNodes + 3);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 2, pNodes + 4);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_OUTSIDE;
	m_pGraphData->m_pEdges[i++].SetNodes(pNodes + 3, pNodes + 4);
	m_pGraphData->m_pEdges[i - 1].m_eEdgeState = E_EDGESTATE_INSIDE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_NEXT, &CChildView::OnButtonNext)
	ON_BN_CLICKED(IDC_BTN_RUN, &CChildView::OnButtonRun)
	ON_BN_CLICKED(IDC_BTN_CREATE, &CChildView::OnButtonCreate)
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()

	MyOnPaint(&dc);


// 	if (m_bButtonDown)
// 	{
// 		m_bButtonDown = m_bButtonDown;
// 		m_bButtonDown = FALSE;
// 	}
// 	dc.SetBkMode(TRANSPARENT);
// 	DrawAllInsideEdges(dc);
// 	DrawAllOutsideEdges(dc);
// 	DrawAllNodes(dc);
// 	DrawMessageStratic(dc);
}

void CChildView::OnButtonNext()
{
	OnNext(FALSE);
}

void CChildView::OnButtonRun()
{
#if 0
	m_pBtnRun->SetWindowTextW(_T("running"));
	Invalidate(TRUE);
	while (m_pTestDataCreater->m_NodeTable.judge() == 0)
	{
		OnNext(FALSE);
	}
	m_pBtnRun->SetWindowTextW(_T("OVER"));
	Invalidate(TRUE);
	return;
#endif
	if (m_bIsRunning == FALSE)
	{
		m_pBtnRun->SetWindowTextW(_T("PAUSE"));
		SetTimer(RUN_TIMER_ID, RUN_TIME_INTER, NULL);
	}
	else
	{
		m_pBtnRun->SetWindowTextW(_T("RUN"));
		KillTimer(RUN_TIMER_ID);
	}
	m_bIsRunning = !m_bIsRunning;
}

void CChildView::OnButtonCreate()
{
	CreateData();
}

void CChildView::OnNext(BOOL bRefresh)
{

	if (m_pTestDataCreater->m_NodeTable.judge() != 0)
	{
		if (m_bIsRunning)
		{
			KillTimer(RUN_TIMER_ID);
			m_bIsRunning = FALSE;
		}
		m_pBtnRun->SetWindowTextW(_T("OVER"));
		return;
	}
	switch (m_nPhase)
	{
	case 0:
	{
		m_pTestDataCreater->m_NodeTable.CleanReport();
		m_pTestDataCreater->m_NodeTable.AllReport();
		m_pTestDataCreater->m_NodeTable.AllGroupSetChoosen();
		int nInsideMessage = m_pTestDataCreater->m_NodeTable.GetMessageCountThisIteration();
		int nConnectCount = m_pTestDataCreater->m_NodeTable.GetConnectMessageCount();
		m_nMessageInOneIteration = nInsideMessage + nConnectCount;
		m_nIterationId++;
		//OutputDebugString(_T("\n\nNew Iteration"));
		m_nMessageCount += nInsideMessage + nConnectCount;
		m_nDebug[0] = nInsideMessage;
		m_nCityCount = m_pTestDataCreater->m_NodeTable.GetCityCount();
		break;
	}
	case 1:
	{
		m_pTestDataCreater->m_NodeTable.AllMerge();
		m_pTestDataCreater->m_Graph.UpdateAllEdges();
		int nNotify = m_pTestDataCreater->m_NodeTable.GetNotifyMessageCount();
		m_nDebug[1] = nNotify;
		m_nMessageInOneIteration += nNotify;
		m_nMessageCount += nNotify;
		m_nCityCount = m_pTestDataCreater->m_NodeTable.GetCityCount();

		CString strOut;
		strOut.Format(_T("\nCity %5d  "), m_nCityCount);
		OutputDebugString(strOut);
		break;
	}
	}
	m_nPhase++;
	m_nPhase = m_nPhase % 2;
	Invalidate(bRefresh);
}

void CChildView::GetBottomCoor(const POINT & p1, const POINT & p2, POINT & pL, POINT & pR, double fRadius) const
{
	double X1 = p1.x;
	double Y1 = p1.y;
	double X2 = p2.x;
	double Y2 = p2.y;
	if (Y1 != Y2)
	{
		double fRate = (X2 - X1) / (Y2 - Y1);
		double divresult = fRate*fRate;
		double fMpositive = sqrt(fRadius*fRadius / (1 + divresult));
		double fMnegative = -fMpositive;
		double fNpositive = -fMpositive*fRate;
		double fNnegative = -fMnegative*fRate;
		if (Y2 > Y1)
		{
			pL.x = fMpositive + X1;
			pL.y = fNpositive + Y1;
			pR.x = fMnegative + X1;
			pR.y = fNnegative + Y1;
		}
		else
		{
			pR.x = fMpositive + X1;
			pR.y = fNpositive + Y1;
			pL.x = fMnegative + X1;
			pL.y = fNnegative + Y1;
		}
	}
	else
	{
		pL.x = X1;
		pR.x = X1;
		if (X2 > X1)
		{
			pL.y = Y1 - fRadius;
			pR.y = Y1 + fRadius;
		}
		else
		{
			pL.y = Y1 + fRadius;
			pR.y = Y1 - fRadius;
		}
	}
}

POINT CChildView::GetHalfCoor(const POINT & p1, const POINT & p2, double fRate)
{
	double X1 = p1.x;
	double Y1 = p1.y;
	double X2 = p2.x;
	double Y2 = p2.y;
	POINT pntRet;
	pntRet.x = (X2 - X1)*fRate + X1;
	pntRet.y = (Y2 - Y1)*fRate + Y1;
	return pntRet;
}

void CChildView::DrawTriangle(CDC & dc, COLORREF crBoundary, COLORREF crInside, const POINT & pntTop, const POINT & pntBottomCenter, double fRadius, double fBoundaryWidth)
{
	POINT pnts[3];
	pnts[0] = pntTop;
	GetBottomCoor(pntBottomCenter, pntTop, pnts[1], pnts[2], fRadius);

	CPen * pCirclePen = new CPen(PS_SOLID, fBoundaryWidth, crBoundary);
	CPen * pOldPen = dc.SelectObject(pCirclePen);
	CBrush * pBrush = new CBrush(crInside);
	CBrush * pOldBrush = dc.SelectObject(pBrush);

	dc.MoveTo(pnts[2]);
	dc.Polygon(pnts, 3);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	delete pCirclePen;
	delete pBrush;
}

void CChildView::DrawAllInsideEdges(CDC & dc)
{
	if (!m_pGraphData)
	{
		return;
	}
	for (int i = 0; i < m_pGraphData->m_nEdgeCount; ++i)
	{
		CEdgeInPaper * pEdge = m_pGraphData->m_pEdges + i;
		E_NODERELATION eRelation = pEdge->GetRelationByNode1();
		if (eRelation == E_NODERELATION_NONE)
		{
			if (pEdge->IsInsideEdge())
			{
				POINT pntStart = { pEdge->m_pNode1->m_nX + m_nScreenLeft, pEdge->m_pNode1->m_nY + m_nScreenUp };
				POINT pntEnd = { pEdge->m_pNode2->m_nX + m_nScreenLeft, pEdge->m_pNode2->m_nY + m_nScreenUp };
				DrawDashLine(dc, m_crEdgeInsideBound, pntStart, pntEnd, 3);
			}
		}
	}
	for (int i = 0; i < m_pGraphData->m_nEdgeCount; ++i)
	{
		CEdgeInPaper * pEdge = m_pGraphData->m_pEdges + i;
		E_NODERELATION eRelation = pEdge->GetRelationByNode1();
		if (eRelation == E_NODERELATION_CHILD)
		{
			POINT pntStart = { pEdge->m_pNode1->m_nX + m_nScreenLeft, pEdge->m_pNode1->m_nY + m_nScreenUp };
			POINT pntEnd = { pEdge->m_pNode2->m_nX + m_nScreenLeft, pEdge->m_pNode2->m_nY + m_nScreenUp };
			DrawTriangle(dc, m_crEdgeRelationBound, m_crEdgeRelationFill, pntEnd, pntStart, m_fRadius/2.0, 3);
		}
		else if(eRelation == E_NODERELATION_FATHER)
		{
			POINT pntStart = { pEdge->m_pNode2->m_nX + m_nScreenLeft, pEdge->m_pNode2->m_nY + m_nScreenUp };
			POINT pntEnd = { pEdge->m_pNode1->m_nX + m_nScreenLeft, pEdge->m_pNode1->m_nY + m_nScreenUp };
			DrawTriangle(dc, m_crEdgeRelationBound, m_crEdgeRelationFill, pntEnd, pntStart, m_fRadius / 2.0, 3);
		}
	}
}

void CChildView::DrawAllOutsideEdges(CDC & dc)
{
	if (!m_pGraphData)
	{
		return;
	}

	for (int i = 0; i < m_pGraphData->m_nEdgeCount; ++i)
	{
		CEdgeInPaper * pEdge = m_pGraphData->m_pEdges + i;
		if (!pEdge->IsInsideEdge())
		{
			POINT pntStart = { pEdge->m_pNode1->m_nX+m_nScreenLeft, pEdge->m_pNode1->m_nY + m_nScreenUp };
			POINT pntEnd = { pEdge->m_pNode2->m_nX + m_nScreenLeft, pEdge->m_pNode2->m_nY + m_nScreenUp };
			DrawDashLine(dc, m_crEdgeOutsideFill, pntStart, pntEnd, 1);
		}
	}
	if (m_nPhase != 0)
	{
		for (int i = 0; i < m_pGraphData->m_nNodeCount; ++i)
		{
			CMegaNode * pNodeData = m_pGraphData->m_pNodes[i].m_pNodeData;
			if (pNodeData->m_GroupInfo.pMinInside != pNodeData || pNodeData->m_GroupInfo.pMinOutside == NULL)
			{
				continue;
			}

			int nNodeIndex = pNodeData - m_pTestDataCreater->m_NodeTable.m_pNodes;
			int nAnotherIndex = pNodeData->m_GroupInfo.pMinOutside - m_pTestDataCreater->m_NodeTable.m_pNodes;

			CNodeInPaper * pNode = m_pGraphData->m_pNodes + nNodeIndex;
			CNodeInPaper * pAnotherNode = m_pGraphData->m_pNodes + nAnotherIndex;
			POINT pntStart = { pNode->m_nX + m_nScreenLeft, pNode->m_nY + m_nScreenUp };
			POINT pntAnotherSide = { pAnotherNode->m_nX + m_nScreenLeft, pAnotherNode->m_nY + m_nScreenUp };
			POINT pntEnd = GetHalfCoor(pntStart, pntAnotherSide, 0.4);
			CEdgeInPaper * pEdge = m_pGraphData->m_pEdges + i;
			E_NODERELATION eRelation = pEdge->GetRelationByNode1();
			DrawTriangle(dc, m_crEdgeWishBound, m_crEdgeWishFill, pntEnd, pntStart, m_fRadius / 3.0, 3);
		}
	}
// 	CString strValue;
// 	POINT pnt = { SUMMARY_X, 15 };
// 	strValue.Format(_T("Totle messages:%3d"), m_nMessageCount);
// 	DrawOneText(dc, RGB(0, 0, 0), pnt, strValue);
}

void CChildView::DrawAllNodes(CDC & dc)
{
	if (!m_pGraphData)
	{
		return;
	}

	int nCtrlCount = 0;
	double drawRadius = m_fRadius *0.85;
	double CircleBound = m_fRadius *0.3;
	for (int i = 0; i < m_pGraphData->m_nNodeCount; ++i)
	{
		CNodeInPaper * pNode = m_pGraphData->m_pNodes + i;
		POINT pntCenter = {pNode->GetX()+m_nScreenLeft, pNode->GetY()+m_nScreenUp};
		if(!pNode->m_pNodeData)
			DrawOneNode(dc, m_crNodeCommonBound, m_crNodeCommonFill, pntCenter, drawRadius, CircleBound);
		else
		{
			if (pNode->m_pNodeData == pNode->m_pNodeData->m_GroupInfo.pRoot)
			{
				DrawOneNode(dc, m_crNodeChargeBound, m_crNodeChargeFill, pntCenter, drawRadius, CircleBound);
				++nCtrlCount;
			}
			else
			{
				DrawOneNode(dc, m_crNodeCommonBound, m_crNodeCommonFill, pntCenter, drawRadius, CircleBound);
			}
		}
	}
	if (m_fRadius > 8)
	{
		for (int i = 0; i < m_pGraphData->m_nNodeCount; ++i)
		{
			CNodeInPaper * pNode = m_pGraphData->m_pNodes + i;
			POINT pntCenter = { pNode->GetX() + m_nScreenLeft - 10, pNode->GetY() + m_nScreenUp + m_fRadius };
			CString strValue;
			strValue.Format(_T("%.3f"), pNode->m_pNodeData->m_fValue);
			DrawOneText(dc, RGB(0, 0, 0), pntCenter, strValue);
		}
	}

// 	CString strValue;
// 	POINT pnt = { SUMMARY_X + 180, 15 };
// 	strValue.Format(_T("Charge Nodes:%3d"), nCtrlCount);
// 	DrawOneText(dc, RGB(0, 0, 0), pnt, strValue);
}

void CChildView::DrawDashLine(CDC & dc, COLORREF crColor, const POINT & pntStart, const POINT & pntEnd, double fWidth)
{
	CPen * pCirclePen = new CPen(PS_DASH, fWidth, crColor);
	CPen * pOldPen = dc.SelectObject(pCirclePen);
	dc.SelectStockObject(NULL_BRUSH);

	dc.MoveTo(pntStart);
	dc.LineTo(pntEnd);

	dc.SelectObject(pOldPen);
	delete pCirclePen;
}

void CChildView::DrawOneNode(CDC & dc, COLORREF crBoundary, COLORREF crInside, const POINT & pntCenter, double fRadius, double fBoundaryWidth)
{
	RECT rect = { pntCenter.x - m_fRadius, pntCenter.y - m_fRadius, pntCenter.x + m_fRadius, pntCenter.y + m_fRadius };
	CPen * pCirclePen = new CPen(PS_SOLID, fBoundaryWidth, crBoundary);
	CPen * pOldPen = dc.SelectObject(pCirclePen);
	CBrush * pBrush = new CBrush(crInside);
	CBrush * pOldBrush = dc.SelectObject(pBrush);

	dc.Ellipse(&rect);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	delete pCirclePen;
	delete pBrush;

}

void CChildView::DrawOneText(CDC & dc, COLORREF crText, const POINT & pntCenter, const CString & strValue)
{
	CPen * pCirclePen = new CPen(PS_SOLID, 3, crText);
	CPen * pOldPen = dc.SelectObject(pCirclePen);

	dc.TextOutW(pntCenter.x, pntCenter.y, strValue);

	dc.SelectObject(pOldPen);
	delete pCirclePen;
}



void CChildView::DrawMessageStratic(CDC & dc)
{
	CPen * pCirclePen = new CPen(PS_SOLID, 3, RGB(0,0,0));
	CPen * pOldPen = dc.SelectObject(pCirclePen);

	CRect rect;
	GetClientRect(rect);

	int nYaxis = 30;
	int nXaxis = rect.right - m_nScreenRight + 15;
	int nTextHeigh = 15;
	int nNumberTab = 20;
	CString strOut;
	strOut.Format(_T("Iteration:"));
	dc.TextOutW(nXaxis, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("%d"), m_nIterationId);
	dc.TextOutW(nXaxis + nNumberTab, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("Totle messages:"));
	dc.TextOutW(nXaxis, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("%d"), m_nMessageCount);
	dc.TextOutW(nXaxis + nNumberTab, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("Message this time:"));
	dc.TextOutW(nXaxis, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("%d"), m_nMessageInOneIteration);
	dc.TextOutW(nXaxis + nNumberTab, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("City count:"));
	dc.TextOutW(nXaxis, nYaxis, strOut);
	nYaxis += nTextHeigh;
	strOut.Format(_T("%d"), m_nCityCount);
	dc.TextOutW(nXaxis + nNumberTab, nYaxis, strOut);

	nYaxis += nTextHeigh;
// 	for (int i = 0; i < 5; ++i)
// 	{
// 		nYaxis += nTextHeigh;
// 		strOut.Format(_T("DBG%d__%d"),i,  m_nDebug[i]);
// 		dc.TextOutW(nXaxis + nNumberTab, nYaxis, strOut);
// 	}

	dc.SelectObject(pOldPen);
	delete pCirclePen;
}

void CChildView::MyOnPaint(CDC * pDC)
{
	CDC memDC;
	CBitmap cMemBitmap;
	CBitmap * pOldBitmap;
	memDC.CreateCompatibleDC(pDC);
	CRect rctClient;
	GetClientRect(rctClient);
	cMemBitmap.CreateCompatibleBitmap(pDC, rctClient.right, rctClient.bottom);
	pOldBitmap = memDC.SelectObject(&cMemBitmap);
	memDC.FillSolidRect(0, 0, rctClient.right, rctClient.bottom, pDC->GetBkColor());
	memDC.SetBkMode(TRANSPARENT);
	DrawAllInsideEdges(memDC);
	DrawAllOutsideEdges(memDC);
	DrawAllNodes(memDC);
	DrawMessageStratic(memDC);

	pDC->BitBlt(0, 0, rctClient.right, rctClient.bottom, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	cMemBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CChildView::CreateData()
{
	if (m_bIsRunning)
	{
		OnButtonRun();
	}

	if (m_pTestDataCreater)
	{
		delete m_pTestDataCreater;
	}
	m_pTestDataCreater = new CTestDataCreater();
	m_pGraphData = &m_pTestDataCreater->m_Graph;

	CRect crtClient;
	GetClientRect(&crtClient);
	CString strCount;
	m_pEditNodeCount->GetWindowTextW(strCount);
	
	int xMax = crtClient.right - m_nScreenLeft - m_nScreenRight;
	int yMax = crtClient.bottom - m_nScreenUp - m_nScreenDown;
	int nNodeCount = _ttoi(strCount.GetBuffer(0));
	if (nNodeCount == 0)
	{
		nNodeCount = 200;
	}
	int nEdgeCount = nNodeCount -1;
	if (nNodeCount <= 5)
	{
		nEdgeCount = nNodeCount * (nNodeCount - 1) / 2;
	}
	else
	{
		nEdgeCount = nNodeCount * 4;
	}
	m_fRadius = sqrt(0.05 * xMax * yMax / nNodeCount);
	if (m_fRadius > 15)
	{
		m_fRadius = 15;
	}

	m_pTestDataCreater->Init(nNodeCount, nEdgeCount, m_fRadius, xMax, yMax);
	SetGraphData(&m_pTestDataCreater->m_Graph);
	Invalidate(FALSE);
	m_pBtnRun->SetWindowTextW(_T("Run"));


	m_nMessageCount = 0;
	m_nMessageInOneIteration = 0;
	m_nIterationId = 0;
	m_nCityCount = nNodeCount;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	srand(time(0));
	int nButtonWidth = 80;
	int nButtonLeft = 5;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
	m_pBtnNext = new CButton();
	m_pBtnNext->Create(_T("NEXT"), dwStyle, CRect(nButtonLeft, 5, nButtonLeft + nButtonWidth, m_nScreenUp - 20), this, IDC_BTN_NEXT);
	nButtonLeft += nButtonWidth + 10;
	m_pBtnRun = new CButton();
	m_pBtnRun->Create(_T("Run"), dwStyle, CRect(nButtonLeft, 5, nButtonLeft + nButtonWidth, m_nScreenUp - 20), this, IDC_BTN_RUN);
	nButtonLeft += nButtonWidth + 10;
	m_pBtnCreate = new CButton();
	m_pBtnCreate->Create(_T("CREATE"), dwStyle, CRect(nButtonLeft, 5, nButtonLeft + nButtonWidth, m_nScreenUp - 20), this, IDC_BTN_CREATE);
	nButtonLeft += nButtonWidth + 10;
	m_pEditNodeCount = new CEdit();
	m_pEditNodeCount->Create(dwStyle, CRect(nButtonLeft, 5, nButtonLeft+100, m_nScreenUp - 20), this, IDC_EDIT_COUNT);

	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
	m_tt.AddTool(this, IDS_STRING_TIP);
	m_tt.SetMaxTipWidth(NULL);

	return 0;
}


BOOL CChildView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_tt.RelayEvent(pMsg);

	return CWnd::PreTranslateMessage(pMsg);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
// 	str.Format(_T("%d\n%d"), point.x, point.y);
// 	m_tt.UpdateTipText(str, this);
	for (int i = 0; i < m_pGraphData->m_nNodeCount; ++i)
	{
		CNodeInPaper * pNode = m_pGraphData->m_pNodes + i;
		double dx = point.x - m_nScreenLeft - pNode->GetX();
		double dy = point.y - m_nScreenUp - pNode->GetY();
		if (dx*dx + dy*dy <= m_fRadius*m_fRadius)
		{
			int nSuperId = i;
			for (int j = 0; j < pNode->m_pNodeData->m_nEdgeCount; ++j)
			{
				if (pNode->m_pNodeData->m_pEdges[j].relation == E_NODERELATION_CHILD)
				{
					CMegaNode * pSuper = m_pTestDataCreater->m_NodeTable.FromValueToNode(pNode->m_pNodeData->m_pEdges[j].value);
					nSuperId = pSuper - m_pTestDataCreater->m_NodeTable.m_pNodes;
				}
			}
			str.Format(_T("value:\t%.5f\nsuper:\t%.5f\nroot:\t%.5f\nlevel:\t%d"), pNode->m_pNodeData->m_fValue, m_pGraphData->m_pNodes[nSuperId].GetValue(), pNode->m_pNodeData->m_GroupInfo.pRoot->m_fValue, pNode->m_pNodeData->m_GroupInfo.level);
			m_tt.UpdateTipText(str, this);
			break;
		}
	}

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == RUN_TIMER_ID)
	{
		OnButtonNext();
	}

	CWnd::OnTimer(nIDEvent);
}
