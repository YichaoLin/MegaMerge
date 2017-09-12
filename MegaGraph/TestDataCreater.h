#pragma once
#include "GraphInPaper.h"
#include "OriginalData.h"
#include "NodeTable.h"

class CNodeptrAndDistance
{
public:
	CNodeInPaper * m_pNode;
	double m_fDistance;
	bool m_bHaveConnected;

	CNodeptrAndDistance():m_pNode(NULL),m_fDistance(0), m_bHaveConnected(false){}
	bool operator < (const CNodeptrAndDistance & src) { return m_fDistance < src.m_fDistance; }
	bool operator > (const CNodeptrAndDistance & src) { return m_fDistance > src.m_fDistance; }
	bool operator <= (const CNodeptrAndDistance & src) { return m_fDistance <= src.m_fDistance; }
};

class CTestDataCreater
{
public:
	CTestDataCreater();
	~CTestDataCreater();

	BOOL Init(int nMaxNodeCount, int nMaxEdgeCount, double fRadius, int nXSize, int nYSize);
	BOOL InitAllNodes();
	void CalcuAllDistances();
	void OrderAllRows();
	void OrderOneRow(int nRowId);
	int AdjustArray(int nRowId, int l, int r);
	void QuickSort(int nRowId, int l, int r);
	void BuildConnectedTree(int nStartIndex, int nDegree, int nRandomRange);
	void BuildConnectedTreeOnOneNode(int nStartIndex, int nDegree, int nRandomRange, int * pRecord);
	static int GetRandomInOne(int * pSelectSet, int nLength, int nRange, int nTargetNum);
	void ConnectNodes(int nStartIndex, int nRandomRange);
	void AddExtraEdges(int nRange, double fProbability);
	BOOL IsAlreadyHaveOneEdge(const CNodeInPaper * N1, const CNodeInPaper * N2);
	void FromGraphToNodeTable();
	void ConnectGraphANdTable();
	CGraphInPaper m_Graph;
	CNodeTable m_NodeTable;

public:

	CNodeptrAndDistance ** m_ppNodeMatrix;
	double * m_pValues;
};

