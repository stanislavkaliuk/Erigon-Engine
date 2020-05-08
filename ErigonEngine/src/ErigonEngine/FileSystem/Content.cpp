#include "eepch.h"
#include "Content.h"
#include "ContentDB.h"
#include "ContentScanner.h"
#include "ContentLoader.h"

namespace ErigonEngine::Content
{
	static bool IsContentMapReady;
	static bool IsContentDirty;

	void Content::Init()
	{
		IsContentMapReady = false;
		Internal::ContentScanner::ScanNow(Internal::ContentDB::GetContentMetaData(), "assets", std::bind(&Content::OnScanDone));
	}

	Ref<IContent> Content::Load(const char* path)
	{
		Internal::ContentMetaData metaData = Internal::ContentDB::GetContentData("assets\\" + std::string(path));
		if (metaData.IsEmpty())
		{
			return Ref<IContent>();
		}

		return Internal::ContentLoader::Load(metaData.path, metaData.contentType);
	}

	std::vector<Ref<IContent>> Content::LoadAll(const char* path)
	{
		std::vector<Ref<IContent>> loadedContent;
		auto wholepath = std::filesystem::path("assets\\" + std::string(path));
		if (!std::filesystem::is_directory(wholepath))
		{
			if (std::filesystem::is_regular_file(wholepath))
			{
				loadedContent.push_back(Load(path));
				return loadedContent;
			}
			else
			{
				EE_CORE_WARN("Cannot detect supported content at path: " + wholepath.string());
			}
		}
		std::vector<Internal::ContentMetaData> contentMetaData;
		Internal::ContentDB::GetRequestedContentData(&contentMetaData, wholepath.string());
		for (auto it = contentMetaData.begin(); it != contentMetaData.end(); it++)
		{
			loadedContent.push_back(Internal::ContentLoader::Load(it->path, it->contentType));
		}
		return loadedContent;
	}

	std::future<Ref<IContent>> Content::LoadAsync(const char* path)
	{
		return std::async(std::launch::async, Load, path);
	}

	bool Content::UnloadContent(Ref<IContent> contentToUnload)
	{
		contentToUnload.reset();
		return true;
	}


	inline void Content::SetAsDirty()
	{
		IsContentDirty = true;
	}

	inline bool Content::IsDirty()
	{
		return IsContentDirty;
	}

	void Content::OnScanDone()
	{
		IsContentMapReady = true;
	}
}