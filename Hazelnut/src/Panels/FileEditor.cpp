#include "FileEditor.h"
#include "imgui/imgui.h"
#include <fstream>
#include <sstream>
#include "Hazel.h"


void FileEditor::LoadFile(std::string filepath, FileType type,bool* close)
{
	m_FilePath = filepath;
	m_FileType = type; 
	m_ShouldClose = close;
	m_FileSrc = "";
	std::ifstream file;
	file.open(filepath);
	if(file) // read the file code
	{
		std::stringstream ss;
		ss << file.rdbuf();
		m_FileSrc = ss.str();
	}
	m_editor.SetText(m_FileSrc);
}

void FileEditor::Show()
{
	if (m_FileType == FileType::Text)
		ShowEditor();
	else if (m_FileType == FileType::Image)
		ShowImage();
}

void FileEditor::ShowEditor()
{
	ImGui::Begin("Editor", nullptr);
	ImGui::TextDisabled(m_FilePath.c_str());
	m_editor.Render("TextEditor");
	ImGui::End();
}

void FileEditor::ShowImage()
{
	ImGui::Begin("Editor", nullptr);
	ImGui::TextDisabled(m_FilePath.c_str());
	static Hazel::Ref<Hazel::Texture2D> image = Hazel::Texture2D::Create(m_FilePath);
	ImGui::Image((void*)image->GetRendererID(), { (float)image->GetWidth(),(float)image->GetHeight() });
	ImGui::End();
}

FileType GetFileTypeFromExtension(std::string ext)
{
	if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp") return FileType::Image;
	else if (ext == ".txt" /* || ext == ".vert" || ext == ".frag" */ || ext == ".glsl") return FileType::Text;
	else if (ext == ".hazel") return FileType::Scene;
	return FileType::None;
}
