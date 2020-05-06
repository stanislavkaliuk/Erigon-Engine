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

	Ref<IContent> Content::Load(const char* name)
	{
		Internal::ContentMetaData metaData = Internal::ContentDB::GetContentData(std::string(name));
		if (metaData.IsEmpty())
		{
			return Ref<IContent>();
		}

		return Internal::ContentLoader::Load(metaData.path, metaData.contentType);
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