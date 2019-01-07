#include "LeverBase.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

LeverBase::LeverBase()
{
}

LeverBase::~LeverBase()
{
}

void LeverBase::generate()
{
	mesh = new RightRegularPrism(5.0f, 1.0f, 4, glm::vec3(0.0f, 0.5f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

	addChild(&leverCon);
	leverCon.generate();
	leverCon.position = glm::vec3(0.0f, 5.15f, -0.2f);

	mesh->init();
}

void LeverBase::update(float delta_time, glm::mat4 trans)
{
	leverCon.rotation.y += leverCon.angle;
	if (leverCon.rotation.y >= 30.0f)
		leverCon.angle *= -1.0f;
	else if(leverCon.rotation.y <= -30.0f)
		leverCon.angle *= -1.0f;
		
	Node::update(delta_time, trans);
}