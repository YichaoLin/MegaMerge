#include "stdafx.h"
#include "NodeTable.h"
#include <iostream>
using namespace std;

CNodeTable::CNodeTable()
	: m_nNodeCount(0)
	, m_pNodes(NULL)
{
}


CNodeTable::~CNodeTable()
{
	if (m_pNodes)
	{
		delete[] m_pNodes;
		m_pNodes = NULL;
	}
	m_nNodeCount = 0;
}


void CNodeTable::Init(const COriginalData & od)
{
	m_nNodeCount = od.GetNodeCount();
	m_pNodes = new CMegaNode[m_nNodeCount];

	const double * pValues = od.GetValues();
	double ** pDistances = od.GetDistances();
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		m_pNodes[i].Init(pValues[i], m_nNodeCount, pDistances[i], pValues);
	}
}

void CNodeTable::Order()
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		m_pNodes[i].Bubble();
	}
}

void CNodeTable::Display()
{
	cout << "CNodeTable::Display" << endl;
	TRACE("\nCNodeTable::Display");
	for (int i = 0; i < m_nNodeCount; i++)
	{
		TRACE("\n");
		cout << endl;
		m_pNodes[i].Display();
	}
}

void CNodeTable::CleanReport()
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		m_pNodes[i].m_GroupInfo.pMinInside = NULL;
		m_pNodes[i].m_GroupInfo.pMinOutside = NULL;
		m_pNodes[i].m_GroupInfo.min_distance = DBL_MAX;
		m_pNodes[i].m_bGroupInfoInsideChanged = false;
		m_pNodes[i].m_pRootChangeMessageFrom = NULL;
	}
}

void CNodeTable::AllReport()
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		CNodeRelation * pShortest = m_pNodes[i].FindShortestOutside();
		if (pShortest && m_pNodes[i].m_GroupInfo.min_distance > pShortest->m_fDistance)
		{
			m_pNodes[i].m_GroupInfo.min_distance = pShortest->m_fDistance;
			m_pNodes[i].m_GroupInfo.pMinInside = m_pNodes + i;
			m_pNodes[i].m_GroupInfo.pMinOutside = FromValueToNode(pShortest->value);
			for (int j = 0; j < m_nNodeCount; j++)
			{
				if (m_pNodes[i].m_GroupInfo.pRoot == m_pNodes[j].m_GroupInfo.pRoot)
				{
					m_pNodes[j].m_GroupInfo = m_pNodes[i].m_GroupInfo;
					m_pNodes[j].m_bGroupInfoInsideChanged = true;
				}
			}
		}
	}
}

void CNodeTable::AllGroupSetChoosen()
{

}

void CNodeTable::AllMerge()
{

	for (int i = 0; i < m_nNodeCount; i++)
	{
		for (int j = i + 1; j < m_nNodeCount; j++)
		{
			if (IsChooseEachOther(m_pNodes + i, m_pNodes + j))
			{
				if (m_pNodes[i].m_GroupInfo.level == m_pNodes[j].m_GroupInfo.level)
				{
					change_root_friendlymerge(m_pNodes + i, m_pNodes + j);
				}
				else
				{
					MergeDifferentLevelGroup(m_pNodes + i, m_pNodes + j);
				}
			}
			else
			{
				;
			}
		}
	}
	SetInside();
}

void CNodeTable::SetInside()
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		for (int j = i + 1; j < m_nNodeCount; j++)
		{
			if (m_pNodes[i].m_GroupInfo.pRoot == m_pNodes[j].m_GroupInfo.pRoot)
			{
				for (int k = 0; k < m_pNodes[i].m_nEdgeCount; ++k)
				{
					if (m_pNodes[i].m_pEdges[k].value == m_pNodes[j].m_fValue)
					{
						m_pNodes[i].m_pEdges[k].edgeState = E_EDGESTATE_INSIDE;
					}
					else
					{
						int xx = 0;
					}
				}
				for (int k = 0; k < m_pNodes[j].m_nEdgeCount; ++k)
				{
					if (m_pNodes[j].m_pEdges[k].value == m_pNodes[i].m_fValue)
					{
						m_pNodes[j].m_pEdges[k].edgeState = E_EDGESTATE_INSIDE;
					}
					else
					{
						int yy = 0;
					}
				}
			}
			else
			{
				int zz = 0;
			}
		}
	}
}

bool CNodeTable::IsChooseEachOther(CMegaNode * Node1, CMegaNode * Node2)
{
	if (Node1->m_GroupInfo.pMinOutside != Node2)
	{
		return false;
	}
	if (Node2->m_GroupInfo.pMinOutside != Node1)
	{
		return false;
	}
	return true;
}

int CNodeTable::judge()
{
	int nJudge = 1;
	for (int i = 0; i < m_nNodeCount; i++)
	{
		for (int j = i + 1; j < m_nNodeCount; j++)
		{
			if (m_pNodes[i].m_GroupInfo.pRoot != m_pNodes[j].m_GroupInfo.pRoot)
			{
				nJudge = 0;
				break;
			}
		}
		if (nJudge == 0)
			break;
	}
	return nJudge;
}

// set_relationship(new_root_value, value, root1, root2, a, true);//value点需要以newrootvalue为父亲
void CNodeTable::set_relationship(CMegaNode * pRoot, CMegaNode * pFather, CMegaNode * pEveryBegining)
{
	if (pFather)
	{
		CString strOut;
		strOut.Format(_T("\nSR_F: %f  %f  %f  %f"), pRoot->m_fValue, pFather->m_fValue, pRoot->m_GroupInfo.pRoot->m_fValue, pFather->m_GroupInfo.pRoot->m_fValue);
		//OutputDebugString(strOut);
		SetRelation(pFather, pRoot, E_EDGESTATE_INSIDE);
		//if (pRoot->m_GroupInfo.pRoot != pFather->m_GroupInfo.pRoot && pEveryBegining != pRoot)
		if (pEveryBegining != pRoot)
		{
			pRoot->m_pRootChangeMessageFrom = pEveryBegining;
			//OutputDebugString(_T("  YES"));
		}
		pRoot->m_GroupInfo = pFather->m_GroupInfo;
	}
	else
	{
		CString strOut;
		strOut.Format(_T("\nSR_NF: %f  %f "), pRoot->m_fValue, pRoot->m_GroupInfo.pRoot->m_fValue);
		//OutputDebugString(strOut);
		if (pRoot->m_GroupInfo.pRoot != pRoot && pEveryBegining != pRoot)
		{
			//OutputDebugString(_T("  YES"));
			pRoot->m_pRootChangeMessageFrom = pEveryBegining;
		}
		pRoot->m_GroupInfo.pRoot = pRoot;
	}
	for (int i = 0; i < pRoot->m_nEdgeCount; ++i)
	{
		CMegaNode * pTmp = FromValueToNode(pRoot->m_pEdges[i].value);
		if (pTmp == pFather)
		{
			continue;
		}
		if (pRoot->m_pEdges[i].relation == E_NODERELATION_CHILD || pRoot->m_pEdges[i].relation == E_NODERELATION_FATHER)
		{
			set_relationship(pTmp, pRoot, pEveryBegining);
		}
	}
}

void CNodeTable::change_root_friendlymerge(CMegaNode * pA, CMegaNode * pB)
{
	CMegaNode * pNewRoot = pA->m_fValue < pB->m_fValue ? pA : pB;
	CMegaNode * pAnother = pA->m_fValue > pB->m_fValue ? pA : pB;
	int nNewLevel = pNewRoot->m_GroupInfo.level + 1;

	set_relationship(pNewRoot, NULL, pNewRoot);//value点需要以newrootvalue为父亲
	set_relationship(pAnother, pNewRoot, pAnother);//value点不需要以newrootvalue为父亲

	SetLevel(pNewRoot, nNewLevel);
}

void CNodeTable::SetRelation(CMegaNode * pFather, CMegaNode * pChild, E_EDGESTATE eState)
{
	for (int i = 0; i < pFather->m_nEdgeCount; ++i)
	{
		if (pFather->m_pEdges[i].value == pChild->m_fValue)
		{
			pFather->m_pEdges[i].relation = E_NODERELATION_FATHER;
			pFather->m_pEdges[i].edgeState = eState;
		}
	}
	for (int i = 0; i < pChild->m_nEdgeCount; ++i)
	{
		if (pChild->m_pEdges[i].value == pFather->m_fValue)
		{
			pChild->m_pEdges[i].relation = E_NODERELATION_CHILD;
			pChild->m_pEdges[i].edgeState = eState;
		}
	}
}

CMegaNode * CNodeTable::MergeDifferentLevelGroup(CMegaNode * Node1, CMegaNode * Node2)
{
	CMegaNode * pNewRoot = Node1->m_GroupInfo.level > Node2->m_GroupInfo.level ? Node1 : Node2;
	CMegaNode * pAnother = Node1->m_GroupInfo.level < Node2->m_GroupInfo.level ? Node1 : Node2;
	set_relationship(pAnother, pNewRoot, pAnother);
	return NULL;
}

CMegaNode * CNodeTable::FromValueToNode(double fValue)
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		if (m_pNodes[i].m_fValue == fValue)
		{
			return m_pNodes + i;
		}
	}
	return NULL;
}

void CNodeTable::SetLevel(CMegaNode * pRoot, int nLevel)
{
	for (int i = 0; i < m_nNodeCount; i++)
	{
		if (m_pNodes[i].m_GroupInfo.pRoot == pRoot)
		{
			m_pNodes[i].m_GroupInfo.level = nLevel;
		}
	}
}

void CNodeTable::ShowTree(ofstream & fout)
{
	bool bIsFirst = true;
	for (int i = 0; i < m_nNodeCount; i++)
	{
		CMegaNode * pFather = m_pNodes + i;
		bool bIsFather = true;
		for (int i = 0; i < pFather->m_nEdgeCount; ++i)
		{
			if (pFather->m_pEdges[i].relation == E_NODERELATION_CHILD)
			{
				bIsFather = false;
				break;
			}
		}
		if (bIsFather)
		{
			ShowTreeRecursion(fout, pFather, 0, bIsFirst);
			bIsFirst = false;
		}
	}
}

#define ourout cout

void CNodeTable::ShowTreeRecursion(ofstream & fout, CMegaNode * pFather, int nLevel, bool bIsFirst)
{
	if (bIsFirst)
	{
		ourout << "-----\t";
	}
	else
	{
		ourout << endl;
		for (int i = 0; i < nLevel; ++i)
		{
			ourout << "\t";
		}
		ourout << "|----\t";
	}
	ourout << pFather->m_fValue;
	bool bFirstChild = true;
	for (int i = 0; i < pFather->m_nEdgeCount; ++i)
	{
		if (pFather->m_pEdges[i].relation == E_NODERELATION_FATHER)
		{
			CMegaNode * pChild = FromValueToNode(pFather->m_pEdges[i].value);
			ShowTreeRecursion(fout, pChild, nLevel + 1, bFirstChild);
			bFirstChild = false;
		}
	}

}

int CNodeTable::GetLevelDiffToRoot(CMegaNode * pNode)
{
	return GetLevelDiffToAnother(pNode, pNode->m_GroupInfo.pRoot);
}

int CNodeTable::GetLevelDiffToAnother(CMegaNode * pNode, CMegaNode * pAnother)
{
	if (pNode == pAnother)
	{
		return 0;
	}
	CMegaNode * pSuper = GetSuperNode(pNode);
	if (pSuper == pAnother)
	{
		return 1;
	}
	else if (pSuper == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + GetLevelDiffToRoot(pSuper);
	}
}

CMegaNode * CNodeTable::GetSuperNode(CMegaNode * pNode)
{
	CMegaNode * pSuperNode = NULL;
	for (int i = 0; i < pNode->m_nEdgeCount; ++i)
	{
		if (pNode->m_pEdges[i].relation == E_NODERELATION_CHILD)
		{
			pSuperNode = FromValueToNode(pNode->m_pEdges[i].value);
			break;
		}
	}
	return pSuperNode;
}

int CNodeTable::GetUpMessageCountThisIteration()
{
	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; i++)
	{
		if (m_pNodes[i].m_bGroupInfoInsideChanged == true)
		{
			int nRouteLength = GetLevelDiffToRoot(m_pNodes + i);
			nRet += nRouteLength;
		}
	}
	return nRet;
}

int CNodeTable::GetDownMessageCountThisIteration()
{
	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; i++)
	{
		if (m_pNodes[i].m_bGroupInfoInsideChanged == true && m_pNodes[i].m_GroupInfo.pMinInside == m_pNodes + i)
		{
			int nRouteLength = GetLevelDiffToRoot(m_pNodes + i);
			nRet += nRouteLength;
		}
	}
	return nRet;
}

int CNodeTable::GetMessageCountThisIteration()
{
	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; i++)
	{
		if (m_pNodes[i].m_bGroupInfoInsideChanged == true && IsNodeHaveReport(m_pNodes+i))
		{
			CString strOut;
			strOut.Format(_T("\nGetMessageCountThisIteration %f "), m_pNodes[i].m_fValue);
			//OutputDebugString(strOut);
			int nRouteLength = GetLevelDiffToRoot(m_pNodes + i);
			strOut.Format(_T("\nGetMessageCountThisIteration Leng %d "), nRouteLength);
			//OutputDebugString(strOut);
			if (m_pNodes[i].m_GroupInfo.pMinInside == m_pNodes + i)
			{
				strOut.Format(_T("\nGetMessageCountThisIteration %f double "), m_pNodes[i].m_fValue);
				//OutputDebugString(strOut);
				nRouteLength *= 2;
			}
			nRet += nRouteLength;
		}
	}
	return nRet;
}

int CNodeTable::GetNotifyMessageCount()
{
	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		if (m_pNodes[i].m_pRootChangeMessageFrom)
		{
			nRet++;
		}
	}
	return nRet;
}

int CNodeTable::GetConnectMessageCount()
{
	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		if (m_pNodes[i].m_GroupInfo.pMinInside == m_pNodes + i)
		{
			nRet++;
		}
	}
	return nRet;
}

int CNodeTable::GetCityCount()
{

	int nRet = 0;
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		if (m_pNodes[i].m_GroupInfo.pRoot == m_pNodes + i)
		{
			nRet++;
		}
	}
	return nRet;
}

bool CNodeTable::IsNodeHaveReport(CMegaNode* pNode)
{
	for (int i = 0; i < pNode->m_nEdgeCount; ++i)
	{
		if (pNode->m_pEdges[i].edgeState == E_EDGESTATE_OUTSIDE)
		{
			CMegaNode * pNode22 = FromValueToNode(pNode->m_pEdges[i].value);
			CString strOut;
			strOut.Format(_T("\nReport %f  %f"), pNode->m_fValue, pNode22->m_fValue);
			//OutputDebugString(strOut);
			return true;
		}
	}
	return false;
}
