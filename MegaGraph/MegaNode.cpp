#include "stdafx.h"
#include "MegaNode.h"
#include <iostream>
using namespace std;

/*
double root;
int level;
double min_distance;
double value_min;
double value_min_connected;
*/
CMegaNode::CMegaNode()
	: m_pEdges(NULL)
	, m_nEdgeCount(0)
	, m_fValue(NODE_VALUE_ILLEGAL)
{
	m_GroupInfo.pRoot = this;
	m_GroupInfo.level = 0;
	m_GroupInfo.min_distance = DBL_MAX;
	m_GroupInfo.pMinInside = this;
	m_GroupInfo.pMinOutside = NULL;
}


CMegaNode::~CMegaNode()
{
	if (m_pEdges)
	{
		delete[] m_pEdges;
		m_pEdges = NULL;
	}
	m_nEdgeCount = 0;
}

void CMegaNode::Init(double fValue, int nEdgeCount, const double * pEdgeValues, const double * pNodeValues)
{
	m_fValue = fValue;
	int nActualEdgeCount = 0;
	for (int i = 0; i < nEdgeCount; ++i)
	{
		if (pEdgeValues[i] > 0)
		{
			nActualEdgeCount++;
		}
	}
	if (nActualEdgeCount > 0)
	{
		m_nEdgeCount = nActualEdgeCount;
		m_pEdges = new CNodeRelation[nActualEdgeCount];
	}
	int nIndex = 0;
	for (int i = 0; i < nEdgeCount; ++i)
	{
		if (pEdgeValues)
		{
			if (pEdgeValues[i] > 0)
			{
				m_pEdges[nIndex].m_fDistance = pEdgeValues[i];
				m_pEdges[nIndex].value = pNodeValues[i];
				++nIndex;
			}

		}
	}
}

void CMegaNode::Bubble()
{
	CNodeRelation temp;
	for (int i = 0; i < m_nEdgeCount; i++)
	{
		for (int j = 0; j < m_nEdgeCount - i - 1; j++)
		{
			if (m_pEdges[j].m_fDistance > m_pEdges[j + 1].m_fDistance)
			{
				temp = m_pEdges[j];
				m_pEdges[j] = m_pEdges[j + 1];
				m_pEdges[j + 1] = temp;
			}
		}
	}
}

void CMegaNode::Display()
{
	cout << m_fValue << "\tval";
	TRACE("%.3f\tval", m_fValue);
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		cout << "\t" << m_pEdges[i].value;
		TRACE("\t%.3f", m_pEdges[i].value);
	}
	cout << endl << "\tdis";
	TRACE("\tdis");
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		cout << "\t" << m_pEdges[i].m_fDistance;
		TRACE("\t%.3f", m_pEdges[i].m_fDistance);
	}
	cout << endl << "\trel";
	TRACE("\trel");
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		cout << "\t" << m_pEdges[i].relation;
		TRACE("\t%d", m_pEdges[i].relation);
	}
	cout << endl << "\tinout";
	TRACE("\tinout");
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		cout << "\t" << m_pEdges[i].edgeState;
		TRACE("\t%d", m_pEdges[i].edgeState);
	}
	cout << endl << "\t";
	TRACE("\n\t");
	cout << "\tL " << m_GroupInfo.level;
	TRACE("\tL%d", m_GroupInfo.level);
	cout << "\tD " << m_GroupInfo.min_distance;
	TRACE("\tD%.3f", m_GroupInfo.min_distance);
	if (m_GroupInfo.pMinInside)
	{
		cout << "\tI " << m_GroupInfo.pMinInside->m_fValue;
		TRACE("\tI %.3f", m_GroupInfo.pMinInside->m_fValue);
	}
	if (m_GroupInfo.pMinOutside)
	{
		cout << "\tO " << m_GroupInfo.pMinOutside->m_fValue;
		TRACE("\tO %.3f", m_GroupInfo.pMinOutside->m_fValue);
	}
	if (m_GroupInfo.pRoot)
	{
		cout << "\tR " << m_GroupInfo.pRoot->m_fValue;
		TRACE("\tR %.3f", m_GroupInfo.pRoot->m_fValue);
	}
}

CNodeRelation * CMegaNode::FindShortestOutside()
{
	for (int i = 0; i < m_nEdgeCount; ++i)
	{
		if (m_pEdges[i].edgeState == E_EDGESTATE_OUTSIDE)
		{
			return m_pEdges + i;
		}
	}
	return NULL;
}
