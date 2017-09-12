#pragma once

class CNodeInPaper;
class CEdgeInPaper;

class CGraphInPaper
{
public:
	CGraphInPaper();
	~CGraphInPaper();
	void Init(int nMaxNodeCount, int nMaxEdgeCount, double fRadius, int nXSize, int nYSize);
	BOOL SetOneNode(int nX, int nY);
	BOOL SetOneEdge(CNodeInPaper * pN1, CNodeInPaper * pN2);
	int GetNodeIndex(CNodeInPaper * pNode);
	void UpdateAllEdges();

	int m_nNodeCount;
	int m_nEdgeCount;
	CNodeInPaper * m_pNodes;
	CEdgeInPaper * m_pEdges;

	friend class CTestDataCreater;
private:
	int m_nMaxNodeCount;
	int m_nMaxEdgeCount;
	double m_fRadius;
	int m_nXSize;
	int m_nYSize;
	int m_nXStart;
	int m_nYStart;
};

