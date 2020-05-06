#include "eepch.h"
#include "ContentDB.h"

namespace ErigonEngine::Content::Internal
{
	static std::vector<ContentMetaData> contentData;

	bool ContentDB::IsContentExists(std::string& name)
	{
		std::vector<ContentMetaData>::iterator pos = std::find_if(contentData.begin(), contentData.end(), [&n = name](const ContentMetaData& data) {return data.name == n; });
		return pos != contentData.end();
	}

	ContentMetaData& ContentDB::GetContentData(std::string& name)
	{
		if (IsContentExists(name))
		{
			std::vector<ContentMetaData>::iterator it = std::find_if(contentData.begin(), contentData.end(), [&n = name](const ContentMetaData& data) {return data.name == n; });
			return *it;
		}

		EE_CORE_WARN("Content: " + name + " not exist");
		return ContentMetaData();
	}

	std::vector<ContentMetaData>* ContentDB::GetContentMetaData()
	{
		return &contentData;
	}
}
