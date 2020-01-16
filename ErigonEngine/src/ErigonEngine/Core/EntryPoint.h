#pragma once
#ifdef ERIGON_WINDOWS
extern ErigonEngine::Application* ErigonEngine::CreateApplication();

void LaunchEngine()
{
	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

int main(int argc, char** argv)
{
	ErigonEngine::Log::Init();
	EE_CORE_WARN("Initialize Log!");
	LaunchEngine();
}



#endif