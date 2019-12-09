#pragma once
#include "Engine2D.h"
#include "EngineUIData.h"
#include <imgui/imgui.h>

struct TransformResult
{
	UITransform transform;
	TransformTarget target;
};

class EngineUI
{
public:
	bool Open = true;
	bool Close = false;
	EngineUI(uint32_t windowWidth, uint32_t windowHeight);
	void Draw();
	void DrawInspector(bool state, UITransform* transform, ErigonEngine::OrthographicCameraController* cameraController);
	void DrawSceneHierarchy(bool state, UITransform* transform);
private:
	TransformResult* results;
	void RecalculateTransforms(TransformResult* results);
	uint32_t windowWidth, windowHeight;
};