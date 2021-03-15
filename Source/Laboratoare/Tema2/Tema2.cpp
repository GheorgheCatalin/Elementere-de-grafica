#include "Tema2.h"
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "Transform3D2.h"
#include <Core/Engine.h>

using namespace std;
#define platforms 18

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	cstY = 1.25; //Constanta Y camera
	cameraDistance = 3.2; //Constanta distanta camera 3rd person 
	platformMax = 15;
	counter = 0;
	redCounter = 6; //Primele 6 platforme nu pot fi rosii
	scale = 1;
	fuel = 200;

	sphereX = 0; sphereY = 0.5; /*1*/ sphereZ = 0; //0
	platformY = -0.03;
	spawnZ = 3.5;
	speed = 0;
	speedCounter = 0;
	highSpeed = 20;
	deformation = 0;
	deformationCounter = 0;

	renderCameraTarget = true;
	jump = false;
	fall = false;
	
	red = glm::vec3(0.9, 0.05, 0.05);
	green = glm::vec3(0.05, 0.9, 0.05);
	blue = glm::vec3(0.05, 0.05, 0.9);
	purple = glm::vec3(0.5, 0.2, 0.7);
	orange = glm::vec3(1, 0.45, 0);
	yellow = glm::vec3(0.9, 0.9, 0);

	camera = new Laborator::Camera2();
	camera->Set(glm::vec3(sphereX, sphereY + cstY, sphereZ + cameraDistance), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	Mesh* square = Object2D::CreateSquare("square", glm::vec3(0, 0, 0), 1, glm::vec3(0.9, 0.9, 0.9), true);
	AddMeshToList(square);

	Mesh* square2 = Object2D::CreateSquare("square2", glm::vec3(0, 0, 0), 1, glm::vec3(0.9, 0.4, 0.1), true);
	AddMeshToList(square2);

	// Shader
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	srand(time(NULL));

	// Generare platforme
	for (int i = 0; i < platforms; i ++) {
		float randomZ = ((float)rand()) / (float)(RAND_MAX / 6) + (platformMax - 6);
		platformSize.push_back(randomZ);
	}
	for (int i = 0; i < platforms - 2; i += 3) {
		platformZ.push_back(spawnZ);
		platformZ.push_back(spawnZ);
		platformZ.push_back(spawnZ);
		platformX.push_back(-3.5);
		platformX.push_back(0);
		platformX.push_back(3.5);
		spawnZ += platformMax;
	}

	// Primele 3 platforme sunt albastre, dupa care celelalte au culori generate aleator
	platformType.push_back(blue); platformType.push_back(blue); platformType.push_back(blue);
	for (int i = 2; i < platforms; i++) {
		int randomColor = rand() % 30;
		if (randomColor == 0 || randomColor == 1) {
			platformType.push_back(red);
		}
		else if (randomColor >= 2 && randomColor <= 5) {
			platformType.push_back(yellow);
		}
		else if (randomColor >= 6 && randomColor <= 8) {
			platformType.push_back(orange);
		}
		else if (randomColor >= 9 && randomColor <= 13) {
			platformType.push_back(green);
		}
		else {
			platformType.push_back(blue);
		}
	}
	
}

void Tema2::FrameStart()
{
	glClearColor(0, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glm::mat4 modelMatrix;

	// Consumare combustibil 
	if (speedCounter > 0) {
		speedCounter -= deltaTimeSeconds;
		fuel -= 0.5 * highSpeed * deltaTimeSeconds;
	}
	else {
		fuel -= 0.5 * speed * deltaTimeSeconds;
	}

	fall = true;
	for (int i = 0; i < platforms; i++) {
		// Verificare coliziuni
		//if (sphereX <= platformX[i] + 1 + 0.25 && sphereX >= platformX[i] - 1 - 0.25
		//	&& sphereZ <= (platformZ[i] + platformSize[i] / 2.0f) + 0.25 && sphereZ >= platformZ[i] - platformSize[i] / 2.0f - 0.25
		if( sphereY - 0.5 <= -0.25) {
			speedCounter = 10;
			highSpeed = 0;
		}
		else if (sphereX <= platformX[i] + 1 + 0.25 && sphereX >= platformX[i] - 1 - 0.25
			&& sphereZ <= (platformZ[i] + platformSize[i] / 2.0f) + 0.25 && sphereZ >= platformZ[i] - platformSize[i] / 2.0f - 0.25
			&& sphereY - 0.5 <= platformY + 0.05 && sphereY - 0.5 >= -0.2) {
			if (platformType[i] == red) {
				cout << "-----------GAME OVER-----------\n";
				exit(1);
			}
			if (platformType[i] == orange) {
				speedCounter = 5;
			}
			if (platformType[i] == yellow) {
				fuel -= 30;
			}
			if (platformType[i] == green) {
				if (fuel + 40 >= 200) {
					fuel = 200;
				}
				else {
					fuel += 40;
				}
				deformation = 1;
			}
			platformType[i] = purple;
			fall = false;
		}

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D2::Translate(platformX[i], platformY, -platformZ[i]);
		modelMatrix *= Transform3D2::Scale(2, 0.1, platformSize[i]);
		RenderSimpleMesh(meshes["box"], shaders["ShaderTema2"], modelMatrix, platformType[i], 0);

		if (speedCounter > 0) {
			platformZ[i] -= highSpeed * deltaTimeSeconds;
		}
		else {
			platformZ[i] -= speed * deltaTimeSeconds;
		}

		//Eliminare platforma si creare platforma noua
		if (platformZ[i] <= -15) {
			platformSize.erase(platformSize.begin() + i); //sterge platforma i
			float randomZ = ((float)rand()) / (float)(RAND_MAX / 6) + (platformMax - 6);
			platformSize.push_back(randomZ);

			platformX.push_back(platformX[i]);
			platformX.erase(platformX.begin() + i);

			platformZ.push_back(platformZ[platforms - 3] + platformMax);
			platformZ.erase(platformZ.begin() + i);

			// Creare aleatorie a tipului noii platforme
			platformType.erase(platformType.begin() + i);
			int randomColor = rand() % 30;
			if (randomColor == 0 || randomColor == 1) {
				platformType.push_back(red);
			}
			else if (randomColor >= 2 && randomColor <= 5) {
				platformType.push_back(yellow);
			}
			else if (randomColor >= 6 && randomColor <= 8) {
				platformType.push_back(orange);
			}
			else if (randomColor >= 9 && randomColor <= 13) {
				platformType.push_back(green);
			}
			else {
				platformType.push_back(blue);
			}
		}
	}

	if (jump) {
		counter += deltaTimeSeconds;
		// Sare pt 0.5 secunde
		if (counter <= 0.5) {
			sphereY += 2 * deltaTimeSeconds;
			camera->position += glm::vec3(0, 2 * deltaTimeSeconds, 0);
			fall = false;
		}
		// Dupa care revine pana la inaltimea initiala: fall = true
		// Daca sfera a picat inapoi, se poate sarii iar si se reseteaza counter-ul 
		else if (sphereY <= 0.6) { 
			jump = false;
			counter = 0;
		}
	}
	
	// Daca nu mai exista combustibil se termina jocul
	if (fuel < 2) {
		cout << "-----------OUT OF FUEL-----------\n";
		exit(1);
	}

	modelMatrix = glm::mat4(1);
	if (fall) {
		sphereY -= 2 * deltaTimeSeconds;
		camera->position += glm::vec3(0, -2 * deltaTimeSeconds, 0);
		deformation = 0;
	}
	if (sphereY < -1 && scale >= 0) {
		scale -= 0.3 * deltaTimeSeconds;
	}
	if (sphereY < -3) {
		deformation = 1;
	}
	if (sphereY < -9.5) {
		exit(1);
		cout << "-----------GAME OVER-----------\n";
	}

	modelMatrix *= Transform3D2::Translate(sphereX, sphereY, sphereZ);
	modelMatrix *= Transform3D2::Scale(scale, scale, scale);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.2, 0.8, 0.7), 1);

	//Fuel bar
	glDisable(GL_DEPTH_TEST);
	modelMatrix2 = glm::mat3(1);
	modelMatrix2 *= Transform2D::Translate(sphereX / 50 - 2.8, sphereY / 50 );
	modelMatrix2 *= Transform2D::Scale(fuel / 200, 0.2);
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix2);
	modelMatrix2 *= Transform2D::Scale(200 / fuel, 1);
	RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix2);
	glEnable(GL_DEPTH_TEST);
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3& color, int isSphere)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);
	
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	int def = glGetUniformLocation(shader->program, "deformation");
	glUniform1i(def, deformation);

	int is_sph = glGetUniformLocation(shader->program, "isSphere");
	glUniform1i(is_sph, isSphere); //;;;;;;;;;;;;;;;;;;;

	int time = glGetUniformLocation(shader->program, "Time");
	GLfloat elaspedTime = Engine::GetElapsedTime();
	glUniform1f(time, elaspedTime);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	//glm::mat4 projectionMatrix = projectionMatrix;
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_W)) {
			if (speed < 14)
				speed += 8 * deltaTime;
		}
		if (window->KeyHold(GLFW_KEY_S)) {
			if (speed > 4)
				speed -= 8 * deltaTime;
		}
		if (window->KeyHold(GLFW_KEY_D)) {
			sphereX += (3 + speed/10) * deltaTime;
			camera->position += glm::vec3((3 + speed / 10) * deltaTime, 0, 0);
		}
		if (window->KeyHold(GLFW_KEY_A)) {
			sphereX -= (3 + speed / 10) * deltaTime;
			camera->position += glm::vec3(-(3 + speed / 10) * deltaTime, 0, 0);
		}
	}

}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C)
	{
		if (renderCameraTarget) {
			camera->Set(glm::vec3(sphereX, sphereY + cstY, sphereZ + cameraDistance), glm::vec3(sphereX, 1.6, sphereZ), glm::vec3(0, 1, 0));
			camera->position += glm::vec3(0, -0.9, -3.57);	
		}
		else {
			camera->Set(glm::vec3(sphereX, sphereY + cstY, sphereZ + cameraDistance), glm::vec3(sphereX, 1, sphereZ), glm::vec3(0, 1, 0));
		}
		renderCameraTarget = !renderCameraTarget;	
	}

	if (key == GLFW_KEY_SPACE && !fall)
	{
		if (!jump) {
			jump = true;
			deformation = 0;
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (renderCameraTarget) {
			camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}
		else{
			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}