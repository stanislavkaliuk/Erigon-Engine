#pragma once
#ifdef ERIGON_WINDOWS
#include "ProjectSelector/ProjectWindowController.h"
extern ErigonEngine::Application* ErigonEngine::CreateApplication();
extern ErigonEngine::ProjectWindowApp* ErigonEngine::CreateProjectSelector();

void LaunchEngine()
{
	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

void LaunchProjectSelector()
{
	auto app = ErigonEngine::CreateProjectSelector();
	app->Run();
}
int main(int argc, char** argv)
{
	ErigonEngine::Log::Init();
	EE_CORE_WARN("Initialize Log!");
	LaunchProjectSelector();
	
	LaunchEngine();
}



#endif