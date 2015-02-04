#include "Animator.h"

Animator::Animator(){

}

Animator::~Animator(){

}

void Animator::Update(){

}

void Animator::SetSprite(std::string a_Sprite){
	m_UVData[0].x = mSprites[a_Sprite].x0;
	m_UVData[0].y = mSprites[a_Sprite].y0;
	m_UVData[1].x = mSprites[a_Sprite].x1;
	m_UVData[1].y = mSprites[a_Sprite].y1;
	m_SpriteScale.x = mSprites[a_Sprite].width;
	m_SpriteScale.y = mSprites[a_Sprite].height;
}

void Animator::SetUVData(glm::vec2 * a_data)
{
	a_data[0].x = m_UVData[0].x / atlas.width;
	a_data[0].y = m_UVData[0].y / atlas.height;
	a_data[1].x = m_UVData[1].x / atlas.width;
	a_data[1].y = m_UVData[0].y / atlas.height;
	a_data[2].x = m_UVData[0].x / atlas.width;
	a_data[2].y = m_UVData[1].y / atlas.height;
	a_data[3].x = m_UVData[1].x / atlas.width;
	a_data[3].y = m_UVData[1].y / atlas.height;

}

void Animator::LoadSprites(const char* a_SpriteSheet){

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	
	if (doc.LoadFile(a_SpriteSheet) != tinyxml2::XML_NO_ERROR)
	{
		doc.PrintError();
	}// load the doc

	rootNode = doc.FirstChildElement("atlas"); //Set root node
	currentNode = rootNode;

	childElement = rootNode->ToElement();
	atlas.width = (float)childElement->IntAttribute("width");
	atlas.height = (float)childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("sheet");
	atlas.sAnimations = childElement->Attribute("animations");

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		mSprites[str].Name = str;
		mSprites[str].x0 = childElement->IntAttribute("x0");
		mSprites[str].x1 = childElement->IntAttribute("x1");
		mSprites[str].y0 = childElement->IntAttribute("y0");
		mSprites[str].y1 = childElement->IntAttribute("y1");
		mSprites[str].height = mSprites[str].y1 - mSprites[str].y0;
		mSprites[str].width = mSprites[str].x1 - mSprites[str].x0;
	}
std:printf("Sprite load done!\n");
}