#pragma once
#include "NodeRelation.h"

class CNodeInPaper;

class CEdgeInPaper
{
public:
	CEdgeInPaper();
	~CEdgeInPaper();
	void SetNodes(CNodeInPaper * pNode1, CNodeInPaper * pNode2);
	double GetDistance();

	CNodeInPaper * m_pNode1;
	CNodeInPaper * m_pNode2;

	BOOL IsInsideEdge();
	E_NODERELATION GetRelationByNode1();

public:
	E_NODERELATION m_eRelation;
	E_EDGESTATE m_eEdgeState;
};

