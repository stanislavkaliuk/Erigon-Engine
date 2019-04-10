#pragma once

#ifdef ERIGON_WINDOWS

extern ErigonEngine::Application* ErigonEngine::CreateApplication();

int main(int argc,char** argv)
{
	printf("Helllowwww\n");
	auto app = ErigonEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif