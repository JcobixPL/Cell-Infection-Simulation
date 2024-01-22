#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include "Cell.h"

class CellGrid : public wxGrid {
public:
	CellGrid(wxWindow* parent, int rows, int cols);
	std::vector<std::vector<Cell>> getCells() const;
	void initGrid(int rows, int cols);
	static int GetInfectionTime();
	static int GetImmunityTime();
	void SetInfectionTime(int time);
	void SetImmunityTime(int time);
	Cell* GetCell(int row, int col);
	void setCells(const std::vector<std::vector<Cell>>& newCells);
	void SetCellState(int row, int col, Cell::State newState);
	void AdjustCellSize(int rows, int cols);

private:
	std::vector<std::vector<Cell>> cells;
	int healthyCount;
	int infectedCount;
	int immuneCount;
	static int infectionTime;
	static int immunityTime;
};

