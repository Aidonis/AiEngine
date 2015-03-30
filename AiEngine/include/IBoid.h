#ifndef _I_BOID_H_
#define _I_BOID_H_

#include "glm\glm.hpp"

class IBoid{
public:
	virtual glm::vec2& GetVelocity() = 0;
	virtual glm::vec2& GetPosition() = 0;
	virtual float GetMaxVelocity() = 0;
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
	
};

#endif //_I_BOID_H_