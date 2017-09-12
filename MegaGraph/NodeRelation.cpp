#include "stdafx.h"
#include "NodeRelation.h"



CNodeRelation::CNodeRelation()
	: m_fDistance(DISTANCE_NO_RELATION)
	, value(NODE_VALUE_ILLEGAL)
	, relation(E_NODERELATION_NONE)
	, edgeState(E_EDGESTATE_OUTSIDE)
{
}


CNodeRelation::~CNodeRelation()
{
}
