#pragma once
#ifdef ERIGON_WINDOWS
#include "ProjectSelector/ProjectWindowController.h"
extern ErigonEngine::Application* ErigonEngine::CreateApplication();
extern ErigonEngine::ProjectWindowApp* ErigonEngine::CreateProjectSelector(int argc, char** argv);

void LaunchEngine()
{
	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

void LaunchProjectSelector(int argc, char** argv)
{
	auto app = ErigonEngine::CreateProjectSelector(argc,argv);
	app->Run();
	delete app;
}
int main(int argc, char** argv)
{
	ErigonEngine::Log::Init();
	EE_CORE_WARN("Initialize Log!");
	LaunchProjectSelector(argc, argv);
	
	LaunchEngine();
}



#endif