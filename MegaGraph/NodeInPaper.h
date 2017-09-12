#pragma once

class CMegaNode;

class CNodeInPaper
{
public:
	CNodeInPaper();
	CNodeInPaper(int nX, int nY);
	CNodeInPaper(CMegaNode * pNodeData);
	~CNodeInPaper();
	double GetDistance(const CNodeInPaper * pAnother)const;
	void SetValue(int nX, int nY);
	void SetValue(CMegaNode * pNodeData);

	int GetX() { return m_nX; }
	int GetY() { return m_nY; }
	double GetValue();


	int m_nX;
	int m_nY;

	CMegaNode * m_pNodeData;
};

