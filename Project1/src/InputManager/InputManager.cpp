#include "InputManager.h"
#include "../Renderer.h"
InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::AddObserver(iInputObserver* observer)
{
	observersList.push_back(observer);
}

void InputManager::RemoveObserver(iInputObserver* observer)
{
	std::vector<iInputObserver*>::iterator it = std::remove(observersList.begin(), observersList.end(), observer);

	observersList.erase(it,observersList.end());
}

void InputManager::OnKeyPressed(const int& key)
{
	for (iInputObserver* observer :observersList)
	{
		observer->OnKeyPressed(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = true;
	}
	else if(key == GLFW_KEY_S)
	{
		isDownPressed = true;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = true;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = true;
	}
}

void InputManager::OnKeyReleased(const int& key)
{
	for (iInputObserver* observer : observersList)
	{
		observer->OnKeyReleased(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = false;
	}
	else if (key == GLFW_KEY_S)
	{
		isDownPressed = false;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = false;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = false;
	}
}

void InputManager::OnkeyHold(const int& key)
{
	for (iInputObserver* observer : observersList)
	{
		observer->OnKeyHold(key);
	}
}

float InputManager::GetMouseX()
{
	return mouseX;
}

float InputManager::GetMouseY()
{
	return mouseY;
}

float InputManager::GetAxisX()
{
	return axisX;
}

float InputManager::GetAxisY()
{
	return axisY;
}
