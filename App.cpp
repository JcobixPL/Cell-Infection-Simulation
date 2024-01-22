#include "App.h"
#include <cstdlib>
#include <ctime>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    std::srand(std::time(NULL));
    Simulation* simulation = new Simulation("Problem liszaja", wxDefaultPosition, wxDefaultSize);
    simulation->SetMinSize(wxSize(800, 620));
    simulation->Show(true);
    return true;
}