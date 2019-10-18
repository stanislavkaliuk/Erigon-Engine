#include "eepch.h"
#include "StartupWindow.h"

StartupWindow::StartupWindow() : wxFrame(nullptr, wxID_ANY, "Erigon Engine v0.1", wxPoint(50, 50), wxSize(900,600), wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER)
{
	Centre();
	SetBackgroundColour(wxColour(200, 200, 200, 255));
}

StartupWindow::~StartupWindow()
{
}
