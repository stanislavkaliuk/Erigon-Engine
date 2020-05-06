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
		static Ref<IContent> Load(const char* name);
		static Ref<std::vector<IContent>> LoadAll(const char* path);
		static Ref<IContent> LoadAsync(const char* path);
		static bool UnloadContent(IContent& contnetToUnload);
		static bool CreateBinaryFile(std::string& path);
		static bool CreateMaterialFile(std::string& path);
		static bool CreateMapFile(std::string& path);
		inline static void SetAsDirty();
		inline static bool IsDirty();
	private:
		static void OnScanDone();
	};
}