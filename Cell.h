#pragma once

#include <wx/wx.h>

class Cell {
public:
	enum State {
		Healthy,
		Infected,
		Immune
	};
	Cell();
	void setState(State newState);
	State getState() const;
	void setDuration(int newDuration);
	int getDuration() const;
	wxColour getColor() const;
	void setColors(wxColor c1, wxColor c2, wxColor c3);
	static wxColour getHealthyColor();
	static wxColour getInfectedColor();
	static wxColour getImmuneColor();

private:
	State currentState;
	int duration;
	static wxColour healthyColor;
	static wxColour infectedColor;
	static wxColour immuneColor;
};

