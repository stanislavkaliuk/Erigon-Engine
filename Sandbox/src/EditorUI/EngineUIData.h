#pragma once
#include <imgui/imgui.h>

struct UITransform
{
	ImVec2 position;
	ImVec2 size;
};

enum class TransformTarget
{
	Inspector = 1,
	Hierarchy = 2
};


