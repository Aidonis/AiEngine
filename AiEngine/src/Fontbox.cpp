#include "Fontbox.h"

Fontbox& Fontbox::Instance()
{
	if (MInstance == 0)
		MInstance = new Fontbox();
	return *MInstance;
}

Fontbox* Fontbox::MInstance = 0;

Fontbox::Fontbox(){
	glGenBuffers(1, &PositionBuffer);
	glGenBuffers(1, &ColorBuffer);
	glGenBuffers(1, &UVBuffer);
	glGenBuffers(1, &MatrixBuffer);
}

void Fontbox::LoadFont(const char* a_FontSheet){
	/*
	XML structure
	- Element "TextureAtlas"	the root element
	- - Attribute "imagePath"	attribute of TextureAtlas Element
	- - Attribute "width"		attribute of TextureAtlas Element
	- - Attribute "height"		attribute of TextureAtlas Element
	- -	Element "char"			child of TextureAtlas Element
	- - - Attribute "name"		attribute of char Element
	- - - Attribute "x"			attribute of char Element
	- - - Attribute "y"			attribute of char Element
	- - - Attribute "width"		attribute of char Element
	- - - Attribute "height"	attribute of char Element
	*/

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;

	char ch;
	if (doc.LoadFile(a_FontSheet) != tinyxml2::XML_NO_ERROR){
		doc.PrintError();
	}//Load Doc
	rootNode = doc.FirstChildElement("FontAtlas");//Set Root Node
	currentNode = rootNode;

	childElement = rootNode->ToElement();
	fontAtlas.sSheet = childElement->Attribute("imagePath");
	fontAtlas.v2Size.x = (float)childElement->IntAttribute("width");
	fontAtlas.v2Size.y = (float)childElement->IntAttribute("height");
	fontAtlas.kerning = (float)childElement->IntAttribute("kerningx");

	text.LoadTexture(fontAtlas.sSheet.c_str());
	text.s_Scale.x = fontAtlas.v2Size.x;
	text.s_Scale.y = fontAtlas.v2Size.y;

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		int id = childElement->IntAttribute("id");
		str = childElement->IntAttribute("id");
		ch = id;
		charMap[ch].id = str;
		charMap[ch].x0 = childElement->IntAttribute("x");
		charMap[ch].y0 = childElement->IntAttribute("y");
		charMap[ch].width = childElement->IntAttribute("width");
		charMap[ch].height = childElement->IntAttribute("height");
		charMap[ch].x1 = charMap[ch].x0 + charMap[ch].width;
		charMap[ch].y1 = charMap[ch].y0 + charMap[ch].height;
		charMap[ch].offset = childElement->IntAttribute("xoffset");
		
	}
std:printf("Font load done!\n");
}

void Fontbox::LoadStr(std::string str){
	Drawlist.clear();
	char ch;
	for (CharCount = 0; CharCount < str.length(); CharCount++){
		ch = str.at(CharCount);
		Drawlist.push_back(charMap[ch]);
		Char foo = charMap[ch];
	}
}

void Fontbox::DrawString(std::string str, glm::vec2 pos, float scale){
	LoadStr(str);

	Char ch;
	float newPos = 0;
	for (int i = 0; i < Drawlist.size(); i++){
		ch = Drawlist[i];
		if (i != 0){
			newPos = text.s_Position.x + ((ch.width / 2)*scale) + ((Drawlist[i - 1].width / 2) *scale) + fontAtlas.kerning;
			text.s_Position = glm::vec3(newPos, pos.y - (ch.offset*scale), 0.f);
		}
		else{
			text.s_Position = glm::vec3(pos.x + ((ch.width / 2) * scale), pos.y - (ch.offset*scale), 0.f);
		}
		text.s_UVData[0] = glm::vec2(ch.x0 / fontAtlas.v2Size.x, ch.y0 / fontAtlas.v2Size.y);
		text.s_UVData[1] = glm::vec2(ch.x1 / fontAtlas.v2Size.x, ch.y0 / fontAtlas.v2Size.y);
		text.s_UVData[2] = glm::vec2(ch.x0 / fontAtlas.v2Size.x, ch.y1 / fontAtlas.v2Size.y);
		text.s_UVData[3] = glm::vec2(ch.x1 / fontAtlas.v2Size.x, ch.y1 / fontAtlas.v2Size.y);

		text.s_Scale = glm::vec2(ch.width * scale, ch.height * scale);

		text.SetUVData();
		text.Update();
	}
}