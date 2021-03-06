
// ChildView.h : CChildView 类的接口
//


#pragma once
#include "TestDataCreater.h"

class CGraphInPaper;

#define IDC_BTN_NEXT 10000
#define IDC_BTN_RUN  10001
#define IDC_BTN_CREATE  10002
#define IDC_EDIT_COUNT 10003

#define RUN_TIMER_ID 900
#define RUN_TIME_INTER 1000

#define SUMMARY_X 400

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:
	void SetGraphData(CGraphInPaper * pGraphData);

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonRun();
	afx_msg void OnButtonCreate();
	DECLARE_MESSAGE_MAP()

	void OnNext(BOOL bRefresh);
	void GetBottomCoor(const POINT & p1, const POINT & p2, POINT & pL, POINT & pR, double fRadius) const;
	POINT GetHalfCoor(const POINT & p1, const POINT & p2, double fRate);
	void DrawTriangle(CDC & dc, COLORREF crBoundary, COLORREF crInside, const POINT & pntTop, const POINT & pntBottomCenter, double fRadius, double fBoundaryWidth);
	void DrawAllInsideEdges(CDC & dc);
	void DrawAllOutsideEdges(CDC & dc);
	void DrawAllNodes(CDC & dc);
	void DrawDashLine(CDC & dc, COLORREF crColor, const POINT & pntStart, const POINT & pntEnd, double fWidth);
	void DrawOneNode(CDC & dc, COLORREF crBoundary, COLORREF crInside, const POINT & pntCenter, double fRadius, double fBoundaryWidth);
	void DrawOneText(CDC & dc, COLORREF crText, const POINT & pntCenter, const CString & strValue);
	void DrawMessageStratic(CDC & dc);
	void MyOnPaint(CDC * pDC);
	void CreateData();
public:
	double m_fRadius;
	CGraphInPaper * m_pGraphData;

	CButton* m_pBtnNext;
	CButton* m_pBtnRun;
	CButton* m_pBtnCreate;
	CEdit * m_pEditNodeCount;

private:
	CTestDataCreater m_TestDataCreater;
	CTestDataCreater * m_pTestDataCreater;

	COLORREF m_crEdgeRelationFill;
	COLORREF m_crEdgeRelationBound;
	COLORREF m_crEdgeInsideFill;
	COLORREF m_crEdgeInsideBound;
	COLORREF m_crEdgeOutsideFill;
	COLORREF m_crEdgeOutsideBound;
	COLORREF m_crEdgeWishFill;
	COLORREF m_crEdgeWishBound;

	COLORREF m_crNodeCommonFill;
	COLORREF m_crNodeCommonBound;
	COLORREF m_crNodeChargeFill;
	COLORREF m_crNodeChargeBound;
	
	BOOL m_bButtonDown;
	int m_nPhase;
	CToolTipCtrl m_tt;
	BOOL m_bIsRunning;
	int m_nMessageCount;
	int m_nMessageInOneIteration;
	int m_nIterationId;
	int m_nCityCount;
	int m_nDebug[5];

	int m_nScreenUp;
	int m_nScreenDown;
	int m_nScreenLeft;
	int m_nScreenRight;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

