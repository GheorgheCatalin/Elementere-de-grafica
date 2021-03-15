#include "Tema1.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	angularStep = 0;
	arrowSpeed = 0;
	drawSpeed = 0;
	lives = 3;
	score = 0;

	bowX = 30;	
	bowY = 350;
	arrowX = 0;
	arrowY = 0;

	balloonR1Y = -70;
	balloonR2Y = -250;
	balloonR3Y = -500;
	balloonY1Y = -170;
	balloonY2Y = -370;
	// Generare random a baloanelor in intervalul [400, 1200]
	balloonR1X = rand() % 800 + 400;
	balloonR2X = rand() % 800 + 400;
	balloonR3X = rand() % 800 + 400;
	balloonY1X = rand() % 800 + 400;
	balloonY2X = rand() % 800 + 400;	

	shuriken1X = 1300;
	shuriken2X = 1700;
	shuriken1Y = rand() % 660 + 30;
	shuriken2Y = rand() % 660 + 30;

	hitR1 = false; hitR2 = false; hitR3 = false; hitY1 = false; 
	hitY2 = false; hitS1 = false; hitS2 = false; bowHitS1 = false; bowHitS2 = false;
	destroyedR1 = false; destroyedR2 = false; destroyedR3 = false; 
	destroyedY1 = false; destroyedY2 = false; destroyedS1 = false; destroyedS2 = false;
	released = false;

	scaleR1X = 37; scaleR2X = 37; scaleR3X = 37; scaleR1Y = 37; scaleR2Y = 37; scaleR3Y = 37;
	scaleY1X = 37;  scaleY2X = 37;  scaleY3X = 37;  scaleY1Y = 37;  scaleY2Y = 37;
	scaleS1X = 20;  scaleS2X = 20;  scaleS1Y = 20;  scaleS2Y = 20;

	Mesh* balloonR = Object2D::CreateBalloon("balloonR", glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	AddMeshToList(balloonR);

	Mesh* balloonY = Object2D::CreateBalloon("balloonY", glm::vec3(0, 0, 0), glm::vec3(1, 1, 0));
	AddMeshToList(balloonY);
	
	Mesh* string = Object2D::CreateString("string", glm::vec3(0, 0, 0), glm::vec3(0.6, 0.6, 0.6));
	AddMeshToList(string);

	Mesh* bow = Object2D::CreateBow("bow", glm::vec3(0, 0, 0));
	AddMeshToList(bow); 

	Mesh* arrow = Object2D::CreateArrow("arrow", glm::vec3(0, 0, 0));
	AddMeshToList(arrow);

	Mesh* shuriken = Object2D::CreateShuriken("shuriken", glm::vec3(0, 0, 0));
	AddMeshToList(shuriken);

	Mesh* rectangle1 = Object2D::CreateSquare("rectangle1", glm::vec3(0, 0, 0), 2 , glm::vec3(1, 0, 0), true);
	AddMeshToList(rectangle1);

	Mesh* rectangle2 = Object2D::CreateSquare("rectangle2", glm::vec3(0, 0, 0), 2, glm::vec3(1, 0, 0), false);
	AddMeshToList(rectangle2);

	Mesh* heart = Object2D::CreateDisk("heart", glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	AddMeshToList(heart);
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Hit(float deltaTimeSeconds)
{
	// Check if targets are hit, if so scale them untill they disappear
	if (hitR1) {
		scaleR1X -= 30 * deltaTimeSeconds;
		scaleR1Y -= 30 * deltaTimeSeconds;
		if (scaleR1X < 0) {
			destroyedR1 = true;
			hitR1 = false;
		}
	}

	if (hitR2) {
		scaleR2X -= 30 * deltaTimeSeconds;
		scaleR2Y -= 30 * deltaTimeSeconds;
		if (scaleR2X < 0) {
			destroyedR2 = true;
			hitR2 = false;
		}
	}

	if (hitR3) {
		scaleR3X -= 30 * deltaTimeSeconds;
		scaleR3Y -= 30 * deltaTimeSeconds;
		if (scaleR3X < 0) {
			destroyedR3 = true;
			hitR3 = false;
		}
	}

	if (hitY1) {
		scaleY1X -= 30 * deltaTimeSeconds;
		scaleY1Y -= 30 * deltaTimeSeconds;
		if (scaleY1X < 0) {
			destroyedY1 = true;
			hitY1 = false;
		}
	}

	if (hitY2) {
		scaleY2X -= 30 * deltaTimeSeconds;
		scaleY2Y -= 30 * deltaTimeSeconds;
		if (scaleY2X < 0) {
			destroyedY2 = true;
			hitY2 = false;
		}
	}

	if (hitS1) {
		scaleS1X -= 30 * deltaTimeSeconds;
		scaleS1Y -= 30 * deltaTimeSeconds;
		if (scaleS1X < 0) {
			destroyedS1 = true;
			hitS1 = false;
		}
	}

	if (hitS2) {
		scaleS2X -= 30 * deltaTimeSeconds;
		scaleS2Y -= 30 * deltaTimeSeconds;
		if (scaleS2X < 0) {
			destroyedS2 = true;
			hitS2 = false;
		}
	}
}

void Tema1::OutOfScene(float deltaTimeSeconds)
{
	// Check if object is out of scene, if so respawn it at a new random position
	if (balloonR1Y > 820 || destroyedR1) {
		balloonR1Y = -50;
		balloonR1X = rand() % 800 + 400;
		destroyedR1 = false;
		hitR1 = false;
		scaleR1X = 37;
		scaleR1Y = 37;
	}

	if (balloonR2Y > 820 || destroyedR2) {
		balloonR2Y = -80;
		balloonR2X = rand() % 800 + 400;
		destroyedR2 = false;
		hitR2 = false;
		scaleR2X = 37;
		scaleR2Y = 37;
	}

	if (balloonR3Y > 820 || destroyedR3) {
		balloonR3Y = -70;
		balloonR3X = rand() % 800 + 400;
		destroyedR3 = false;
		hitR3 = false;
		scaleR3X = 37;
		scaleR3Y = 37;
	}

	if (balloonY1Y > 820 || destroyedY1) {
		balloonY1Y = -50;
		balloonY1X = rand() % 800 + 400;
		destroyedY2 = false;
		hitY1 = false;
		scaleY1X = 37;
		scaleY1Y = 37;
	}

	if (balloonY2Y > 820 || destroyedY2) {
		balloonY2Y = -70;
		balloonY2X = rand() % 800 + 400;
		destroyedY2 = false;
		hitY2 = false;
		scaleY2X = 37;
		scaleY2Y = 37;
	}
	
	if (shuriken1X < 0 || destroyedS1 || bowHitS1) {
		shuriken1X = 1300;
		shuriken1Y = rand() % 660 + 30;
		destroyedS1 = false;
		hitS2 = false;
		bowHitS1 = false;
		scaleS1X = 20;
		scaleS1Y = 20;
	}

	if (shuriken2X < 0 || destroyedS2 || bowHitS2) {
		shuriken2X = 1500;
		shuriken2Y = rand() % 660 + 30;
		destroyedS2 = false;
		hitS2 = false;
		bowHitS2 = false;
		scaleS2X = 20;
		scaleS2Y = 20;
	}

	if (arrowX > 1380 || arrowY > 760 || arrowY < 0) {
		released = false;
		arrowX = 0;
		arrowY = 0;
	}
}

void Tema1::CheckCollision()
{
	// Make hit variable true for further use, and change score
	if (pow((arrowX - balloonR1X), 2) / pow(37, 2) + pow((arrowY - balloonR1Y), 2) / pow((1.3 * 37), 2) <= 1 && !hitR1) {
		hitR1 = true;
		score += 10;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - balloonR2X), 2) / pow(37, 2) + pow((arrowY - balloonR2Y), 2) / pow((1.3 * 37), 2) <= 1 && !hitR2) {
		hitR2 = true;
		score += 10;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - balloonR3X), 2) / pow(37, 2) + pow((arrowY - balloonR3Y), 2) / pow((1.3 * 37), 2) <= 1 && !hitR3) {
		hitR3 = true;
		score += 10;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - balloonY1X), 2) / pow(37, 2) + pow((arrowY - balloonY1Y), 2) / pow((1.3 * 37), 2) <= 1 && !hitY1) {
		hitY1 = true;
		score -= 5;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - balloonY2X), 2) / pow(37, 2) + pow((arrowY - balloonY2Y), 2) / pow((1.3 * 37), 2) <= 1 && !hitY2) {
		hitY2 = true;
		score -= 5;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - shuriken1X), 2) / pow(20, 2) + pow((arrowY - shuriken1Y), 2) / pow(20, 2) <= 1 && !hitS1) {
		hitS1 = true;
		score += 3;
		cout << "Score = " << score << "\n";
	}
	if (pow((arrowX - shuriken2X), 2) / pow(20, 2) + pow((arrowY - shuriken2Y), 2) / pow(20, 2) <= 1 && !hitS2) {
		hitS2 = true;
		score += 3;
		cout << "Score = " << score << "\n";
	}

	if (shuriken1X >= bowX && !hitS1 &&
		pow((shuriken1X - 20 - bowX), 2) / pow(37, 2) + pow((shuriken1Y - bowY), 2) / pow(94, 2) <= 1) {
		lives--;
		bowHitS1 = true;
		cout << "LIVES = " << lives << "\n";
	}
	if (shuriken2X >= bowX && !hitS2 &&
		pow((shuriken2X - 20 - bowX), 2) / pow(37, 2) + pow((shuriken2Y - bowY), 2) / pow(94, 2) <= 1) {
		lives--;
		bowHitS2 = true;
		cout << "LIVES = " << lives << "\n";
	}
}

void Tema1::Update(float deltaTimeSeconds)
{
	angularStep += 1.5 * M_PI * deltaTimeSeconds;

	balloonR1Y += 190 * deltaTimeSeconds;
	balloonR2Y += 190 * deltaTimeSeconds;
	balloonR3Y += 190 * deltaTimeSeconds;
	balloonY1Y += 190 * deltaTimeSeconds;
	balloonY2Y += 190 * deltaTimeSeconds;
	shuriken1X -= 230 * deltaTimeSeconds;
	shuriken2X -= 230 * deltaTimeSeconds;

	// Get mouse angle
	mouseY = resolution.y - window->GetCursorPosition().y - 2;
	mouseX = window->GetCursorPosition().x;
	if (mouseX > bowX) {
		angle = atan((mouseY - bowY) / (mouseX - bowX));
	}

	// Check if targets have been hit
	Hit(deltaTimeSeconds);
	// Check if target objects are out of scene, if so respawn them at random positions
	OutOfScene(deltaTimeSeconds);
	
	// Balon rosu 1
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR1X, balloonR1Y);
	modelMatrix *= Transform2D::Scale(scaleR1X, scaleR1Y);
	RenderMesh2D(meshes["balloonR"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR1X, balloonR1Y - 50 + (40 - scaleR1Y));
	modelMatrix *= Transform2D::Scale(scaleR1X, scaleR1Y);
	RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);
	// Balon rosu 2
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR2X, balloonR2Y);
	modelMatrix *= Transform2D::Scale(scaleR2X, scaleR2Y);
	RenderMesh2D(meshes["balloonR"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR2X, balloonR2Y - 50 + (40 - scaleR2Y));
	modelMatrix *= Transform2D::Scale(scaleR2X, scaleR2Y);
	RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);
	// Balon rosu 3
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR3X, balloonR3Y);
	modelMatrix *= Transform2D::Scale(scaleR3X, scaleR3Y);
	RenderMesh2D(meshes["balloonR"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonR3X, balloonR3Y - 50 + (40 - scaleR3Y));
	modelMatrix *= Transform2D::Scale(scaleR3X, scaleR3Y);
	RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);
	// Balon galben 1
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonY1X, balloonY1Y);
	modelMatrix *= Transform2D::Scale(scaleY1X, scaleY1Y);
	RenderMesh2D(meshes["balloonY"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonY1X, balloonY1Y - 50 + (40 - scaleY1Y));
	modelMatrix *= Transform2D::Scale(scaleY1X, scaleY1Y);
	RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);
	// Balon galben 2
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonY2X, balloonY2Y);
	modelMatrix *= Transform2D::Scale(scaleY2X, scaleY2Y);
	RenderMesh2D(meshes["balloonY"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(balloonY2X, balloonY2Y - 50 + (40 - scaleY2Y));
	modelMatrix *= Transform2D::Scale(scaleY2X, scaleY2Y);
	RenderMesh2D(meshes["string"], shaders["VertexColor"], modelMatrix);

	// Shuriken1
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(shuriken1X, shuriken1Y);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Scale(scaleS1X, scaleS1Y);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
	// Shuriken 2
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(shuriken2X, shuriken2Y);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Scale(scaleS2X, scaleS2Y);
	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

	// Power bar
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bowX - 5, bowY - 95);
	modelMatrix *= Transform2D::Scale(3 + drawSpeed/3, 5);
	RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bowX - 5, bowY - 95);
	modelMatrix *= Transform2D::Scale(23, 5);
	RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

	// Bow
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bowX, bowY);
	modelMatrix *= Transform2D::Rotate(angle);	
	modelMatrix *= Transform2D::Scale(40, 40);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	// Arrow
	modelMatrix = glm::mat3(1);
	if (!released) {
		modelMatrix *= Transform2D::Translate(bowX, bowY);
		modelMatrix *= Transform2D::Rotate(angle);		
	}
	else {
		modelMatrix *= Transform2D::Translate(arrowX, arrowY);
		modelMatrix *= Transform2D::Rotate(arrowAngle);	

		arrowX += 27 * arrowSpeed * deltaTimeSeconds * cos(arrowAngle);
		arrowY += 27 * arrowSpeed * deltaTimeSeconds * sin(arrowAngle);
	}
	modelMatrix *= Transform2D::Translate(70, 0);
	modelMatrix *= Transform2D::Scale(12, 12);
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	
	for (int i = 0; i < lives; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(bowX + 15 * i - 5, bowY + 95);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}

	// Check collision
	CheckCollision();

	if (lives == 0) {
		cout << "\n---------------GAME OVER---------------\n---------------Score: " << score << "--------------";
		exit(0);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (bowY < 635) {
			bowY += 300 * deltaTime;
		}
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		if (bowY > 85){
			bowY -= 300 * deltaTime;
		}
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (drawSpeed < 60 && !released)
			drawSpeed += 1;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		released = false;
		//arrowX = 0;
		//arrowY = 0;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (!released) {
		arrowAngle = angle;
		arrowX = bowX;
		arrowY = bowY;
		arrowSpeed = drawSpeed;
		drawSpeed = 0;
		released = true;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	//mouseX = window->GetCursorPosition().x;
	//mouseY = window->GetCursorPosition().y;

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
