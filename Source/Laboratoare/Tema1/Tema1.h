#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <stdlib.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void Hit(float deltaTimeSeconds);
	void OutOfScene(float deltaTimeSeconds);
	void CheckCollision();

protected:
	glm::mat3 modelMatrix;
	int lives, score;
	float angularStep;
	float balloonR1Y, balloonR2Y, balloonR3Y, balloonR1X, balloonR2X, balloonR3X;
	float scaleR1X, scaleR2X, scaleR3X, scaleR1Y, scaleR2Y, scaleR3Y;
	float balloonY1Y, balloonY2Y, balloonY1X, balloonY2X;
	float scaleY1X, scaleY2X, scaleY3X, scaleY1Y, scaleY2Y;
	float shuriken1Y, shuriken2Y, shuriken1X, shuriken2X;
	float scaleS1X, scaleS2X, scaleS1Y, scaleS2Y;
	float bowY, bowX, arrowX, arrowY;
	float mouseX, mouseY, angle, arrowSpeed, arrowAngle, drawSpeed;;
	bool hitR1, hitR2, hitR3, hitY1, hitY2, hitS1, hitS2, bowHitS1, bowHitS2;
	bool destroyedR1, destroyedR2, destroyedR3, destroyedY1, destroyedY2, destroyedS1, destroyedS2;
	bool released;
	
	glm::ivec2 resolution;
};
