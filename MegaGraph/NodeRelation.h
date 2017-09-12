#pragma once
#include <float.h>

#define NODE_VALUE_ILLEGAL -1

#define DISTANCE_NO_RELATION -1
#define DISTANCE_TO_SELF 0


//-1 Iam the child;1 Iam the father;0 no relationship;-2 I am myself
typedef enum
{
	E_NODERELATION_SELF = -2,
	E_NODERELATION_CHILD = -1,
	E_NODERELATION_NONE = 0,
	E_NODERELATION_FATHER = 1
}E_NODERELATION;

//0 inside;1 outside;-1 chosen
typedef enum
{
	//E_EDGESTATE_CHOSEN = -1,
	E_EDGESTATE_INSIDE = 0,
	E_EDGESTATE_OUTSIDE = 1,
}E_EDGESTATE;

class CNodeRelation
{
public:
	CNodeRelation();
	~CNodeRelation();

	double value;//the value of the node
	double m_fDistance;
	E_NODERELATION relation;
	E_EDGESTATE edgeState;
};

