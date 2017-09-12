#pragma once
#include "NodeRelation.h"

class CMegaNode;

typedef struct _tree_ {
	//double value;
	//double root;
	CMegaNode * pRoot;
	int level;
	double min_distance;
 	CMegaNode * pMinInside;
 	CMegaNode * pMinOutside;
	//double value_min;
	//double value_min_connected;
}tree;

class CMegaNode
{
public:
	CMegaNode();
	~CMegaNode();
	void Init(double fValue, int nEdgeCount, const double * pEdgeValues, const double * pNodeValues);
	void Bubble();
	void Display();
	CNodeRelation * FindShortestOutside();

	double m_fValue;
	int m_nEdgeCount;
	CNodeRelation * m_pEdges;

	tree m_GroupInfo;


	bool m_bGroupInfoInsideChanged;
	CMegaNode * m_pRootChangeMessageFrom;

};

