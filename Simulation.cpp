#include "Simulation.h"

Simulation::Simulation(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size), leftPanel(nullptr), rightPanel(nullptr), lowerRightPanel(nullptr), upperRightPanel(nullptr), line1(nullptr), line2(nullptr), cellGrid(nullptr), rows(35), cols(25), rowsSpin(nullptr), colsSpin(nullptr), infectionTimeSpin(nullptr), immunityTimeSpin(nullptr), healthyColourPicker(nullptr), infectedColourPicker(nullptr), immuneColourPicker(nullptr) {
    timer = new wxTimer(this, wxID_ANY);
    Bind(wxEVT_TIMER, &Simulation::OnTimer, this, timer->GetId());
    isSimulationRunning = false;

    createLayout();
}

void Simulation::createLayout() {
    leftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(150, -1), wxBORDER_SIMPLE);
    leftPanel->SetBackgroundColour(*wxWHITE);

    rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);

    upperRightPanel = new wxPanel(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    upperRightPanel->SetBackgroundColour(*wxWHITE);

    lowerRightPanel = new wxPanel(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    lowerRightPanel->SetBackgroundColour(*wxWHITE);
    lowerRightPanel->SetMinSize(wxSize(-1, 100));

    line1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

    line2 = new wxStaticLine(rightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    leftPanelSizer = new wxBoxSizer(wxVERTICAL);
    upperRightPanelSizer = new wxBoxSizer(wxVERTICAL);
    lowerRightPanelSizer = new wxBoxSizer(wxVERTICAL);

    simulateButton = new wxButton(leftPanel, wxID_ANY, "SIMULATE", wxDefaultPosition, wxDefaultSize, 0);
    simulateButton->Bind(wxEVT_BUTTON, &Simulation::OnSimulate, this);

    stopButton = new wxButton(leftPanel, wxID_ANY, "STOP", wxDefaultPosition, wxDefaultSize, 0);
    stopButton->Bind(wxEVT_BUTTON, &Simulation::OnStop, this);

    resetButton = new wxButton(leftPanel, wxID_ANY, "RESET", wxDefaultPosition, wxDefaultSize, 0);
    resetButton->Bind(wxEVT_BUTTON, &Simulation::OnReset, this);

    startText = new wxStaticText(leftPanel, wxID_ANY, "INFECTION START BY", wxDefaultPosition, wxDefaultSize);

    choices.Add("MIDDLE CELL");
    choices.Add("CHOOSE BY MOUSE");

    choice = new wxChoice(leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
    choice->SetSelection(0);

    chancesText = new wxStaticText(leftPanel, wxID_ANY, "INFECTION CHANCES", wxDefaultPosition, wxDefaultSize);
    chancesSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 1, 100, 50);

    fpsText = new wxStaticText(leftPanel, wxID_ANY, "FPS", wxDefaultPosition, wxDefaultSize);
    fpsSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 1, 100, 80);

    rowsSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 3, 150, rows);
    colsSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 3, 150, cols);

    infectionTimeSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 1, 1000, CellGrid::GetInfectionTime());
    immunityTimeSpin = new wxSpinCtrl(leftPanel, wxID_ANY, wxString(), wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 1, 1000, CellGrid::GetImmunityTime());

    healthyColourPicker = new wxColourPickerCtrl(leftPanel, wxID_ANY, Cell::getHealthyColor(), wxDefaultPosition, wxDefaultSize);
    infectedColourPicker = new wxColourPickerCtrl(leftPanel, wxID_ANY, Cell::getInfectedColor(), wxDefaultPosition, wxDefaultSize);
    immuneColourPicker = new wxColourPickerCtrl(leftPanel, wxID_ANY, Cell::getImmuneColor(), wxDefaultPosition, wxDefaultSize);

    leftPanelSizer->Add(simulateButton, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(stopButton, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(resetButton, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(startText, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(choice, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(chancesText, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(chancesSpin, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(fpsText, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(fpsSpin, 0, wxEXPAND | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Rows:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(rowsSpin, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Columns:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(colsSpin, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Infection Time [s]:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(infectionTimeSpin, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Immunity Time [s]:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(immunityTimeSpin, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Healthy color:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(healthyColourPicker, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Infected color:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(infectedColourPicker, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "Immune color:"), 0, wxALIGN_CENTER | wxALL, 5);
    leftPanelSizer->Add(immuneColourPicker, 0, wxALIGN_CENTER | wxALL, 5);
    leftPanel->SetSizer(leftPanelSizer);
    cellGrid = new CellGrid(upperRightPanel, rows, cols);
    upperRightPanelSizer->AddStretchSpacer(1);
    upperRightPanelSizer->Add(cellGrid, 0, wxALIGN_CENTER | wxALL, 5);
    upperRightPanelSizer->AddStretchSpacer(1);
    upperRightPanel->SetSizer(upperRightPanelSizer);

    statsText = new wxStaticText(lowerRightPanel, wxID_ANY, "STATS:\n0 HEALTHY / 0 CELLS\n0 INFECTED / 0 CELLS\n0 IMMUNE / 0 CELLS", wxDefaultPosition, wxDefaultSize);
    lowerRightPanelSizer->Add(statsText, 0, wxEXPAND | wxALL, 5);

    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    rightPanelSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(leftPanel, 0, wxEXPAND);
    mainSizer->Add(line1, 0, wxEXPAND);
    mainSizer->Add(rightPanel, 1, wxEXPAND);

    rightPanelSizer->Add(upperRightPanel, 1, wxEXPAND);
    rightPanelSizer->Add(line2, 0, wxEXPAND);
    rightPanelSizer->Add(lowerRightPanel, 0, wxEXPAND);

    rightPanel->SetSizer(rightPanelSizer);

    SetSizerAndFit(mainSizer);

}

void Simulation::OnSimulate(wxCommandEvent& event) {
    if (!isSimulationRunning) {
        rows = rowsSpin->GetValue();
        cols = colsSpin->GetValue();
        newCellGrid = new CellGrid(upperRightPanel, rows, cols);
        upperRightPanel->GetSizer()->Replace(cellGrid, newCellGrid);
        delete cellGrid;
        cellGrid = newCellGrid;
        upperRightPanel->Layout();
    }
    StartSimulation();
}

void Simulation::OnStop(wxCommandEvent& event) {
    cellGrid->Unbind(wxEVT_GRID_CELL_LEFT_CLICK, &Simulation::OnCellClick, this);
    cellGrid->SetSelectionMode(wxGrid::wxGridSelectNone);
    timer->Stop();
}

void Simulation::OnReset(wxCommandEvent& event) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cellGrid->SetCellState(row, col, Cell::Healthy);
        }
    }
    cellGrid->Unbind(wxEVT_GRID_CELL_LEFT_CLICK, &Simulation::OnCellClick, this);
    cellGrid->SetSelectionMode(wxGrid::wxGridSelectNone);
    timer->Stop();
    UpdateStats();
    isSimulationRunning = false;
    this->Refresh();
}

void Simulation::OnTimer(wxTimerEvent& event) {
    SpreadInfection();
}

void Simulation::StartSimulation() {
    if (!isSimulationRunning) {
        selectedChoices = choices[choice->GetSelection()];
        isSimulationRunning = true;
        if (selectedChoices == "MIDDLE CELL") InfectMiddleCell();
        interval = 1000 / fpsSpin->GetValue();
        timer->Start(interval);
        cellGrid->SetSelectionMode(wxGrid::wxGridSelectCells);
        cellGrid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &Simulation::OnCellClick, this);
    }
    else {
        interval = 1000 / fpsSpin->GetValue();
        timer->Start(interval);
        cellGrid->SetSelectionMode(wxGrid::wxGridSelectCells);
        cellGrid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &Simulation::OnCellClick, this);
    }
}

void Simulation::InfectMiddleCell() {
    int middleRow = rows / 2;
    int middleCol = cols / 2;
    middleCell = cellGrid->GetCell(middleRow, middleCol);
    middleCell->setState(Cell::Infected);
    middleCell->setDuration(1);
    cellGrid->initGrid(rows, cols);
    UpdateStats();
    this->Refresh();
}

void Simulation::InfectByMouse(int row, int col) {
    selectedCell = cellGrid->GetCell(row, col);
    selectedCell->setState(Cell::Infected);
    selectedCell->setDuration(1);
    cellGrid->initGrid(rows, cols);
    UpdateStats();
    this->Refresh();
}

void Simulation::SpreadInfection() {
    std::vector<std::vector<Cell>> newCells = cellGrid->getCells();
    int newRows = rowsSpin->GetValue();
    int newCols = colsSpin->GetValue();
    int newInfectionTime = infectionTimeSpin->GetValue();
    int newImmunityTime = immunityTimeSpin->GetValue();
    wxColor newHealthyColor = healthyColourPicker->GetColour();
    wxColor newInfectedColor = infectedColourPicker->GetColour();
    wxColor newImmuneColor = immuneColourPicker->GetColour();

    if (newRows != rows || newCols != cols || newInfectionTime != cellGrid->GetInfectionTime() || newImmunityTime != cellGrid->GetImmunityTime() || newHealthyColor != Cell::getHealthyColor() || newInfectedColor != Cell::getInfectedColor() || newImmuneColor != Cell::getImmuneColor()) {

        cell->setColors(newHealthyColor, newInfectedColor, newImmuneColor);
        rows = newRows;
        cols = newCols;
        newCellGrid = new CellGrid(upperRightPanel, rows, cols);
        std::vector<std::vector<Cell>> newCells1(rows, std::vector<Cell>(cols));
        for (int i = 0; i < std::min(rows, static_cast<int>(newCells.size())); ++i) {
            for (int j = 0; j < std::min(cols, static_cast<int>(newCells[i].size())); ++j) {
                newCells1[i][j] = newCells[i][j];
            }
        }
        upperRightPanel->GetSizer()->Replace(cellGrid, newCellGrid);
        delete cellGrid;
        cellGrid = newCellGrid;
        cellGrid->SetInfectionTime(newInfectionTime);
        cellGrid->SetImmunityTime(newImmunityTime);
        cellGrid->setCells(updateCells(newCells1, rows, cols));

        upperRightPanel->Layout();
    }
    else cellGrid->setCells(updateCells(newCells, rows, cols));

    cellGrid->initGrid(rows, cols);
    UpdateStats();
    interval = 1000 / fpsSpin->GetValue();
    cellGrid->SetSelectionMode(wxGrid::wxGridSelectCells);
    cellGrid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &Simulation::OnCellClick, this);
    timer->Start(interval);
    this->Refresh();
}

int Simulation::countInfectedNeighbours(int row, int col) {
    int infectedNeighbours = 0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int neighborRow = row + x;
            int neighborCol = col + y;

            if (neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols) {
                neighborCell = cellGrid->GetCell(neighborRow, neighborCol);
                if (neighborCell->getState() == Cell::Infected) {
                    infectedNeighbours++;
                }
            }
        }
    }
    return infectedNeighbours;
}

void Simulation::OnCellClick(wxGridEvent& event) {
    int row = event.GetRow();
    int col = event.GetCol();

    InfectByMouse(row, col);
}

std::vector<std::vector<Cell>> Simulation::updateCells(std::vector<std::vector<Cell>> updatedCells, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            currentCell = cellGrid->GetCell(row, col);

            if (currentCell->getState() == Cell::Infected) {
                int newInfectionTime = infectionTimeSpin->GetValue();
                if (currentCell->getDuration() >= newInfectionTime) {
                    updatedCells[row][col].setState(Cell::Immune);
                    updatedCells[row][col].setDuration(1);
                }
                else {
                    updatedCells[row][col].setDuration(currentCell->getDuration() + 1);
                }
            }
            else if (currentCell->getState() == Cell::Healthy) {
                for (int i = 1; i <= countInfectedNeighbours(row, col); i++) {
                    if ((rand() % 100 + 1 <= chancesSpin->GetValue())) {
                        updatedCells[row][col].setState(Cell::Infected);
                        updatedCells[row][col].setDuration(1);
                        break;
                    }
                }
            }
            else if (currentCell->getState() == Cell::Immune) {
                int newImmunityTime = immunityTimeSpin->GetValue();
                if (currentCell->getDuration() >= newImmunityTime) {
                    updatedCells[row][col].setState(Cell::Healthy);
                }
                else {
                    updatedCells[row][col].setDuration(currentCell->getDuration() + 1);
                }
            }
        }
    }
    return updatedCells;
}

void Simulation::UpdateStats() {
    int healthyCount = 0;
    int infectedCount = 0;
    int immuneCount = 0;

    std::vector<std::vector<Cell>> cells = cellGrid->getCells();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            currentCell = &cells[row][col];
            switch (currentCell->getState()) {
            case Cell::Healthy:
                healthyCount++;
                break;
            case Cell::Infected:
                infectedCount++;
                break;
            case Cell::Immune:
                immuneCount++;
                break;
            default:
                break;
            }
        }
    }
    statsString = wxString::Format("STATS:\n%d HEALTHY / %d CELLS\n%d INFECTED / %d CELLS\n%d IMMUNE / %d CELLS", healthyCount, rows * cols, infectedCount, rows * cols, immuneCount, rows * cols);
    statsText->SetLabel(statsString);
    this->Refresh();
}

