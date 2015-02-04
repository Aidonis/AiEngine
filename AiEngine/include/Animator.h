#include <string>
#include <map>
#include "tinyxml2\tinyxml2.h"

struct AniSprite
{
	std::string Name;
	float width, height;
	float x0, x1, y0, y1;
};
struct Atlas{
	float width, height;
	std::string sSheet;
	std::string sAnimations;
};

class Animator{
public:


	std::map<std::string, AniSprite> mSprites;
	Atlas atlas;

	void Animator::LoadSprites(const char* a_pSpriteSheet)
	{
		/*
		XML structure
		- Element "atlas"			the root element
		- - Attribute "width"		attribute of atlas Element
		- - Attribute "height"		attribute of atlas Element
		- - Attribute "sheet"		attribute of atlas Element
		- - Attribute "animations"	attribute of atlas Element

		- -	Element "sprite"		child of atlas Element
		- - - Attribute "name"		attribute of sprite Element
		- - - Attribute "x"			attribute of sprite Element
		- - - Attribute "y"			attribute of sprite Element
		- - - Attribute "width"		attribute of sprite Element
		- - - Attribute "height"	attribute of sprite Element
		*/
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLNode *rootNode, *currentNode;
		tinyxml2::XMLElement *childElement;
		std::string str;
		doc.LoadFile(a_pSpriteSheet); // load the document
		rootNode = doc.FirstChildElement("atlas");// set the root node
		currentNode = rootNode;

		//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
		childElement = currentNode->ToElement();
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
};