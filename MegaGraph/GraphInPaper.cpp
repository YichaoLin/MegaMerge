#include "stdafx.h"
#include "GraphInPaper.h"
#include "NodeInPaper.h"
#include "EdgeInPaper.h"


CGraphInPaper::CGraphInPaper()
	:m_nNodeCount(0)
	, m_nEdgeCount(0)
	, m_pNodes(NULL)
	, m_pEdges(NULL)
	, m_nMaxNodeCount(0)
	, m_nMaxEdgeCount(0)
	, m_nXStart(0)
	, m_nYStart(0)
{
}


CGraphInPaper::~CGraphInPaper()
{
}

void CGraphInPaper::Init(
	int nMaxNodeCount, int nMaxEdgeCount, 
	double fRadius, 
	int nXSize, int nYSize)
{
	m_nMaxNodeCount = nMaxNodeCount;
	m_nMaxEdgeCount = nMaxEdgeCount;
	m_pNodes = new CNodeInPaper[nMaxNodeCount];
	m_pEdges = new CEdgeInPaper[nMaxEdgeCount];
	m_fRadius = fRadius;
	m_nXSize = nXSize;
	m_nYSize = nYSize;
}

BOOL CGraphInPaper::SetOneNode(int nX, int nY)
{
	if (m_nNodeCount >= m_nMaxNodeCount)
	{
		return FALSE;
	}
	if (nX - m_fRadius < 0 || nX + m_fRadius > m_nXSize)
	{
		return FALSE;
	}
	if (nY - m_fRadius < 0 || nY + m_fRadius > m_nYSize)
	{
		return FALSE;
	}
	CNodeInPaper tmpNode(nX, nY);
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		double fDistance = tmpNode.GetDistance(m_pNodes + i);
		if (m_fRadius*3 > fDistance)
		{
			return FALSE;
		}
	}
	m_pNodes[m_nNodeCount++] = tmpNode;
	return TRUE;
}

BOOL CGraphInPaper::SetOneEdge(CNodeInPaper * pN1, CNodeInPaper * pN2)
{
	if (m_nEdgeCount >= m_nMaxEdgeCount)
	{
		return FALSE;
	}
	m_pEdges[m_nEdgeCount++].SetNodes(pN1, pN2);
	return TRUE;
}

int CGraphInPaper::GetNodeIndex(CNodeInPaper * pNode)
{
	return pNode - m_pNodes;
}

void CGraphInPaper::UpdateAllEdges()
{
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		m_pEdges[i].SetNodes(m_pEdges[i].m_pNode1, m_pEdges[i].m_pNode2);
	}
}

