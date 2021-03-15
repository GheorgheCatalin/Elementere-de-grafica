#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	translateX2 = 0;
	translateY2 = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	angularStep = 0;
	angularStep2 = 0;

	translateStepY = 10;
	translateStepX = 100;
	scaleStep = 0.02;

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 0));
	AddMeshToList(square4);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	if (translateY >= 400) {
		translateStepY = -10;
	}
	else if (translateY <= 0) {
		translateStepY = 10;
	}
	translateY += translateStepY * 35 * deltaTimeSeconds;

	if (scaleX >= 2) {
		scaleStep -= 0.02;
	}
	else if (scaleX <= 1){
		scaleStep += 0.02;
	}
	scaleX += scaleStep * 35 * deltaTimeSeconds;
	scaleY += scaleStep * 35 * deltaTimeSeconds;


	if (translateX2 >= 400) {
		translateStepX = -100;
	}
	else if (translateX2 <= 100) {
		translateStepX = 100;
	}
	


	angularStep = fmod((angularStep + M_PI  * deltaTimeSeconds ), 2 * M_PI);
	angularStep2 = fmod((angularStep2 + M_PI * deltaTimeSeconds / 4), M_PI);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, 250);
	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
	modelMatrix *= Transform2D::Translate(translateX, translateY);

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(450, 250);
	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	//Matrix = Translatie2 * Scalare * Transaltie1;
	modelMatrix *= Transform2D::Translate(50, 50);
	modelMatrix *= Transform2D::Scale(scaleX, scaleY);
	modelMatrix *= Transform2D::Translate(-50, -50);
	
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(650, 250);
	//modelMatrix *= Transform2D::Translate(650, 250);
	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	modelMatrix *= Transform2D::Translate(50, 50);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-50, -50);
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	translateX2 += translateStepX * deltaTimeSeconds;
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150 , 50);
	modelMatrix *= Transform2D::Translate(translateX2, 0);
	modelMatrix *= Transform2D::Rotate2(-angularStep2);
	modelMatrix *= Transform2D::Translate(50, 0);
	//modelMatrix *= Transform2D::Translate(100, 0);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
	
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
