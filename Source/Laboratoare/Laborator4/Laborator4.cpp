#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	translateStepX = 0.05;
	translateStepY = 0.05;
	translateXSun = 0;
	translateYSun = 0;

	angularStep = 0;

	rEarth = 4;
	rMoon = 2;
 }

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	if (translateXSun >= 18) {
		translateStepX = -0.05;
		translateStepY = -0.05;
	}
	else if (translateXSun <= -15) {
		translateStepX = 0.05;
		translateStepY = 0.05;
	}
	translateXSun += translateStepX * 20 * deltaTimeSeconds;
	translateYSun += translateStepY * 20 * deltaTimeSeconds;

	angularStep = fmod((angularStep + M_PI * deltaTimeSeconds / 8), 2 * M_PI);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f,-1.5f);
	modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	//Soare
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 2.5f, -1.5f);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, 0);
	modelMatrix *= Transform3D::RotateOY(angularStep);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	//Pamant
	modelMatrix = glm::mat4(1);
	//Coordonate Soare
	modelMatrix *= Transform3D::Translate(-2.5f, 2.5f, -1.5f);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, 0);
	modelMatrix *= Transform3D::RotateOY(angularStep);
	//Rotatie in jurul soarelui
	modelMatrix *= Transform3D::RotateOY(angularStep * 2);
	modelMatrix *= Transform3D::Translate(rEarth, 0, 0);
	//Rotatie in jurul axei
	modelMatrix *= Transform3D::RotateOY(angularStep * 2);

	modelMatrix *= Transform3D::Scale(0.75, 0.75, 0.75);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	//Luna
	modelMatrix = glm::mat4(1);
	//Coordonate Pamant 
	modelMatrix *= Transform3D::Translate(-2.5f, 2.5f, -1.5f);
	modelMatrix *= Transform3D::Translate(translateXSun, translateYSun, 0);
	modelMatrix *= Transform3D::RotateOY(angularStep);
	modelMatrix *= Transform3D::RotateOY(angularStep * 2);
	modelMatrix *= Transform3D::Translate(rEarth, 0, 0);
	modelMatrix *= Transform3D::RotateOY(angularStep * 2);
	//Rotatie in jurul Pamantului
	modelMatrix *= Transform3D::RotateOY(angularStep * 4);
	modelMatrix *= Transform3D::Translate(rMoon, 0, 0);
	//Rotatie in jurul axei
	modelMatrix *= Transform3D::RotateOY(angularStep* 4);

	modelMatrix *= Transform3D::Scale(0.5, 0.5, 0.5);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// TODO
	if (window->KeyHold(GLFW_KEY_W)) {
		translateZ -= 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		translateZ += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		translateX += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		translateX -= 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_R)) {
		translateY += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_F)) {
		translateY -= 2.5 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_1)) {
		scaleX += 2.5 * deltaTime;
		scaleY += 2.5 * deltaTime;
		scaleZ += 2.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_2)) {
		if (scaleX - 2.5 * deltaTime >= 0) {
			scaleX -= 2.5 * deltaTime;
			scaleY -= 2.5 * deltaTime;
			scaleZ -= 2.5 * deltaTime;
		}
	}

	if (window->KeyHold(GLFW_KEY_3)) {
		angularStepOX = fmod((angularStepOX + M_PI * deltaTime), 2 * M_PI);
	}
	if (window->KeyHold(GLFW_KEY_4)) {
		angularStepOX = fmod((angularStepOX - M_PI * deltaTime), 2 * M_PI);
	}
	if (window->KeyHold(GLFW_KEY_5)) {
		angularStepOY = fmod((angularStepOY + M_PI * deltaTime), 2 * M_PI);
	}
	if (window->KeyHold(GLFW_KEY_6)) {
		angularStepOY = fmod((angularStepOY - M_PI * deltaTime), 2 * M_PI);
	}
	if (window->KeyHold(GLFW_KEY_7)) {
		angularStepOZ = fmod((angularStepOZ + M_PI * deltaTime), 2 * M_PI);
	}
	if (window->KeyHold(GLFW_KEY_8)) {
		angularStepOZ = fmod((angularStepOZ - M_PI * deltaTime), 2 * M_PI);
	}


}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
