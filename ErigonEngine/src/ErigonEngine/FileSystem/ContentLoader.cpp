#include "eepch.h"
#include "ContentLoader.h"
#include "ErigonEngine/Core/Core.h"
#include "IContent.h"
#include "ErigonEngine/Renderer/Texture.h"

namespace ErigonEngine::Content::Internal
{
	Ref<IContent> ContentLoader::Load(std::string& path, ContentType contentType)
	{
		switch (contentType)
		{
		case ContentType::Texture:
			return std::static_pointer_cast<IContent>(Texture2D::Create(path));
			break;
		case ContentType::Binary:
			break;
		case ContentType::Material:
			break;
		}
	}
}