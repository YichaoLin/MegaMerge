#pragma once
#define MAX_NODE_COUNT 30

typedef double * doubleptr;

class COriginalData
{
public:
	COriginalData();
	~COriginalData();

	void InitFromFile(char * strFileName);
	static double * GetNumsFromString(char * pStr, int nStrLen, int nMaxNumCount, int & nRetLength);
	void ShowData();
	int GetNodeCount() const { return m_nNodeCount; }
	const double * GetValues() const { return m_pValues; }
	double ** GetDistances() const { return m_ppDistances; }

	void SetData(int nNodeCount, double * pValues, double ** ppDistances);

	void PrintFile(char * strFile);

private:
	int m_nNodeCount;
	double * m_pValues;
	double ** m_ppDistances;
};

