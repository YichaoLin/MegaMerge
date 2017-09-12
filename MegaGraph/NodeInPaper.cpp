#include "stdafx.h"
#include "NodeInPaper.h"
#include "MegaNode.h"


CNodeInPaper::CNodeInPaper()
	: m_nX(0)
	, m_nY(0)
	, m_pNodeData(NULL)
{
}


CNodeInPaper::CNodeInPaper(int nX, int nY)
	: m_pNodeData(NULL)
{
	SetValue(nX, nY);
}

CNodeInPaper::CNodeInPaper(CMegaNode * pNodeData)
	: m_nX(0)
	, m_nY(0)
{
	SetValue(pNodeData);
}

CNodeInPaper::~CNodeInPaper()
{
}

double CNodeInPaper::GetDistance(const CNodeInPaper * pAnother) const
{
	if (pAnother == NULL)
	{
		return DBL_MAX;
	}
	if (this == pAnother)
	{
		return 0.0;
	}

	double fDiffX = m_nX - pAnother->m_nX;
	double fDiffY = m_nY - pAnother->m_nY;
	double fRet = sqrt(fDiffX*fDiffX + fDiffY*fDiffY);
	return fRet;
}

void CNodeInPaper::SetValue(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
}

void CNodeInPaper::SetValue(CMegaNode * pNodeData)
{
	m_pNodeData = pNodeData;
}

double CNodeInPaper::GetValue()
{
	if (m_pNodeData)
	{
		return m_pNodeData->m_fValue;
	}
	else
	{
		return NODE_VALUE_ILLEGAL;
	}
}
