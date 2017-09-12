#include "stdafx.h"
#include "TestDataCreater.h"
#include "GraphInPaper.h"
#include "NodeInPaper.h"
#include "EdgeInPaper.h"


CTestDataCreater::CTestDataCreater()
	:m_pValues(NULL)
	, m_ppNodeMatrix(NULL)
{
}


CTestDataCreater::~CTestDataCreater()
{
	if (m_ppNodeMatrix)
	{
		for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
		{
			delete[] m_ppNodeMatrix[i];
		}
		delete[] m_ppNodeMatrix;
		m_ppNodeMatrix = NULL;
	}
}

BOOL CTestDataCreater::Init(int nMaxNodeCount, int nMaxEdgeCount, double fRadius, int nXSize, int nYSize)
{
	if (nMaxEdgeCount < nMaxNodeCount - 1)
	{
		return FALSE;
	}
	m_Graph.Init(nMaxNodeCount, nMaxEdgeCount, fRadius, nXSize, nYSize);
	m_ppNodeMatrix = new CNodeptrAndDistance *[nMaxNodeCount];
	for (int i = 0; i < nMaxNodeCount; ++i)
	{
		m_ppNodeMatrix[i] = new CNodeptrAndDistance [nMaxNodeCount];
	}
	InitAllNodes();
	CalcuAllDistances();
	OrderAllRows();
	//BuildConnectedTree(0, 2, 3);
	ConnectNodes(0, 2);
	AddExtraEdges(4, 1);
	FromGraphToNodeTable();
	ConnectGraphANdTable();
}

BOOL CTestDataCreater::InitAllNodes()
{
	int nEnableNodeCount = 0;
	double * pValues = new double[m_Graph.m_nMaxNodeCount];
	while (nEnableNodeCount < m_Graph.m_nMaxNodeCount)
	{
		double tmpValue = 0.0;
		BOOL bValueExist = FALSE;
		do 
		{
			bValueExist = FALSE;
			tmpValue = (rand() % 10000) / 1000.0;
			for (int i = 0; i < nEnableNodeCount; ++i)
			{
				if (pValues[i] == tmpValue)
				{
					bValueExist = TRUE;
					break;
				}
			}
		} while (bValueExist == TRUE);
		int x = rand() % m_Graph.m_nXSize + m_Graph.m_nXStart;
		int y = rand() % m_Graph.m_nYSize + m_Graph.m_nYStart;
		if (TRUE == m_Graph.SetOneNode(x, y))
		{
			pValues[nEnableNodeCount++] = tmpValue;
		}
	}
	m_pValues = pValues;
	return TRUE;
}

void CTestDataCreater::CalcuAllDistances()
{
	for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
	{
		for (int j = 0; j < m_Graph.m_nNodeCount; ++j)
		{
			m_ppNodeMatrix[i][j].m_fDistance = m_Graph.m_pNodes[i].GetDistance(m_Graph.m_pNodes + j);
			m_ppNodeMatrix[i][j].m_pNode = m_Graph.m_pNodes + j;
		}
	}
}

void CTestDataCreater::OrderAllRows()
{
	for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
	{
		//OrderOneRow(i);
		QuickSort(i, 0, m_Graph.m_nMaxNodeCount - 1);
	}
}

void CTestDataCreater::OrderOneRow(int nRowId)
{
	CNodeptrAndDistance tmp;
	for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
	{
		for (int j = 0; j < m_Graph.m_nMaxNodeCount - i - 1; ++j)
		{
			int a = m_Graph.GetNodeIndex(m_ppNodeMatrix[nRowId][j + 1].m_pNode);
			int b = m_Graph.GetNodeIndex(m_ppNodeMatrix[nRowId][j].m_pNode);
			if (m_ppNodeMatrix[nRowId][j + 1] < m_ppNodeMatrix[nRowId][j])
			{
				tmp = m_ppNodeMatrix[nRowId][j + 1];
				m_ppNodeMatrix[nRowId][j + 1] = m_ppNodeMatrix[nRowId][j];
				m_ppNodeMatrix[nRowId][j] = tmp;
			}
		}
	}
	for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
	{
		int a = m_Graph.GetNodeIndex(m_ppNodeMatrix[nRowId][i].m_pNode);
		double fx = m_ppNodeMatrix[nRowId][i].m_fDistance;
		int b = 0;
	}
}

int CTestDataCreater::AdjustArray(int nRowId, int l, int r)
{
	CNodeptrAndDistance * pNodeMatrix = m_ppNodeMatrix[nRowId];
	CNodeptrAndDistance firstdata = pNodeMatrix[l];
	int i = l, j = r;
	while (i < j)
	{
		while (i < j && firstdata <= pNodeMatrix[j])
		{
			--j;
		}
		if (i < j)
		{
			pNodeMatrix[i] = pNodeMatrix[j];
			++i;
		}

		while (i < j && firstdata > pNodeMatrix[i])
		{
			++i;
		}
		if (i < j)
		{
			pNodeMatrix[j] = pNodeMatrix[i];
			--j;
		}
	}
	pNodeMatrix[i] = firstdata;
	return i;
}

void CTestDataCreater::QuickSort(int nRowId, int l, int r)
{
	if (l < r)
	{
		int i = AdjustArray(nRowId, l, r);
		QuickSort(nRowId, l, i - 1);
		QuickSort(nRowId, i + 1, r);
	}
}

void CTestDataCreater::BuildConnectedTree(int nStartIndex, int nDegree, int nRandomRange)
{
	int * pLocalRecord = new int[m_Graph.m_nMaxNodeCount];
	memset(pLocalRecord, 0, sizeof(int)*m_Graph.m_nMaxNodeCount);
	int * pSelected = new int[m_Graph.m_nMaxNodeCount];
	memset(pSelected, 0, sizeof(int)*m_Graph.m_nMaxNodeCount);

	int * pLocalRecordBackup = new int[m_Graph.m_nMaxNodeCount];
	memset(pLocalRecordBackup, 0, sizeof(int)*m_Graph.m_nMaxNodeCount);

	pLocalRecord[nStartIndex] = 1;

	BOOL bNeedContinue;
	do 
	{
		bNeedContinue = FALSE;
		for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
		{
			if (pLocalRecord[i] != pLocalRecordBackup[i])
			{
				bNeedContinue = TRUE;
				pSelected[i] = 1;
			}
			else
			{
				pSelected[i] = 0;
			}
		}
		if (bNeedContinue == FALSE)
		{
			break;
		}
		memcpy(pLocalRecordBackup, pLocalRecord, sizeof(int)*m_Graph.m_nMaxNodeCount);
		for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
		{
			if (pSelected[i] == 1)
			{
				BuildConnectedTreeOnOneNode(i, nDegree, nRandomRange, pLocalRecord);
			}
		}
	} while (bNeedContinue);

	delete[] pLocalRecord;
	delete[] pSelected;
}

void CTestDataCreater::BuildConnectedTreeOnOneNode(int nRecentNodeIndex, int nDegree, int nRandomRange, int * pRecord)
{
	int * pLocalRecord = new int[m_Graph.m_nMaxNodeCount];
	memset(pLocalRecord, 0, sizeof(int)*m_Graph.m_nMaxNodeCount);

	for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
	{
		int nTestIndex = m_ppNodeMatrix[nRecentNodeIndex][i].m_pNode - m_Graph.m_pNodes;
		if (pRecord[nTestIndex] == 1)
		{
			pLocalRecord[i] = 1;
		}
	}

	int * pLocalRecordBackup = new int[m_Graph.m_nMaxNodeCount];
	memcpy(pLocalRecordBackup, pLocalRecord, sizeof(int) * m_Graph.m_nMaxNodeCount);

	if (nDegree >= m_Graph.m_nMaxNodeCount)
	{
		nDegree = m_Graph.m_nMaxNodeCount;
	}
	if (nRandomRange < nDegree)
	{
		nRandomRange = nDegree;
	}
	int nEndIndex = 0;
	int nZeroCount = 0;
	while (nZeroCount < nRandomRange && nEndIndex < m_Graph.m_nMaxNodeCount)
	{
		if (pLocalRecord[nEndIndex++] == 0)
		{
			nZeroCount++;
		}
	}
	if (nZeroCount == 0)
	{
		return;
	}

	int nGetCount = 0;
	int nIndex = 0;
	while (nGetCount < nDegree && nGetCount < nZeroCount)
	{
		int nStepCount = 0;
		int nTmp = rand() % nRandomRange + 1;
		while (nStepCount < nTmp)
		{
			nIndex++;
			nIndex = nIndex % nEndIndex;
			if (pLocalRecord[nIndex] == 0)
			{
				nStepCount++;
			}
		}
		int xx = m_ppNodeMatrix[nRecentNodeIndex][nIndex].m_pNode - m_Graph.m_pNodes;
		m_Graph.SetOneEdge(m_Graph.m_pNodes + nRecentNodeIndex, m_ppNodeMatrix[nRecentNodeIndex][nIndex].m_pNode);
		pLocalRecord[nIndex] = 1;
		nGetCount++;
	}

	for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
	{
		if (pLocalRecord[i] == pLocalRecordBackup[i])
		{
			continue;
		}
		int nTestIndex = m_ppNodeMatrix[nRecentNodeIndex][i].m_pNode - m_Graph.m_pNodes;
		pRecord[nTestIndex] = 1;
	}
	delete[] pLocalRecord;
	delete[] pLocalRecordBackup;
}

int CTestDataCreater::GetRandomInOne(int * pSelectSet, int nLength, int nRange, int nTargetNum)
{
	int nEndIndex = 0;
	int nLegalCount = 0;
	for (nEndIndex = 0; nEndIndex < nLength;)
	{
		if (pSelectSet[nEndIndex++] == nTargetNum)
		{
			nLegalCount++;
			if (nLegalCount >= nRange)
			{
				break;
			}
		}
	}
	int nBlank = rand() % nLegalCount + 1;
	int nStep = 0;
	int nRet = -1;
	do 
	{
		++nRet;
		if (pSelectSet[nRet] == nTargetNum)
		{
			nStep++;
		}
	} while (nStep < nBlank);
	return nRet;
}

void CTestDataCreater::ConnectNodes(int nStartIndex, int nRandomRange)
{
	int * pConnectedSet = new int[m_Graph.m_nNodeCount];
	memset(pConnectedSet, 0, sizeof(int)*m_Graph.m_nNodeCount);
	int * pSelectSet = new int[m_Graph.m_nNodeCount];
	pConnectedSet[nStartIndex] = 1;
	for (int i = 1; i < m_Graph.m_nNodeCount; ++i)
	{
		int nOutsideIndex = m_ppNodeMatrix[nStartIndex][i].m_pNode - m_Graph.m_pNodes;
		memset(pSelectSet, 0, sizeof(int)*m_Graph.m_nNodeCount);
		int nSelectCount = 0;
		int nIndex = 1;
		m_ppNodeMatrix[nOutsideIndex][0].m_bHaveConnected = true;
		while (nSelectCount < nRandomRange && nIndex < m_Graph.m_nNodeCount)
		{
			int nTestIndex = m_ppNodeMatrix[nOutsideIndex][nIndex].m_pNode - m_Graph.m_pNodes;
			if (pConnectedSet[nTestIndex] == 1)
			{
				pSelectSet[nIndex] = 1;
				nSelectCount++;
				if (nSelectCount >= nRandomRange)
				{
					break;
				}
			}
			else
			{
				pSelectSet[nIndex] = 0;
			}
			++nIndex;
		}
		int nFatherIndex = GetRandomInOne(pSelectSet, nIndex, nRandomRange, 1);
		int aa = m_ppNodeMatrix[nStartIndex][i].m_pNode - m_Graph.m_pNodes;
		int nAnotherIndex = m_ppNodeMatrix[nOutsideIndex][nFatherIndex].m_pNode - m_Graph.m_pNodes;
		m_Graph.SetOneEdge(m_ppNodeMatrix[nStartIndex][i].m_pNode, m_ppNodeMatrix[nOutsideIndex][nFatherIndex].m_pNode);
		bool bx = m_ppNodeMatrix[0][2].m_bHaveConnected;
		if (bx == true)
		{
			bx = bx;
		}
		if (nOutsideIndex == 0 && nFatherIndex == 2)
		{
			nFatherIndex = nFatherIndex;
		}
		m_ppNodeMatrix[nOutsideIndex][nFatherIndex].m_bHaveConnected = true;
		for (int j = 0; j < m_Graph.m_nNodeCount; ++j)
		{
			if (m_ppNodeMatrix[nAnotherIndex][j].m_pNode - m_Graph.m_pNodes == nOutsideIndex)
			{
				if (nAnotherIndex == 0 && j == 2)
				{
					j = j;
				}
				m_ppNodeMatrix[nAnotherIndex][j].m_bHaveConnected = true;
			}
		}
		pConnectedSet[nOutsideIndex] = 1;
	}
}

void CTestDataCreater::AddExtraEdges(int nRange, double fProbability)
{
	while (m_Graph.m_nEdgeCount < m_Graph.m_nMaxEdgeCount)
	{
		for (int j = 1; j < m_Graph.m_nNodeCount; ++j)
		{
			for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
			{
				int xxx = m_Graph.GetNodeIndex(m_ppNodeMatrix[i][j].m_pNode);
				if (m_ppNodeMatrix[i][j].m_bHaveConnected)
				{
					continue;
				}
				int nRandNum = rand() % (m_Graph.m_nNodeCount + 1);
				if (((double)nRandNum) / m_Graph.m_nNodeCount < j * 0.3 / m_Graph.m_nNodeCount)
				{
					continue;
				}

				int nAnotherIndex = m_ppNodeMatrix[i][j].m_pNode - m_Graph.m_pNodes;
				CNodeInPaper * m_pAnotherNode = m_ppNodeMatrix[i][j].m_pNode;

				m_Graph.SetOneEdge(m_Graph.m_pNodes + i, m_pAnotherNode);
				m_ppNodeMatrix[i][j].m_bHaveConnected = true;
				for (int k = 0; k < m_Graph.m_nNodeCount; ++k)
				{
					if (m_ppNodeMatrix[nAnotherIndex][k].m_pNode == m_pAnotherNode)
					{
						m_ppNodeMatrix[nAnotherIndex][k].m_bHaveConnected = true;
						break;
					}
				}
				if (m_Graph.m_nEdgeCount >= m_Graph.m_nMaxEdgeCount)
				{
					return;
				}
			}
		}
	}
}

BOOL CTestDataCreater::IsAlreadyHaveOneEdge(const CNodeInPaper * N1, const CNodeInPaper * N2)
{
	for (int i = 0; i < m_Graph.m_nEdgeCount; ++i)
	{
		if (m_Graph.m_pEdges[i].m_pNode1 == N1 && m_Graph.m_pEdges[i].m_pNode2 == N2)
		{
			return TRUE;
		}
		if (m_Graph.m_pEdges[i].m_pNode2 == N1 && m_Graph.m_pEdges[i].m_pNode1 == N2)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CTestDataCreater::FromGraphToNodeTable()
{
	double * pValues = new double[m_Graph.m_nNodeCount];
	double ** ppDistances = new double * [m_Graph.m_nNodeCount];
	for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
	{
		ppDistances[i] = new double[m_Graph.m_nNodeCount];
	}

	for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
	{
		pValues[i] = m_pValues[i];
	}

	for (int i = 0; i < m_Graph.m_nNodeCount; ++i)
	{
		for (int j = 0; j < m_Graph.m_nNodeCount; ++j)
		{
			if (i == j)
			{
				ppDistances[i][j] = 0.0;
			}
			else
			{
				ppDistances[i][j] = -1.0;
			}
		}
	}

	for (int i = 0; i < m_Graph.m_nEdgeCount; ++i)
	{
		int nIndex1 = m_Graph.m_pEdges[i].m_pNode1 - m_Graph.m_pNodes;
		int nIndex2 = m_Graph.m_pEdges[i].m_pNode2 - m_Graph.m_pNodes;
		double fDistance = m_Graph.m_pEdges[i].m_pNode1->GetDistance(m_Graph.m_pEdges[i].m_pNode2);

		ppDistances[nIndex1][nIndex2] = fDistance;
		ppDistances[nIndex2][nIndex1] = fDistance;
	}
	COriginalData od;
	od.SetData(m_Graph.m_nNodeCount, pValues, ppDistances);
	//od.PrintFile("test.csv");
	m_NodeTable.Init(od);
	m_NodeTable.Order();
}

void CTestDataCreater::ConnectGraphANdTable()
{
	for (int i = 0; i < m_Graph.m_nMaxNodeCount; ++i)
	{
		m_Graph.m_pNodes[i].SetValue(m_NodeTable.m_pNodes + i);
	}
}
