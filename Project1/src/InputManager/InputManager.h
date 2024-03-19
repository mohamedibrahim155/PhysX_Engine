#pragma once
#include "iInputOberver.h"
#include <vector>
class InputManager
{
public:

	InputManager();
	~InputManager();

	static InputManager& GetInstance();

	void AddObserver(iInputObserver* observer);
	void RemoveObserver(iInputObserver* observer);

	void OnKeyPressed(const int& key);
	void OnKeyReleased(const int& key);
	void OnkeyHold(const int& key);

	float GetMouseX();
	float GetMouseY();

	float GetAxisX();
	float GetAxisY();


private:
	std::vector<iInputObserver*> observersList;

	float mouseX = 0;
	float mouseY = 0;
	float axisX = 0;
	float axisY = 0;

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;
};

