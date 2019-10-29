#include "PathFinding.h"

PathFinding::PathFinding()
{
	InitStartGoal = false;
	FoundGoal = false;
}

PathFinding::~PathFinding()
{
}

void PathFinding::SetStartSetGoal(SearchCell _Start, SearchCell _Goal)
{
	StartCell = new SearchCell(_Start.Xpos, _Start.Ypos, 0);
	GoalCell = new SearchCell(_Goal.Xpos, _Goal.Ypos, &_Goal);

	StartCell->G = 0;
	StartCell->H = StartCell->ManDistance(GoalCell);
	StartCell->Parent = 0;

	OpenList.push_back(StartCell);
}

SearchCell* PathFinding::GetNextCell()
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

void PathFinding::PathOpened(int _x, int _y, float _newCost, SearchCell* _parent)
{
	//returns nothing if the path is blocked
	/*if (CELLBLOCKED)
	{
		return;
	}*/

	int Id = (_y * WorldSIZE) + _x;

	for (int i = 0; i < ClosedList.size(); i++)
	{
		if (Id == ClosedList[i]->Id)
		{
			return;
		}
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

void PathFinding::ContinuePath()
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
			Path.push_back(new Vector3(GetPath->Xpos, GetPath->Ypos, 0));
		}

		FoundGoal = true;
		return;
	}
	else
	{
		//Right
		PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos, CurrentCell->G + 1, CurrentCell);
		//Left
		PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos, CurrentCell->G + 1, CurrentCell);

		//Up
		PathOpened(CurrentCell->Xpos, CurrentCell->Ypos + 1, CurrentCell->G + 1, CurrentCell);
		//Down
		PathOpened(CurrentCell->Xpos, CurrentCell->Ypos - 1, CurrentCell->G + 1, CurrentCell);

		//Diagonal Up Left
		PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos + 1, CurrentCell->G + 1.414f, CurrentCell);
		//Diagonal Up Right
		PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos + 1, CurrentCell->G + 1.414f, CurrentCell);

		//Diagonal Down Left
		PathOpened(CurrentCell->Xpos - 1, CurrentCell->Ypos - 1, CurrentCell->G + 1.414f, CurrentCell);
		//Diagonal Down Right
		PathOpened(CurrentCell->Xpos + 1, CurrentCell->Ypos - 1, CurrentCell->G + 1.414f, CurrentCell);

		for (int i = 0; i < OpenList.size(); i++)
		{
			if (CurrentCell->Id == OpenList[i]->Id)
			{
				OpenList.erase(OpenList.begin() + i);
			}
		}
	}
}

Vector3 PathFinding::NextPathPos(SearchCell* obj)
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

void PathFinding::FindPath(Vector3 _Currentpos, Vector3 _Targetpos)
{
	//To Initialize 
	if (!InitStartGoal)
	{
		//Clears Everything
		for (int i = 0; i < OpenList.size(); i++)
		{
			delete OpenList[i];
		}
		OpenList.clear();

		for (int i = 0; i < ClosedList.size(); i++)
		{
			delete ClosedList[i];
		}
		ClosedList.clear();

		for (int i = 0; i < Path.size(); i++)
		{
			delete Path[i];
		}
		Path.clear();

		//Initialize Start
		SearchCell Start;
		Start.Xpos = _Currentpos.x;
		Start.Ypos = _Currentpos.y;

		//Initialize Goal
		SearchCell Goal;
		Goal.Xpos = _Targetpos.x;
		Goal.Ypos = _Targetpos.y;

		SetStartSetGoal(Start, Goal);
		InitStartGoal = true;
	}

	//If Initialized
	if (InitStartGoal)
	{
		ContinuePath();
	}
}

void PathFinding::ClearOpenList()
{
	OpenList.clear();
}

void PathFinding::ClearClosedList()
{
	ClosedList.clear();
}

void PathFinding::ClearPath()
{
	Path.clear();
}


