#include "stdafx.h"
#include "EdgeInPaper.h"
#include "NodeInPaper.h"
#include "MegaNode.h"


CEdgeInPaper::CEdgeInPaper()
	:m_pNode1(NULL)
	,m_pNode2(NULL)
	,m_eRelation(E_NODERELATION_NONE)
	,m_eEdgeState(E_EDGESTATE_OUTSIDE)
{
}


CEdgeInPaper::~CEdgeInPaper()
{
}

void CEdgeInPaper::SetNodes(CNodeInPaper * pNode1, CNodeInPaper * pNode2)
{
	m_pNode1 = pNode1;
	m_pNode2 = pNode2;
	if (m_pNode1->m_pNodeData && m_pNode2->m_pNodeData)
	{
		CMegaNode * pNodeData1 = m_pNode1->m_pNodeData;
		for (int i = 0; i < pNodeData1->m_nEdgeCount; ++i)
		{
			if (pNodeData1->m_pEdges[i].value == m_pNode2->GetValue())
			{
				m_eEdgeState = pNodeData1->m_pEdges[i].edgeState;
				m_eRelation = pNodeData1->m_pEdges[i].relation;
				break;
			}
		}
	}
}

double CEdgeInPaper::GetDistance()
{
	if (m_pNode1 == NULL || m_pNode2 == NULL)
	{
		return DBL_MAX;
	}
	return m_pNode1->GetDistance(m_pNode2);
}

BOOL CEdgeInPaper::IsInsideEdge()
{
	return m_eEdgeState == E_EDGESTATE_INSIDE;
}

E_NODERELATION CEdgeInPaper::GetRelationByNode1()
{
	return m_eRelation;
}
