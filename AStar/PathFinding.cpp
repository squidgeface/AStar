#include "PathFinding.h"

CPathFinding::CPathFinding()
{
	InitStartGoal = false;
	FoundGoal = false;
	Corner = false;
	uBlocker = false;
	lBlocker = false;
	rBlocker = false;
	dBlocker = false;
	blocked = false;
	firstRun = true;
	uCount = 0;
	lCount = 0;
	rCount = 0;
	dCount = 0;
}

CPathFinding::~CPathFinding()
{
}

void CPathFinding::InitialiseBlockers(std::vector<SearchCell*> _blockers)
{
	if (firstRun) 
	{
		for (int i = 0; i < _blockers.size(); i++)
		{
			blockerCells.push_back(new SearchCell(_blockers[i]->Xpos, _blockers[i]->Ypos, 0));

		}
	}
	////Initialise vector boundry blockers
	//for (int i = 0; i < 11; i++)
	//{
	//	SearchCell* BlockerCells = new SearchCell(i - 1, -1, 0);
	//	BlockerCells->isBarriar = true;

	//	blockerCells.push_back(BlockerCells);
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//	SearchCell* BlockerCells = new SearchCell(-1, i, 0);
	//	BlockerCells->isBarriar = true;
	//	blockerCells.push_back(BlockerCells);
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//	SearchCell* BlockerCells = new SearchCell(0, i, 0);
	//	BlockerCells->isBarriar = true;
	//	blockerCells.push_back(BlockerCells);
	//}
	//for (int i = 0; i < 9; i++)
	//{
	//	SearchCell* BlockerCells = new SearchCell(i, 10, 0);
	//	BlockerCells->isBarriar = true;
	//	blockerCells.push_back(BlockerCells);
	//}
	
}

void CPathFinding::SetStartSetGoal(SearchCell* _Start, SearchCell* _Goal, std::vector<SearchCell*> _blockers)
{
	
		StartCell = new SearchCell(_Start->Xpos, _Start->Ypos, 0);
		GoalCell = new SearchCell(_Goal->Xpos, _Goal->Ypos, _Goal);

		StartCell->G = 0;
		StartCell->H = StartCell->ManDistance(GoalCell);
		StartCell->Parent = 0;

		InitialiseBlockers(_blockers);

		OpenList.push_back(StartCell);

		for (int j = 0; j < blockerCells.size(); j++)
		{
			blockerCells[j]->isBlocker = true;
			blockerCells[j]->H = 99;
			OpenList.push_back(blockerCells[j]);		
		}
		
		InitStartGoal = true;
}

SearchCell* CPathFinding::GetNextCell()
{
	float BestF = 9999999999999999999.0f;
	int CellIndex = -1;

	SearchCell* NextCell = nullptr;

	for (int i = 0; i < OpenList.size(); i++)
	{
		
		if (OpenList[i]->GetF() < BestF)
		{
			BestF = OpenList[i]->GetF();
			CellIndex = i;
		}
	}

	if (CellIndex >= 0)
	{
		NextCell = OpenList[CellIndex];
		ClosedList.push_back(NextCell);
		OpenList.erase(OpenList.begin() + CellIndex);
	}

	return NextCell;
}

void CPathFinding::PathOpened(int _x, int _y, float _newCost, SearchCell* _parent)
{

	int Id = (_y * WorldSIZE) + _x;

	for (int i = 0; i < ClosedList.size(); i++)
	{
		if (Id == ClosedList[i]->Id)
		{
			return;
		}
	}

	if (_x < 0 || _x > 9 || _y < 0 || _y > 9)
	{
		return;
	}

	SearchCell* NewChild = new SearchCell(_x, _y, _parent);
	NewChild->G = _newCost;
	NewChild->H = _parent->ManDistance(GoalCell);

	for (int i = 0; i < OpenList.size(); i++)
	{
		if (Id == OpenList[i]->Id)
		{
			float NewF = NewChild->G + _newCost + OpenList[i]->H;

			if (OpenList[i]->GetF() > NewF)
			{
				OpenList[i]->G = NewChild->G + _newCost;
				OpenList[i]->Parent = NewChild;
			}
			else
			{
				delete NewChild;
				return;
			}
		}
	}

	OpenList.push_back(NewChild);
}

void CPathFinding::ContinuePath()
{
	if (OpenList.empty())
	{
		return;
	}

	SearchCell* CurrentCell = GetNextCell();

	if (CurrentCell->Id == GoalCell->Id)
	{
		GoalCell->Parent = CurrentCell->Parent;

		SearchCell* GetPath;

		for (GetPath = GoalCell; GetPath != nullptr; GetPath = GetPath->Parent)
		{
			if (GetPath->isBlocker)
			{
				if (firstRun)
				{
					ClearOpenList();
					ClearClosedList();
					ClearPath();

					OpenList.push_back(StartCell);

					for (int j = 0; j < blockerCells.size(); j++)
					{
						OpenList.push_back(blockerCells[j]);
					}

					firstRun = false;

					ContinuePath();
				}
				else {

					blocked = true;
					FoundGoal = true;
					

				}
				return;
			}

			Path.push_back(new Vector3(GetPath->Xpos, GetPath->Ypos, 0));
			
		}

		FoundGoal = true;
		return;
	}
	else
	{
		if (firstRun)
		{
			SearchCell* finder1 = new SearchCell();
			finder1->Xpos = CurrentCell->Xpos + 1;
			finder1->Ypos = CurrentCell->Ypos;

			for (int i = 0; i < OpenList.size(); i++)
			{
				if (OpenList[i]->Xpos < 10)
				{
					if (OpenList[i]->Xpos == finder1->Xpos && OpenList[i]->Ypos == finder1->Ypos && OpenList[i]->isBlocker)
					{
						rBlocker = true;
						Corner = true;
					}
				}
			}
			
			SearchCell* finder2 = new SearchCell();
			finder2->Xpos = CurrentCell->Xpos;
			finder2->Ypos = CurrentCell->Ypos - 1;

			for (int i = 0; i < OpenList.size(); i++)
			{
				if (OpenList[i]->Ypos > -1)
				{
					if (OpenList[i]->Ypos == finder2->Ypos && OpenList[i]->Xpos == finder2->Xpos && OpenList[i]->isBlocker)
					{
						Corner = true;
						uBlocker = true;
					}
				}
			}
			
			SearchCell* finder3 = new SearchCell();
			finder3->Xpos = CurrentCell->Xpos;
			finder3->Ypos = CurrentCell->Ypos + 1;

			for (int i = 0; i < OpenList.size(); i++)
			{
				if (OpenList[i]->Ypos < 10)
				{
					if (OpenList[i]->Ypos == finder3->Ypos && OpenList[i]->Xpos == finder3->Xpos && OpenList[i]->isBlocker)
					{
						Corner = true;
						dBlocker = true;
					}
				}
			}
			
			SearchCell* finder4 = new SearchCell();
			finder4->Xpos = CurrentCell->Xpos - 1;
			finder4->Ypos = CurrentCell->Ypos;

			for (int i = 0; i < OpenList.size(); i++)
			{
				if (OpenList[i]->Xpos > 0)
				{
					if (OpenList[i]->Xpos == finder4->Xpos && OpenList[i]->Ypos == finder4->Ypos && OpenList[i]->isBlocker)
					{
						lBlocker = true;
						Corner = true;
					}
				}
			}
			
		}

		if (!rBlocker || (!rBlocker && dBlocker) || (!rBlocker && uBlocker)) {
			//Right
			PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos, CurrentCell->G + 1, CurrentCell);
		}
		
		if (!lBlocker || (!lBlocker && dBlocker) || (!lBlocker && uBlocker)) {
			//Left
			PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos, CurrentCell->G + 1, CurrentCell);
		}

		if (!uBlocker || (!dBlocker && uBlocker)) {
			//Up
			PathOpened(CurrentCell->Xpos, CurrentCell->Ypos + 1, CurrentCell->G + 1, CurrentCell);
		}

			if (!dBlocker || (dBlocker && !uBlocker)) {
				//Down
				PathOpened(CurrentCell->Xpos, CurrentCell->Ypos - 1, CurrentCell->G + 1, CurrentCell);
			}

			if (!Corner)
			{
				//Diagonal Up Left
				PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos + 1, CurrentCell->G + 1.414f, CurrentCell);
				//Diagonal Up Right
				PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos + 1, CurrentCell->G + 1.414f, CurrentCell);
				//Diagonal Down Left
				PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos - 1, CurrentCell->G + 1.414f, CurrentCell);
				//Diagonal Down Right
				PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos - 1, CurrentCell->G + 1.414f, CurrentCell);
				
			}

		for (int i = 0; i < OpenList.size(); i++)
		{
			
			for (int j = 0; j < blockerCells.size(); j++)
			{
				if (OpenList[i]->Id == blockerCells[j]->Id)
				{
					OpenList[i]->isBlocker = true;
					OpenList[i]->H = 99;
				}	
			}

				if (CurrentCell->Id == OpenList[i]->Id && !OpenList[i]->isBlocker)
				{
					OpenList.erase(OpenList.begin() + i);
				}
		}
	}


		Corner = false;
		rBlocker = false;
		lBlocker = false;
		uBlocker = false;
		dBlocker = false;

}

Vector3 CPathFinding::NextPathPos(SearchCell* obj)
{
	int Index = 1;

	Vector3 NextPos(Path[Path.size() - Index]->x, Path[Path.size() - Index]->y, 0);

	Vector3 Distance(NextPos.x - obj->Xpos, NextPos.y - obj->Ypos, 0); // = NextPos - obj.Currentpos; // Need get Current Pos;

	Distance.z = sqrt((pow(Distance.x, 2) + pow(Distance.y, 2)));	//Length

	if (Index < Path.size())
	{
		if (Distance.z < 4) //Radius
		{
			Path.erase(Path.end() - Index);
		}
	}

	return NextPos;

}

void CPathFinding::FindPath(Vector3 _Currentpos, Vector3 _Targetpos)
{

	//If Initialized
	if (InitStartGoal)
	{
		ContinuePath();
	}
}

void CPathFinding::ClearOpenList()
{
	OpenList.clear();
}

void CPathFinding::ClearClosedList()
{
	ClosedList.clear();
}

void CPathFinding::ClearPath()
{
	Path.clear();
}
