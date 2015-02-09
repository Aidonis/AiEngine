#include "Fontbox.h"


void Fontbox::LoadFont(const char* a_FontSheet){

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;

	if (doc.LoadFile(a_FontSheet) != tinyxml2::XML_NO_ERROR)
	{
		doc.PrintError();
	}// load the doc

	rootNode = doc.FirstChildElement("atlas"); //Set root node
	currentNode = rootNode;

	childElement = rootNode->ToElement();
	fontAtlas.width = (float)childElement->IntAttribute("width");
	fontAtlas.height = (float)childElement->IntAttribute("height");
	fontAtlas.sSheet = childElement->Attribute("sheet");
	fontAtlas.sAnimations = childElement->Attribute("animations");

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