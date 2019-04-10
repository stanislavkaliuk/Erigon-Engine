#pragma once

#include "Core.h"

namespace ErigonEngine
{
	class ERIGON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
}