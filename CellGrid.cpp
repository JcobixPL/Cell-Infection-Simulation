#include "CellGrid.h"

int CellGrid::infectionTime = 6;
int CellGrid::immunityTime = 4;

CellGrid::CellGrid(wxWindow* parent, int rows, int cols) : wxGrid(parent, wxID_ANY), healthyCount(0), infectedCount(0), immuneCount(0) {
    CreateGrid(rows, cols);
    SetDefaultColSize(30, true);
    SetDefaultRowSize(30, true);
    SetSelectionMode(wxGrid::wxGridSelectNone);
    EnableEditing(false);
    EnableDragColSize(false);
    EnableDragRowSize(false);
    HideRowLabels();
    HideColLabels();

    initGrid(rows, cols);
}

std::vector<std::vector<Cell>> CellGrid::getCells() const {
    return cells;
}

void CellGrid::initGrid(int rows, int cols) {
    cells.resize(rows, std::vector<Cell>(cols));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            SetCellBackgroundColour(row, col, cells[row][col].getColor());

            if (cells[row][col].getState() == Cell::State::Healthy) {
                ++healthyCount;
            }
            else if (cells[row][col].getState() == Cell::State::Infected) {
                ++infectedCount;
            }
            else if (cells[row][col].getState() == Cell::State::Immune) {
                ++immuneCount;
            }
        }
    }
    AdjustCellSize(rows, cols);
}

int CellGrid::GetInfectionTime() {
    return infectionTime;
}

int CellGrid::GetImmunityTime() {
    return immunityTime;
}

void CellGrid::SetInfectionTime(int time) {
    infectionTime = time;
}

void CellGrid::SetImmunityTime(int time) {
    immunityTime = time;
}

Cell* CellGrid::GetCell(int row, int col) {
    return &cells[row][col];
}

void CellGrid::setCells(const std::vector<std::vector<Cell>>& newCells) {
    cells = newCells;
}

void CellGrid::SetCellState(int row, int col, Cell::State newState) {
    cells[row][col].setState(newState);
    SetCellBackgroundColour(row, col, cells[row][col].getColor());
}

void CellGrid::AdjustCellSize(int rows, int cols) {
    int clientWidth, clientHeight;
    GetClientSize(&clientWidth, &clientHeight);

    int maxCellSize = std::min(clientWidth / cols, clientHeight / rows);

    int newCellSize = maxCellSize;
    while ((newCellSize + 1) * cols <= clientWidth && (newCellSize + 1) * rows <= clientHeight) {
        newCellSize++;
    }

    SetDefaultColSize(newCellSize, true);
    SetDefaultRowSize(newCellSize, true);
}
