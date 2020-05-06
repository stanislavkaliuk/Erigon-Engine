#pragma once
#include "ContentDB.h"

namespace ErigonEngine::Content::Internal
{
	class ContentLoader
	{
	public:
		static Ref<IContent> Load(std::string& path, ContentType contentType);
	};
}