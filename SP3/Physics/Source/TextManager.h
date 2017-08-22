//#ifndef TEXTMANAGER_H
//#define TEXTMANAGER_H
//
//#include "SingletonTemplate.h"
//#include <map>
//#include <sstream>
//#include "RenderHelper.h"
//#include "Graphics.h"
//#include "Application.h"
//#include "LoadTGA.h"
//#include "Mesh.h"
//#include "LoadTextData.h"
//#include "FontType.h"
//#include "GlobalVariableManager.h"
//#include <utility>
//#include "Vector3.h"
//
////FOR DEBUGING PURPOSES
//class TextManager : public Singleton<TextManager>
//{
//	friend Singleton;
//	
//	std::map<int, std::string> text;
//	//Mesh* text_mesh;
//	
//public:
//	FontType calibri;
//	void add_text(int row, std::string text) {
//		this->text[row] = text;
//	}
//	void update_text(int row, std::string text) {
//		this->text.at(row) = text;
//	}
//	void render_all_text() {
//		float scale = 3.f;
//		//float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
//		//float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
//		float halfWindowWidth = *GlobalVariables::get()->worldWidth * 0.5f;
//		float halfWindowHeight = *GlobalVariables::get()->worldHeight * 0.5f;
//
//		for each(std::pair<int, std::string> t in text)
//		{
//
//			MS &ms = Graphics::getInstance()->modelStack;
//			ms.PushMatrix();
//			ms.Translate(-halfWindowWidth, scale * t.first - halfWindowHeight, 0);
//			ms.Scale(scale, scale, scale);
//			RenderHelper::RenderText(&calibri, t.second, Color(1, 1, 1));
//			ms.PopMatrix();
//		}
//		
//	}
//
//	Mesh* get_text_mesh()
//	{
//		//return text_mesh;
//	}
//
//protected:
//	TextManager() {
//		//text_mesh = EntityBase::getInstance()->getEntity("CALIBRI");
//		//calibri.mesh = text_mesh;
//		//calibri.textWidth = LoadTextData("Image//Calibri Data.csv");
//	};
//	virtual ~TextManager() {};
//};
//
//
//#endif