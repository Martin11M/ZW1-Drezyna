#pragma once

#include "Node.h"
#include "Draisine.h"

class Desert : public engine::Node
{
public:
	Desert();
	~Desert();

	void generate();
	virtual void update(float delta_time, glm::mat4 trans);

private:
	Draisine draisine;
	// Rails rails;
};

