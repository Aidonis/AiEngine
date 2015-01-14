#include "Framework.h"
#include "Globals.h"

#include <iostream>

class Application
	: public AIF::Framework
{
public:
	Application()
	{

	}

	void Start()
	{

	}

	void Finish()
	{
		Shutdown();
	}


};