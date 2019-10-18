#pragma once
#include <wx/wx.h>

namespace ErigonEngine
{
	class ProjectWindowApp : public wxApp
	{
	public:
		ProjectWindowApp();
		~ProjectWindowApp();
		virtual bool Run() { return false; };
	};

	ProjectWindowApp* CreateProjectSelector(int argc, char** argv);
}