#include "eepch.h"
#include "ContentDB.h"

namespace ErigonEngine::Content::Internal
{
	static std::vector<ContentMetaData> contentData;

	void ContentDB::GetRequestedContentData(std::vector<Internal::ContentMetaData>* data, std::string& path)
	{
		std::for_each(contentData.begin(), contentData.end(), [path, data](ContentMetaData& item) mutable
			{
				if (item.path.find(path) != std::string::npos)
				{
					data->push_back(item);
				}
			});
	}

	bool ContentDB::IsContentExists(std::string& path)
	{
		std::vector<ContentMetaData>::iterator pos = std::find_if(contentData.begin(), contentData.end(), [&p = path](const ContentMetaData& data) {return data.path == p; });
		return pos != contentData.end();
	}

	ContentMetaData& ContentDB::GetContentData(std::string& path)
	{
		if (IsContentExists(path))
		{
			std::vector<ContentMetaData>::iterator it = std::find_if(contentData.begin(), contentData.end(), [&p = path](const ContentMetaData& data) {return data.path == p; });
			return *it;
		}

		EE_CORE_WARN("Content on path: " + path + " not exist");
		return ContentMetaData();
	}

	std::vector<ContentMetaData>* ContentDB::GetContentMetaData()
	{
		return &contentData;
	}
}
