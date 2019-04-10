#pragma once

#ifdef ERIGON_WINDOWS

extern ErigonEngine::Application* ErigonEngine::CreateApplication();

int main(int argc,char** argv)
{
	ErigonEngine::Log::Init();
	ErigonEngine::Log::GetCoreLogger()->warn("Initialize Log!");
	ErigonEngine::Log::GetClientLogger()->info("Initialize Client Log!");

	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif