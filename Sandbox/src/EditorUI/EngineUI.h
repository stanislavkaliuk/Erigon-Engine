#pragma once
#include "Editor.h"
#include <vector>

namespace Editor
{
	class EngineUI
	{
	public:
		bool Open = true;
		bool Close = false;
		EngineUI(uint32_t windowWidth, uint32_t windowHeight);
		void Setup();
		void Draw();
		//void DrawInspector(bool state, ErigonEngine::OrthographicCameraController* cameraController);
		//void DrawSceneHierarchy(bool state);
	private:
		uint32_t windowWidth, windowHeight;
		std::vector<IViewUI*> views;
	};
}