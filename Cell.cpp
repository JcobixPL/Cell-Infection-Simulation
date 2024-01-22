#include "Cell.h"
#include "Simulation.h"

wxColour Cell::healthyColor = *wxGREEN;
wxColour Cell::infectedColor = *wxRED;
wxColour Cell::immuneColor = *wxYELLOW;

Cell::Cell() : currentState(State::Healthy), duration(1) {
}

void Cell::setState(State newState) {
    currentState = newState;
    duration = 0;
}

Cell::State Cell::getState() const {
    return currentState;
}

void Cell::setDuration(int newDuration) {
    duration = newDuration;
}

int Cell::getDuration() const {
    return duration;
}

wxColor Cell::getColor() const {
    switch (currentState) {
    case Healthy:
       return healthyColor;
    case Infected:
        return infectedColor;
    case Immune:
        return immuneColor;
    }
}

void Cell::setColors(wxColor c1, wxColor c2, wxColor c3) {
    healthyColor = c1;
    infectedColor = c2;
    immuneColor = c3;
}

wxColour Cell::getHealthyColor() {
    return healthyColor;
}

wxColour Cell::getInfectedColor() {
    return infectedColor;
}

wxColour Cell::getImmuneColor() {
    return immuneColor;
}