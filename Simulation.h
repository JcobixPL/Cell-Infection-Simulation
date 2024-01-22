#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/statline.h>
#include "CellGrid.h"

class Simulation : public wxFrame {
public:
    Simulation(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void createLayout();
    void OnSimulate(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnReset(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void StartSimulation();
    void InfectMiddleCell();
    void InfectByMouse(int row, int col);
    void SpreadInfection();
    int countInfectedNeighbours(int row, int col);
    void OnCellClick(wxGridEvent& event);
    std::vector<std::vector<Cell>> updateCells(std::vector<std::vector<Cell>> updatedCells, int rows, int cols);
    void UpdateStats();
    Cell* cell;
    Cell* middleCell;
    Cell* selectedCell;
    Cell* currentCell;
    Cell* neighborCell;
    CellGrid* cellGrid;
    CellGrid* newCellGrid;
    wxPanel* leftPanel;
    wxPanel* rightPanel;
    wxPanel* lowerRightPanel;
    wxPanel* upperRightPanel;
    wxStaticLine* line1;
    wxStaticLine* line2;
    wxBoxSizer* mainSizer;
    wxBoxSizer* rightPanelSizer;
    wxBoxSizer* leftPanelSizer;
    wxBoxSizer* upperRightPanelSizer;
    wxBoxSizer* lowerRightPanelSizer;
    wxButton* simulateButton;
    wxButton* stopButton;
    wxButton* resetButton;
    wxSpinCtrl* chancesSpin;
    wxSpinCtrl* fpsSpin;
    wxChoice* choice;
    wxArrayString choices;
    wxString selectedChoices;
    wxString statsString;
    wxString summaryText;
    wxTimer* timer;
    wxStaticText* startText;
    wxStaticText* chancesText;
    wxStaticText* fpsText;
    wxStaticText* statsText;
    wxCheckBox* infectionFocusCB;
    wxSpinCtrl* rowsSpin;
    wxSpinCtrl* colsSpin;
    wxSpinCtrl* infectionTimeSpin;
    wxSpinCtrl* immunityTimeSpin;
    wxColourPickerCtrl* healthyColourPicker;
    wxColourPickerCtrl* infectedColourPicker;
    wxColourPickerCtrl* immuneColourPicker;
    int interval;
    int rows;
    int cols;
    bool isSimulationRunning;
};

