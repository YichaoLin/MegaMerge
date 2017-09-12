#pragma once
#include "MegaNode.h"
#include "OriginalData.h"
#include <fstream>
using namespace std;
class CNodeTable
{
public:
	CNodeTable();
	~CNodeTable();

	void Init(const COriginalData & od);
	void Order();
	void Display();
	void CleanReport();
	void AllReport();
	void AllGroupSetChoosen();
	void AllMerge();
	void SetInside();
	bool IsChooseEachOther(CMegaNode * Node1, CMegaNode * Node2);
	int judge();
	void set_relationship(CMegaNode * pRoot, CMegaNode * pFather, CMegaNode * pEveryBegining);
	void change_root_friendlymerge(CMegaNode * pA, CMegaNode * pB);
	void SetRelation(CMegaNode * pFather, CMegaNode * pChild, E_EDGESTATE eState);
	CMegaNode * MergeDifferentLevelGroup(CMegaNode * Node1, CMegaNode * Node2);
	CMegaNode * FromValueToNode(double fValue);
	void SetLevel(CMegaNode * pRoot, int nLevel);
	void ShowTree(ofstream & fout);
	void ShowTreeRecursion(ofstream & fout, CMegaNode * pFather, int nLevel, bool bIsFirst);
	int GetLevelDiffToRoot(CMegaNode * pNode);
	int GetLevelDiffToAnother(CMegaNode * pNode, CMegaNode * pAnother);
	CMegaNode * GetSuperNode(CMegaNode * pNode);
	int GetUpMessageCountThisIteration();
	int GetDownMessageCountThisIteration();
	int GetMessageCountThisIteration();
	int GetNotifyMessageCount();
	int GetConnectMessageCount();
	int GetCityCount();
	bool IsNodeHaveReport(CMegaNode* pNode);

	int m_nNodeCount;
	CMegaNode * m_pNodes;

	int m_nNotifyMessageCount;
};

