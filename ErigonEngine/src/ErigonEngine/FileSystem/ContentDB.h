#pragma once
#include "ErigonEngine/Log/Log.h"
#include "IContent.h"
#include <string>
#include <vector>

namespace ErigonEngine::Content::Internal
{
	struct ContentMetaData
	{
		ContentType contentType;
		std::string name;
		std::string path;

		bool IsEmpty()
		{
			return name.empty() || path.empty();
		}
	};

	class ContentDB
	{
	public:
		static void GetRequestedContentData(std::vector<Internal::ContentMetaData>* contentData, std::string& path);
		static bool IsContentExists(std::string& path);
		static ContentMetaData& GetContentData(std::string& path);
		static std::vector<ContentMetaData>* GetContentMetaData();
	};
}
