#include "stdafx.h"
#include "OriginalData.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


COriginalData::COriginalData()
	:m_nNodeCount(0)
	,m_pValues(NULL)
	,m_ppDistances(NULL)
{
}


COriginalData::~COriginalData()
{
	delete[] m_pValues;
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		delete[] m_ppDistances[i];
	}
	delete[] m_ppDistances;
}

void COriginalData::InitFromFile(char * strFileName)
{
	ifstream fin(strFileName);
	const int rowlength = MAX_NODE_COUNT * 20;
	char tmprow[rowlength];
	bool bIsFirstRow = true;
	int nRowId = 0;
	while (!fin.eof())
	{
		fin.getline(tmprow, rowlength);
		if (strlen(tmprow) == 0)
		{
			continue;
		}
		int nNodeCount = 0;
		double * pNumbers = GetNumsFromString(tmprow, strlen(tmprow), MAX_NODE_COUNT, nNodeCount);
		if (bIsFirstRow)
		{
			m_nNodeCount = nNodeCount;
			m_pValues = new double[m_nNodeCount];
			m_ppDistances = new double*[m_nNodeCount];
			for (int i = 0; i < nNodeCount; ++i)
			{
				m_pValues[i] = pNumbers[i];
			}
			bIsFirstRow = false;
		}
		else
		{
			if (nRowId >= nNodeCount)
			{
				break;
			}
			m_ppDistances[nRowId] = new double[nNodeCount];
			for (int i = 0; i < nNodeCount; ++i)
			{
				m_ppDistances[nRowId][i] = pNumbers[i];
			}
			++nRowId;
		}
		delete[] pNumbers;
		pNumbers = NULL;
	}
}

double * COriginalData::GetNumsFromString(char * pStr, int nStrLen, int nMaxNumCount, int & nRetLength)
{
	nRetLength = 0;
	char * pTmpStr = new char[nStrLen + 1];
	memcpy(pTmpStr, pStr, nStrLen);
	pTmpStr[nStrLen] = 0;
	double * pRet = new double[nMaxNumCount];
	char * p1 = pTmpStr, *p2;
	while (p1 - pTmpStr < nStrLen)
	{
		p2 = p1 + 1;
		while ((isdigit(*p2) || *p2 == '.') && (p2-pTmpStr) < nStrLen)
		{
			++p2;
		}
		if (p2 == p1)
			break;
		*p2 = 0;
		double fTmpNum = atof(p1);
		pRet[nRetLength] = fTmpNum;
		++nRetLength;
		p1 = p2 + 1;
	}
	return pRet;
}

void COriginalData::ShowData()
{
	cout << "   \t";
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		cout << setprecision(3) << m_pValues[i] << "\t";
	}
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		cout << endl << m_pValues[i] << "\t";
		for (int j = 0; j < m_nNodeCount; ++j)
		{
			cout << setprecision(3) << m_ppDistances[i][j] << "\t";
		}
	}
}

void COriginalData::SetData(int nNodeCount, double * pValues, double ** ppDistances)
{
	m_nNodeCount = nNodeCount;
	m_pValues = pValues;
	m_ppDistances = ppDistances;
}

void COriginalData::PrintFile(char * strFile)
{
	ofstream fout(strFile);
	for (int i = 0; i < m_nNodeCount; i++)
	{
		fout << m_pValues[i] << ",";
	}
	for (int i = 0; i < m_nNodeCount; ++i)
	{
		fout << endl;
		for (int j = 0; j < m_nNodeCount; ++j)
		{
			fout << m_ppDistances[i][j] << ",";
		}
	}
	fout.close();
}
