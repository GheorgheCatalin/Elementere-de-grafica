#include "Laborator1.h"

#include <math.h>
#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
	changeColor = false;
	cycle = 0;
	rotPos = glm::vec3(2, 0.5f, -2);
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box1");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box3");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters\\Archer", "Archer.fbx");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box4");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;
	
	// sets the clear color for the color buffer
	//glClearColor(0, 0, 0, 1);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);

	if (changeColor) {
		glClearColor(0, 1, 0, 0.2);
	}
	
	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	changeColor = false;

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	

	// render the object
	RenderMesh(meshes["box1"], rotPos, glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box1"], glm::vec3(-1, 0.5f, 0));

	// render the new object
	if (cycle == 0) {
		RenderMesh(meshes["box2"], glm::vec3(2, 0.5f, 0), glm::vec3(0.5f));
	} else if (cycle == 1) {
		RenderMesh(meshes["box3"], glm::vec3(2, 0.5f, 0), glm::vec3(0.01f));
	} else {
		RenderMesh(meshes["box4"], glm::vec3(2, 0.5f, 0), glm::vec3(0.5f));
	}

	RenderMesh(meshes["box3"], pos, glm::vec3(0.01f));

	t += deltaTimeSeconds * 1.5;
	rotPos.x = rotPos.x + 0.05 * cos(t);
	rotPos.y = rotPos.y + 0.05 * sin(t);
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		pos.z -= 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		pos.z += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		pos.x += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		pos.x -= 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_Q)) {
		pos.y += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_E)) {
		pos.y -= 2.5 * deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		changeColor = true;
	}

	if (key == GLFW_KEY_G) {
		clearColor.x = fmod(clearColor.x + 0.1, 1);
		clearColor.y = fmod(clearColor.y + 0.2, 1);
		clearColor.z = fmod(clearColor.z + 0.25, 1);
	}

	if (key == GLFW_KEY_C) {
		cycle = (cycle + 1) % 3;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
