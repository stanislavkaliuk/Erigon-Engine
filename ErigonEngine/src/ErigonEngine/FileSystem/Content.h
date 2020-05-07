#pragma once
#include <string>
#include "ErigonEngine/Core/Core.h"
#include "IContent.h"
#include <vector>

namespace ErigonEngine::Content
{
	class Content
	{
	public:
		static void Init();
		static Ref<IContent> Load(const char* path);
		static std::vector<Ref<IContent>> LoadAll(const char* path);
		static std::future<Ref<IContent>> LoadAsync(const char* path);
		static bool UnloadContent(Ref<IContent> contnetToUnload);
		inline static void SetAsDirty();
		inline static bool IsDirty();
	private:
		static void OnScanDone();
	};
}