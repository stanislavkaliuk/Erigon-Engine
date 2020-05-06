#include "eepch.h"
#include "ContentScanner.h"

namespace ErigonEngine::Content::Internal
{
	static const char* contentFolderPath;
	static std::vector<std::future<void>> scanTasks;

	void ContentScanner::ScanNow(std::vector<ContentMetaData>* contentCollection, const char* contentFolder, std::function<void()> callback)
	{
		contentFolderPath = contentFolder;
		ScanNow(contentCollection, callback);
	}

	void ContentScanner::ScanNow(std::vector<ContentMetaData>* contentCollection, std::function<void()> callback)
	{
		ScanAsync(contentCollection, callback);
	}

	static ContentType DetectExtensionType(std::string& extension)
	{
		if (extension == ".jpg" || extension == ".png")
		{
			return ContentType::Texture;
		}

		if (extension == ".egl")
		{
			return ContentType::Shader;
		}

		if (extension == ".emat")
		{
			return ContentType::Material;
		}

		if (extension == ".emap")
		{
			return ContentType::Map;
		}

		if (extension == ".enoded" || extension == ".dbon")//node editor or dragon bones file
		{
			return ContentType::Binary;
		}
	}

	static std::mutex scanMutex;

	static void BuildFileInfo(std::vector<ContentMetaData>* contentCollection, std::filesystem::directory_entry info)
	{
		if (!info.path().has_extension())
		{
			return;
		}
		ContentMetaData data;
		std::string extension = info.path().extension().string();
		data.path = info.path().string();
		data.name = info.path().filename().string();
		data.contentType = DetectExtensionType(extension);

		std::lock_guard<std::mutex> lock(scanMutex);
		contentCollection->push_back(data);
	}

	static void WaitForTasksDone(std::vector<std::future<void>>* tasks, std::function<void()> callback)
	{
		for (auto it = tasks->begin(); it != tasks->end(); it++)
		{
			it->get();
		}

		callback();
	}

	void ContentScanner::ScanAsync(std::vector<ContentMetaData>* contentCollection, std::function<void()> callback)
	{
		for (auto& file : std::filesystem::recursive_directory_iterator(contentFolderPath))
		{
			if (file.is_directory())
			{
				continue;
			}

			if (file.is_regular_file())
			{
				scanTasks.push_back(std::async(std::launch::async, BuildFileInfo, contentCollection, file));
			}
		}

		std::async(std::launch::async, WaitForTasksDone, &scanTasks, callback);
		
	}
}