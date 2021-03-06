#include "Rail.h"
#include "Mesh.h"

using namespace engine;

Rail::Rail()
{
}


Rail::~Rail()
{
}

void Rail::generate(float length)
{
	setMesh(new Cylinder(0.5f, 0.5f, 4, glm::vec3(0.6901f, 0.7686f, 0.8705f), glm::vec3(length/0.707f, 1.0f, 1.0f)));
	mesh->loadTexture("railTexture.jpg");
	mesh->init();
}

void Rail::update(float delta_time, glm::mat4 trans)
{
	Node::update(delta_time, trans);
}