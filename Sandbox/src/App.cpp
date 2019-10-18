#include "Engine2D.h"
#include "StartupWindow.h"
#include <ErigonEngine/Core/EntryPoint.h>
#include <ProjectSelector/ProjectWindowController.h>
#include <wx/wx.h>

class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new Engine2D());
	}
	~Sandbox()
	{

	}
};

class ProjectWindow : public ErigonEngine::ProjectWindowApp, public wxApp
{
public:
	ProjectWindow()
	{
		wxApp::SetInstance(this);
		wxEntryStart(0, nullptr);
		wxTheApp->OnInit();
	}
	~ProjectWindow()
	{

	}
	virtual bool OnInit()
	{
		window = new StartupWindow();
		window->Show();
	}
	bool Run() override
	{
		wxTheApp->OnRun();
	}
private:
	StartupWindow* window = nullptr;
};

ErigonEngine::ProjectWindowApp* ErigonEngine::CreateProjectSelector()
{
	return new ProjectWindowApp();
}

ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}