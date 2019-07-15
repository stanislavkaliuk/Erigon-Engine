#pragma once

#ifdef ERIGON_WINDOWS

extern ErigonEngine::Application* ErigonEngine::CreateApplication();

int main(int argc,char** argv)
{
	ErigonEngine::Log::Init();
	EE_CORE_WARN("Initialize Log!");
	int a = 50;
	EE_INFO("Initialize Client Log! Var = {0}",a);

	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif