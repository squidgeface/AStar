#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include <vector>
#include <cmath>
#include "SearchCell.h"

struct Vector3
{
	int x, y, z;

	Vector3(int _x, int _y, int _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

class CPathFinding
{
public:
	CPathFinding();
	~CPathFinding();

	void InitialiseBlockers(std::vector<SearchCell*> _blockers);

	void SetStartSetGoal(SearchCell * _Start, SearchCell * _Goal, std::vector<SearchCell*> _blockers);

	void FindPath(Vector3 _Currentpos, Vector3 _Targetpos);
	Vector3 NextPathPos(SearchCell* obj);
	

	void ClearOpenList();
	void ClearClosedList();
	void ClearPath();

	bool InitStartGoal;
	bool FoundGoal;
	bool Corner;
	bool uBlocker;
	int uCount;
	bool lBlocker;
	int lCount;
	bool rBlocker;
	int rCount;
	bool dBlocker;
	int dCount;
	bool blocked;
	bool firstRun;


	void PathOpened(int _x, int _y, float _newCost, SearchCell* _parent);

	SearchCell* GetNextCell();
	void ContinuePath();

	SearchCell* StartCell;
	SearchCell* GoalCell;
	

	std::vector<SearchCell*> OpenList;
	std::vector<SearchCell*> ClosedList;
	std::vector<Vector3*> Path;
	std::vector<SearchCell*> blockerCells;
};

#endif __PATHFINDING_H__

