#include "World.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "App.h"

World::World()
{
	ambientStrength = 0.2f;
}

World::~World()
{
}

void World::init(float aspect_ratio)
{
	// Najpierw shader, bo potem r�ne rzeczy s� do niego �adowane
	setCurrentShaderProgram(new engine::ShaderProgram("default.vert", "default.frag"));
	
	shader_program->Use();

	// Potem RootNode
	setRootNode(&desert);

	desert.generate();
	// I ca�a reszta

	camera.setScene(this);

	camera.set(glm::vec3(50.0f, -1.5f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f));
	
	Scene::init(aspect_ratio);

	skybox = new SkyBox();
	skybox->setScene(this);
	skybox->generate(900.0f, glm::vec3(0.2f, 0.35f, 0.7f), "skybox.png");
}

void World::render()
{	
	Scene::render();
}

void World::update(float delta_time, const Input& input)
{	
	static unsigned int light_index = 0;
	static float light_sens = 100;

	if (input.keyboard.keys_pressed[GLFW_KEY_0])
		light_index = 0;
	if (input.keyboard.keys_pressed[GLFW_KEY_1])
		light_index = 1;
	if (input.keyboard.keys_pressed[GLFW_KEY_2])
		light_index = 2;
	if (input.keyboard.keys_pressed[GLFW_KEY_3])
		light_index = 3;
	if (input.keyboard.keys_pressed[GLFW_KEY_4])
		light_index = 4;
	if (input.keyboard.keys_pressed[GLFW_KEY_5])
		light_index = 5;
	if (input.keyboard.keys_pressed[GLFW_KEY_6])
		light_index = 6;
	if (input.keyboard.keys_pressed[GLFW_KEY_7])
		light_index = 7;
	if (input.keyboard.keys_pressed[GLFW_KEY_8])
		light_index = 8;
	if (input.keyboard.keys_pressed[GLFW_KEY_9])
		light_index = 9;

	if (input.keyboard.keys_pressed[GLFW_KEY_U])
		ambientStrength -= delta_time * 0.5f;
	if (input.keyboard.keys_pressed[GLFW_KEY_I])
		ambientStrength += delta_time * 0.5f;
	if (lights.size() > light_index) {
		light_sens = lights[light_index]->intensity / 2.0f;

		if (light_sens < 10.0f)
			light_sens = 10.0f;

		if (light_index >= 5) {
			for (unsigned int i = 5; i < lights.size(); ++i) {
				if (input.keyboard.keys_pressed[GLFW_KEY_J])
					lights[i]->intensity -= delta_time * light_sens;
				if (input.keyboard.keys_pressed[GLFW_KEY_K])
					lights[i]->intensity += delta_time * light_sens;
				if (lights[i]->intensity < 0)
					lights[i]->intensity = 0;
				if (input.keyboard.keys_pressed[GLFW_KEY_H]) {
					lights[i]->intensity = lights[i]->default_intens;
				}
			}
		}
		else 
		{
			if (input.keyboard.keys_pressed[GLFW_KEY_J])
				lights[light_index]->intensity -= delta_time * light_sens;
			if (input.keyboard.keys_pressed[GLFW_KEY_K])
				lights[light_index]->intensity += delta_time * light_sens;
			if (lights[light_index]->intensity < 0)
				lights[light_index]->intensity = 0;
			if (input.keyboard.keys_pressed[GLFW_KEY_H]) {
				lights[light_index]->intensity = lights[light_index]->default_intens;
			}
		}
	}

	if (ambientStrength < 0.0f)
		ambientStrength = 0.0f;
	if (ambientStrength > 1.0f)
		ambientStrength = 1.0f;
	
	if (input.keyboard.keys_pressed[GLFW_KEY_P])
		f_pause = true;
	if (input.keyboard.keys_pressed[GLFW_KEY_O])
		f_pause = false;

	Scene::update(delta_time, input);
}