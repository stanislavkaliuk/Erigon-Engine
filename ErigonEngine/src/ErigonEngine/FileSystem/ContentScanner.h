#pragma once
#include "IContent.h"
#include "ContentDB.h"
#include <future>
#include <functional>

namespace ErigonEngine::Content::Internal
{
	class ContentScanner
	{
	public:
		static void ScanNow(std::vector<ContentMetaData>* contnentCollection, const char* contentFolderPath, std::function<void()> callback);
		static void ScanNow(std::vector<ContentMetaData>* contnentCollection, std::function<void()> callback);
	private:
		static void ScanAsync(std::vector<ContentMetaData>* contnentCollection, std::function<void()> callback);
	};
}