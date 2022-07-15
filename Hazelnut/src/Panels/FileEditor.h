#pragma once
#include <filesystem>
#include "TextEditor/ImGuiColorTextEdit/TextEditor.h"

enum class FileType
{
	None = 0,
	Image,
	Text,
	Scene
};

FileType GetFileTypeFromExtension(std::string ext);

class FileEditor
{
public:
	
	void LoadFile(std::string filepath, FileType type, bool* close = nullptr);
	void Show();
	void ShowEditor();
	void ShowImage();
private:
	std::string m_FilePath;
	FileType m_FileType;
	bool* m_ShouldClose;
	TextEditor m_editor;
	std::string m_FileSrc;
};
