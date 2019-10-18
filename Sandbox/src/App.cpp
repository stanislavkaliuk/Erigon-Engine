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

class ProjectWindow : public wxApp
{
public:
	ProjectWindow(int argc, char** argv)
	{
		wxApp::SetInstance(this);
		
	}
	~ProjectWindow()
	{

	}
	virtual bool OnInit()
	{
		window = new StartupWindow();
		window->Show();
		return true;
	}
	
private:
	StartupWindow* window = nullptr;
};

class ProjectSelectorApp : public ErigonEngine::ProjectWindowApp
{
	bool Run() override
	{
		wxTheApp->OnRun();
		return true;
	}
};

ErigonEngine::ProjectWindowApp* ErigonEngine::CreateProjectSelector(int argc, char** argv)
{
	auto windowApp = new ProjectWindow(argc, argv);
	wxApp::SetInstance(windowApp);
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	return new ProjectSelectorApp();
}

ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}