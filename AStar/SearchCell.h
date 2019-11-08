#ifndef __SEARCHCELL_H__
#define __SEARCHCELL_H__

#include <math.h>

#define WorldSIZE 100

struct SearchCell
{
	int Xpos; int Ypos;

	int Id;

	bool isBlocker = false;

	bool isBarriar = false;

	SearchCell* Parent;

	float G; float H;

	SearchCell()
	{
		Parent = 0;
	}

	SearchCell(int _x, int _y, SearchCell* _parent = 0)
	{
		Xpos = _x; Ypos = _y;

		Id = (_y * WorldSIZE) + _x;

		Parent = _parent;

		G = 0; H = 0;
	}

	float GetF()
	{
		return G + H;
	}

	float ManDistance(SearchCell* Goal)
	{
		float x = (float)(fabs((float)this->Xpos - Goal->Xpos));
		float y = (float)(fabs((float)this->Ypos - Goal->Ypos));

		return x + y;
	}
};

#endif __SEARCHCELL_H__
